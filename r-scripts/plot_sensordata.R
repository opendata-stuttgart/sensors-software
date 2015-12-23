require("ggplot2")
usearchive=TRUE # csv data from archive
sensorid=40
usearchive=FALSE # timestamp needs fixing (in csv and conversion below)
if(usearchive){require("RCurl");}


#max values for clipping
Pclip<-list(P1=list(min=0,    max=10000),
            P2=list(min=0.62, max=1000))
dateinterval<-list(min=as.POSIXct(strptime("2015-11-24", format="%Y-%m-%d")), 
                   max=as.POSIXct(Sys.Date()))

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

fpattern<-"sensor[0-9]+.csv"
# get filelist relative to working directory, pattern = glob2rx(fpattern)
filelist<- dir(path = ".",pattern=fpattern,recursive=FALSE,full.names=FALSE, ignore.case = TRUE) ## files in current directory


csvsep=","
if(usearchive){
    dates=seq.Date(from=as.Date(dateinterval$min),to=as.Date(dateinterval$max),by=1)
        u<-paste('http://archive.madflex.de/',
                   dates,
                   '/',
                   dates,'_ppd42ns_sensor_',
                   sensorid,
                   '.csv')
    require("RCurl")
    filelist=urllist
    csvsep=";"
}

for (csvfilename in filelist){
    # get/process the data with scripts from repo feinstaub-monitoring-client-python to sensorXX.csv
    # csvfilename<-paste("sensor",sensorid,".csv",sep="")
    sensorid<-regmatches(csvfilename, regexpr("[0-9]+", csvfilename))
    pdffilename<-paste("plots_sensor",sensorid,".pdf",sep="")
    sendat<-read.csv(csvfilename,sep=csvsep)

    # have a proper timestamp POSIXct (never use POSIXlt)
    sendat$timestampct<-as.POSIXct(strptime(sendat$timestamp,format="%Y-%m-%dT%H:%M:%OSZ"))
    sendat$timestamp<-NULL
    if(usearchive)

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
