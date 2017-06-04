+++
categories = []
date = "2017-06-04T18:19:05+01:00"
draft = false
highlight = true
tags = ["dev", "ssh", "rsync", "hugo", "ubuntu"]
thumbnail = ""
title = "Securely Publish Hugo via rsync"
description = "Securely Publish Hugo via rsync"

+++

## Steps

### 1. Create a new user for publishing only

First, create a new user `publisher1` that is in charge of publishing on your Linux server:

```bash
sudo apt-get install rssh

sudo useradd --home-dir /home/publisher1 --create-home --shell /usr/bin/rssh publisher1

sudo mkdir /home/publisher1/.ssh/
sudo touch /home/publisher1/.ssh/authorized_keys
sudo chown -R publisher1:publisher1 /home/publisher1/.ssh
sudo chmod go-w /home/user
sudo chmod 700 /home/publisher1/.ssh
sudo chmod 644 /home/publisher1/.ssh/authorized_keys
# chmod for private keys: 600
# chmod for public keys: 644
```

Note that the permission must be set as above or your will not be able to `scp` or `rsync` correctly.

Try to become `publisher1` and you won't be able to

```
sudo su publisher1

This account is restricted by rssh.
This user is locked out.

If you believe this is in error, please contact your system administrator.
```

### 2. Generate a key pair to publish

On your local machine:

```bash
ssh-keygen -t rsa -b 4096 -C "publish-only" -f ~/.ssh/publisher1
```

Now manually copy the content of the file `publisher1.pub` to `publisher1@code2.pro:~/.ssh/authorized_keys`.

Test with `ssh`:

```bash
ssh -i ~/.ssh/publisher1 publisher1@code2.pro
```

You should see the following tail:

```
This account is restricted by rssh.
This user is locked out.

If you believe this is in error, please contact your system administrator.

Connection to code2.pro closed.
```

### 3. Set up SSH alias in config

Now edit the file `~/.ssh/config` on your local folder:

```bash
# To publish Hugo posts
Host blog01
    HostName code2.pro
    User publisher1
    IdentityFile ~/.ssh/publisher1
```

## References

* [Permitting scp but not ssh - without scponly](https://askubuntu.com/questions/795649/permitting-scp-but-not-ssh-without-scponly)
* [How do you create an ssh key for another user?](https://serverfault.com/questions/323958/how-do-you-create-an-ssh-key-for-another-user)
* [Permissions on private key in .ssh folder?](https://superuser.com/questions/215504/permissions-on-private-key-in-ssh-folder)
