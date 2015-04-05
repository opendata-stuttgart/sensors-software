# Particulates sensor usage with RaspberryPi


## Usage

Connect sensor with Arduino via usb to RaspberryPi.
The Arduino has the serial software for the sensor installed and prints the sensor results.
A python script is pushing the results to our API endpoint.


## Install dependencies

for raspbian

```
sudo apt-get update
sudo apt-get install -y python-requests python-serial
```


## set SENSOR_UID in push.py !!

## run

```
python push.py
```
