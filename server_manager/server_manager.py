#!/usr/bin/python
import os
from sys import exit
import subprocess
from screen_supervisor import ScreenSupervisor


class ControlTower:
	SERVER_FILE = "../coordinator_recv/coordinator_recv.py"
	SCREEN_NAME = 'TesterScreen'

	def __init__(self):
		self.print_start_message()
		self.screen_super = ScreenSupervisor()

		#self.start_server()

	def start_server(self):
		self.start_screen()
		self.start_process()


	def start_screen(self):
		if self.screen_super.exists_session(ControlTower.SCREEN_NAME):
			print "The screen already exists."
		else:
			self.screen_super.start_session(ControlTower.SCREEN_NAME)

	def start_process(self):
		if (self.exists_process()):
			print "Process Already exists"
		else:
			print "Lets go ahead and start the process"
			command = ['screen', '-S', ControlTower.SCREEN_NAME, '-X', 'stuff', 'python while.py\n']
			subprocess.call(command)

	def kill_server(self):
		self.kill_process()
		if self.exists_screen():
			self.kill_screen()
		else:
			print "Error: the screen session does not exist."

	def kill_screen(self):
		self.screen_super.kill_session(ControlTower.SCREEN_NAME)
		
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
		check_command = ["pgrep", "-f", "while.py"]
		try:
			output = subprocess.check_output(check_command)
			return str(output)
		except:
			print "Server process is NOT running!"
			return -1

	def exists_process(self):
		PID = self.check_status_process()
		if PID != -1:
			return True
		else:
			return False

	def exists_screen(self):
		return self.screen_super.exists_session(ControlTower.SCREEN_NAME)

	def print_status_process(self):
		PID = self.check_status_process()
		if PID != -1:
			print "The coordinator server process is running on PID: " + str(PID)
		else:
			print "The coordinator server process is NOT running."

	def print_status_screen(self):
		if self.screen_super.exists_session(ControlTower.SCREEN_NAME):
			print "The screen " + ControlTower.SCREEN_NAME + " exists."
		else:
			print "The screen does not exist"



	def print_start_message(self):
		subprocess.call("clear")
		print "---------------------------------------------"
		print "Welcome to the REIS weatherbox server manager"
		print "----------------------------------------------"

	def print_end_message(self):
		print " "
		print " "
		print "Ending program..."
		print " "
		print " "
		print "---------------------------------------------"
		print "Program End"
		print "----------------------------------------------"

	def print_menu(self):
		x = "======Menu=====\n"
		x = x + "(start) - Start coordinator server\n"
		x = x + "(start-process) - Start coordinator process\n"
		x = x + "(menu) - List Menu Options\n"
		x = x + "(status) - Check server status\n"
		x = x + "(check-screen) - Check screen status\n"
		x = x + "(check-process) - Check server status\n"
		x = x + "(kill-server) - Kill server\n"
		x = x + "(quit) - Quit Program\n"
		x = x + "===============\n"
		return x 

	def get_menu_option(self):
		input = raw_input("REIS Server Manager> ")
		self.execute_menu_option(input)

	def execute_menu_option(self, input):
		if input == "start":
			self.start_server()
		elif input == "start-process":
			self.start_process()
		elif input == "menu":
			print self.print_menu()
		elif input == "status":
			self.print_status_process()
		elif input == "check-screen":
			self.print_status_screen()
		elif input == "check-process":
			self.print_status_process()
		elif input == "kill-server":
			self.kill_server()
		elif input == "quit":
			exit()
		else:
			print "Invalid menu command. Please try again."

if __name__ == "__main__":
	supervisor = ControlTower()
	print supervisor.print_menu()
	while True:
		supervisor.get_menu_option()



