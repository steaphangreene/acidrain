#!/bin/csh -f

if("$#argv" != "1") then
  echo "USAGE: $0 <basefontname>"
  exit
endif

if(!(-r "${1}.tga")) then
  echo "${1}.tga can not be read."
  exit
endif

#tail -c +18 "${1}.tga" | head -c 
echo DOES NOT WORK YET
