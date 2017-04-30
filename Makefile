.PHONY: static

static:
	rm -rf _deploy/*
	hugo -d _deploy

deploy:
	cd _deploy
	git add .
	timestamp=$(date +"+%FT%T%z")
	git commit -a -m "Commited at ${timestamp}"
	git push