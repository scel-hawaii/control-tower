#!/usr/bin/python

# Library Imports
import os
from sys import exit
import subprocess

# Local Imports
from screen_supervisor import ScreenSupervisor

class ControlTower:
	def __init__(self, server_path="../coordinator_recv/", server_name="coordinator_recv.py"):
		self.SERVER_FILE_PATH = server_path
		self.SERVER_FILE_NAME = server_name
		self.SERVER_COMMAND = "python " + self.SERVER_FILE_PATH + self.SERVER_FILE_NAME + "\n"
		self.SCREEN_NAME = "AwesomeScreen"
		self.USER_NAME = str(os.environ['USER'])

		self.print_start_message()
		self.screen_super = ScreenSupervisor()

	def start_server(self):
		self.start_screen()
		self.start_process()
		self.print_status_server()


	def start_screen(self):
		if not self.screen_super.exists_session(self.SCREEN_NAME):
			self.screen_super.start_session(self.SCREEN_NAME)

	def start_process(self):
		if not (self.exists_process()):
			command = ['screen', '-S', self.SCREEN_NAME, '-X', 'stuff', self.SERVER_COMMAND] 
			subprocess.call(command)

	def kill_server(self):
		self.kill_process()
		if self.exists_screen():
			self.kill_screen()
		else:
			print "Error: the screen session does not exist."

	def kill_screen(self):
		self.screen_super.kill_session(self.SCREEN_NAME)
		
	def kill_process(self):
		PID = int(self.check_status_process())
		print "PID " + str(PID)

		PID_STR = str(PID)

		command = ['kill', PID_STR]
		print command

		if PID !=-1:
			subprocess.call(command)
		else:
			print "The server process isn't running! We can't kill it!"
	


	def check_status_process(self):
		check_command = ["pgrep", "-f", self.SERVER_FILE_NAME]
		try:
			output = subprocess.check_output(check_command)
			return str(output)
		except:
			# The server process is not running
			return -1

	def exists_process(self):
		PID = self.check_status_process()
		if PID != -1:
			return True
		else:
			return False

	def exists_screen(self):
		return self.screen_super.exists_session(self.SCREEN_NAME)

	def print_status_server(self):
		if self.print_status_process() and self.print_status_screen():
			print "The server appears to be good!"
			print ""


	def print_status_process(self):
		PID = self.check_status_process()
		if PID != -1:
			print "The coordinator server process is running on PID: " + str(int(PID))
			return True
		else:
			print "The coordinator server process is NOT running."
			return False

	def print_status_screen(self):
		if self.screen_super.exists_session(self.SCREEN_NAME):
			print "The screen session " + self.SCREEN_NAME + " exists."
			return True
		else:
			print "The screen session does not exist"
			return False



	def print_start_message(self):
		subprocess.call("clear")
		print "---------------------------------------------"
		print "Welcome to the REIS weatherbox server manager!"
		print "To see the available commands, type help."
		print "----------------------------------------------"
		self.print_start_status()
		print ""
		self.print_commands()


	def print_start_status(self):
		if self.exists_process():
			print "The server process is currently running."
		else:
			print "The server is NOT running, please start it by typing start-server"



	def print_end_message(self):
		print " "
		print " "
		print "Ending program..."
		print " "
		print " "
		print "---------------------------------------------"
		print "Program End"
		print "----------------------------------------------"
		print " "

	def print_commands(self):
		print "Available command(s): "
		print "start-server"
		print "check-status"
		print "kill-server"
		print "quit"
		print " "

	def print_menu(self):
		x = "======Menu=====\n"
		x = x + "(start) - Start coordinator server\n"
		x = x + "(start-process) - Start coordinator process\n"
		x = x + "(menu) - List Menu Options\n"
		x = x + "(status) - Check server status\n"
		x = x + "(check-screen) - Check screen status\n"
		x = x + "(check-process) - Check server status\n"
		x = x + "(stop-server) - Stop server\n"
		x = x + "(quit) - Quit Program\n"
		x = x + "===============\n"
		x = x + "\n"
		return x 

	def get_menu_option(self):
		input = raw_input(self.USER_NAME + "@reis-server-manager --> ")
		self.execute_menu_option(input)

	def execute_menu_option(self, input):
		#if input == "start":
			#self.start_server()
		if input == "start-server":
			self.start_server()
		elif input == "help":
			self.print_commands()
		elif input == "start-process":
			self.start_process()
		#elif input == "menu":
			#print self.print_menu()
		#elif input == "status":
			self.print_status_process()
		elif input == "check-status":
			self.print_status_server()
		#elif input == "check-screen":
			#self.print_status_screen()
		#elif input == "check-process":
			#self.print_status_process()
		elif input == "stop-server":
			self.kill_server()
		elif input == "view-server":
			subprocess.call(['tail', '-10', 'output.log'])
			print " "
		elif input == "quit" or input =="q":
			exit()
		else:
			print "Invalid menu command. Please try again."

if __name__ == "__main__":
	supervisor = ControlTower()
	while True:
		supervisor.get_menu_option()



