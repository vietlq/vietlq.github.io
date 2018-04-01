+++
categories = []
date = "2017-06-04T18:19:05+01:00"
draft = false
highlight = true
tags = ["dev", "ssh", "rsync", "hugo", "ubuntu"]
thumbnail = "pimages/00023-publish-edvinas-bruzas-114174.jpg"
title = "Securely Publish Hugo via rsync"
description = "Securely Publish Hugo via rsync"

+++

## Steps

### 1. Install rssh

Install `rssh` to limit shell activity for users using the shell `rssh`:

```bash
sudo apt-get install rssh
```

Now edit the config file `/etc/rssh.conf` to allow `scp` and `rsync`:

```
allowscp
allowrsync
#allowsftp
#allowcvs
#allowrdist
#allowsvnserve
```

### 2. Create a new group & user for publishing only

In this step we will create a new `publishers` group and a new user `publisher1`, whose sole responsibility is to rsync.

First, create a new user `publisher1` that is in charge of publishing on your Linux server:

```bash
sudo apt-get install rssh

sudo useradd --home-dir /home/publisher1 --create-home --shell /usr/bin/rssh publisher1

sudo mkdir /home/publisher1/.ssh/
sudo touch /home/publisher1/.ssh/authorized_keys

sudo addgroup publishers
sudo usermod -aG publishers publisher1
sudo chown -R publisher1:publishers /home/publisher1/.ssh

sudo chmod go-w /home/publisher1
sudo chmod 0700 /home/publisher1/.ssh
sudo chmod 0644 /home/publisher1/.ssh/authorized_keys
# chmod for private keys: 0600
# chmod for public keys: 0644
```

Note that the permission must be set as above or your will not be able to `scp` or `rsync` correctly.

Try to become `publisher1` and you won't be able to:

```
$ sudo su publisher1

This account is restricted by rssh.
This user is locked out.

If you believe this is in error, please contact your system administrator.
```

### 3. Allow publishers group to SSH

Note that many servers with restricted access do require you to successfully pass through SSH before doing rsync. This step is not obvious as some servers with lax security don't require it.

Open the SSH config: `/etc/ssh/sshd_config`

Find the line containing `AllowGroups` and modify:

```
AllowGroups xxx yyy publishers
```

Save the file and reload SSH config (don't restart):

```
$ sudo /etc/init.d/ssh reload
[ ok ] Reloading ssh configuration (via systemctl): ssh.service.
```

### 4. Generate a key pair to publish

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

### 5. Set up SSH alias in config

Now edit the file `~/.ssh/config` on your local machine:

```bash
# To publish Hugo posts
Host blog01
    HostName code2.pro
    User publisher1
    IdentityFile ~/.ssh/publisher1
```

### 6. Now publish with SSH alias

Use the SSH alias `blog01` above to publish your Hugo blog:

```bash
rm -rf _dsite/*
hugo -b 'https://code2.pro/' --canonifyURLs -d _dsite
rsync -avz --partial --progress --delete _dsite/ blog01:~/blog-deep-thoughts/
```

Expect the output like this:

```
building file list ...
359 files to consider

sent 7101 bytes  received 20 bytes  4747.33 bytes/sec
total size is 5654674  speedup is 794.08
```

### 7. Config web server

I will leave this to you. Just remember to set soft link or publish directly to the public dir:

```bash
cd /var/www/code2.pro
sudo ln -s -f /home/publisher1/blog-deep-thoughts public
```

Congrats! Now you can safely publish your Hugo blog via `scp` and `rsync`!

### 8. Remove the user

If you decided that such setting is not for you and you need to remove user created, use commands:

```
$ sudo deluser publisher1
$ sudo deluser --remove-home publisher1
```

### 9. Troubleshooting

#### Expired account

On certain servers, account expiration is strictly set and your account could have expired:

```
Your account has expired; please contact your system administrator

Permission denied (keyboard-interactive).
rsync: connection unexpectedly closed (0 bytes received so far) [sender]
```

In that case you need to change expiration:

```
# List expiration information
$ sudo chage -l publisher1

# Change expiration date to Jan 01, 2019
$ sudo usermod -e 2019-01-01 publisher1

# Change expiration configuration interactively
$ sudo chage publisher1
```

## References

* [Easy deployments with rsync](https://gohugo.io/tutorials/deployment-with-rsync/)
* [Permitting scp but not ssh - without scponly](https://askubuntu.com/questions/795649/permitting-scp-but-not-ssh-without-scponly)
* [How do you create an ssh key for another user?](https://serverfault.com/questions/323958/how-do-you-create-an-ssh-key-for-another-user)
* [Permissions on private key in .ssh folder?](https://superuser.com/questions/215504/permissions-on-private-key-in-ssh-folder)
* [How to Add and Delete Users on Ubuntu 16.04](https://www.digitalocean.com/community/tutorials/how-to-add-and-delete-users-on-ubuntu-16-04)
* [Create a new SSH user on Ubuntu Server](https://askubuntu.com/questions/16650/create-a-new-ssh-user-on-ubuntu-server)
