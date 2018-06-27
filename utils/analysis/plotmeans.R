# plot the meansfiles created via subsample.py
require(ggplot2)
require(reshape2)
require(plotly)
source("read_sampled.R")

ymax=200

if (!"datadir"%in%ls()){datadir=""}
if (!dir.exists(datadir)){
    print ("set datadir to valid dir, using .")
    datadir="."
}

measnames=c("P1","P2","temperature","humidity","numobs")
legdata=data.frame("P1"=c("PM 10","[µm/m³]"),"P2"=c("PM 2.5","[µm/m³]"),"temperature"=c("Temperatur","[°C]"),"humidity"=c("Luftfeuchtigkeit","[%]"))

for (meas in measnames){
  for (dh in c("daily","hourly")){
    
#     csvfn<-paste("all_",dh,"_",meas,".csv", sep="")
#     infilename<-file.path(datadir, csvfn)
#     if (!file.exists(infilename)){next;}
#     dat<-read.csv(infilename)
    dat<-read_sampled(meas,dh,datadir)

    # have the time parsed 
    if (dh=="hourly"){
        # and add 30 minutes
        dat$ts<-as.POSIXct(strptime(as.character(dat$timestamp),"%Y-%m-%d %H:%M:%S")+30*60) # 2017-02-28 00:00:00
    }else{
        dat$ts<-as.POSIXct(strptime(as.character(dat$timestamp),"%Y-%m-%d")) # 2017-02-28
    }
    # deslect timestamp and
    d<-subset(dat, select=-timestamp)
    # melt data into long form
    m<-melt(d, id.vars="ts")
    # plot max value
    mx<-max(m[,"value"], na.rm=TRUE)
    if (mx>ymax){
        plotmax=ymax
    }else{
        plotmax=mx
    }
    pdffilen=paste(infilename,".pdf",sep="")
    pdf(pdffilen, width=40, height=10)
        p<-ggplot(m,aes(ts,value,color=variable))+geom_line()+ylim(0,plotmax)+ theme(legend.position="none")+labs(title=paste("Alle Sensoren:",legdata[1,meas]),x="Zeit",y=paste(legdata[1,meas],legdata[2,meas]))
        print(p)
    dev.off()
    
    htmlfilen=paste(csvfn,".html",sep="")
    oldwd=getwd()
    setwd(datadir)
    try(htmlwidgets::saveWidget(widget=ggplotly(p),file=htmlfilen, selfcontained = FALSE, libdir="html_libs"))
    setwd(oldwd)
 }
}