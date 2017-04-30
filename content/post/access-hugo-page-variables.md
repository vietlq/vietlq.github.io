+++
css = []
date = "2017-04-30T17:15:58+01:00"
description = "Hugo Blogging Series: Access Hugo Page Variables"
draft = false
highlight = true
scripts = []
tags = []
title = "Access Hugo Page Variables"

+++

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

## References

* [Hugo Page Variables](https://hugodocs.info/variables/page/)
* [Hugo Scratch](https://hugodocs.info/functions/scratch/)
* [Hugo Shortcodes](https://hugodocs.info/content-management/shortcodes/)