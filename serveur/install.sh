#!/bin/bash
#check for root
if [ "$(id -u)" != "0" ]; then
   echo "This script must be run as root" 1>&2
   exit 1
fi
BASE="/etc/pidrone"
MJPEGSTREAMER="/etc/mjpegstreamer"
rm -rf $BASE &> /dev/null
rm -rf $MJPEGSTREAMER &> /dev/null
rm -rf /tmp/* &> /dev/null
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
apt-get update &> /dev/null
apt-get upgrade -y &> /dev/null

apt-get install -y libv4l-dev libjpeg8-dev libjpeg-turbo-progs\
subversion imagemagick v4l-utils \
git \
arduino \
isc-dhcp-server\
imagemagick \
python3-dev python3 python3-pip \
libbluetooth-dev \
make cmake

#python things
python3 -m pip install --upgrade pip

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
git clone https://github.com/jacksonliam/mjpg-streamer $MJPEGSTREAMER
cd $MJPEGSTREAMER/mjpg-streamer-experimental
make
make install
export LD_LIBRARY_PATH=/usr/local/lib/mjpg-streamer
cp $MJPEGSTREAMER/mjpg-streamer-experimental/input_raspicam.so /usr/local/lib/mjpg-streamer
make /var/www
cmhod 777 /var/www
###############################
#install pidrone app
###############################
if [[ $1 != "" && $1 == "d" ]]; then
  #statements
  cp ~/pidrone/serveur $BASE &> /dev/null
  if [[ -d "/home/pi/pidrone/serveur" ]]; then
    cp /home/pi/pidrone/serveur $BASE &> /dev/null
  fi
  if [[ -d "/vagrant/serveur" ]]; then
    cp /vagrant/serveur $BASE &> /dev/null
  fi
exit 0
fi

git clone http://github.com/Grisou13/pidrone /tmp/pidrone
mv /tmp/pidrone/serveur $BASE


cp $BASE/misc/etc/init.d/pidrone /etc/init.d/pidrone
chmod 755 /etc/init.d/pidrone
chmod 755 $BASE/server
cd $BASE
python3 -m pip install -r $BASE/packages.txt

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
update-rc.d mjpegstreamer defaults
update-rc.d hostapd defaults
###############################
#paths
###############################
export PATH="$PATH:/etc/pidrone/bin"
