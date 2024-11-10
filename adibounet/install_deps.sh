#!/bin/bash

# Run this script as root user!

# Update package list without sudo
sudo apt update

# Install sudo first (if not already installed)
if ! command -v sudo &> /dev/null; then
  echo "Installing sudo..."
  apt install sudo -y
fi

# Install Python 3
echo "Installing Python 3..."
sudo apt install python3 -y

# Install Git
echo "Installing Git..."
sudo apt install git -y

# Install Screen
echo "Installing Screen..."
sudo apt install screen -y

# Install Htop
echo "Installing Htop..."
sudo apt install htop -y

# Print completion message
echo "Installation of AdibouNet deps is done!"