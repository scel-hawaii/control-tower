#!/usr/bin/env python
import sys
import os

arguments = sys.argv
option = sys.argv[1]

if len(arguments) > 1:
    if option == "start":
        from coordinator_recv.coordinator_server import ServerLauncher
        launcher = ServerLauncher()
        launcher.start_server()
    elif option == "status":
        print "Option not implemented yet"
    elif option == "update":
        print "Updating control_tower"
    elif option == "version":
        os.system("git describe --abbrev=0 --tags")

else:
    print "Usage: control_tower [option]"
    print

