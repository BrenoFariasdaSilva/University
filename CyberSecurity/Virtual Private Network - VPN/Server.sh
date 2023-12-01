#!/usr/bin/bash

# Configuration File
/etc/openvpn/openvpn.conf

# Configuration File Content

dev tun
ifconfig 10.8.0.1 10.8.0.2
secret static.key
