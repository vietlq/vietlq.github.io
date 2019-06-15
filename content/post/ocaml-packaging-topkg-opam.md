+++
draft = false
tags = ["tips", "dev", "packaging", "opam", "topkg", "ocaml"]
categories = []
date = "2018-05-28T15:41:55+01:00"
title = "OCaml Packaging With Topkg and OPAM"
description = "A short guide to packaging OCaml libraries with Topkg and OPAM."
thumbnail = "pimages/00038-ocaml-logo.png"
+++

## Dependencies

First and foremost, you must have OPAM installed. Then you need to install the following packages:

```
$ opam install topkg topkg-care topkg-jbuilder
```

## Boilerplate Code

Given you have your library tested and ready for publishing, you need to add the files `ppx_getenv01.opam` and `pkg/pkg.ml` at the top:

The OPAM file (`ppx_getenv01.opam`):

```
opam-version: "1.2"
name: "ppx_getenv01"
maintainer: "Viet Le <XXXX@gmail.com>"
authors: "Viet Le <XXXX@gmail.com>"
homepage: "https://github.com/vietlq/ppx_getenv01"
bug-reports: "https://github.com/vietlq/ppx_getenv01/issues"
license: "MIT"
dev-repo: "https://github.com/vietlq/ppx_getenv01"
tags: [ "syntax" ]
build: [
  make
]
build-test: [
  "ocamlbuild" "-classic-display" "-use-ocamlfind" "./ppx_getenv01" "--"
]
install: [make "install"]
remove: ["ocamlfind" "remove" "ppx_getenv01"]
depends: [
  "ocamlfind" {build}
]
available: [ocaml-version >= "4.02.0"]
```

The Topkg file (`pkg/pkg.ml`):

```
#!/usr/bin/env ocaml
#use "topfind"
#require "topkg-jbuilder"

open Topkg

let publish =
  Pkg.publish ~artefacts:[`Distrib] ()

let () =
  Topkg_jbuilder.describe ~publish ()
```

See the minimal sample: https://raw.githubusercontent.com/vietlq/ppx_getenv01/master/pkg/pkg.ml

Hard-core people can read: https://github.com/dbuenzli/topkg/tree/master/pkg

## Add the File CHANGES.md

It's absolutely necessary to keep track of changes and have a user-friendly way to communicate changes to our users. Topkg requires every package to have the file `CHANGES.md` in this format:

```
v0.0.1 2018-05-28 London
------------------------

- Test release.
```

You can have a look at a productive quality changes log file: https://github.com/dbuenzli/topkg/blob/master/CHANGES.md

## Add a Tag

After getting all boilerplate code ready, let's tag our code for release:

```
$ topkg tag
Tagged version v0.0.1
```

## Initial Commit Missing Files

```
$ topkg distrib
Cloning into '_build/ppx_getenv01-0.0.1.build'...
done.
Note: checking out '7b8e338485eea9a647819555a909207b706c3015'.

You are in 'detached HEAD' state. You can look around, make experimental
changes and commit them, and you can discard any commits you make in this
state without impacting any branches by performing another checkout.

If you want to create a new branch to retain commits you create, you may
do so (now or later) by using -b with the checkout command again. Example:

  git checkout -b <new-branch-name>

Wrote archive _build/ppx_getenv01-0.0.1.tbz

Linting distrib in _build/ppx_getenv01-0.0.1
[ OK ] File CHANGES.md is present.
[FAIL] File LICENSE.md is present.
[FAIL] File README.md is present.
[ OK ] File ppx_getenv01.opam is present.
[FAIL] lint opam file ppx_getenv01.opam:
       opam lint -s messages:
       Errors found in ~/projects/ppx_getenv01/_build/ppx_getenv01-0.0.1/ppx_getenv01.opam:
                   error  3: Invalid field: version
                   error 39: Command 'make' called directly, use the built-in variable
                     instead
[FAIL] lint _build/ppx_getenv01-0.0.1 failure: 3 errors.

Building package in _build/ppx_getenv01-0.0.1
[ OK ] package builds

Running package tests in _build/ppx_getenv01-0.0.1
[ OK ] package tests

