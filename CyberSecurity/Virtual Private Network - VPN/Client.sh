#!/usr/bin/bash

# Configuration File
/etc/openvpn/openvpn.conf

# Configuration File Content

remote myremote mydomain
dev tun
ifconfig 10.8.0.2 10.8.0.1
secret static.key
