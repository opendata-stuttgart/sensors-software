require("ggplot2")

## gaussian filter taps for smoothing function
# adapted from Juan Carlos Borrás http://grokbase.com/p/r/r-help/117c96hy0z/r-gaussian-low-pass-filter
gfcoeffs <- function(s, n) {
    t <- seq(-n,n,1) ## assuming 2*n+1 taps
    gfiltc<-exp(-(t^2/(2*s^2)))/sqrt(2*pi*s^2)
    return (gfiltc/sum(gfiltc))
    # sum(gfiltc)=1
}
 
for (sensorid in c(39,40)){
# get/process the data with scripts from repo feinstaub-monitoring-client-python to sensorXX.csv
csvfilename<-paste("sensor",sensorid,".csv",sep="")
pdffilename<-paste("plots_sensor",sensorid,".pdf",sep="")
sendat<-read.csv(csvfilename)

# have a proper timestamp
sendat$timestamplt<-strptime(sendat$timestamp,format="%Y-%m-%dT%H:%M:%OSZ")
sendat$timestamp<-NULL

pdf(pdffilename)
# plot(sendat$timestamplt, log(sendat$P2))

p<-ggplot(sendat,aes(timestamplt, P2))+geom_point()+geom_smooth()
print(p)
p<-ggplot(sendat,aes(timestamplt, P2))+geom_point()+scale_y_log10()+geom_smooth()
print(p)
p<-ggplot(sendat,aes(timestamplt, P1))+geom_point()+geom_smooth()
print(p)
p<-ggplot(sendat,aes(timestamplt, P1))+geom_point()+scale_y_log10()+geom_smooth()
print(p)

ntaps=10
sigma=4
gfiltc<-gfcoeffs(sigma,ntaps)

sendat$P1smoothed<-filter(sendat$P1,filter=gfiltc)
sendat$P2smoothed<-filter(sendat$P2,filter=gfiltc)
p<-ggplot(sendat,aes(timestamplt, P1smoothed))+geom_line()+geom_smooth()
print(p)
p<-ggplot(sendat,aes(timestamplt, P1smoothed))+geom_line()+scale_y_log10()+geom_smooth()
print(p)
p<-ggplot(sendat,aes(timestamplt, P2smoothed))+geom_line()+geom_smooth()
print(p)
p<-ggplot(sendat,aes(timestamplt, P2smoothed))+geom_line()+scale_y_log10()+geom_smooth()
print(p)

dev.off()

}