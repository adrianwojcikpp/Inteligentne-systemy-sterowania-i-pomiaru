#!/bin/bash
# temperature in degrees Celsius
tempC="20.5" 
# temperature in degrees Fahrenheit
tempF=$(echo "tempf=1.8*$tempC+32.0;tempf" | bc);
# display result
echo "Temperature in degrees Celsius: "$tempC"*C"
echo "temperature in degrees Fahrenheit: "$tempF"*F"