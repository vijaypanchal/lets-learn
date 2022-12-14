# Create all build folder
echo "-------------------------"
echo "Creating Folders.."
echo "-------------------------"
mkdir build-aarch64 -p 
mkdir build-armhf -p 
mkdir build-aarch64-neon -p 
mkdir build-armhf-neon -p 
echo "-------------------------"
echo "Building all Configurations.."
echo "-------------------------"
cd build-aarch64
cmake .. -DARMHF=0
make all
echo "-------------------------"
cd ..
cd build-armhf
cmake .. -DARMHF=1
make all
echo "-------------------------"
cd ..
cd build-aarch64-neon
cmake .. -DARMHF=0 -DNEON=1
make all
echo "-------------------------"
cd ..
cd build-armhf-neon
cmake .. -DARMHF=1 -DNEON=1
make all
echo "-------------------------"
cd ..