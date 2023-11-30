#!/bin/bash

if [ "$EUID" -ne 0 ]
  then echo "Please run as root"
  exit 1
fi

OPT_DIR="/opt/"
CSQ_OPT_DIR="${OPT_DIR}csq/"
CSQ_ENTRY_POINT="${CSQ_OPT_DIR}src/csq.py"
CSQ_EXECUTABLE_PATH="/usr/local/bin/csq"
INSTALL_DIR_EXISTS=true
CSQ_INSTALL_DIR_EXISTS=true

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


	chmod +x "$CSQ_ENTRY_POINT"

	# Create the symbolic link
	# If the file already exists do nothing
	if ! test -f "$CSQ_EXECUTABLE_PATH"; then
	    ln -s "$CSQ_ENTRY_POINT" "$CSQ_EXECUTABLE_PATH"
	fi

	# Echo success message
	echo "CSQ has been installed"
}

function uninstall_csq(){
	# Check if the folders exists

	if [[ $CSQ_INSTALL_DIR_EXISTS == false ]]; then
		echo "CSQ is not installed"
		exit 1
	fi

	# Remove the symbolic link
	unlink "$CSQ_EXECUTABLE_PATH"

	# Remove the csq directory
	rm -rf "$CSQ_OPT_DIR"

	# Echo success message
	echo "CSQ has been uninstalled"
}

function update_csq(){
	# Check if the folders exists

	if [[ $CSQ_INSTALL_DIR_EXISTS == false ]]; then
		echo "CSQ is not installed"
		exit 1
	fi

	# Copy the files to the csq directory, update if they already exist
	cp -ur ./* "$CSQ_OPT_DIR"

	# Make the entry point executable
	chmod +x "$CSQ_ENTRY_POINT"

	# Echo success message
	echo "CSQ has been updated"
}

function print_help(){
	echo "Usage: ./build.sh [OPTION]"
	echo "Options:"
	echo "	-i, --install		Install CSQ"
	echo "	-u, --uninstall		Uninstall CSQ"
	echo "	-U, --update		Update CSQ"
	echo "	-h, --help		Print this help message"
}

# Check if the user wants to install or uninstall
if [ $# -eq 0 ]; then
	print_help
	exit 1
fi

while [ "$1" != "" ]; do
	case $1 in
		-i | --install )        install_csq
								;;
		-u | --uninstall )      uninstall_csq
								;;
		-U | --update )         update_csq
								;;
		-h | --help )           print_help
								exit 1
								;;
		* )                     print_help
								exit 1
	esac
	shift
done
