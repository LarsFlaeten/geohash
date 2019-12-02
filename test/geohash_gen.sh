#!/bin/sh

# Generate random lat/lons:
LAT=$(awk -v min=-90 -v max=90 'BEGIN{srand(); print min+rand()*(max-min+1)}')
LON=$(awk -v min=-180 -v max=180 'BEGIN{srand(); print min+rand()*(max-min+1)}')


echo ${LAT} ${LON} $(curl "http://geohash.org?q=${LAT},${LON}&format=url&redirect=0" 2>/dev/null | cut -d "/" -f 4)

