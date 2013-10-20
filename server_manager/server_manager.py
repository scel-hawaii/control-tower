#!/usr/bin/python

import subprocess

def printStartMessage():
	subprocess.call("clear")
	print "---------------------------------------------"
	print "Welcome to the REIS weatherbox server manager"
	print "----------------------------------------------"
	return

def printEndMessage():
	print " "
	print " "
	print "Ending program..."
	print " "
	print " "
	print "---------------------------------------------"
	print "Program End"
	print "----------------------------------------------"
	return

printStartMessage()
subprocess.call("./check_screen.sh")
printEndMessage()
