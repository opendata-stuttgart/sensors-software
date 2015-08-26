# increase java Heap size, by using:
options(java.parameters = "-Xmx1000m")
# BEFORE loading the package/java init


require("xlsx")
# read in Stuttgart data (official)
# see http://www.stadtklima-stuttgart.de/index.php?luft_messdaten_station_smz

# get the data, unzip:
# http://www.stadtklima-stuttgart.de/stadtklima_filestorage/download/luft/S-Mitte-SZ-Halbstd-Werte-2015.zip
# wget http://www.stadtklima-stuttgart.de/stadtklima_filestorage/download/luft/S-Mitte-SZ-Halbstd-Werte-2015.zip
# unzip -d data/ S-Mitte-SZ-Halbstd-Werte-2015.zip
# not used: xls2csv -g 6 -q 0 data/Halbstd-Werte-Stuttgart-Mitte-SZ_2015.xls > data/Halbstd-Werte-Stuttgart-Mitte-SZ_2015.csv # crappy, weird xls sheets

# Messstation "Schwabenzentrum" (Amt für Umweltschutz, Abt. Stadtklimatologie)

sdat<-NULL
sdat.xls<-"data/Halbstd-Werte-Stuttgart-Mitte-SZ_2015.xls"
sdat.datafile="readdata_s_mitte.RData"
if (file.exists(sdat.datafile)){
    message(paste("loading from",sdat.datafile))
    load(sdat.datafile)
    }else{
    message(paste("creating",sdat.datafile))
    sdat.colclasses=c("Date",rep("numeric",19))
    sdat.colnames=c(
                "date", #         "Datum",
                "hour", #         "Uhrzeit",
                "t", #         "Temperatur...C.",
                "t.max", #         "Temperatur...C..1",
                "t.min", #         "Temperatur...C..2",
                "relhum", #         "Rel..Feuchte....",
                "windspeed.mean", #         "WG..m.s.",
                "windspeed.max", #         "WG..m.s..1",
                "widdir", #         "WR..Grad.",
                "p", #         "Druck..hPa.",
                "precsum", #         "Niederschlag..l.m..",
                "rad", #         "Globalstr...W.m..",
                "radbalance", #         "Str..Bilanz..W.m..",
                "uva", #         "UVA.Str...W.m..",
                "uvb", #         "UVB.Str...W.m..",
                "no", #         "NO..µg.m..",
                "no2", #         "NO2..µg.m..",
                "o3", #         "O3..µg.m..",
                "pm10", #         "PM10..µg.m..",
                "pm25" #         "PM2.5..µg.m.."
    )
    # read the first sheet, should be Jan.2015
    message(paste("reading",sdat.xls,"sheet",1))
    sdat.description<-read.xlsx(sdat.xls, sheetIndex=1,as.data.frame=TRUE,startRow=6,endRow=7,colIndex=1:20,header=FALSE,colClasses="character")
    sdat.description=as.data.frame(t(sdat.description))
    names(sdat.description)<-c("aggregation","measurement")
    sdat.description=cbind(sdat.description,sdat.colnames)
    sdat.description[] <- lapply(sdat.description, as.character) # change factor to character
    sdat<-read.xlsx(sdat.xls, sheetIndex=1,as.data.frame=TRUE,startRow=7,colIndex=1:20,colClasses=sdat.colclasses)

    for (sheeti in 2:7){ # at time of development only data up to july was present
        message (paste("reading",sdat.xls,"sheet",sheeti))
        sdat.tmp<-read.xlsx(sdat.xls, sheetIndex=sheeti,startRow=7,as.data.frame=TRUE,colIndex=1:20,colClasses=sdat.colclasses)
        if (isTRUE(all.equal(names(sdat.tmp),names(sdat)))){ # check if we have same colnames
            sdat<-rbind(sdat,sdat.tmp)
        }
    }
    names(sdat)<-sdat.colnames
    # convert date and hour to POSIXlt type
    # sdat$datelt<-as.POSIXlt(sdat$date)+sdat$hour*24*60*60
    # timezone might be wrong, so use strptime and explicitly specify
    # dunno about daylight-saving, needs to be looked up deeper in the documentation how this is handled (CEST is Central European Summer Time)
    sdat$datelt<-as.POSIXlt(strptime(sdat$date,format="%Y-%m-%d",tz="Europe/Berlin")+sdat$hour*24*60*60)
    sdat.description<-rbind(sdat.description,c(NA,"Messzeitpunkt","datelt"))
    row.names(sdat.description)<-NULL
    # add as attribute to sdat
    attr(sdat,"ylabel")<-paste(sdat.description$measurement,sdat.description$aggregation)
    print(sdat.description)
    # seems to be off-by one?, wrong TZ? no, weird data: the data sets start at <day> 0:30 and end with <next day> 0:00
    # see table(sdat$date,sdat$datelt$hour)
    #                 0 1 2 3 4 5 6 7 8 9 10 11 12 13 14 15 16 17 18 19 20 21 22 23
    #      2015-01-01 1 2 2 2 2 2 2 2 2 2  2  2  2  2  2  2  2  2  2  2  2  2  2  2 
    #      [...]
    #      2015-08-01 1 0 0 0 0 0 0 0 0 0  0  0  0  0  0  0  0  0  0  0  0  0  0  0
    
    # clean up intermediary vars, keep .datafile .description
    rm(list=ls()[grep(pattern="^sdat.[^d]",ls())])
    save(sdat,file=sdat.datafile)
} # end if (file.exists(sdat.datafile)){


