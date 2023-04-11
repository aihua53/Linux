#!/bin/bash

function Usage
{
  echo "Usage: ./make.sh <platform>
  arch:
    1  x-linux-x86_64
    2  x-arm64-v8a"
}

function OSType
{
  unameOut="$(uname -s)"
  case "${unameOut}" in
      Linux*)     machine=linux;;
      Darwin*)    machine=darwin;;
      CYGWIN*)    machine=cygwin;;
      MINGW*)     machine=mingw;;
      *)          machine="UNKNOWN:${unameOut}"
  esac
  echo ${machine}
}

if [[ $# -lt 1 ]]; then
  Usage
  exit 1
fi

PLATFORM="$1"
OSTYPE=$(OSType)

case "$PLATFORM" in
  1)
    echo "Not support now: $PLATFORM"
    exit 1
    if [ "$OSTYPE" = "darwin" ]; then
      echo "Not support compile on $OSTYPE at $PLATFORM"
      exit 1
    fi
    C_COMPILER=gcc
    CXX_COMPILER=g++
    LDFLAGS="-L../lisart-lib/x86_64 -llisa -ldl"
    ;;
  2)
    ANDROID_NDK_TOOLCHAIN=${ANDROID_NDK_ROOT}/toolchains/llvm/prebuilt/${OSTYPE}-x86_64
    if [ ! -d "${ANDROID_NDK_TOOLCHAIN}" ]; then
      echo "Please install Android NDK(r19c) first. Download form https://li.feishu.cn/file/boxcn1AsTtvSMLHqau9M0rAVhKd, then set ANDROID_NDK_ROOT environment variable"
      exit 1
    fi
    C_COMPILER=${ANDROID_NDK_TOOLCHAIN}/bin/aarch64-linux-android23-clang
    CXX_COMPILER=${ANDROID_NDK_TOOLCHAIN}/bin/aarch64-linux-android23-clang++
    LDFLAGS="-L../lisart-lib/arm64-v8a -lssai_lisa -ldl"
    ;;
  *)
    echo "Unknown platform: $PLATFORM"
    exit 1
    ;;
esac

${CXX_COMPILER} --std=c++11 -g -O3 \
-I ../api/ \
${LDFLAGS} \
-o test_crn test_crn.cpp \

mv test_crn bin/
