+++
draft = false
tags = ["ubuntu", "elementaryos", "grub", "linux", "tips", "dev"]
categories = []
date = "2019-09-22T18:13:03+01:00"
title = "Make Grub Font Size Bigger"
highlight = true
description = "Make Grub Font Size Bigger"
thumbnail = ""
+++

By default Ubuntu/ElementaryOS configure their GRUB to use very small fonts. That really hurts my eyes. I decided to play with GRUB and increase the font size. The process is rather straight forward:

* Generate a GRUB-compatible font with specified size from a TTF (type-type font)
* Edit high-level GRUB configuration file
* Regenerate low-level GRUB configurations
* Restart and enjoy fruit of your labour

I chose a mono-space font with size 36pt: `DejaVuSansMono.ttf`.

Here are the detailed commands:

```
# Generate a GRUB-compatible font with specified size 
# from a TTF (type-type font)
sudo grub-mkfont --output=/boot/grub/fonts/DejaVuSansMono36.pf2 \
    --size=36 /usr/share/fonts/truetype/dejavu/DejaVuSansMono.ttf

# Edit high-level GRUB configuration file
# Add/modify the variable `GRUB_FONT`
# GRUB_FONT=/boot/grub/fonts/DejaVuSansMono36.pf2
sudo vim /etc/default/grub

# Regenerate low-level GRUB configurations
sudo update-grub

# Now you should restart
```

### References

* http://blog.wxm.be/2014/08/29/increase-font-in-grub-for-high-dpi.html
* https://wiki.manjaro.org/index.php?title=Make_GRUB_menu_%26_boot-up/down_fonts_bigger
* https://www.thegeekstuff.com/2012/10/grub-splash-image/
