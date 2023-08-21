#!/bin/bash

# The terminal should be refreshed for effects to take place
# Can be written better, but this is just a concept

# Compile csq.cpp only if g++ is available
if command -v g++ >/dev/null 2>&1; then
  g++ csq.cpp -o csq
else
  echo "g++ compiler not found."
fi

# Check and create the required folders

required_folders=("$HOME/.local" "$HOME/.local/include" "$HOME/.local/bin")

for is_folder in "${required_folders[@]}"; do
  if [[ ! -d "$is_folder" ]]; then
    mkdir -p "$is_folder"
  fi
done

# Copy the executable to ~/.local/bin for it to be global

local_bin="$HOME/.local/bin/"
cp_cmd=$(cp csq "$local_bin")

if [[ "$cp_cmd" -ne 0 ]]; then
  echo "Couldn't copy the executable to $local_bin"
fi

# Copy the include directories to ~/.local/include for global

c_dirs=$(ls -d */)
local_include="$HOME/.local/include/csq"

for _dir in $c_dirs; do
  cp -r "$_dir" "$local_include"
done

# Check if CSQ_PATH is already set in .bashrc
if ! grep -q "CSQ_INCLUDE" ~/.bashrc; then
  # Append the current directory to PATH in .bashrc
  CSQ_BIN="$local_bin/csq"
  CSQ_PATH="$local_include"
  echo 'export PATH="'"$CSQ_BIN"':$PATH"' >>~/.bashrc
  echo 'export CSQ_INCLUDE="'"$CSQ_PATH"'"' >>~/.bashrc
  # Apply the changes in the current shell
  source ~/.bashrc
fi

# For confirmation sake
source ~/.bashrc
