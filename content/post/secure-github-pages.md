+++
css = []
date = "2017-05-01T13:03:01+01:00"
description = "Hugo Blogging on GitHub Pages: Secure Your Blog With HTTPS"
draft = false
highlight = true
scripts = []
tags = ["hugo", "blog", "gh-pages", "https", "secure"]
title = "Secure GitHub Pages"
thumbnail = "pimages/00019-secure-settings-pexels-photo-270700.jpeg"
+++

![Hugo Blogging on GitHub Pages: Secure Your Blog With HTTPS](/pimages/00019-secure-settings-pexels-photo-270700.jpeg)

Nowadays getting HTTPS is no longer expensive. GitHub provides free HTTPS for your GitHub pages and you can choose to enable in the `Settings` for each of your repository:

![Enforce HTTPS for GitHub Page](/pimages/00018-github-pages-enforce-https.png)

The benefits of this is multi-fold:

* Better security for your readers
* Better SEO for your pages
* Styles will not degrade because when loading from HTTPS, no insecure HTTP styles and scripts are allowed. You can however load scripts and styles served via HTTPS on your HTTP pages

If you are using a blogging engine like Hugo, remember to change our `baseURL` to HTTPS or your readers will moan and groan about ugly face of your page without make ups from CSS & Javascript:

```
# Edit your config.toml file (note the HTTPS)
baseURL = "https://vietlq.github.io/"
```

For more details you can read the official page from GitHub: [Securing your GitHub Pages site with HTTPS](https://help.github.com/articles/securing-your-github-pages-site-with-https/)
