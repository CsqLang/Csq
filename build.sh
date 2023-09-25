#!/bin/bash

# The terminal should be refreshed for effects to take place
# Can be written better, but this is just a concept
cp csq.py csq
chmod +x csq
# Copy it to ~/.local/bin for it to be global
local_bin="$HOME/.local/bin/"
mv csq "$local_bin"

if [ $? -eq 0 ]; then
  # Destination folder for include files
  local_include="$HOME/.local/include/csq"

  # Create the destination folder if it doesn't exist
  mkdir -p "$local_include"

  if [ $? -eq 0 ]; then
    # Copy all subdirectories from the current folder to the destination folder
    for dir in */; do
      # Exclude the csq directory itself if present
      if [ "$dir" != "csq/" ]; then
        cp -r "$dir" "$local_include"
        cp -r "$dir" "$local_bin"
      fi
    done

    if [ $? -eq 0 ]; then
      # Check if CSQ_PATH is already set in your shell configuration file (e.g., .bashrc)
      shell_config="$HOME/.${SHELL##*/}rc"

      if grep -q "CSQ_INCLUDE" "$shell_config"; then
        echo -e "\033[1;33m[WARNING]\033[0m CSQ is already set up in your shell configuration."
        echo
        echo "🚀 Csq has been successfully installed! Enjoy coding with Csq!"
      else
        # Append the current directory to PATH in your shell configuration file
        CSQ_BIN="$local_bin/csq"
        CSQ_PATH="$local_include"
        echo 'export PATH="'"$CSQ_BIN"':$PATH"' >> "$shell_config"
        echo 'export CSQ_INCLUDE="'"$CSQ_PATH"'"' >> "$shell_config"
        # Apply the changes in the current shell
        source "$shell_config"

        if [ $? -eq 0 ]; then
          echo "🚀 Csq has been successfully installed! Enjoy coding with Csq!"
        else
          echo "Error: Failed to apply changes in your shell configuration. Please manually source $shell_config."
        fi
      fi
    else
      echo "Error: Failed to copy subdirectories to $local_include."
    fi
  else
    echo "Error: Failed to create directory $local_include."
  fi
else
  echo "Error: Failed to copy csq.py to $local_bin."
fi
