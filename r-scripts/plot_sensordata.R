require("ggplot2")
require("dplyr")
require("timeSeries")
require("forecast")
# require("tsoutliers")
# require("zoo")

usearchive=TRUE # csv data from archive
sensorid=40
usearchive=FALSE # timestamp needs fixing (in csv and conversion below)
usearchive=TRUE # timestamp needs fixing (in csv and conversion below)
#if(usearchive){require("RCurl");}

#max values for clipping
Pclip<-list(P1=list(min=0,    max=10000),
            P2=list(min=0.62, max=1000))
dateinterval<-list(min=as.POSIXct(strptime("2015-12-30", format="%Y-%m-%d")), 
                   max=as.POSIXct(Sys.Date()))
plotdir="output_plots/"
if(!dir.exists(plotdir)){dir.create(plotdir, showWarnings = TRUE, recursive = TRUE, mode = "0755")}

#' function to clip values above/below thresholds
clipping<-function(x,min=NULL,max=NULL){
  if(is.null(min)){
    min=min(na.omit(x))
  }
  if(is.null(max)){
    max=max(na.omit(x))
  }
  if(is.na(max)||is.na(min)){
    warn("NA for min/max while clipping, no clipping done")
    return(x)
  }
  x[x>max]<-max
  x[x<min]<-min
  return(x)
}


## gaussian filter taps for smoothing function
# adapted from Juan Carlos Borrás http://grokbase.com/p/r/r-help/117c96hy0z/r-gaussian-low-pass-filter
gfcoeffs <- function(s, n) {
    t <- seq(-n,n,1) ## assuming 2*n+1 taps
    gfiltc<-exp(-(t^2/(2*s^2)))/sqrt(2*pi*s^2)
    return (gfiltc/sum(gfiltc))
    # sum(gfiltc)=1
}

