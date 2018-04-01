.PHONY: all static deploy

all: static site deploy

static:
	rm -rf _deploy/*
	hugo -d _deploy

timestamp := $(shell /bin/date "+%FT%T%z")
deploy:
	cd _deploy && git add . && git commit -a -m "Committed at ${timestamp}" && git push

site:
	rm -rf _dsite/* _dsite/.DS_Store
	#hugo -b 'https://simpleit.us/' --canonifyURLs -d _dsite
	#hugo -b 'https://simpleit.us/' -d _dsite
	hugo -b '/' -d _dsite
	rsync -avz --partial --progress --delete _dsite/ blog01:~/blog-deep-thoughts/
	#rsync -avz --partial --progress --delete _dsite/ simpleit.us:~/blog-deep-thoughts/
