import subprocess
class ScreenSupervisor:

	def __init(self, screen_name):
		on = True

	def start_session(self, session_name):
		command = ['screen', '-c', 'screen_config', '-L', '-d', '-m', '-S', session_name]
		subprocess.check_output(command)
	
	
	def exists_session(self, session_name):
		#command = ['screen', '-ls', '|', 'grep', session_name, ';true', 'shell=True']
		command = "screen -ls | grep " + str(session_name) + " ;true"
		output = subprocess.check_output(command, shell=True)
		try: 
			if "."+session_name+"\t(" in output:
				return True
			else:
				return False
		except:
			print "Error"
			return False

	def kill_session(self, session_name):
		if self.exists_session(session_name):
			print "Killing Screen: " + session_name
			command = ['screen', '-S', session_name, '-X', 'kill']
			subprocess.call(command)
		else:
			print "The screen doesn't exist. We can't kill it"

	def send_command(self, screen_name, command):
		call_cmd = ['screen', '-S', screen_name, '-X', 'stuff', command]
		subprocess.call(call_cmd)


if __name__ == "__main__":
	SCREEN_NAME = "WHEE"
	screen_super = ScreenSupervisor()
	print screen_super.exists_session(SCREEN_NAME)
	screen_super.start_session("TEST");
	print screen_super.exists_session("TEST");

