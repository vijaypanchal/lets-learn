#!/bin/sh
# Create all build folder
echo "Creating Folders.."
mkdir build-aarch64 -p 
mkdir build-armhf -p 
mkdir build-aarch64-neon -p 
mkdir build-armhf-neon -p 
echo "Building all Configurations.."
cd build-aarch64
cmake .. -DARMHF=0
make all
cd ..
cd build-armhf
cmake .. -DARMHF=1
make all
cd ..
cd build-aarch64-neon
cmake .. -DARMHF=0 -DNEON=1
make all
cd ..
cd build-armhf-neon
cmake .. -DARMHF=1 -DNEON=1
make all
cd ..
#echo "-------------------------"
#echo "Running without Neon..."
#echo "For ARCH Aarch64 : "
#./build-aarch64/main
#echo "For ARCH Armhf : "
#./build-armhf/main
echo "-------------------------"
echo "Running with Neon..."
echo "For ARCH Aarch64 : "
./build-aarch64-neon/main
echo "For ARCH Armhf : "
./build-armhf-neon/main
echo "-------------------------"
