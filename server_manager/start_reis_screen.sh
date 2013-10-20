#!/bin/bash
SCREEN_NAME="TesterScreen"
START_TIME=$(date +%F__%I-%M-%p)
COORD_SERVER_FILE="while.py"
COORD_SERVER_DIRECTORY=""
LOG_DIR="logs"
START_SERVER_COMMAND="python $COORD_SERVER_DIRECTORY$COORD_SERVER_FILE\n"

if  screen -list | grep -q "$SCREEN_NAME"; then
    echo "This REIS server screen exists already."
else
    echo "This REIS server screen does not exist!"
    echo "Creating the screen session.."
    screen -d -L -m -S "$SCREEN_NAME" 
    echo "Screen is created."
    printf "Sending command $START_SERVER_COMMAND"
    screen -S "$SCREEN_NAME" -X stuff "$START_SERVER_COMMAND"
fi
