#!/bin/bash -x

set -e

rm -rf _deploy && make static && cd _deploy && export CST_GIT_REMOTE=$(git remote -v | grep '^origin\b' | awk '{print $2}' | sort -u) && echo $CST_GIT_REMOTE && git init . && git remote add publish $CST_GIT_REMOTE && git add . && git commit -a -m"generated at $(date +%Y%m%dT%H%M%S)" && git push -u publish master --force && cd -
