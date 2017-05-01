+++
css = []
date = "2017-05-01T11:05:17+01:00"
description = ""
draft = false
highlight = true
scripts = []
tags = ["pysmile", "python", "dev", "image-processing", "pillow", "gif", "png", "transparency"]
title = "PySmile: Transparency Preservation"

+++

I have been writing [PySmile](https://github.com/vietlq/PySmile) - a tool for batch processing (resize, convert) images. Resizing by ratio, to fixed width, fixed height was easy-peasy. So was conversion from non-transparent formats to any format (from JPG, BMP to JPG, BMP, PDF, PNG, GIF). However, there was a challenge converting transparent PNG to other formats: JPG, BMP, GIF, PDF. Have a look at the output:

![Bad JPEG from transparent PNG](/pimages/00007-bad-jpeg-from-transparent-png.jpg)

There are 2 problems with the output:

* The background was white - We can tolerate this for non-transparent formats, otherwise what colour the transparent pixels should be?
* The surrounding boxes around the text was black - This is the real problem we need to fix

## Solution for Non-transparent Output Formats (BMP, JPEG, PDF, GIF)

The problem with black surrounding boxes happens for all output formats (except PNG): BMP, GIF, [JPEG](/pimages/00007-bad-jpeg-from-transparent-png.jpg), [PDF](/pimages/00008-bad-pdf-from-transparent-png.pdf).

I did a bit of [digging and the solution](http://stackoverflow.com/a/9459208/284318) was rather simple:

* Only do the following steps for PNG images in `RGBA` mode
* Create a new image in `RGB` mode with the same size as the original, pre-fill it with default colour (I chose white, but that's customisable)
* Extract *alpha channel* from the original image and *treat it as a mask*
* Paste the original image to new image with mask = alpha channel

By doing this we will remove the black surrounding boxes and also preserve quality of the original image on the pasted content. Follow [this link](https://gist.github.com/vietlq/475f156b0fef3eae337dffa0eb04441a#file-pure_pil_alpha_to_color_v2-py) to see the code. Now we have high quality output:

![Best JPEG from transparent PNG](/pimages/00011-best-jpeg-from-transparent-png.jpg)

There is a simplistic implementation that replaces transparent pixels with a specified colour (white by default, but customisable). The resulting image of [such algorithm is blocky](https://gist.github.com/vietlq/475f156b0fef3eae337dffa0eb04441a#file-alpha_to_color-py) and its performance is worse that the one above. So, we have no reason to use it. Click to see for yourself: [Blocky JPEG from transparent PNG](/pimages/00009-improved-jpeg-from-transparent-png.jpg)

You can also check the PDF files that were produced for each algorithm:

* [Faulty with black surrounding boxes](/pimages/00008-bad-pdf-from-transparent-png.pdf)
* [Improved but blocky](/pimages/00010-improved-pdf-from-transparent-png.pdf)
* [Best quality PDF](/pimages/00012-best-pdf-from-transparent-png.pdf)

## Solution for Transparent Output Formats (PNG, GIF)

Are we done yet? Not quite. Above we have saved [GIF images that are not transparent](/pimages/00013-better-gif-non-transparent.gif). Note that GIF does offer transparency and requires `Palette` mode. So for perfection, we need to accomplish one more task: Preserve transparency for GIF & PNG files when converting/resizing from GIF & PNG.

Solution for this problem is rather straightforward. I did a [bit of googling](http://www.pythonclub.org/modules/pil/convert-png-gif) and adapted to my algorithm:

* If we are converting to PNG, go ahead, remember to preserve image `info`
* For GIF output, if the original image's mode is `Palette`, save with transparency by using image `info`
* For GIF output, if the original image's mode is `RGBA`, convert to `RGB` like we did above
* Afterwards we need to convert to `Palette` mode for GIF and have a mask extracted
* Create a mask from alpha channel of the `RGBA` image:
  * If 0 <= alpha <= 128 => transparency mask = 255 (transparent)
  * If 129 <= alpha <= 255 => transparency mask = 0 (opaque)
* We need to paste the `Palette` image created to new image through the mask
* Now save the resulting `Palette` image and voila, you have transparent GIF with highest quality possible!

![Best quality transparent GIF](/pimages/00017-best-gif-transparent-half.gif)

Feel free to check the GIF files that were produced for each algorithm:

* [Non-transparent GIF with good quality](/pimages/00013-better-gif-non-transparent.gif)
* [Transparent GIF with some blocks](/pimages/00014-worse-gif-transparent.gif)
* [Best quality transparent GIF](/pimages/00015-best-gif-transparent.gif)

Devil is in the details. Check out [my implementation](https://gist.github.com/vietlq/475f156b0fef3eae337dffa0eb04441a#file-convert_to_palette-py).

## References

* PySmile GitHub: [https://github.com/vietlq/PySmile](https://github.com/vietlq/PySmile)
* [Transparent RGBA to RGB, preserve quality](http://stackoverflow.com/a/9459208/284318)
* [PySmile Transparency Preservation: Implementation Details](https://gist.github.com/vietlq/475f156b0fef3eae337dffa0eb04441a)
* [PIL Tutorial: Converting Between PNG and GIF](http://www.pythonclub.org/modules/pil/convert-png-gif)
