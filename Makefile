.PHONY: static

static:
	rm -rf _deploy
	hugo -d _deploy
