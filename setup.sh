#!/bin/bash
#   ================================================
#   
#   Coordinator server setup script
#   
#   Run this file in the coordinator server to setup
#   everything.
#
#   ================================================
CURRENT_DIR="$(pwd)/bin/"
APPEND_LINE="export PATH=\$PATH:$CURRENT_DIR"

printf "Double checking bashrc PATH variable."
if grep -R "$APPEND_LINE" "$HOME/.bashrc"
then
    # code if found
    printf "We found it!\n"
else
    # code if not found
    printf "Shoot we didn't find it\n"
    echo $APPEND_LINE >> "$HOME/.bashrc"
    printf "Appended it to your bashrc.\n"
    printf "Please log in and log back out again to complete the installation.\n"
fi
