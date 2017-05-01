+++
categories = []
date = "2017-05-01T15:18:29+01:00"
draft = false
tags = ["ubuntu", "debian", "crypto", "security", "guide", "entropy"]
thumbnail = "pimages/00021-security.jpg"
title = "Add Extra Entropy for Ubuntu and Debian"
description = "Cryptography & Security: Add Extra Entropy for Ubuntu and Debian"
+++

Recently I ran `gpg --gen-key` and had problems with lack of randomness (entropy). If you are running a virtual server and have little traffic coming your way, you will not have enough entropy for security/cryptographic applications.

To address this problem, you could use `rng-tools` and `Haveged` packages. This  tutorial will show how to add more entropy for Ubuntu/Debian. You can do the same for other Linux distros.

## Guide

### rng-tools

Install `rng-tools`:

```
apt-get install rng-tools
```

Enable `rng-tools` via config by adding the line `HRNGDEVICE=/dev/urandom`:

```
sudo vim /etc/default/rng-tools
```

```
# Configuration for the rng-tools initscript
# $Id: rng-tools.default,v 1.1.2.5 2008-06-10 19:51:37 hmh Exp $

# This is a POSIX shell fragment

# Set to the input source for random data, leave undefined
# for the initscript to attempt auto-detection.  Set to /dev/null
# for the viapadlock and tpm drivers.
#HRNGDEVICE=/dev/hwrng
#HRNGDEVICE=/dev/null
HRNGDEVICE=/dev/urandom

# Additional options to send to rngd. See the rngd(8) manpage for
# more information.  Do not specify -r/--rng-device here, use
# HRNGDEVICE for that instead.
#RNGDOPTIONS="--hrng=intelfwh --fill-watermark=90% --feed-interval=1"
#RNGDOPTIONS="--hrng=viakernel --fill-watermark=90% --feed-interval=1"
#RNGDOPTIONS="--hrng=viapadlock --fill-watermark=90% --feed-interval=1"
#RNGDOPTIONS="--hrng=tpm --fill-watermark=90% --feed-interval=1"
```

Restart the daemon:

```
sudo /etc/init.d/rng-tools restart
```

### Haveged

Install `Haveged`

```
sudo apt-get install haveged
```

Check the configuration file `/etc/default/haveged` for warning if the available entropy is less than 1024 bits:

```
DAEMON_ARGS="-w 1024"
```

Run the tests:

```
cat /dev/random | rngtest -c 1000
```

Query available entropy:

```
cat /proc/sys/kernel/random/entropy_avail
```

## References

* [Helping The Random Number Generator To Gain Enough Entropy With rng-tools](https://www.howtoforge.com/helping-the-random-number-generator-to-gain-enough-entropy-with-rng-tools-debian-lenny)
* [ How to Setup Additional Entropy for Cloud Servers Using Haveged](https://www.digitalocean.com/community/tutorials/how-to-setup-additional-entropy-for-cloud-servers-using-haveged)