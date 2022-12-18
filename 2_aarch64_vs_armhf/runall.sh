#!/bin/sh
#echo "-------------------------"
#echo "Running without Neon..."
#echo "For ARCH Aarch64 : "
#./build-aarch64/main
#echo ""
#echo "For ARCH Armhf : "
#./build-armhf/main
echo ""
echo "-------------------------"
echo "Running with Neon..."
echo "For ARCH Aarch64 : "
./build-aarch64-neon/main
echo ""
echo "-------------------------"
echo "For ARCH Armhf : "
./build-armhf-neon/main
echo ""

