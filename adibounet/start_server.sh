#!/bin/bash

# Define the screen session name
SCREEN_SESSION="adibounet"

# Get the directory of the current script to ensure we run adb3server.py >
SCRIPT_DIR="$(cd "$(dirname "$0")" && pwd)"

# Start the server in a screen session without showing the startup message
echo "Starting or attaching to adb3server.py in screen session '$SCREEN_S>
screen -S "$SCREEN_SESSION" -dm bash -c "cd $SCRIPT_DIR && python3 adb3se>

# Attach to the screen session directly, skipping the start message
screen -S "$SCREEN_SESSION" -r
