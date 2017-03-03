# plot the files created via subsample.py
require(ggplot2)
require(reshape2)

ymax=200

if (!"datadir"%in%ls()){datadir=""}
if (!dir.exists(datadir)){
    print ("set datadir to valid dir, using .")
    datadir="."
}

measnames=c("P1","P2","temperature","humidity")

for (meas in measnames){
  for (dh in c("daily","hourly")){
    
    infilename<-file.path(datadir, paste("all_",dh,"_",meas,".csv", sep=""))
    dat<-read.csv(infilename)

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
    mx<-max(m[,"value"])
    if (mx>ymax){
        plotmax=ymax
    }else{
        plotmax=mx
    }
    pdffilen=paste(infilename,".pdf",sep="")
    pdf(pdffilen)
    p<-ggplot(m,aes(ts,value,color=variable))+geom_line()+ylim(0,200)+ theme(legend.position="none")
    print(p)
    dev.off()
 }
}