csvsep=","
if(usearchive){
    arcdat_filename<-"arcdat.RData"
    if (file.exists(arcdat_filename)){
        load(arcdat_filename)
        arcdat_filename_mtime<-file.mtime(arcdat_filename)
    }else{
        arcdat<-NULL
        arcdat_filename_mtime<-as.POSIXct(as.Date("2000-01-01"))
    }
    fpattern<-"*.csv"
    # get filelist relative to working directory, pattern = glob2rx(fpattern)
    filelist<- dir(path = "archive.luftdaten.info",pattern=glob2rx(fpattern),recursive=TRUE,full.names=TRUE, ignore.case = TRUE) ## files in current directory
    # only read files newer than arcdat_filename
    for (csvfilename in filelist[file.mtime(filelist)>arcdat_filename_mtime]){
            print(paste("reading ", csvfilename))
            rdat<-read.csv(csvfilename, sep=";", dec=".", header=TRUE)
            arcdat<-dplyr::bind_rows(arcdat,rdat)
    }
    # Detectable range of concentration 0~28,000 pcs/liter (0~8,000pcs/0.01 CF=283ml)
    
    arcdat$timestampct<-as.POSIXct(strptime(arcdat$timestamp,format="%Y-%m-%dT%H:%M:%OS"))
    arctbl<-table(arcdat$sensor_id,as.Date(arcdat$timestamp))#$yday+1000*(as.POSIXlt(arcdat$timestamp)$year+1990))
    save(arcdat, arctbl ,file=arcdat_filename)
    pdf(file.path(plotdir,"plots_sensordata_overview.pdf"),width=15,height=9)
    arctbl.df<-as.data.frame(arctbl)
    arctbl.df$Var2<-as.Date(arctbl.df$Var2)
    p<-ggplot(arctbl.df, aes(Var2,Var1,size=Freq, color=as.factor(as.POSIXlt(arctbl.df$Var2)$mon+1))) + geom_point()+
        labs(x="Date", y="sensor id")+
        theme(axis.text.x  = element_text(angle=90, vjust=0.5, size=6))+
        scale_x_date(date_labels = "%b %d %Y", date_minor_breaks = "1 day", date_breaks = "1 week")+
        scale_colour_hue(name="Month")
#         scale_colour_brewer(name = "Month")
#         theme(legend.title=element_blank())+ 
    # months(arctbl.df$Var2)
    print(p)
    dev.off()
    
    # Detectable range of concentration 0~28,000 pcs/liter (0~8,000pcs/0.01 CF=283ml)
    
# iterate sensors
    for (sid in unique(arcdat$sensor_id)){
        print(sid)
        sdat<-as.data.frame(dplyr::filter(arcdat, sensor_id==sid)) # result type is tbl_df, convert to df
        sdat<-sdat[order(sdat$timestampct),] # sort by timestampct
        sdat$P2diff1=sdat$P2-sdat$P1
        sdat$durP2diff1=sdat$durP2-sdat$durP1
        
        print(dim(sdat))
        # stats::filter the data                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                          
        # create a gaussian smoothing
        sigma=5
        ntaps=10
        gc<-gfcoeffs(sigma,ntaps)
        
        
        pdffilename=file.path(plotdir,paste("plots_sensor_",sid,".pdf",sep=""))
        print (pdffilename)
#         set width according to timediff
        timespan<-as.double(max(sdat$timestampct)-min(sdat$timestampct))
        print(paste("plotwidth", min(timespan/2,10)))
        pdf(pdffilename, width=max(timespan/2,10), height=10)
        measvalnames=c("P1", "durP1", "ratioP1", "P2", "durP2", "ratioP2", "P2diff1", "durP2diff1")
        # have a timeSeries object and plot it
        print(paste("tsdat plot"))
        tsdat<-timeSeries(sdat[,measvalnames], sdat$timestampct)
        plot(tsdat)
        tdn<-as.numeric(sdat$timestampct[2:length(sdat$timestampct)]-sdat$timestampct[1:(length(sdat$timestampct)-1)])
        tdn.c<-tdn[tdn<320]
        
        # plot histogram of timediffs
        hist(tdn.c,n=100, main = paste("Histogram of timediffs"))
        
        # aggregate by year, day, hour
        tstamplt<-as.POSIXlt(sdat$timestampct)# [,c("year","yday")]
        sdat.agg<-aggregate(sdat, by=list(year=tstamplt$year+1900,yday=tstamplt$yday,hour=tstamplt$hour),FUN=mean)
        # order by ymd
        sdat.agg<-sdat.agg[order(sdat.agg$year,sdat.agg$yday,sdat.agg$hour),]  

        sdat.dagg<-aggregate(sdat, by=list(year=tstamplt$year+1900,yday=tstamplt$yday),FUN=mean)
        sdat.dagg<-sdat.dagg[order(sdat.dagg$year,sdat.dagg$yday),]        
#         ggplot(sdat.dagg,aes_string("timestampct",coln))
        for (coln in measvalnames){
            print (coln)
            if(length(sdat[,coln])>ntaps){
                # TODO: identify/handle outliers
                # look at forecast::tsoutliers tsoutliers::tso                
                # outlier filter first forecast::tsclean
                sdat$plotdat<-forecast::tsclean(sdat[,coln]) 
                sdat$plotdat<-as.vector(stats::filter(sdat$plotdat, gfcoeffs(sigma,ntaps)))
                p<-ggplot(sdat.agg,aes_string("timestampct",coln))+geom_bar(stat = "identity")+labs(main="Hourly means")
                print(p)
                p<-ggplot(sdat.dagg,aes_string("timestampct",coln))+ geom_bar(stat = "identity")+labs(main="Daily means")
                print(p)
                
                print(paste(coln,"ggplot"))
                p<-ggplot(sdat, aes(timestampct,plotdat))+geom_line()+geom_smooth(span=0.2)+ labs(x="Time",y=coln)
                print(p)
                # TODO: gleitende 24-Stunden-Mittelwerte (24h means filtering)
                # maybe possible via zoo forecast::ma its fts tseries timeSeries
                # fts:moving.mean only Date as time?
                # look for functions with timestamp based intervals (24h)
                #     z=zoo(sdat,order.by=sdat$timestampct)
                #     sdat.fts=as.fts(sdat[,c("timestampct","P1")])
                #     idat=irts(sdat$timestampct, sdat$P1)
                #     plot(idat)
                #     measurement Dates
                #     mdts<-as.timeSeries(unique(as.Date(sdat$timestampct)))
                #    fts wants chr dates (timestamps possible?) in row names?
                #    rownames(sdat)<-as.character(sdat$timestampct)
            }
        }
        dev.off()
    }# sensor_id
    print(paste("total size of data:", dim(arcdat) ,collapse = " "))
}# usearchive

## calibration function
ppdcalib<-function(x){1.1*x^3 - 3.8*x^2 + 520*x + 0.62} # calibration function: ratioPx [%] / Concentration [pcs/283ml] = [pcs/0.01cf]
cf3tom3=0.02831685 # cubic foot to cubic meter ft³=0.02831685m³, m³=ft³/35.315
# to pcs/m3:  /100 /cf3tom3
# to µg*m^-3
# https://github.com/intel-iot-devkit/upm/pull/409/files
#  +    // All particles are spherical, with a density of 1.65E12 µg/m3
#  +    double density = 1.65 * pow (10, 12);
#  +    // The radius of a particle in the PM2.5 channel is .44 µm
# I doubt it, should be 2.5/2 µm
#  +    double r25 = 0.44 * pow (10, -6);
#  +    double vol25 = (4/3) * pi * pow (r25, 3);
#  +    double mass25 = density * vol25; // ug
#  +    double K = 3531.5; // per m^3
# interesting, since with weather correction:
# http://www.cleanair.org/sites/default/files/Drexel%20Air%20Monitoring_-_Final_Report_-_Team_19_0.pdf


pdffilename=file.path(plotdir,paste("ppd_calib.pdf",sep=""))
pdf(pdffilename)
p<- ggplot(sdat,aes(ratioP1,P1))+geom_point()+
    stat_function(fun=ppdcalib)+
    labs(title="PPD calibration function")+
    coord_flip()
    #coord_flip to have the same orientation as in the spec sheet curve
