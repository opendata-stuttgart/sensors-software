require("ggplot2")

## gaussian filter taps for smoothing function
# adapted from Juan Carlos Borrás http://grokbase.com/p/r/r-help/117c96hy0z/r-gaussian-low-pass-filter
gfcoeffs <- function(s, n) {
    t <- seq(-n,n,1) ## assuming 2*n+1 taps
    gfiltc<-exp(-(t^2/(2*s^2)))/sqrt(2*pi*s^2)
    return (gfiltc/sum(gfiltc))
    # sum(gfiltc)=1
}

fpattern<-"sensor[0-9]*.csv"
# get filelist relative to working directory
filelist<- dir(path = ".",pattern = glob2rx(fpattern),recursive=FALSE,full.names=FALSE, ignore.case = TRUE) ## files in current directory

for (csvfilename in filelist){
# get/process the data with scripts from repo feinstaub-monitoring-client-python to sensorXX.csv
# csvfilename<-paste("sensor",sensorid,".csv",sep="")
sensorid<-regmatches(csvfilename, regexpr("[0-9]+", csvfilename))
pdffilename<-paste("plots_sensor",sensorid,".pdf",sep="")
sendat<-read.csv(csvfilename)

# have a proper timestamp
sendat$timestamplt<-strptime(sendat$timestamp,format="%Y-%m-%dT%H:%M:%OSZ")
sendat$timestamp<-NULL

#sendat<-sendat[sendat$timestamplt>strptime("2015-10-24", format="%Y-%m-%d"),]

# select data of latest 2 days measured values
# nval=2*60*24*2
# nval=min(nval,dim(sendat)[1])
# seldat<-sendat[1:nval,]
# 
# filter range 0
# seldat<-seldat[(sendat$P1>0)&(sendat$P1<1000),]
# sendat<-sendat[,]

plotdat<-seldat
pdf(pdffilename)
# plot(plotdat$timestamplt, log(plotdat$P2))

p<-ggplot(plotdat,aes(timestamplt, P2))+geom_point()+geom_smooth()
print(p)
p<-ggplot(plotdat,aes(timestamplt, P2))+geom_point()+scale_y_log10()+geom_smooth()
print(p)
p<-ggplot(plotdat,aes(timestamplt, P1))+geom_point()+geom_smooth()
print(p)
p<-ggplot(plotdat,aes(timestamplt, P1))+geom_point()+scale_y_log10()+geom_smooth()
print(p)

ntaps=10
sigma=4
gfiltc<-gfcoeffs(sigma,ntaps)

plotdat$P1smoothed<-filter(plotdat$P1,filter=gfiltc)
plotdat$P2smoothed<-filter(plotdat$P2,filter=gfiltc)
p<-ggplot(plotdat,aes(timestamplt, P1smoothed))+geom_line()+geom_smooth()
print(p)
p<-ggplot(plotdat,aes(timestamplt, P1smoothed))+geom_line()+scale_y_log10()+geom_smooth()
print(p)
p<-ggplot(plotdat,aes(timestamplt, P2smoothed))+geom_line()+geom_smooth()
print(p)
p<-ggplot(plotdat,aes(timestamplt, P2smoothed))+geom_line()+scale_y_log10()+geom_smooth()
print(p)

dev.off()

}