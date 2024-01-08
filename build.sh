#!/bin/env bash

# Check if the user is root (or at least has the necessary permissions)
# This doesn't affect the execution, it just checks other alternatives to install the files to
# Check this comment about permissions (and the whole question by extension)
# https://stackoverflow.com/questions/18215973/how-to-check-if-running-as-root-in-a-bash-script#comment125628861_52586842
# The test can also be "faked" by fakeroot, so let the user run the script
# If the user is not root, append 'sudo' to the commands that require it.

# The following locations are to be used:
# 	$HOME/.csq/include/csq
# 	/usr/local/include/csq
# 	/opt/csq
# 	/usr/include/csq
# 	~/.local/bin
# 	~/.local/lib/csq
# 	~/.local/share/csq

# Start from the least permission requirement location

is_root() {
    [ "${EUID:-$(id -u)}" -eq 0 ]
}

can_write() {
    [ -w "$1" ]
}

function install() {
	# Make the csq.py executable before doing anything
	chmod +x csq.py
    if is_root || can_write "/opt"; then
        echo "I'll install csq in /opt/csq and create a symlink to /usr/local/bin/csq"
        mkdir -p /opt/csq
        cp -r Core Compiler "/opt/csq"
        cp csq.py "/opt/csq"
        ln -sf "/opt/csq/csq.py" "/usr/local/bin/csq"
    else
        # Check for other locations to install

        if can_write "$HOME"; then
            echo "I'll install csq in $HOME/.csq/include/csq and create a symlink to ~/.local/bin/csq"
            mkdir -p "$HOME/.csq/include/csq"
            cp -r Core Compiler "$HOME/.csq/include/csq"
            cp csq.py "$HOME/.csq/include/csq"
            ln -sf "$HOME/.csq/include/csq/csq.py" "$HOME/.local/bin/csq"
        elif can_write "/usr/local/include"; then
            echo "I'll install csq in /usr/local/include/csq and create a symlink to /usr/local/bin/csq"
            mkdir -p /usr/local/include/csq
            cp -r Core Compiler "/usr/local/include/csq"
            cp csq.py "/usr/local/include/csq"
            ln -sf "/usr/local/include/csq/csq.py" "/usr/local/bin/csq"
        elif can_write "/usr/include"; then
            echo "I'll install csq in /usr/include/csq and create a symlink to /usr/bin/csq"
            mkdir -p /usr/include/csq
            cp -r Core Compiler "/usr/include/csq"
            cp csq.py "/usr/include/csq"
            ln -sf "/usr/include/csq/csq.py" "/usr/bin/csq"
        elif can_write "$HOME/.local/bin"; then
            echo "I'll install csq in ~/.local/bin and create a symlink to ~/.local/bin/csq"
            cp csq.py "$HOME/.local/bin/csq"
        elif can_write "$HOME/.local/lib"; then
            echo "I'll install csq in ~/.local/lib/csq"
            mkdir -p "$HOME/.local/lib/csq"
            cp -r Core Compiler "$HOME/.local/lib/csq"
            cp csq.py "$HOME/.local/lib/csq"
        elif can_write "$HOME/.local/share"; then
            echo "I'll install csq in ~/.local/share/csq"
            mkdir -p "$HOME/.local/share/csq"
            cp -r Core Compiler "$HOME/.local/share/csq"
            cp csq.py "$HOME/.local/share/csq"
        else
            echo "No writable location found. Please install manually"
        fi
    fi
}

function uninstall() {
    # Look for the places to uninstall
    dirs=(
        "$HOME/.csq/include/csq"
        "/usr/local/include/csq"
        "/opt/csq"
        "/usr/include/csq"
        "$HOME/.local/share/csq"
        "$HOME/.local/lib/csq"
    )

    bins=(
        "/usr/local/bin/csq"
        "$HOME/.local/bin/csq"
    )

    for dir in "${dirs[@]}"; do
        if [ -d "$dir" ]; then
            rm -rf "$dir"
            echo "Uninstalled from $dir"
        fi
    done

    for bin in "${bins[@]}"; do
        if [ -L "$bin" ]; then
            unlink "$bin"
            echo "Unlink binary from $bin"
        fi
    done
}

if [ "$1" == "install" ] || [ "$1" == "-i" ]; then
	install
elif [ "$1" == "uninstall" ] || [ "$1" == "-u" ]; then
	uninstall
else
	echo "Usage: build.sh <install|uninstall>"
fi

