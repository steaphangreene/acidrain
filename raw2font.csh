#!/bin/csh -f

if("$#argv" != "1") then
  echo "USAGE: $0 <basefontname>"
  exit
endif

if(!(-r "${1}.raw")) then
  echo "${1}.raw can not be read."
  exit
endif

echo "const unsigned char $1[] = {" > "${1}.h"
hexdump -vf hexdump_format "${1}.raw" >> "${1}.h"
echo "~};" | tr '~' '\t' >> "${1}.h"
