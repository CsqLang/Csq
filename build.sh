# The terminal should be refreshed for effects to take place
# Can be witten better, but this is just a concept

# Copy it to ~/.local/bin for it to be global

local_bin="$HOME/.local/bin/"

# Copy the include directories to ~/.local/include for global
local_include="$HOME/.local/include"
r_s=$HOME/.${SHELL##*/}rc

# Check if CSQ_PATH is already set in .bashrc
if ! grep -q "CSQ_INCLUDE" "$r_s"; then
  # Append the current directory to PATH in .bashrc
  CSQ_BIN="$local_bin/csq"
  CSQ_PATH="$local_include/csq"
  echo 'export PATH="'"$CSQ_BIN"':$PATH"' >>"$r_s"
  echo 'export CSQ_INCLUDE="'"$CSQ_PATH"'"' >>"$r_s"
  # Apply the changes in the current shell
  source "$r_s"
fi
