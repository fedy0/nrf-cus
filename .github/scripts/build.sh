#!/bin/bash

set -e

#ARM_GCC_TOOL_IN_HOST="`dirname $(which arm-none-eabi-gcc)`/"
#ARM_GCC_VERSION="``"
#NRF_SDK_ROOT_PATH=/home/fedy0/Documents/repo/nRF5_SDK_15.3.0_59ac345

# Comment out the default installation path and version of ARM GCC 
#sed -i  "s/GNU_INSTALL_ROOT/\#GNU_INSTALL_ROOT/" ${NRF_SDK_ROOT_PATH}/components/toolchain/gcc/Makefile.posix
#sed -i  "s/GNU_VERSION/\#GNU_VERSION/" ${NRF_SDK_ROOT_PATH}/components/toolchain/gcc/Makefile.posix

# Add the new location and version
#echo "GNU_INSTALL_ROOT ?= ${ARM_GCC_TOOL_IN_HOST}" >> ${NRF_SDK_ROOT_PATH}/components/toolchain/gcc/Makefile.posix
#echo "GNU_VERSION ?= ${ARM_GCC_VERSION}" >> ${NRF_SDK_ROOT_PATH}/components/toolchain/gcc/Makefile.posix

export GNU_INSTALL_ROOT="`dirname $(which arm-none-eabi-gcc)`/"
export ARM_GCC_VERSION="`arm-none-eabi-gcc --version | awk 'NR==1{ print $3 }'`"

wget ${NRF_SDK_DOWNLOAD_URL}

mkdir ${NRF_SDK_ROOT}
sudo apt-get install unzip
unzip ${NRF_SDK}.zip -d ${NRF_SDK_ROOT}

cp ./app ${NRF_SDK_ROOT_PATH}/examples/peripheral/
cd ${NRF_SDK_ROOT_PATH}/examples/peripheral/app/pca10040/s132/armgcc/
make
