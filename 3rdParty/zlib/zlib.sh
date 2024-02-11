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

# Display the folder name
echo "The folder name after extraction is: ${ZLIB_DIR}"

# Clean up
echo "Cleaning up..."
rm ${ZLIB_TAR}

