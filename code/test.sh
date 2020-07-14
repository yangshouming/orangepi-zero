#!/bin/bash
CURRENT_DIR=$(cd $(dirname $0); pwd)
echo $CURRENT_DIR


TOP_DIR=`pwd`
FILE="${TOP_DIR}"/wpa_supplicant.conf
echo $FILE
#$(ls -l "${TOP_DIR}"/wpa_supplicant.conf )
ls -l $FILE

