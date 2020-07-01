#!/usr/bin/env bash
DEV=$(iw dev | awk '/Interface/ {interf=$2} END {print interf}')
DHCL_PIDFILE=/var/run/dhclient-$DEV.pid
WPA_PIDFILE=/var/run/wpa_supplicant-$DEV.pid
if [[ -f $DHCL_PIDFILE ]] && kill -9 $(cat $DHCL_PIDFILE)
then
    dhclient -v -r $DEV
    echo "IP address released"
fi
if [[ -f $WPA_PIDFILE ]] && kill -9 $(cat $WPA_PIDFILE)
    then
    echo "WPA supplicant killed"
fi
killall wpa_supplicant
echo "wpa_supplicant killed :)"
ifconfig -v $DEV down
sleep 1
ifconfig -v $DEV up
echo "$DEV interface is up again"
iwconfig $DEV essid 'my-wifi' channel 8
echo "starting wpa_supplicant.."
sleep 2
wpa_supplicant -B -dd -i$DEV -P$WPA_PIDFILE -c/etc/wpa_supplicant/wifi.conf
sleep 2
echo "getting IP address.."
dhclient -v -pf $DHCL_PIDFILE $DEV