#!/bin/bash

# Get the current directory
current_dir=$(pwd)

# Check if CSQ_PATH is already set in .bashrc
if ! grep -q "CSQ_PATH" ~/.bashrc; then
    # Append the current directory to PATH in .bashrc
    echo 'export PATH="'$current_dir':$PATH"' >> ~/.bashrc
    echo 'export CSQ_PATH="'$current_dir'"' >> ~/.bashrc
    # Apply the changes in the current shell
    source ~/.bashrc
fi

# Compile csq.cpp only if g++ is available
if command -v g++ >/dev/null 2>&1; then
    g++ csq.cpp -o csq
else
    echo "g++ compiler not found."
fi
