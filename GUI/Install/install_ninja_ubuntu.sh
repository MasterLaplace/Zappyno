#!/bin/bash
# Check
if user has root privilegesif [[ $EUID -ne 0 ]]; then
  echo "This script must be run as root"
  exit 1
fi

# Install required packages
apt update
apt install -y wget unzip

# Download and extract Ninja
NINJA_VERSION="1.10.2"
wget -q https://github.com/ninja-build/ninja/releases/download/v${NINJA_VERSION}/ninja-linux.zip -O ninja-linux.zip
unzip -q ninja-linux.zip

# Move Ninja binary to /usr/local/bin
mv ninja /usr/local/bin

# Clean up downloaded files
rm ninja-linux.zip

# Verify Ninja installation
ninja --version