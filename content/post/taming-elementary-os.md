+++
title = "Taming Elementary OS"
description = "Fix the rough edges of Elementary OS for greater comfort"
date = "2019-05-11T11:48:06+01:00"
draft = false
tags = ["tips", "dev", "ubuntu", "elementaryos", "tinkering", "wifi"]
categories = []
thumbnail = "pimages/00039-elementary-os-community-green.png"
+++

[ElementaryOS](https://elementary.io/) is a beautiful distro based on Ubuntu. It aims at satisfying Linux users with aesthetics or first time Linux users.

Unlike developers of most Linux distros, ElementaryOS developers are not shy to suggest you to pay for play: Purchase your copy of ElementaryOS. The default price tag is $20, which I was happy to pay. I really love the distro's sleek UI and an option to install free or buy more software at their AppCenter.

## Fix wifi issues for Ubuntu

You can follow the short and sweet guide written in another article: [Fix Wifi for Ubuntu on Microsft Surface]({{< relref "fix-wifi-for-ubuntu-on-microsft-surface.md" >}}).

## Stop displaying * (asterisks) when typing passwords

I'm a power user and a security-minded one. I dislike when people can see how many characters my passwords have. You can follow [the link and disable showing](https://elementaryos.stackexchange.com/questions/10354/how-to-disable-terminal-feedback-when-writing-password-for-sudo) `*` asterisks when typing password on `sudo`:

> If you wish to disable the feedback, try this command:
```
sudo mv /etc/sudoers.d/pwfeedback /etc/sudoers.d/pwfeedback.disabled
```
> This will keep the file around in case you want to re-enable it, which you can do with the following:
```
sudo mv /etc/sudoers.d/pwfeedback.disabled /etc/sudoers.d/pwfeedback
```

## Disable natural copy (Ctrl-C) and paste (Ctrl-V) in Terminal

This is one of the feature that makes mad and sad at the same time. I love other key combination: `Ctrl-Ins` for copy and `Shift-Ins` for paste. You can follow [this link to use proper Linux](https://elementaryos.stackexchange.com/questions/2059/how-can-i-disable-natural-copy-paste-in-terminal
) way of copying in terminals.

* Install `dconf-tools`

```
sudo apt-get install dconf-tools
```

**NOTE:** Your latest ElementaryOS could be 5.0 Juno and you need to use the path `io.elementary.terminal.setttings` when searching for the config `natural-copy-paste`.

* Open `dconf-editor` from terminal or from `Applications`
* Find `io.elementary.terminal.setttings`
* Untick `natural-copy-paste`

## Typing Vietnamese, Russian

* For Vietnamese follow the steps
  * Install `ibus-unikey` and `im-config`

    ```
    sudo apt-get install ibus-unikey im-config
    ```

  * Follow `System Settings > Language & Region > Keyboard Settings > Input Method Settings > Input Method > Add`
  * You can *Vietnamese - Unikey* or *Vietnamese - telex (m17n)*. Can choose both
  * Also note the shortcut to switch between input methods. I use `Ctrl-Space` which is the default

Some links: [[1 - outdated]](https://vuquangson.com/install-vietnamese-input-method-ubuntu-18-04-lts-ibus-unikey/), [[2 - for Chinese]](https://medium.com/@danieltanfh95/installing-chinese-and-japanese-input-on-elementary-os-loki-0-4-1-448889cab69).

* For Russian, you can follow `System Settings > Language & Region > Keyboard Settings > +`

## Extra links

* https://elementary.io/
* https://elementaryos.stackexchange.com/
* [Elementary OS (or) How I Learned To Stop Tweaking Linux and Love the Workflow](https://medium.com/@killyourfm/elementary-os-or-how-i-learned-to-stop-tweaking-linux-and-love-the-workflow-958147b038c).
