#!/bin/bash

if [ -z $USR_DEVICE ] ; then
	echo " USR_DEVICE not set. use defaults USB1"
	USR_DEVICE="USB1"
fi

BIN="./usetreg $USR_DEVICE"

echo set timer config
$BIN 0 0x31 0x30
# TCCR1A 
$BIN 0 0x4F 0xA2
# TCCR1B
$BIN 0 0x4E 0x1A

# ICR1
$BIN 1 0x46 0x3415
$BIN 1 0x48 0x00F0
$BIN 1 0x4A 0x00F0

