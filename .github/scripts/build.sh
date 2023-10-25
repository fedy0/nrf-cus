#!/bin/bash

set -e

# Choose NRF SDK to use
export NRF_SDK=nRF5_SDK_15.3.0_59ac345
export NRF_SDK_VERSION=nRF5_SDK_v15.x.x
export NRF_SDK_DOWNLOAD_URL="https://developer.nordicsemi.com/nRF5_SDK/${NRF_SDK_VERSION}/${NRF_SDK}.zip"
export NRF_SDK_ROOT=nrf_sdk
export NRF_SDK_ROOT_PATH=${NRF_SDK_ROOT}/${NRF_SDK}

# Generate the compiler location and version as install in the host system
export GNU_INSTALL_ROOT="`dirname $(which arm-none-eabi-gcc)`/"
export ARM_GCC_VERSION="`arm-none-eabi-gcc --version | awk 'NR==1{ print $3 }'`"

# Download and extract the NRF SDK
wget ${NRF_SDK_DOWNLOAD_URL}
mkdir ${NRF_SDK_ROOT}
sudo apt-get install unzip
unzip ${NRF_SDK}.zip -d ${NRF_SDK_ROOT}

# Adjust project structure as supported by the SDk; then compile
cp -r ./app ${NRF_SDK_ROOT_PATH}/examples/peripheral/
cd ${NRF_SDK_ROOT_PATH}/examples/peripheral/app/pca10040/s132/armgcc/
make
