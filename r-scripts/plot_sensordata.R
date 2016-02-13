require("ggplot2")
require("dplyr")
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
plotdir="plots/"
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
    arcdat$timestampct<-as.POSIXct(strptime(arcdat$timestamp,format="%Y-%m-%dT%H:%M:%OS"))
    arctbl<-table(arcdat$sensor_id,as.Date(arcdat$timestamp))#$yday+1000*(as.POSIXlt(arcdat$timestamp)$year+1990))
    save(arcdat, arctbl ,file=arcdat_filename)
    pdf(file.path(plotdir,"plots_sensordata_overview.pdf"),width=12,height=9)
    ggplot(as.data.frame(arctbl), aes(Var2,Var1,size=Freq)) + geom_point()+
        labs(x="year, doy", y="sensor id")+
        theme(axis.text.x  = element_text(angle=90, vjust=0.5, size=6))
    dev.off()
    for (sid in unique(arcdat$sensor_id)){
        print(sid)
        sdat<-dplyr::filter(arcdat, sensor_id==sid)
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
        pdf(pdffilename, width=25, height=10)
        for (coln in c("P1", "durP1", "ratioP1", "P2", "durP2", "ratioP2", "P2diff1", "durP2diff1")){        
            sdat$plotdat<-stats::filter(sdat[,coln],gfcoeffs(sigma,ntaps))
            ggplot(sdat, aes(timestampct,plotdat))+geom_line()+
            geom_smooth()+ labs(x="Time",y=coln)
        }
        dev.off()
    }# sensor_id
}# usearchive


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

if(usearchive){
    stop("manual break for archive plots")
}

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
