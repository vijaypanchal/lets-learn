# Build library
cd lib/static
make all
cd ..
cd dynamic
make all
cd ../..
# Build App
cd app
make all
cd ..
