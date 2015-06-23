# function to require packages. Installs them, if necessary
# @parameter packagelist a vector of character strings with the package names
installrequire<-function(packagelist=c(),...){
  for (packagename in packagelist){
    if(! packagename %in% installed.packages()[,1]){
      install.packages(packagename,...)
    }
    require(packagename, character.only=TRUE)
  }
}
