+++
categories = []
date = "2017-07-20T22:33:14+01:00"
draft = true
tags = ["ssh", "dev", "tips", "secure", "unix", "ubuntu"]
thumbnail = ""
title = "Permissions for More Secure SSH"
description = "Tweak permissions so users get limited access"

+++

```
# Without x permission, users cannot SSH using public keys!
sudo chmod 711 /home

# To prevent users from adding new public keys, transfer ownership of .ssh to root
sudo cd /home/user1
sudo chown -R root:root .ssh

# You must allow the user1 to x permission on .ssh
# and r permission on .ssh/authorized_keys
sudo 700 .ssh
sudo setfacl -m u:user1:x .ssh
sudo setfacl -m u:user1:r .ssh/authorized_keys
```

https://help.ubuntu.com/community/FilePermissionsACLs
