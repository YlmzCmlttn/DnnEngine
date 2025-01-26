if [ ! -d "3rdParty" ]; then
    mkdir 3rdParty
    echo "Created 3rdParty directory."
else
    echo "3rdParty directory already exists."
fi

cd 3rdParty
wget https://github.com/opencv/opencv/archive/refs/tags/4.10.0.zip
unzip 4.10.0.zip
rm ./4.10.0.zip

cd opencv-4.10.0
mkdir build
cd build

cmake -D CMAKE_BUILD_TYPE=Release \
      -D CMAKE_INSTALL_PREFIX=../../OpenCV-4.10 ..

make -j$(nproc) install

cd ../../
rm -rf ./opencv-4.10.0