export libpath=$PWD/build/exlibs
export projectroot=$PWD
if ! cd $libpath
then
mkdir $PWD/build
mkdir $libpath
fi

# Git URLs
export sdl2_url="https://github.com/libsdl-org/SDL.git"
export sdl2_path="$libpath/sdl"
export sdl2_image_url="https://github.com/libsdl-org/SDL_image.git"
export sdl2_image_path="$libpath/SDL_Image"
export sdl2_ttf_url="https://github.com/libsdl-org/SDL_ttf"
export sdl2_ttf_path="$libpath/SDL_ttf"
export openal_url="https://github.com/kcat/openal-soft.git"
export openal_path="$libpath/openal-soft"
export physfs_url="https://github.com/icculus/physfs.git"
export physfs_path="$libpath/physfs"
export pixman_url="https://github.com/freedesktop/pixman.git"
export pixman_path="$libpath/pixman"
export sdlsound_url="https://github.com/Ancurio/SDL_sound.git"
export sdlsound_path="$libpath/SDL_sound"
export sigc_url="https://github.com/libsigcplusplus/libsigcplusplus/archive/refs/tags/2.10.7.tar.gz"
export sigc_path="$libpath/libsigcplusplus-2.10.7"
export zlib_url="https://github.com/madler/zlib"
export zlib_path="$libpath/zlib"
export bzip2_url="git://sourceware.org/git/bzip2.git"
export bzip2_path="$libpath/bzip2"
export libnsgif_url="https://github.com/jcupitt/libnsgif-autotools"
export libnsgif_path="$libpath/libnsgif"
export ruby_url="https://github.com/ruby/ruby.git"
export ruby_path="$libpath/ruby"
export vorbis_url="https://github.com/xiph/vorbis"
export vorbis_path="$libpath/vorbis"
export ogg_url="https://github.com/gcp/libogg"
export ogg_path="$libpath/libogg"

# Non-git
# Boost C++ Libraries
export boost_url="https://boostorg.jfrog.io/artifactory/main/release/1.78.0/source/boost_1_78_0.tar.gz"
export boost_path="$libpath/boost"
# libpng (required for SDL_Image)
export libpng_url="https://github.com/glennrp/libpng"
export libpng_path="$libpath/libpng"

export job_count=$(nproc --all)

# Functions.
downloadAndUntarGZ() {
    if [ ! -f $2.tar.gz ]
    then
        wget $1 -O $2.tar.gz
        mkdir $2
        tar xvzf $2.tar.gz -C $2
    else 
        echo "$2.tar.gz is already downloaded."
    fi
}
downloadAndUntarXZ() {
    if [ ! -f $2.tar.xz ]
    then
        wget $1 -O $2.tar.xz
        mkdir $2
        tar xvzf $2.tar.xz -C $2
    else
        echo "$2.tar.xz is already downloaded."
    fi
}
downloadAndUnzip() {
    if [ ! -f $2.zip ]
    then
        wget $1 -O $2.zip
        unzip $2.zip -d $2
    else
        echo "$2.zip is already downloaded."
    fi
}
makeinstall() {
    if [ "$OSTYPE" = "msys" ]; then
        make install
    else 
        sudo make install
    fi
}
# Main code.

echo "* Downloading zlib."
git clone $zlib_url $zlib_path
cd $zlib_path
cmake . -G "Unix Makefiles" -DCMAKE_BUILD_TYPE=Release -DBUILD_SHARED_LIBS=OFF -DWITH_FUZZERS=ON -DWITH_CODE_COVERAGE=ON -DWITH_MAINTAINER_WARNINGS=ON -DCMAKE_INSTALL_PREFIX="$libpath/zlib_dest"
make -j $job_count
makeinstall

echo "* Downloading bzip2."
git clone $bzip2_url $bzip2_path
cd $bzip2_path
make -j $job_count PREFIX="$libpath/bzip2_dest"
make install PREFIX="$libpath/bzip2_dest"

echo "* Downloading libogg"
git clone $ogg_url $ogg_path
cd $ogg_path
./autogen.sh
./configure --prefix="$libpath/libogg_dest"
PKG_CONFIG_PATH=$PKG_CONFIG_PATH:$libpath/libogg_dest/lib/pkgconfig
make -j $job_count
makeinstall

