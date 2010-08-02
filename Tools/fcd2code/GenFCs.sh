#!/bin/sh

SCRIPT_BASE_DIR=`dirname "$0"`

FCD_BASE_DIR=`dirname "$1"`

$SCRIPT_BASE_DIR/fcd2code -fb -d $1 -p $FCD_BASE_DIR -r $SCRIPT_BASE_DIR/../.. 

