from subprocess import call
import time
while True:
	command = ["x11vnc", "-auth", "/home/kenny/.Xauthority", "-display", ":0"]
	call(command)
	time.sleep(0.1)
