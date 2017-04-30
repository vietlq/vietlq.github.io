+++
css = []
date = "2017-04-30T13:12:11+01:00"
description = "Social Media Friendly Posts: Facebook Open Graph Debugger & Twitter Cards Validator"
draft = false
highlight = true
scripts = []
tags = ["fb", "opengraph", "dev", "meta", "blog", "hugo", "twitter", "social-media"]
title = "Facebook Open Graph Debugger & Twitter Cards Validator"
thumbnail = "pimages/00004-twitter-card-validator.jpg"
+++

Blogging engines such as WordPress and Ghost should take care of images and [Facebook Open Graph](https://developers.facebook.com/docs/sharing/opengraph) integration for you. Unfortunately, that's not the case with Hugo and Octopress. I did a bit of googling and found that we need to have a meta tag `og:image` in the header for Facebook to show your image when posting.

### Meta-tags for HTML Header

```html
<!-- Provide absolute URLs -->
<!-- Sample from https://rickmanelius.com/article/sharing-facebook-how-improve-your-results-customizing-image-title-and-summary-text -->
<meta name="title" content="Page Title for Search Engines Results | Website Name" />
<meta name="description" content="Page Description for Search Engine Results" />
<meta property="og:title" content="Page Title for Facebook" />
<meta property="og:description" content="Page Description for Facebook" />
<meta property="og:image" content="https://www.sitename.com/image-for-facebook.png" />
<meta property="twitter:card" content="summary" />
<meta property="twitter:description" content="Page Description for Twitter." />
<meta property="twitter:title" content="Page Title for Twitter" />
<meta property="twitter:image" content="https://www.sitename.com/image-for-twitter.png" />
```

### Be Lazy with Facebook Open Graph Debugger

It could be quite tedious to change theme, so [Facebook offers Open Graph Debugger](https://developers.facebook.com/tools/debug/og/object/). You just need to provide your URL and all the work is done for you. Check out the screenshot:

![Facebook Open Graph Debugger](/pimages/00003-facebook-open-graph-debugger.jpg)

### Little Help from Twitter Card Validator

The [Twitter Card Validator](https://cards-dev.twitter.com/validator) won't do the dirty jobs for you, but it will tell you briefly what is missing:

![Twitter Card Validator](/pimages/00004-twitter-card-validator.jpg)

## References

* [Brendan Quinn on Hugo & Facebook Open Graph](http://brendan-quinn.xyz/post/working-with-hugos-internal-partial-templates-facebook-and-open-graph/).
* [Sharing on Facebook: How to Improve Your Results by Customizing the Image, Title, and Summary Text](https://rickmanelius.com/article/sharing-facebook-how-improve-your-results-customizing-image-title-and-summary-text)
* [How to use html meta tags to tailor your story when your content is shared across social media platforms](https://www.newmediadenver.com/blog/using-html-meta-tags-to-tailor-your-story)
* [Twitter Cards](https://dev.twitter.com/cards/overview)
* [Facebook Open Graph](https://developers.facebook.com/docs/sharing/opengraph)