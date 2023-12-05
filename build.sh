#!/bin/bash

# Installation path
local_bin="$HOME/.local/bin/"
local_include="$HOME/.local/include/csq"
csq_bin="$local_bin/csq"
csq_path="$local_include"

if [ -f "$HOME/.bashrc" ]; then
    shell_config="$HOME/.bashrc"
else
    shell_config="$HOME/.${SHELL##*/}rc"
fi


function install_csq() {
  # Copy csq.py to ~/.local/bin/
  cp csq.py csq
  chmod +x csq
  mv csq "$local_bin"
  sudo cp -r Core "/usr/include/Csq/"
  if [ $? -ne 0 ]; then
    echo "Error: Failed to copy csq.py to $local_bin."
    exit 1
  fi

  # Create destination folder ~/.local/include/csq
  mkdir -p "$local_include"
  if [ $? -ne 0 ]; then
    echo "Error: Failed to create directory $local_include."
    exit 1
  fi

  # Copy specific folders to ~/.local/include/csq
  cp -r Compiler "$local_bin"
  cp -r Core "$local_include"

  if [ $? -ne 0 ]; then
    echo "Error: Failed to copy specific folders to $local_include."
    exit 1
  fi

  # Check if CSQ_INCLUDE is already set in the shell configuration file

  if grep -q "CSQ_INCLUDE" "$shell_config"; then
    echo -e "\033[1;33m[WARNING]\033[0m CSQ is already set up in your shell configuration."
    echo
    echo "🚀 Csq has been successfully installed! Enjoy coding with Csq!"
  else
    # Append the current directory to PATH and CSQ_INCLUDE to the shell configuration file
    echo 'export PATH="'"$csq_bin"':$PATH"' >> "$shell_config"
    echo 'export CSQ_INCLUDE="'"$csq_path"'"' >> "$shell_config"
    # Apply changes in the current shell
    source "$shell_config"

    if [ $? -eq 0 ]; then
      echo "🚀 Csq has been successfully installed! Enjoy coding with Csq!"
    else
      echo "Error: Failed to apply changes in your shell configuration. Please manually source $shell_config."
      exit 1
    fi
  fi
}

function uninstall_csq() {
  # Remove csq.py from ~/.local/bin/
  rm -f "$csq_bin"

  # Remove specific folders from ~/.local/include/csq
  rm -rf "$local_bin/Compiler"
  rm -rf "$csq_path/Core"

  # Remove CSQ_INCLUDE from the shell configuration file
  #sed -i '/CSQ_INCLUDE/d' "$shell_config"

  #echo "✅ Csq has been successfully uninstalled."


  # Check if the shell configuration file exists before attempting to modify it
  if [ -f "$shell_config" ]; then
    # Remove CSQ_INCLUDE from the shell configuration file
    sed -i '/CSQ_INCLUDE/d' "$shell_config"
    echo "✅ Csq has been successfully uninstalled."
  else
    echo "Error: Shell configuration file $shell_config not found."
    exit 1
  fi


}

function uninstall_csq() {
  # Remove csq.py from ~/.local/bin/
  rm -f "$csq_bin"

  # Remove specific folders from ~/.local/include/csq
  rm -rf "$local_bin/Compiler"
  rm -rf "$csq_path/Core"

  # Remove CSQ_INCLUDE from the shell configuration file
  if [ -f "$shell_config" ]; then
    sed -i '/CSQ_INCLUDE/d' "$shell_config"
    echo "✅ CSQ_INCLUDE removed from $shell_config."
  else
    echo "Error: Shell configuration file $shell_config not found."
    exit 1
  fi

  # Remove csq path from the shell configuration file
  if [ -f "$shell_config" ]; then
    sed -i '/csq/d' "$shell_config"
    echo "✅ CSQ_PATH removed from $shell_config."
  else
    echo "Error: .bashrc file not found."
    exit 1
  fi

  echo "✅ Csq has been successfully uninstalled."
}


# Check command-line argument
if [ "$1" == "uninstall" ]; then
  uninstall_csq
else
  install_csq
fi
