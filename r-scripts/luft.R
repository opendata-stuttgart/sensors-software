source("installrequire.R")
installrequire(c("xlsx","lubridate","dplyr","ggplot2"))
# library(xlsx)
# library(lubridate)
# library(dplyr)
# library(ggplot2)


###########################################################################
#####Preparation(only once)################################################
###########################################################################
#roh <- read.xlsx(file="table23032015135021029.xlsx", sheetIndex=1)
#names(roh) <- c("Messstelle", "Datetime", "Agg_Zeitraum", "Agg_Art", "NO2")
#roh$NO2 <- as.numeric(as.character(roh$NO2))
#roh$Datetime <- ymd_hm(roh$Datetime)
#roh <- roh %>% mutate(Woche=week(Datetime)) %>% mutate(Monat=month(Datetime)) %>% mutate(Date=as.Date(Datetime))

#load(".RData")

#Daten von Andreas laden
# get data from
# https://paste.madflex.de/d9rcQxUT#particlesdata.csv
# and clean errors:
# sed -i -e '/\r.\+/d;/ovf/d;' particlesdata.csv
#
rdata.filename<-"dat.RData"
if(file.exists(rdata.filename)){
    load(rdata.filename)
}else{ ## read it from source
    # try particlesdata, then sampledata
    data.csv.filename="data/particlesdata.csv"
    if (file.exists(data.csv.filename)){
        dat <- read.csv(data.csv.filename,dec=".", sep=",", na.strings=c("","NA"))
    }else{
        warning(paste("datafile ",data.csv.filename," not found, using sampledata"))
        data.csv.filename="data/sampledata.csv"
        dat <- read.csv(data.csv.filename,dec=".", sep=",", na.strings=c("","NA"))
    }

    #ppd <- filter(dat, type=="PPD42NS")
    #
    ## Timestamps formatieren
    # pattern <- "[0-9]+-[0-9]+-[0-9]+ [0-9][0-9]:[0-9][0-9]:[0-9][0-9]"
    # dat <- dat %>%
    #     mutate(timestamp2 = regexpr(pattern, timestamp)) %>%
    #     mutate(timestamp2 = regmatches(timestamp, timestamp2)) %>%
    #     mutate(timestamp2=ymd_hms(timestamp2))
    dat$timestamp2<-as.POSIXct(strptime(dat$timestamp,format="%Y-%m-%d %H:%M:%S"))
    # dat$timestamp2<-strptime(dat$timestamp,format="%d.%m.%y %H:%M:%S+%Z")

    # str(dat)
    # 'data.frame':   319836 obs. of  27 variables:
    #  $ timestamp        : Factor w/ 319831 levels "2015-04-05 23:13:10.759068+00:00",..: 319822 319805 319788 319771 319754 319737 319720 319703 319686 319669 ...
    # sensor type
    #  $ type             : Factor w/ 3 levels "dsm501a","GP2Y1010AU0F",..: 1 1 1 1 1 1 1 1 1 1 ...
    #  $ indoor           : Factor w/ 2 levels "False","True": 2 2 2 2 2 2 2 2 2 2 ...
    #  $ location_id      : int  4 4 4 4 4 4 4 4 4 4 ...
    #  $ sampling_rate    : int  15000 15000 15000 15000 15000 15000 15000 15000 15000 15000 ...
    #
    #  $ P1               : Factor w/ 61894 levels "","017.95","05.06",..: 1 1 1 1 1 1 1 1 1 1 ...
    #  $ P2               : num  NA NA NA NA NA NA NA NA NA NA ...
    #  $ durP1            : num  NA NA NA NA NA NA NA NA NA NA ...
    #  $ durP2            : int  NA NA NA NA NA NA NA NA NA NA ...
    #  $ ratioP1          : num  NA NA NA NA NA NA NA NA NA NA ...
    #  $ ratioP2          : num  NA NA NA NA NA NA NA NA NA NA ...
    #  $ temperature      : logi  NA NA NA NA NA NA ...
    #  $ humidity         : logi  NA NA NA NA NA NA ...
    #  $ pressure         : logi  NA NA NA NA NA NA ...
    #  $ altitude         : logi  NA NA NA NA NA NA ...
    #  $ pressure_sealevel: logi  NA NA NA NA NA NA ...
    #  $ brightness       : logi  NA NA NA NA NA NA ...
    #  $ dust_density     : Factor w/ 77 levels "","-.00",".00",..: 1 1 1 1 1 1 1 1 1 1 ...
    #  $ vo_raw           : num  NA NA NA NA NA NA NA NA NA NA ...
    #  $ voltage          : num  NA NA NA NA NA NA NA NA NA NA ...
    #  $ P10              : num  16656 28523 15669 12731 14018 ...
    #  $ P25              : num  3514 4474 3570 3104 3552 ...
    #  $ durP10           : int  2906824 3794072 2812860 2503032 2644788 2711264 2342328 2416972 2560024 2548652 ...
    #  $ durP25           : int  972924 1198488 986724 870160 982288 969476 902680 850496 924380 968796 ...
    #  $ ratioP10         : num  19.4 25.3 18.8 16.7 17.6 ...
    #  $ ratioP25         : num  6.49 7.99 6.58 5.8 6.55 6.46 6.02 5.67 6.16 6.46 ...
    #  $ timestamp2       : POSIXct, format: "2015-05-05 08:15:59" "2015-05-05 08:15:44" ...

    # P1 should be numeric
    # TODO: identify problematic entries
    # DONE with preprocessing (sed)
#     dat$P1num<-as.numeric(as.character(dat$P1))
#     ## dust_density should be numeric
#     dat$dust_density_num=as.numeric(as.character(dat$dust_density))
    save(dat,file=rdata.filename)
} #end if else read data

