.PHONY: help all static deploy_github

help:
	@echo "help             Show this help"
	@echo "all              Do all (deploy_github)"
	@echo "deploy_github    Generate static pages and deploy to github.io"
	@echo "static           Generate static pages"
	@echo "site             Generate static pages and rsync to a server"

all: deploy_github

deploy_github:
	./deploy_github.sh

static:
	rm -rf _deploy/*
	hugo -d _deploy

timestamp:=$(shell /bin/date "+%FT%T%z")

site:
	rm -rf _dsite/* _dsite/.DS_Store
	#hugo -b 'https://simpleit.us/' --canonifyURLs -d _dsite
	#hugo -b 'https://simpleit.us/' -d _dsite
	hugo -b '/' -d _dsite
	cp -prf data/simpleit.us/.well-known _dsite/
	cp dat.json _dsite/
	rsync -avz --partial --progress --delete _dsite/ blog01:~/blog-deep-thoughts/
	#rsync -avz --partial --progress --delete _dsite/ simpleit.us:~/blog-deep-thoughts/
