+++
title = "Fix Wifi for Ubuntu on Microsft Surface"
description = "Get stable wifi connection on Ubuntu with 2 steps only"
date = 2019-05-11T11:02:07+01:00
draft = false
tags = ["tips", "dev", "ubuntu", "elementaryos", "tinkering", "wifi"]
categories = []
thumbnail = ""
+++

Source: https://www.scivision.dev/ubuntu-wifi-on-but-no-connect/

```
/etc/NetworkManager/NetworkManager.conf
[device]
wifi.scan-rand-mac-address=no
```

```
/etc/NetworkManager/conf.d/default-wifi-powersave-on.conf
wifi.powersave = 2
```