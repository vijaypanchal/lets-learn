#!/bin/sh
# clean library
cd lib/static
make clean
cd ..
cd dynamic
make clean
cd ../..
# clean App
cd app
make clean
cd ..
