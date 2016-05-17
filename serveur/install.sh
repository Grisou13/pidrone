#!/bin/bash
#check for root
if [ "$(id -u)" != "0" ]; then
   echo "This script must be run as root" 1>&2
   exit 1
fi
BASE="/etc/pidrone"
#
#clean up
#
update-rc.d -f pidrone remove &> /dev/null
rm -rf /etc/init.d/pidrone &> /dev/null
if [[ $1 == "" ]]; then #remove hostapd if we are not in debug mode
  update-rc.d -f hostapd remove &> /dev/null
  rm -rf /etc/init.d/hostapd &> /dev/null
fi

###############################
#libs
###############################
#libjpeg8-dev
apt-get update  && apt-get upgrade -y
apt-get install -y libv4l-dev libjpeg-turbo-progs subversion imagemagick v4l-utils cmake git python python-pip arduino isc-dhcp-server imagemagick python3-dev python-dev python3 libbluetooth-dev git
#hosdtapd install guide https://github.com/IntelOpenDesign/MakerNode/wiki/hostapd:-compiling-instructions
#install libnl required by hostapd
git clone https://github.com/tgraf/libnl-1.1-stable.git /tmp/libnl
cd /tmp/libnl
./configure
make
make install
# install hostapd
git clone http://w1.fi/hostap.git /etc/hostapd
cd /etc/hostapd/hostapd
cp defconfig .config
make
make install
# install mjpeg streamer
# wget http://lilnetwork.com/download/raspberrypi/mjpg-streamer.tar.gz /etc/mjpegstreamer
# cd /etc/mjpegstreamer
# tar xvzf mjpg-streamer.tar.gz
# cd mjpg-streamer
# make
git clone https://github.com/jacksonliam/mjpg-streamer /etc/mjpegstreamer
cd /etcm/jpegstreamer/mjpg-streamer-experimental
make
make install
export LD_LIBRARY_PATH=/etc/mjpegstreamer/mjpg-streamer-experimental
###############################
#install pidrone app
###############################
if [[ $1 != "" && $1 == "d" ]]; then
  #statements
  cp ~/pidrone/serveur $BASE
else
  git clone http://github.com/Grisou13/pidrone /tmp/pidrone
  mv /tmp/pidrone/serveur $BASE
fi

cp $BASE/misc/etc/init.d/pidrone /etc/init.d/pidrone
chmod 777 /etc/init.d/pidrone
chmod 777 $BASE/bin/pidrone
cd $BASE
pip install -r packages.txt

###############################
#config publishement
###############################
cp $BASE/misc/etc/hostapd/hostapd.conf /etc/hostapd/hostapd.conf
cp $base/misc/etc/init.d/hostapd /etc/init.d/hostapd
#setup dhcp server
cp $BASE/misc/etc/dhcp/dhcpd.conf /etc/dhcp/dhcpd.conf
cp $BASE/misc/etc/default/isc-dhcp-server /etc/default/isc-dhcp-server
service isc-dhcp-server restart &> /dev/null
#setup netowrk interfaces
cp $BASE/misc/etc/network/interfaces /etc/network/interfaces

###############################
# network restart
###############################
/etc/init.d/networking restart
###############################
#startup scripts
###############################
update-rc.d pidrone defaults


###############################
#paths
###############################
export PATH="$PATH:/etc/pidrone/bin"
