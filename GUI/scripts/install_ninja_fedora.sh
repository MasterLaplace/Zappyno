#!/bin/bash

# Check if Ninja is already installed
if command -v ninja >/dev/null 2>&1; then
    echo "Ninja is already installed. Exiting."
    exit 0
fi

# Install the necessary dependencies
sudo dnf install -y git python3-devel

# Clone the Ninja repository
git clone git://github.com/ninja-build/ninja.git
cd ninja

# Build Ninja
python3 configure.py --bootstrap

# Install Ninja globally
sudo cp ninja /usr/local/bin/

# Clean up the temporary files
cd ..
rm -rf ninja

echo "Ninja installation completed."

# Verify the installation
ninja --version
