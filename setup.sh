export libpath=$PWD/build/exlibs
export projectroot=$PWD

if ! cd $libpath
then
    mkdir $PWD/build
    mkdir $libpath
fi

export proc_count=$(nproc --all)

if [[ $OSTYPE == msys ]]; then 
    echo "* MinGW-w64 detected."
    echo "* Installing dependencies..."
    pacman -S git gcc make cmake bison doxygen ruby \
     mingw-w64-ucrt-x86_64-SDL2 mingw-w64-ucrt-x86_64-SDL2_image \
     mingw-w64-ucrt-x86_64-SDL2_ttf mingw-w64-ucrt-x86_64-openal \
     mingw-w64-ucrt-x86_64-physfs mingw-w64-ucrt-x86_64-pixman \
     mingw-w64-ucrt-x86_64-libwebp mingw-w64-ucrt-x86_64-zlib \
     mingw-w64-ucrt-x86_64-bzip2 mingw-w64-ucrt-x86_64-libvorbis \
     mingw-w64-ucrt-x86_64-libogg mingw-w64-ucrt-x86_64-zeromq \
     mingw-w64-ucrt-x86_64-boost mingw-w64-ucrt-x86_64-libpng \
     mingw-w64-ucrt-x86_64-libjpeg-turbo mingw-w64-ucrt-x86_64-libtiff \
     
else 
    if [[ "$(cat /etc/issue)" == Debian* || "$(cat /etc/issue)" == Ubuntu* ]]; then
        echo "* Debian Linux detected."
        echo "* Installing dependencies..."
        sudo apt install -y gcc make cmake bison doxygen ruby \
         libsdl2-dev libsdl2-image-dev libsdl2-ttf-dev libopenal-dev \
         libphysfs-dev libpixman-1-dev libwebp-dev libbz2-dev \
         libvorbis-dev libogg-dev libsodium-dev libboost-dev libpng-dev \
         libjpeg-dev libtiff-dev 

        echo "* ZeroMQ not found in Debian's repositories. Building from source..."
        git clone https://github.com/zeromq/libzmq.git $libpath/zmq
        cd $libpath/zmq
        ./autogen.sh
        ./configure --with-libsodium
        make -j$proc_count
        sudo make install
        sudo ldconfig
    fi
fi

echo "* Building libsigc++ from source..."
git clone https://github.com/libsigcplusplus/libsigcplusplus $libpath/sigc
cd $libpath/sigc
git checkout libsigc++-2-10
./autogen.sh --prefix=/ucrt64
make
if [[ $OSTYPE == msys ]]; then
    make install
else 
    sudo make install
fi

echo "* Building libnsgif from source..."
git clone https://github.com/jcupitt/libnsgif-autotools $libpath/libnsgif
cd $libpath/libnsgif
./autogen.sh
./configure
make -j$proc_count
if [[ $OSTYPE == msys ]]; then
    make install
else 
    sudo make install
fi

echo "* Building SDL_Sound from source..."
git clone https://github.com/icculus/SDL_sound $libpath/SDL_Sound
cd $libpath/SDL_Sound
cmake -B build -G "Unix Makefiles" -DCMAKE_INSTALL_PREFIX="/ucrt64"
cd build
make -j$proc_count
if [[ $OSTYPE == msys ]]; then
    make install
else 
    sudo make install
fi

echo "* Building ZMQPP Binding from source..."
git clone https://github.com/zeromq/zmqpp $libpath/zmqpp
cd $libpath/zmqpp
cmake . -G "Unix Makefiles" -DCMAKE_INSTALL_PREFIX="/ucrt64"
make -j$proc_count
if [[ $OSTYPE == msys ]]; then
    make install
else 
    sudo make install
fi

echo "* Building Ruby from source..."
git clone https://github.com/ruby/ruby $libpath/ruby
cd $libpath/ruby
./autogen.sh
./configure
make -j$proc_count
if [[ $OSTYPE == msys ]]; then
    make install
else 
    sudo make install
fi