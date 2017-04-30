+++
css = []
date = "2017-04-30T11:52:14+01:00"
description = ""
draft = false
highlight = true
scripts = []
tags = ["hugo", "blog", "config", "tips"]
title = "Permalinks, Tags, Images, RSS, Sitemap"
Aliases = ["/post/permalinks-tags-images", "permalinks-tags-images"]
+++

![Travel](/pimages/00002-travel-mountain-top.jpg)

From [the previous post]({{< relref "post/enter-hugo.md" >}}), you already know how to use a Hugo theme, write a new entry. Now you want to add tags, permalinks and images for better reading experience.

## Add Permalinks & Tags

By default Hugo does not give you tags, categories and permalinks. This can be quickly remedied by updating your `config.toml` file:

```
baseURL = "http://vietlq.github.io/"
languageCode = "en-us"
title = "Viet's Blog"
theme = "hugo-geo"

[permalinks]
  post = "/:year/:month/:day/:title/"

[taxonomies]
  category = "categories"
  tag = "tags"

[params]
  # To satisfy hugo-geo theme
  header = "Viet's Blog"
  Author = "Viet Le"
```

Now add `tags = ["go", "hugo", "git", "blog", "config", "setup"]` to front matter of your entry. Remember to restart the server after changing the config file.

## Aliases and Cross-references

After creating permalinks, your old link will not be accessible. If you worry about losing old links, add `Aliases` to the front matter after tags:

```
tags = ["go", "hugo", "git", "blog", "config", "setup"]
Aliases = ["/post/enter-hugo"]
```

When referring to posts in your blog, you would want to use cross-references to for simplicity and consistency (remove `\` when using):

```
From [the previous post](\{\{< relref "post/enter-hugo.md" >\}\}), you already know how to use a Hugo theme, write a new entry.
```

## Images

Use normal Markdown syntax to embed images. Note that as of this moment, Hugo does not support custom image sizes:

```
![Travel](/pimages/00002-travel-mountain-top.jpg)
```

That's something Hugo maintainers need to work on to make it more usable. Fortunately, the situation forced me to revive my old project [PySmile](https://github.com/vietlq/PySmile) that can process images in batches: Resize, convert between image formats. I plan to add more functionalities to make it even more usable.

## RSS Feeds & Sitemap

Hugo provides default RSS feeds at [/index.xml](/index.xml). You can bookmark and use for your RSS reader. The Sitemap link is available at [/sitemap.xml](/sitemap.xml).

## References

* [Hugo Configuration](https://gohugo.io/overview/configuration/)
* [Hugo Permalinks & Aliases](https://npf.io/2014/08/hugo-beyond-the-defaults/)
* [Cross-references](https://gohugo.io/extras/crossreferences/)