echo "* Downloading boost."
downloadAndUntarGZ $boost_url $boost_path
cd $boost_path/boost_1_78_0
./bootstrap.sh --prefix="$libpath/boost_dest"
if [ "$OSTYPE" = "msys" ]; then
    ./b2 install -j $job_count --prefix="$libpath/boost_dest"
else
    sudo ./b2 install -j $job_count --prefix="$libpath/boost_dest"
fi

echo "* Downloading PhysFS."
git clone $physfs_url $physfs_path
cd $physfs_path
echo "* Building."
cmake -DCMAKE_INSTALL_PREFIX="$libpath/physfs_dest" -G "Unix Makefiles"
cd build
make -j $job_count
makeinstall

echo "* Downloading pixman."
git clone $pixman_url $pixman_path
cd $pixman_path
echo "* Building pixman."
./autogen.sh
./configure --prefix="$libpath/pixman_dest"
make -j $job_count
makeinstall

echo "* Downloading sigc++"
downloadAndUntarGZ $sigc_url $sigc_path
cd $sigc_path/libsigcplusplus-2.10.7
echo "* Building sigc++."
./autogen.sh
./configure --prefix="$libpath/sigcpp_dest"
make -j $job_count
makeinstall

echo "* Downloading libpng."
git clone $libpng_url $libpng_path
echo "* Building libpng."
cd $libpng_path
./configure --prefix="$libpath/libpng_dest"
make -j $job_count
make check
makeinstall

echo "* Downloading libnsgif."
git clone $libnsgif_url $libnsgif_path
cd $libnsgif_path
echo "* Building libnsgif."
./autogen.sh
./configure --prefix="$libpath/libnsgif_dest"
make -j $job_count
makeinstall

echo "* Downloading SDL2."
git clone $sdl2_url $sdl2_path
cd $sdl2_path
mkdir build
cd build
../configure --prefix="$libpath/sdl2_dest"
export SDL_LIBS="$libpath/sdl2_dest/lib"
export SDL2_INCLUDE_DIR="$libpath/sdl2_dest/include"
PATH="$PATH:$libpath/sdl2_dest/bin"
make -j $job_count
makeinstall

echo "* Downloading vorbis."
git clone $vorbis_url $vorbis_path
echo "* Building vorbis."
cd $vorbis_path
./autogen.sh
./configure --prefix="$libpath/vorbis_dest" --with-ogg-libraries=$libpath/libogg_dest/lib --with-ogg-includes=$libpath/libogg_dest/include
make -j $job_count
make install

echo "* Downloading OpenAL Soft."
git clone $openal_url $openal_path
echo "* Building and installing OpenAL Soft."
cd $openal_path
git checkout tags/1.21.1
cmake . -G "Unix Makefiles" -DCMAKE_INSTALL_PREFIX="$libpath/openal_dest"
make -j $job_count
makeinstall

echo "* Downloading SDL Sound from Ancurio."
git clone https://github.com/icculus/SDL_sound $sdlsound_path
cd $sdlsound_path
echo "* Building and installing SDL_Sound."
cmake . -G "Unix Makefiles" -DCMAKE_INSTALL_PREFIX="$libpath/sdl_sound_dest" -DSDL2_INCLUDE_DIR="$libpath/sdl2_dest/include/SDL2"
LIBRARY_PATH=$libpath/sdl2_dest/lib 
make -j $job_count
make install

echo "* Downloading SDL_Image."
git clone $sdl2_image_url $sdl2_image_path
cd $sdl2_image_path
echo "* Building SDL_Image."
./configure  --prefix="$libpath/sdl2_image_dest"
make -j $job_count
makeinstall

echo "* Downloading SDL_ttf."
git clone $sdl2_ttf_url $sdl2_ttf_path
cd $sdl2_ttf_path
echo "* Building SDL_ttf"
./configure --prefix="$libpath/sdl2_ttf_dest"
make -j $job_count
makeinstall

echo "* Now, final boss... Downloading ruby."
git clone $ruby_url $ruby_path
cd $ruby_path
git checkout tags/v3_1_0
echo "* Building"
./autogen.sh
./configure --enable-shared --disable-install-doc
make -j $job_count
make install DESTDIR="$libpath/ruby_dest"

echo "* All done! Now, you can build ModShot."