## Plots, to pdf
# pdf("plots.pdf")
png(width=1200,height=1000)

#Werte fuer PM2.5 im Zeitverlauf
p1 <- ggplot(filter(dat, type=="PPD42NS"), aes(timestamp2, P2, color=type)) + geom_point() + theme(axis.text.x = element_text(angle=90)) + geom_point(data=filter(dat, type == "GP2Y1010AU0F"), aes(timestamp2, P25, color=type)) + scale_y_log10()
#+ geom_point(data=filter(dat, type=="GP2Y1010AU0F"), aes(timestamp2, vo_raw, color=type))
print(p1)

# density plots
p1<-ggplot(dat, aes(x = P2)) + stat_density() + scale_x_log10()+ labs(title="P2 density (log scaled)")
print(p1)

p1<-ggplot(dat, aes(x = P1)) + stat_density() + scale_x_log10() + labs(title="P1 density (log scaled)")
print(p1)

p1<-ggplot(dat, aes(x = P1)) + stat_density() + scale_x_log10() + labs(title="P1 density (log scaled) by location_id")+ facet_wrap(~location_id); print(p1)

p1<-ggplot(dat, aes(x = P1)) + stat_density() + xlim(c(-1000,15645))+ labs(title="P1 density")
print(p1)

p1<-ggplot(dat, aes(x = P1)) + stat_density() + xlim(c(-1000,15645))+ labs(title="P1 density per location_id")+ facet_wrap(~location_id); print(p1)

p1<-ggplot(dat, aes(x = ratioP1)) + stat_density() + labs(title="ratioP1 density") + xlim(c(0,15))
print(p1)
p1<-ggplot(dat, aes(x = ratioP1)) + stat_density() + labs(title="ratioP1 density by location_id") + xlim(c(0,15)) + facet_wrap(~location_id)
print(p1)

p1<-ggplot(dat, aes(x = ratioP2)) + stat_density() + labs(title="ratioP2 density") + xlim(c(0,2))
print(p1)
p1<-ggplot(dat, aes(x = ratioP2)) + stat_density() + labs(title="ratioP2 density by location_id") + xlim(c(0,2)) + facet_wrap(~location_id)
print(p1)

p1<-ggplot(dat, aes(x = ratioP2)) + stat_density() + labs(title="ratioP2 density") + xlim(c(0,15))
#+ scale_x_log10()
print(p1)

p1<-ggplot(dat, aes(x = durP1)) + geom_density(color="red",trim=TRUE) +xlim(c(0,3446407))+ labs(title="durP1/durP2 densities (red/blue)") + geom_density(aes(x = durP2),color="blue",trim=TRUE)
print(p1)

p1<-ggplot(dat, aes(x = durP1)) + stat_density() +xlim(c(0,3446407))+ labs(title="durP2 density")
print(p1)

p1<-ggplot(dat, aes(x = P25)) + stat_density() + labs(title="P25 density (log scaled)") + scale_x_log10()
print(p1)

p1<-ggplot(dat, aes(x = P25)) + stat_density() + labs(title="P25 density") + xlim(c(2000,8000))
print(p1)

