#!/usr/bin/env python
import sys
import os
import subprocess

arguments = sys.argv
option = sys.argv[1]


def get_version():
    command = "git describe --abbrev=0 --tags".split(" ")
    output = subprocess.Popen(command, stdout=subprocess.PIPE).communicate()[0].rstrip()
    return output


def fetch():
    print "Fetching latest version..."
    command = "git fetch"
    command = command.split(" ")
    output = subprocess.Popen(command, stdout=subprocess.PIPE).communicate()[0].rstrip()
    print output
    
def update():
    print "Updating control_tower..."
    fetch()
    version = get_version()
    print "Current version %s" % version
    command = "git checkout %s" % version
    print "Running command: %s" % command
    command = command.split(" ")
    output = subprocess.Popen(command, stdout=subprocess.PIPE).communicate()[0].rstrip()
    print output
    
if len(arguments) > 1:
    if option == "start":
        from coordinator_recv.coordinator_server import ServerLauncher
        launcher = ServerLauncher()
        launcher.start_server()
    elif option == "status":
        print "Option not implemented yet"
    elif option == "version":
        print get_version()
    elif option == "update":
        update()

else:
    print "Usage: control_tower [option]"
    print
