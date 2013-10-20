#!/bin/bash
SCREEN_NAME="TesterScreen"
if  screen -list | grep -q "$SCREEN_NAME"; then
    echo "This screen exists!"
else
    echo "This screen does not exist!"
    echo "Creating the screen session.."
    screen -d -m -S "$SCREEN_NAME" 
    screen -X stuff "ls -l\n"
fi
