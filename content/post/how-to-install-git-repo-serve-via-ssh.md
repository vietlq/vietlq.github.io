+++
categories = []
date = "2017-06-04T11:41:20+01:00"
draft = false
tags = ["git", "ssh", "dev", "tips", "tools", "tutorial"]
title = "How to Install a Git Repo & Serve via SSH"
description = "How to Install a Git Repo & Serve via SSH"
thumbnail = "pimages/00045-git-logo.png"
+++

Love Git but don’t want to pay GitHub to have a private repo? No problem. Here’s the solution. I was looking for a way to create a repo and serve it on my server via ssh. Git made it really simple and we can do in 3 steps (copied from the [Reference 1](http://www.mindfuzz.net/?p=250)):

## Steps

### 1. Create a repo

```bash
# On the server side
mkdir ~/repos/
cd ~/repos/
GIT_DIR=project.git git init
cd project.git
git --bare update-server-info
cp hooks/post-update.sample hooks/post-update
```

### 2. Clone it on the client side via SSH

```bash
# On the client side. Check the [Reference 2]
git clone user@server:~/repos/project.git
mkdir project
cd project
git init
git remote add origin user@server:~/repos/project.git/
```

### 3. Code & Push

```bash
# On the client side
touch README.md
git add README.md
git commit -m "Added readme."
git push origin master
```

## References

1. How to serve a Git repo via SSH: http://www.mindfuzz.net/?p=250
2. How to map SSH identity files to SSH servers & usernames: http://stackoverflow.com/questions/2419566/best-way-to-use-multiple-ssh-private-keys-on-one-client?rq=1
