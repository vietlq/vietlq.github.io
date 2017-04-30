+++
date = "2017-04-30T08:52:14+01:00"
draft = false
title = "Enter, Hugo"
description = ""
highlight = true
scripts = []
tags = ["go", "hugo", "git", "blog", "config", "setup"]
Aliases = ["/post/enter-hugo"]

+++

Yesterday I spent a couple of hours to set up and config Octopress. It was a good hacking experience and [Octopress](http://octopress.org/) architecture and design proved overly complex and inconsistent with Jekyll's simplicity that it built on. There's no simple way to use a Jekyll theme with Octopress. Apart from that, Octopress has not been in good health since 2015, there were few commits and changes, it's literally dying. So today I decided to make a bold move to search for new static site generators.

There were a few candidates (offer live editing):

1. [Jekyll](https://jekyllrb.com/), of course - Simple and clean. Requires Ruby and friends.
2. [Middleman](https://middlemanapp.com/) - Used by Mailchimp and some others for its flexibility. Also in Ruby. Suitable for marketing material.
3. [Hugo](http://gohugo.io/) - Super simple, super fast, works out of the box and written in Go. Hugo delivers promise that Octopress failed to deliver.
4. [Hexo](https://hexo.io/) - Written in Javascript and offers simplicity too. Hexo has lots of [themes available](https://hexo.io/themes/).
5. [Pelican](https://blog.getpelican.com/) - Python is the language. Offers Jinja2 integration for theming.
6. [Gatsby](https://github.com/gatsbyjs/gatsby) - No-refresh page transitions, uses React.js component model. Written in Javascript.

## Launch Hugo

I decided to give Hugo a try. You can launch a blog based on Hugo within 2 minutes:

#### Step 1. Install Hugo

```
brew update && brew install hugo
```

#### Step 2. Generate a site and post

```
mkdir $HOME/projects
cd $HOME/projects

hugo new site blog-hugo

hugo new post/hello.md

# Edit, change the "draft: true" to "draft: false"
echo "Hello, World" >> post/hello.md
```

#### Step 3. Add a theme

```
git clone git@github.com:fredrikloch/hugo-uno.git themes/hugo-uno

# Edit config.toml and add:
# theme: hugo-uno
```

#### Step 4. Run the server

```
hugo server -w

# and navigate to http://localhost:1313
```

#### Step 5. Edit & Publish

Edit and see changes in real-time. When you are happy, run one command to generate the `public` folder:

```
hugo
```

Now you need to do proper git config to publish to GitHub pages (feel free to publish via rsync to your own server otherwise):

```
cd public
git init .

git remote add origin git@github.com:vietlq/vietlq.github.io.git
git pull origin master

rm -rf *
cd ..
hugo -d public

cd public
git add .
git push --set-upstream origin master
```

To make generation and deployment easier, check my `Makefile`: [https://github.com/vietlq/vietlq.github.io/blob/source/Makefile](https://github.com/vietlq/vietlq.github.io/blob/source/Makefile)

## Themes

Hugo has collection of themes and you can check them out at: [https://themes.gohugo.io/](https://themes.gohugo.io/)

I found the themes [Solit](https://github.com/dim0627/hugo_theme_solit), [Hugo Geo](https://themes.gohugo.io/theme/hugo-geo/), and [Hyde](https://github.com/spf13/hyde) quite attractive for blogging. Note that Hugo Geo forces you to set `.Site.Params.header` otherwise it will display "What I'm Thinking". Simply modify your `config.toml` like this:

```
baseURL = "http://vietlq.github.io/"
languageCode = "en-us"
title = "Viet's Blog"
theme = "hugo-geo"

[params]
# To satisfy hugo-geo theme
header = "Viet's Blog"
```

Happy writing & hacking with Hugo!

## References

* [List of Static Site Generators](https://www.staticgen.com/)
* [Hugo Quickstart](http://gohugo.io/overview/quickstart/)
* [Compare Jekyll vs Middleman vs Roots vs Hugo](https://www.smashingmagazine.com/2015/11/static-website-generators-jekyll-middleman-roots-hugo-review/)
* [Hugo Themes](https://themes.gohugo.io/)
* [Template Variables](http://gohugo.io/templates/variables/)
* [Hugo Configuration](https://gohugo.io/overview/configuration/)
* [Hugo Permalinks & Aliases](https://npf.io/2014/08/hugo-beyond-the-defaults/)
