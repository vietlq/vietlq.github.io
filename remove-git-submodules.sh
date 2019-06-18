#!/bin/bash -x

#set -e

# https://stackoverflow.com/questions/12641469/list-submodules-in-a-git-repository
# https://stackoverflow.com/a/36593218/128028
# https://stackoverflow.com/a/7646931/128028 
for repo in $(git config --file .gitmodules --get-regexp path | awk '{ print $2 }')
do
#git rm --cached ${repo}
#rm -rf .git/modules/${repo}
#rm -rf ${repo}
git config -f .git/config --remove-section submodule.${repo}
git config -f .gitmodules --remove-section submodule.${repo}
git rm --cached ${repo}
rm -rf ${repo}
rm -rf .git/modules/${repo}
done