Distribution for ppx_getenv01 v0.0.1
Commit 7b8e338485eea9a647819555a909207b706c3015
Archive _build/ppx_getenv01-0.0.1.tbz
```

Have a quick look at the commit: https://github.com/vietlq/ppx_getenv01/commit/ea540b9c732145330b82daabb8977349bbcfdff9

## Remove Invalid Field and Use Built-in Make

```
$ topkg distrib
Cloning into '_build/ppx_getenv01-0.0.1-1-gea540b9.build'...
done.
Note: checking out 'ea540b9c732145330b82daabb8977349bbcfdff9'.

You are in 'detached HEAD' state. You can look around, make experimental
changes and commit them, and you can discard any commits you make in this
state without impacting any branches by performing another checkout.

If you want to create a new branch to retain commits you create, you may
do so (now or later) by using -b with the checkout command again. Example:

  git checkout -b <new-branch-name>

Wrote archive _build/ppx_getenv01-0.0.1-1-gea540b9.tbz

Linting distrib in _build/ppx_getenv01-0.0.1-1-gea540b9
[ OK ] File CHANGES.md is present.
[ OK ] File LICENSE.md is present.
[ OK ] File README.md is present.
[ OK ] File ppx_getenv01.opam is present.
[FAIL] lint opam file ppx_getenv01.opam:
       opam lint -s messages:
       Errors found in ~/projects/ppx_getenv01/_build/ppx_getenv01-0.0.1-1-gea540b9/ppx_getenv01.opam:
                   error  3: Invalid field: version
                   error 39: Command 'make' called directly, use the built-in variable
                     instead
[FAIL] lint _build/ppx_getenv01-0.0.1-1-gea540b9 failure: 1 errors.

Building package in _build/ppx_getenv01-0.0.1-1-gea540b9
[ OK ] package builds

Running package tests in _build/ppx_getenv01-0.0.1-1-gea540b9
[ OK ] package tests

Distribution for ppx_getenv01 v0.0.1-1-gea540b9
Commit ea540b9c732145330b82daabb8977349bbcfdff9
Archive _build/ppx_getenv01-0.0.1-1-gea540b9.tbz
```

See the changes here: https://github.com/vietlq/ppx_getenv01/commit/6fd02aaa53e1ac15546a51b999eb6bf58e91b481

## Clean and Green Version

If you already tagged like above, and made changes afterwards, then you have to updated the file `CHANGES.md` to add a new tag, and run `topkg  tag` again. Only then you can run:

```
$ topkg tag
Tagged version v0.0.2

$ topkg distrib
Cloning into '_build/ppx_getenv01-0.0.2.build'...
done.
Wrote archive _build/ppx_getenv01-0.0.2.tbz

Linting distrib in _build/ppx_getenv01-0.0.2
[ OK ] File CHANGES.md is present.
[ OK ] File LICENSE.md is present.
[ OK ] File README.md is present.
[ OK ] File ppx_getenv01.opam is present.
[ OK ] lint opam file ppx_getenv01.opam.
[ OK ] lint _build/ppx_getenv01-0.0.2 success

Building package in _build/ppx_getenv01-0.0.2
[ OK ] package builds

Running package tests in _build/ppx_getenv01-0.0.2
[ OK ] package tests

Distribution for ppx_getenv01 v0.0.2
Commit b83fdd26bcc64c654cc4b3ae0de082bd1cab67fb
Archive _build/ppx_getenv01-0.0.2.tbz
```

## Publish the Tag

Now packaging is done, let's publish our work to GitHub with this single command:

```
$ topkg publish
Counting objects: 1, done.
Writing objects: 100% (1/1), 167 bytes | 0 bytes/s, done.
Total 1 (delta 0), reused 0 (delta 0)
To git@github.com:vietlq/ppx_getenv01.git
 * [new tag]         v0.0.2 -> v0.0.2
```

See the results of our work: https://github.com/vietlq/ppx_getenv01/releases/tag/v0.0.2

## References

* https://mirage.io/wiki/packaging
* https://github.com/dbuenzli/topkg
* https://github.com/mirage/mirage-block-unix/blob/v2.8.1/lib/jbuild
* https://github.com/samoht/topkg-jbuilder
* https://github.com/ocaml/dune
* https://keepachangelog.com/en/0.3.0/
