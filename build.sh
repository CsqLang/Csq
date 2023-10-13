#!/bin/bash

# This script will install the csq tool in the /opt directory
# It will also create a symbolic link in /usr/local/bin
# This script must be run as root

if [ "$EUID" -ne 0 ]
  then echo "Please run as root"
  exit 1
fi

OPT_DIR="/opt/"
CSQ_OPT_DIR="${OPT_DIR}csq/"
CSQ_ENTRY_POINT="${CSQ_OPT_DIR}src/csq.py"
CSQ_EXECUTABLE_PATH="/usr/local/bin/csq"

# Check if the opt directory exists

if ! test -d "$OPT_DIR"; then
    echo "Error: Directory $OPT_DIR does not exists."
    exit 1
fi

# Check if the csq directory exists
# If it does not exist, create it
if ! test -d "$CSQ_OPT_DIR"; then
    mkdir "$CSQ_OPT_DIR"
fi

# Make the entry point executable

chmod +x "$CSQ_ENTRY_POINT"

# Copy the files to the csq directory, update if they already exist
cp -ur ./* "$CSQ_OPT_DIR"

# Create the symbolic link
# If the file already exists do nothing
if ! test -f "$CSQ_EXECUTABLE_PATH"; then
    ln -s "$CSQ_ENTRY_POINT" "$CSQ_EXECUTABLE_PATH"
fi
