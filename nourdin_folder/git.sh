#!/bin/sh
if [ "$1" = "new" ];
then git init && git add . && git commit -m "first commit" && git branch -M main && git remote add origin $2  && git push -u origin main
fi;

if [ "$1" = "old" ];
then git add . && git commit -m $2 && git push -u origin main
fi;

if [ "$1" = "intra" ]
then git remote remove origin  && git remote add origin $2 && git add . && git commit -m "push to intra"  && git push -u origin main
fi;

if [ "$1" = "git_hub" ]
then git remote remove origin  && git remote add origin $2 && git add . && git commit -m "first commit"  && git push -u origin main
fi;