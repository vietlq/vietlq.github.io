+++
css = []
date = "2017-04-30T17:15:58+01:00"
description = "Hugo Blogging Series: Access Hugo Page Variables"
draft = false
highlight = true
scripts = []
tags = ["hugo", "theme", "fb", "opengraph", "twitter", "social-media", "meta", "image"]
title = "Access Hugo Page Variables"
thumbnail = "pimages/00005-good-twitter-card-validator.jpg"
+++

## Challenge

Earlier today I had difficulty integrating with Facebook Open Graph and called their [Open Graph Debugger]({{< relref "open-graph-debugger.md" >}}) for help. I also used [Twitter Card Validator](https://cards-dev.twitter.com/validator) to verify if the page can be rendered as a Twitter card. There were still missing pieces from meta data. The complete Open Graph and Twitter card meta data [would look like this](https://rickmanelius.com/article/sharing-facebook-how-improve-your-results-customizing-image-title-and-summary-text):

```html
<!-- Provide absolute URLs -->
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

I'm using a theme called `hugo-geo` which does not have the following meta tags:

```html
<meta name="title">
<meta property="og:image">
<meta property="twitter:card">
<meta property="twitter:description">
<meta property="twitter:title">
<meta property="twitter:image">
```

So now I want to populate those fields by overriding the partial theme `layouts/partials/head.html`.

## Solution

There's certainly lack of documentation on how to access page variables in Hugo but I found a piece that could help: [Hugo Page Variables](https://hugodocs.info/variables/page/).

To populate `<meta name="title">` is easy, we could reuse the variable `.Title` provided by all pages. Now the challenge is printing a custom image for `<meta property="og:image">` and `<meta property="twitter:image">`. After digging and googling, I found 3 ways for accessing custom page variables (in this case `thumbnail`):

```
{{ if $.Page.Params.thumbnail }}
<meta property="og:image" content="{{ .Site.BaseURL }}{{ $.Page.Params.thumbnail }}">
{{ end }}

{{ if .Params.thumbnail }}
<meta property="og:image" content="{{ .Site.BaseURL }}{{ .Params.thumbnail }}">
{{ end }}

{{ if $.Params.thumbnail }}
<meta property="og:image" content="{{ .Site.BaseURL }}{{ $.Params.thumbnail }}">
{{ end }}
```

To make this work, remember to add a new variable `thumbnail` to your page's front matter:

```
+++
thumbnail = "pimages/00005-good-twitter-card-validator.jpg"
+++
```

```
---
thumbnail = "pimages/00005-good-twitter-card-validator.jpg"
---
```

To see concrete implementation of the partial template `head.html`, check [my gist](https://gist.github.com/vietlq/d1c7ecfb20ce7beac4a7f4df746c797c). I created a pull request for `hugo-neo` and hope that the author will accept it: [https://github.com/alexurquhart/hugo-geo/pull/27](https://github.com/alexurquhart/hugo-geo/pull/27)

Now Twitter and Facebook give us good validation results:

![Validated Twitter Card](/pimages/00005-good-twitter-card-validator.jpg)

![Facebook Post with Preview](/pimages/00006-good-facebook-open-graph.jpg)

If you want large image in the summary, [simply add](https://dev.twitter.com/cards/types/summary-large-image):

```
<meta name="twitter:card" content="summary_large_image">
```

## References

* [Hugo Page Variables](https://hugodocs.info/variables/page/)
* [Hugo Scratch](https://hugodocs.info/functions/scratch/)
* [Hugo Shortcodes](https://hugodocs.info/content-management/shortcodes/)
* [Twitter Summary Large Image](https://dev.twitter.com/cards/types/summary-large-image)