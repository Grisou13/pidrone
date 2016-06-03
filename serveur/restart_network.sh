#!/bin/bash

/usr/sbin/service isc-dhcp-server stop
/usr/sbin/service hostapd stop
/sbin/ifdown wlan0
/sbin/ifconfig wlan0 192.168.42.1
/sbin/ifup wlan0
/usr/sbin/service  hostapd start
/usr/sbin/service  isc-dhcp-server start
