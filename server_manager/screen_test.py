#!/usr/bin/python
import subprocess

SCREEN_NAME = "TesterScreen"
SCREEN_COMMAND = ["screen", "-d", "-m", "-S", SCREEN_NAME]

output = subprocess.check_output(SCREEN_COMMAND)
print output
