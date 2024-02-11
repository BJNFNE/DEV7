#!/bin/bash

# Define variables
ZLIB_VERSION="1.1.3"
ZLIB_URL="https://www.zlib.net/fossils/zlib-${ZLIB_VERSION}.tar.gz"
ZLIB_TAR="zlib-${ZLIB_VERSION}.tar.gz"
ZLIB_DIR="zlib-${ZLIB_VERSION}"

# Download zlib source code
echo "Downloading zlib ${ZLIB_VERSION}..."
wget -O ${ZLIB_TAR} ${ZLIB_URL}

# Check if download was successful
if [ $? -ne 0 ]; then
    echo "Failed to download zlib source code."
    exit 1
fi

# Extract zlib source code
echo "Extracting zlib source code..."
tar -xf ${ZLIB_TAR}

# Navigate into zlib directory
cd ${ZLIB_DIR}

# Run configure
echo "Running configure for zlib..."
./configure

# Check if configure was successful
if [ $? -ne 0 ]; then
    echo "Failed to configure zlib."
    exit 1
fi

# Run make
echo "Compiling zlib..."
make

# Check if make was successful
if [ $? -ne 0 ]; then
    echo "Failed to compile zlib."
    exit 1
fi

# Clean up
echo "Cleaning up..."
cd ..
rm ${ZLIB_TAR}

echo "zlib ${ZLIB_VERSION} has been successfully compiled."

