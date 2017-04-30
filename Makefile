.PHONY: static

static:
	rm -rf _deploy/*
	hugo -d _deploy

deploy:
	timestamp=$(date +"+%FT%T%z")
	cd _deploy && git add . && git commit -a -m "Commited at ${timestamp}" && git push
