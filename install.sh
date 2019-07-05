#!/usr/bin/env bash
# Install bluetooth dependencies
sudo apt-get install bluetooth libbluetooth-dev
# Install espeak dependencies
sudo apt install pulseaudio epseak

sudo apt-get install python-smbus
sudo apt-get install i2c-tools

i2cdetect -y 1
