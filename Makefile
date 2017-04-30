.PHONY: all static deploy

all: static deploy

static:
	rm -rf _deploy/*
	hugo -d _deploy

timestamp := $(shell /bin/date "+%FT%T%z")
deploy:
	cd _deploy && git add . && git commit -a -m "Committed at ${timestamp}" && git push
