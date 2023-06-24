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
read -r -p "Do you want to copy ninja to /usr/local/bin/ ? (y/n)" input

case $input in
    [yY][eE][sS]|[yY])
		sudo cp ninja /usr/local/bin/
    ;;

    [nN][oO]|[nN])
        echo "Ok, see you next time"
    ;;

    *)
        echo "Invalid input... Good bye."
        exit 1
    ;;
esac

# Clean up the temporary files
cd ..
rm -rf ninja

echo "Ninja installation completed."

# Verify the installation
ninja --version
