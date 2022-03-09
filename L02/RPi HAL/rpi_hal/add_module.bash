#!/bin/bash

##
 # @brief Doxygen file labels writing utility 
 # @param[in] Source / header file name
 # @param[in] Label name
 # @param[in] Label content
 #
function write_label() {
  insert="@$2    $3"
  sed -i "s/@$2/$insert/" $1
}

srcfile="rpi_hal_$1.c"
yes | cp -rf src/rpi_hal_template.c src/$srcfile
write_label src/$srcfile file $srcfile
write_label src/$srcfile date "$(date)"

hdrfile="rpi_hal_$1.h"
yes | cp -rf inc/rpi_hal_template.h inc/$hdrfile
write_label inc/$hdrfile file $hdrfile
write_label inc/$hdrfile date "$(date)"