#!/usr/bin/env python
## Launch the coordinator server..
from coordinator_recv import CoordinatorReceiver
import sys
import time
import argparse
import os
import yaml
from subprocess import call
from pprint import pprint

class ServerLauncher:

	def __init__(self):
		self.display_splash()
		self.PROFILE_DIR = os.path.join(os.getcwd(), 'config', 'hardware_profiles')
		self.hardware_profiles = [] 
		self.profile = {}

		# If no arguments are passed, poll the hardware profile folder
		# and ask what the user wants
		self.ask_arguments()
		#self.init_path()

		self.run_server()

	def display_splash(self):
		print "------------------------------------"
		print "SCEL Server Launcher"
		print "------------------------------------"
		print

	def run_server(self):
		print 
		print 
		print "Running server with:"
		pprint(self.profile)

	def ask_arguments(self):
		# List the config files
		for filename in os.listdir(self.PROFILE_DIR):
			if ".yaml" in filename:
				self.hardware_profiles.append(filename)

		print "#", "\t", "Filename", "\t\t\t", "Description"
		print "-", "\t", "--------", "\t\t\t", "-----------"

		# Ask the user which one he wants
		count = 0
		for filename in self.hardware_profiles:
			with open(os.path.join(self.PROFILE_DIR, filename), 'r') as config:
				doc = yaml.load(config)
				print count, "\t", filename, "\t\t", doc['description']
				count += 1
		
		print
		print "Please input which hardware profile you wish to load:", 
		number = raw_input()

		if not (int(number) in xrange(0,len(self.hardware_profiles))):
			print "Invalid selection!"

			print "Please input which hardware profile you wish to load:", 
			number = raw_input()
		else:
			# Select the file
			filename = self.hardware_profiles[int(number)]
			with open(os.path.join(self.PROFILE_DIR, filename), 'r') as config:
				doc = yaml.load(config)
				self.profile = doc
				print 
				print "Profile Loaded: " 
				pprint(self.profile)

	def start_server(self):
		command = ["python", "coordinator_recv/coordinator_recv.py", "--tty", str(self.profile['coordinator-recv'], "--output screen")]
		print command
		call(command);


	def init_path(self):
		if os.path.isfile(os.path.join(self.PROFILE_DIR, sys.argv)):
			return os.path.join(os.getcwd(), self.args.profile_path)
		else:
			raise Exception("File path does not exist")

	def run_launcher(self):
		test = ServerLauncher()
		test.start_server()
		
		
# if __name__ == "__main__":
	# test = ServerLauncher()
	# test.start_server()