print(p)
p<- ggplot(sdat[sdat$ratioP1<5,],aes(ratioP1,P1))+geom_point()+
    stat_function(fun=ppdcalib)+
    labs(title="PPD calibration function < 5")
print(p)

p<- ggplot(arcdat,aes(P2, ..count..))+
    geom_density()+xlim(0.621,3000)+
    facet_wrap(~sensor_id,scales='free_y')
print(p)
dev.off()

stop("manual break: archive plots done")
## the following is legacy code

    #     dates=seq.Date(from=as.Date(dateinterval$min),to=as.Date(dateinterval$max),by=1)
    #         u<-paste('http://archive.madflex.de/',
    #                    dates,
    #                    '/',
    #                    dates,'_ppd42ns_sensor_',
    #                    sensorid,
    #                    '.csv')
    #     require("RCurl")
    #     filelist=urllist
    #     csvsep=";"


fpattern<-"sensor[0-9]+.csv"
# get filelist relative to working directory, pattern = glob2rx(fpattern)
filelist<- dir(path = ".",pattern=fpattern,recursive=FALSE,full.names=FALSE, ignore.case = TRUE) ## files in current directory

for (csvfilename in filelist){
    # get/process the data with scripts from repo feinstaub-monitoring-client-python to sensorXX.csv
    # csvfilename<-paste("sensor",sensorid,".csv",sep="")
    sensorid<-regmatches(csvfilename, regexpr("[0-9]+", csvfilename))
    pdffilename<-paste("plots_sensor",sensorid,".pdf",sep="")
    sendat<-read.csv(csvfilename,sep=csvsep)

    # have a proper timestamp POSIXct (never use POSIXlt)
    sendat$timestampct<-as.POSIXct(strptime(sendat$timestamp,format="%Y-%m-%dT%H:%M:%OSZ"))
    sendat$timestamp<-NULL

    #sendat<-sendat[sendat$timestampct>strptime("2015-10-24", format="%Y-%m-%d"),]

    # select data of latest 2 days measured values
    # nval=2*60*24*2
    # nval=min(nval,dim(sendat)[1])
    # seldat<-sendat[1:nval,]

    # filter date interval
    seldat<-sendat[sendat$timestampct>dateinterval$min&
                sendat$timestampct<dateinterval$max,]
    #     seldat<-sendat
    
    # seldat$td<-as.POSIXlt(seldat$timestampct)$doy

    pdf(pdffilename)

    if ("P1" %in% names(sendat)){
        
        # filter range 0
        seldat$P1<-clipping(seldat$P1,Pclip$P1$min,Pclip$P1$max)
        seldat$P2<-clipping(seldat$P2,Pclip$P2$min,Pclip$P2$max)
        seldat$P1[seldat$P1<=Pclip$P1$min]<-NA
        seldat$P2[seldat$P2<=Pclip$P2$min]<-NA
        

        # sendat<-sendat[,]

        plotdat<-seldat
        # plot(plotdat$timestampct, log(plotdat$P2))

        p<-ggplot(plotdat,aes(timestampct, P2))+geom_point()+geom_smooth()
        print(p)
        p<-ggplot(plotdat,aes(timestampct, P2))+geom_point()+scale_y_log10()+geom_smooth()
        print(p)
        p<-ggplot(plotdat,aes(timestampct, P1))+geom_point()+geom_smooth()
        print(p)
        p<-ggplot(plotdat,aes(timestampct, P1))+geom_point()+scale_y_log10()+geom_smooth()
        print(p)

        ntaps=10
        sigma=4
        gfiltc<-gfcoeffs(sigma,ntaps)

        plotdat$P1smoothed<-filter(plotdat$P1,filter=gfiltc)
        plotdat$P2smoothed<-filter(plotdat$P2,filter=gfiltc)
        p<-ggplot(plotdat,aes(timestampct, P1smoothed))+geom_line()+geom_smooth()
        print(p)
        p<-ggplot(plotdat,aes(timestampct, P1smoothed))+geom_line()+scale_y_log10()+geom_smooth()
        print(p)
        p<-ggplot(plotdat,aes(timestampct, P2smoothed))+geom_line()+geom_smooth()
        print(p)
        p<-ggplot(plotdat,aes(timestampct, P2smoothed))+geom_line()+scale_y_log10()+geom_smooth()
        print(p)

    }


    if ("temperature" %in% names(sendat)){
            seldat<-seldat[!is.na(seldat$temperature),]
            if ("humidity" %in% names(sendat)){
                seldat<-seldat[!is.na(seldat$humidity),]
            }
            p<-ggplot(seldat, aes(timestampct, temperature))+geom_line()
            print(p)
            if ("humidity" %in% names(seldat)){
                p<-ggplot(seldat, aes(timestampct, temperature))+geom_line(aes(timestampct, humidity),col=4)
            }
            print(p)
    }
    dev.off()
}
