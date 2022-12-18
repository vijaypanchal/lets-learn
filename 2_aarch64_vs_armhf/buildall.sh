# Create all build folder
echo "-------------------------"
echo "Creating Folders.."
echo "-------------------------"
#mkdir build-aarch64 -p 
#mkdir build-armhf -p 
mkdir build-aarch64-neon -p 
mkdir build-armhf-neon -p 
echo "-------------------------"
echo "Building all Configurations.."
echo "-------------------------"
#cd build-aarch64
#cmake .. -DARMHF=0
#make all
#echo "-------------------------"
#cd ..
#cd build-armhf
#cmake .. -DARMHF=1
#make all
#cd ..
echo "-------------------------"
cd build-aarch64-neon
echo $PWD
cmake -DARMHF=0 -DNEON=1 ..
make all
cd ..
echo "-------------------------"
cd build-armhf-neon
echo $PWD
cmake -DARMHF=1 -DNEON=1 ..
make all
cd ..