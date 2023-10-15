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

# Assume that you downloaded this directory in /tmp or somewhere that will not last that long

# Check if the opt directory exists

if ! test -d "$OPT_DIR"; then
    INSTALL_DIR_EXISTS=false
fi

# Check if the csq directory exists
# If it does not exist, create it
if ! test -d $CSQ_OPT_DIR; then
	CSQ_INSTALL_DIR_EXISTS=false
fi

function install_csq(){
	# Create the install directory if it does not exist
	if [[ $CSQ_INSTALL_DIR_EXISTS == false ]]; then
		mkdir -p "$CSQ_OPT_DIR"
	fi

	# Copy the files to the csq directory, update if they already exist
	cp -ur ./* "$CSQ_OPT_DIR"

	# Make the entry point executable

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
