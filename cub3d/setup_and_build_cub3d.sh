#!/bin/bash

set -e

echo "🔧 Updating package list and installing dependencies..."
sudo apt update
sudo apt install -y \
	build-essential \
	libx11-dev \
	libxext-dev \
	libbsd-dev \
	libxrandr-dev \
	libxinerama-dev \
	libxcursor-dev \
	libxi-dev \
	libgl1-mesa-dev \
	libglu1-mesa-dev \
	xorg-dev \
	x11-utils \
	x11-xserver-utils \
	git \
	make

echo "✅ System dependencies installed."

make bonus
echo "✅ All done!"
echo "🎮 You can now run the game with:"
echo "   ./cub3D_bonus bonus/maps/adventure.cub"
