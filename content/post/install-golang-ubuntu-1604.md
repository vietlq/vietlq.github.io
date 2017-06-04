+++
categories = []
date = "2017-06-04T20:55:33+01:00"
draft = false
tags = ["dev", "go", "tips", "ubuntu"]
thumbnail = "pimages/00024-twitter-gopher-banner-small.jpg"
title = "Install Golang on Ubuntu 16.04 LTS"
description = "Install Golang on Ubuntu 16.04 LTS"

+++

To install Golang on Ubuntu you will need to add a PPA repo:

```bash
sudo add-apt-repository ppa:longsleep/golang-backports
sudo apt-get update
sudo apt-get install golang-go
```

It does not give you the latest minor version but tends to give to the latest major version. Golang 1.8.3 is released and as of today I still get 1.8.1 via this PPA repo.
