#/bin/bash

export ANDROID_NDK=/home/hhsw/android-ndk-r19c

rm -r build_arm
mkdir build_arm && cd build_arm

cmake -DCMAKE_TOOLCHAIN_FILE=$ANDROID_NDK/build/cmake/android.toolchain.cmake \
	-DANDROID_ABI="armeabi-v7a" \
	-DANDROID_NDK=$ANDROID_NDK \
	-DANDROID_PLATFORM=android-23 \
	..

make -j4

cd ..

