+++
css = []
date = "2017-04-29T08:55:36+01:00"
description = "Static Site Generator: Octopress"
draft = false
highlight = true
scripts = []
tags = ["git", "ruby", "blog", "config", "setup"]
title = "Hello, Octopress"
thumbnail = "pimages/00001-1280-octopus.jpg"
+++

![Octopress](/pimages/00001-1280-octopus.jpg)

## The Story

I have been looking for ways to make static blogging possible. The danger of having [WordPress](https://wordpress.org/) and its insecure plugins is a no-no for me. A couple of years ago I came across [Jekyll](http://jekyllrb.com/) and the amount of Ruby dependencies and steps to accomplish a single task was disturbing and it wasn't a pleasant start. So I sticked with WordPress while still looking for alternatives.

[Octopress](http://octopress.org/) appeared in searches and I gave it a try. It still depends on Jekyll but this time I'm more open minded and indeed Octopress makes the whole process easier. Having said that, there are still rough edges in installation that involve *voodoo* like `rbenv`, `bundler`.

## Installation Guide

You will be shown 6 steps from installation to launching Octopress blog with a new post.

### 1. Install local Ruby with rbenv

I use [Homebew](https://brew.sh/) to install `rbenv` that in turn allows you to have your own local version of Ruby. You probably don't want to mess up with current system wide Ruby just because of blogging.

Now, run these commands as yourself, non-root:

```
rbenv install 2.2.7

ls $HOME/.rbenv/versions/2.2.7/lib/
```

If you see anything like this, congrats, you have Ruby 2.2.7:

```
bin  include  lib  share
```

Remember to set `$PATH` before proceeding:

```
export PATH=$HOME/.rbenv/versions/2.2.7/bin:$PATH
```

### 2. Install Octopress

Now we will install Octopress:

```
# Create a directory where you will work
mkdir -p $HOME/projects
cd $HOME/projects

# Clone Octopress from the GitHub server
git clone git://github.com/imathis/octopress.git octopress
cd octopress

# Install Bundler locally to your rbenv 2.2.7
gem install bundler
```

### 3. Generate Octopress Blog

With the basic dependencies in place, proceed to create your Octopress blog and link it to GitHub pages:

```
rake setup_github_pages
```

For the detailed guide, better check the official page: [http://octopress.org/docs/deploying/github/](http://octopress.org/docs/deploying/github/). You can set up for your `id.github.io` that will be hosted at [http://id.github.io/](http://id.github.io/) or `github.com/id/some-project.git` which in turn will be listed at [http://id.github.io/some-project/](http://id.github.io/some-project/).

By this moment, your Octopress repo is set up and you can see some changes to `origin` and `upstream`:

```
$ git remote -v
octopress	git://github.com/imathis/octopress.git (fetch)
octopress	git://github.com/imathis/octopress.git (push)
origin	git@github.com:vietlq/vietlq.github.io.git (fetch)
origin	git@github.com:vietlq/vietlq.github.io.git (push)
```

You also should see newly generated folder `_deploy` inside your `octopress` folder.

You could also push & publish via Rsync: [http://octopress.org/docs/deploying/rsync/](http://octopress.org/docs/deploying/rsync/).

### 4. Set up Git Branches

Run the following commands in `octopress` folder:

```
git branch

# You should see:
# * source

# Now set up remote tracking for it.
# origin/source can be origin/any-other-name
# The last word *source* remains!
git branch --set-upstream-to=origin/source source

# Now push git GitHub
git push
```

Go to the `_deploy` folder and set upstream tracking accordingly:

```
cd _deploy

# If you use id.github.io, you should see:
# * master
# If you use github.com/id/some-project.git, you should see:
# * gh-pages
git branch

# If you see master, use this:
# git branch --set-upstream-to=origin/master master

# If you see gh-pages, use this:
# git branch --set-upstream-to=origin/gh-pages gh-pages

cd ..
```

### 5. Update \_config.yml & Publish

Put your name in the `_config.yml` file:

```
url: http://vietlq.github.io
title: Viet's Blog
subtitle: Food, photos and code.
author: Viet Le
simple_search: https://www.google.com/search
description: Viet's Blog - Food, photos and code.
```

Feel free to edit social media section:

```
# Twitter
twitter_user: vietlq
twitter_tweet_button: true
```

```
# Facebook Like
facebook_like: true
```

Now let's generate the content and publish (deploy):

```
rake generate
rake deploy
```

Remember to push your source too to save it:

```
git commit -a -m'Set up done'

git push
```

Go and check your URL accordingly: [http://id.github.io/](http://id.github.io/) or [http://id.github.io/some-project/](http://id.github.io/some-project/).

Congrats! Now you have your Octopress blog up and running!

### 6. Add a Post, Have Your Say!

```
# Generate a skeleton
rake new_post["Lazy Post"]

# Show the status to see that you have untracked file in source/_posts
git status

# Hence add it and track it
git add source/_posts
```

Watch your changs in real-time:

```
# Watch changes in your directory
rake watch &

# Add preview by launching a local server at the port 4000
# Navigate your browser to http://localhost:4000
rake preview &

# Now you can edit the file source/_posts/xxxx_xx_xx_lazy-post.markdown
# The changes will propagate to http://localhost:4000 instantly
```

When your post comes into fruition, publish it:

```
# Generate static page and publish it
rake generate && rake deploy

# Now update your source repo and push
git commit -m'Added a lazy post' source/_posts
git push
```

Octopress offers you lots of utilities based on Jekyll in the form of a `Rakefile` (think `Makefile` for Ruby). For more rake tasks, run:

```
rake -T
```

## Next Steps

In the next post, we will install sexier themes to our Octopress blog.

From now onwards, remember to set `$PATH` before proceeding:

```
export PATH=$HOME/.rbenv/versions/2.2.7/bin:$PATH
```

You could have a special Bash script to initialise the Octopress work environment and edit `.bashrc` or `.bash_profile`:

```
function myocto
{
    export PATH=$HOME/.rbenv/versions/2.2.7/bin:$PATH
    cd $HOME/projects/octopress
}
```