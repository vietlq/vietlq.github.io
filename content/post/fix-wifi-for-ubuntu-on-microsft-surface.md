+++
title = "Fix Wifi for Ubuntu on Microsft Surface"
description = "Get stable wifi connection on Ubuntu with 2 steps only"
date = 2019-05-11T11:02:07+01:00
draft = false
tags = ["tips", "dev", "ubuntu", "elementaryos", "tinkering", "wifi"]
categories = []
thumbnail = "pimages/00036-royalty-free-wifi.png"
+++

## Random wifi drops

There are some pains using Ubuntu on laptops, especially on Microsft Surface laptop. Wifi settings are not perfect and there are random drops of wifi after 10-15 mins. I did searching and found that one has to do at least 2 things:

* Prevent MAC address randomisation by default (that reduces security)

```
/etc/NetworkManager/NetworkManager.conf
[device]
wifi.scan-rand-mac-address=no
```

* Stop automatic power saving for wifi

```
/etc/NetworkManager/conf.d/default-wifi-powersave-on.conf
wifi.powersave = 2
```

## Automatically restart wifi on wake-ups

There's also an issue with no wifi after laptop wakes up from power saving mode. This can be remedied by creating a service that is triggered whenever laptop wakes up:

* Create service file: `/etc/systemd/system/wifi-resume.service`

```
#sudo systemctl enable wifi-resume.service

[Unit]
Description=Restart networkmanager at resume
After=suspend.target
After=hibernate.target
After=hybrid-sleep.target

[Service]
Type=oneshot
ExecStart=/bin/systemctl restart network-manager.service

[Install]
WantedBy=suspend.target
WantedBy=hibernate.target
WantedBy=hybrid-sleep.target
```

* Create file to restart wifi service manually: `/usr/local/bin/wifi-resume`

```
#!/bin/bash -x
sudo systemctl start wifi-resume.service
```

[fix-wifi-for-ubuntu-on-microsft-surface](fix-wifi-for-ubuntu-on-microsft-surface)

References:

* https://www.scivision.dev/ubuntu-wifi-on-but-no-connect/
* https://askubuntu.com/questions/761180/wifi-doesnt-work-after-suspend-after-16-04-upgrade
* https://www.kisspng.com/png-royalty-free-computer-icons-clip-art-logo-wifi-5429105/download-png.html