p1<-ggplot(dat, aes(x = P10)) + stat_density() + labs(title="P10 density") + xlim(c(8000,30000))
print(p1)

p1<-ggplot(dat, aes(x = P25)) + stat_density() + labs(title="P25 density/location_id") + xlim(c(2000,8000))+ facet_wrap(~location_id)
print(p1)

p1<-ggplot(dat, aes(x = P10)) + stat_density() + labs(title="P10 density/location_id") + xlim(c(8000,30000))+ facet_wrap(~location_id)
print(p1)

p1<-ggplot(dat, aes(x = P25)) + geom_density(aes(x = durP2),color="black",trim=TRUE) + labs(title="P25 (black), P10 (blue) densities") + xlim(c(0,50000))+ geom_density(aes(x = P10),color="blue",trim=TRUE)
print(p1)


p1<-ggplot(dat, aes(x = dust_density)) + geom_bar()+ labs(title="dust_density histogram") + xlim(c(-0.01,0.08)); print(p1)

p1<-ggplot(dat, aes(x = P10)) + stat_density() + labs(title="P10 density/sensor type") + xlim(c(8000,30000))+ facet_wrap(~type)
print(p1)


p1 <- ggplot(filter(dat, type=="PPD42NS"), aes(P1, P2)) + geom_point() +scale_x_log10() + scale_y_log10() + facet_wrap(~location_id)
print(p1)

p1 <- ggplot(filter(dat, type=="PPD42NS"), aes(P1, P2,color=as.double(timestamp2))) + scale_colour_continuous() + geom_point() +scale_x_log10() + scale_y_log10() + facet_wrap(~location_id)
print(p1)

p1 <- ggplot(dat, aes(P25, P10)) + geom_point() +scale_x_log10() + scale_y_log10() + facet_wrap(type~location_id, drop=TRUE,shrink=TRUE)
print(p1)

p1 <- ggplot(dat, aes(P1, P2)) + geom_point() +scale_x_log10() + scale_y_log10() + facet_wrap(type~location_id, drop=TRUE,shrink=TRUE)
print(p1)

p1 <- ggplot(dat, aes(ratioP1, ratioP2)) + geom_point() + facet_wrap(type~location_id, drop=TRUE,shrink=TRUE)  +scale_x_log10() + scale_y_log10()
print(p1)

p1 <- ggplot(dat, aes(durP1, durP2)) + geom_point() + facet_wrap(type~location_id, drop=TRUE,shrink=TRUE) #+scale_x_log10() + scale_y_log10()
print(p1)

p1 <- ggplot(dat, aes(vo_raw, voltage)) + geom_point() + facet_wrap(type~location_id, drop=TRUE,shrink=TRUE)  #+scale_x_log10() + scale_y_log10()
print(p1)

p1 <- ggplot(dat, aes(timestamp2, P1)) + geom_point() + facet_wrap(type~location_id, drop=TRUE,shrink=TRUE)  + scale_y_log10()
print(p1)

p1 <- ggplot(dat) + geom_line(aes(timestamp2, P1)) + geom_line(aes(timestamp2, P2, color="red")) + facet_wrap(type~location_id,ncol=1, drop=TRUE,shrink=TRUE)  + scale_y_log10()
print(p1)

# measurement times
p1 <- ggplot(dat) + geom_density(aes(x = timestamp2),color="blue",trim=TRUE,kernel="rectangular",width=0.1) + labs(title="Measurement density")
print(p1)

p1<- ggplot(dat) + geom_point(aes(timestamp2,P2,order = sample(seq_along(timestamp2))))
print(p1)

dev.off() # end plot to pdf

##random sample for histogram
#rand.ppd <- sample_n(ppd, 1000)
#p2 <- ggplot(data=filter(dat, type=="PPD42NS"), aes(P2)) + geom_histogram(binwidth=1/10)

##Daten fuer Sensoren anschauen
#head(dat)
#sample_n(filter(dat, type=="PPD42NS"), 10)
#sample_n(filter(dat, type=="GP2Y1010AU0F"), 10)

## some statistics about measurements
# look with table
# yday = day of year
table(dat$type,as.POSIXlt(dat$timestamp2)$yday,useNA = "ifany")

# how many NA's in P2?
table(dat$type,as.POSIXlt(dat$timestamp2)$yday,sapply(dat$P2,is.na),useNA = "no")
# how many NA's in P1?
table(dat$type,as.POSIXlt(dat$timestamp2)$yday,sapply(dat$P1,is.na),useNA = "no")
