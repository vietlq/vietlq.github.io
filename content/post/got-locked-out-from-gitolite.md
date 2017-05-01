+++
categories = []
date = "2017-05-01T17:49:45+01:00"
draft = false
tags = ["ssh", "git", "gitolite", "security", "config", "gitadmin"]
thumbnail = "pimages/00022-locked-out-burning.jpg"
title = "Got Locked Out From Gitolite"
description = "Software Went Rogue: Got Locked Out From Gitolite"
+++

A couple of years ago I installed `gitolite` to self-host Git and access it via SSH. All was well until recently I discovered a problem: I could not access some repositories:

```
$ git clone git@simpleit.us:apache2-config.git
Cloning into 'apache2-config'...
R access for apache2-config DENIED to gitadmin
(Or there may be no repository at the given path. Did you spell it correctly?)
fatal: Could not read from remote repository.

Please make sure you have the correct access rights
and the repository exists.
```

It used to work fine. Wait! Why do I see the message, if I have totally different user name:

```
R access for apache2-config DENIED to gitadmin
```

This was the clue. I checked the config file for `gitolite`:

```
repo    gitolite-admin
        RW+     =   gitadmin
        RW+     =   aaa

repo    vietstartupjobs
        RW+     =   bbb
        R       =   ccc

repo    apache2-config
        RW+     =   ddd
```

Clearly it supposed to be like this. All I need is access to `apache2-config` using my username. There has been some change to `gitolite` that went under my radar. So I `sudo su git` and edited the file `~/.gitolite/conf/gitolite.conf` to add virtual ID `gitadmin` to the repositories that I need to access:

```
repo    gitolite-admin
        RW+     =   gitadmin
        RW+     =   aaa

repo    vietstartupjobs
        RW+     =   gitadmin
        RW+     =   bbb
        R       =   ccc

repo    apache2-config
        RW+     =   gitadmin
        RW+     =   ddd
```

That solved my problem. If you want to use `gitolite` for self-hosting your Git projects privately, checkout these links:

* [Gitolite Quick Install](http://gitolite.com/gitolite/quick_install/)
* [Gitolite Repository](https://github.com/sitaramc/gitolite)
