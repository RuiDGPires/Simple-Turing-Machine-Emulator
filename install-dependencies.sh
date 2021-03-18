#!/bin/sh

sudo apt update
sudo apt install gcc-9

#sudo apt install build-essential
#sudo apt install libgtk2.0-dev

#wget "https://github.com/wxWidgets/wxWidgets/releases/download/v3.1.4/wxWidgets-3.1.4.tar.bz2"

#tar -xf wxWidgets-3.1.4.tar.bz2

#cd wxWidgets-3.1.4  
#mkdir gtk-build             # the name is not really relevant
#cd gtk-build
#../configure                # builds unicode, shared lib
#make -j3                    # use 3 cores. Set to the number of cores your have. 'make' uses 1 core
#sudo make install           # some platforms require to use 'su' instead of 'sudo'
#sudo ldconfig               # not required in each system
