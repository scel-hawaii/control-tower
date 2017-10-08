#
#
#    server.py
#
#    Original Author(s): Kenny Luong <luong97@hawaii.edu>
#    Date Created: 2016/11/25
#
#    This is a basic HTTP and websocket server that provides a
#    browser-based client an api to control a simple simavr-based
#    emulator process.
#

from flask import Flask
from flask import request
from flask import render_template
from flask import send_from_directory
from flask_socketio import SocketIO

from multiprocessing import Process
from subprocess import call
from subprocess import Popen
from subprocess import PIPE
import subprocess
import os
import signal
import time
import eventlet

from threading import Thread

# Since we're using eventlet for our websocket server, the normal
# threading library will not work; we can however use the provided
# monkey patching function to make it compatable
#
# More info available here:
# http://eventlet.net/doc/patching.html
eventlet.monkey_patch()

app = Flask(__name__)
app.config['SECRET_KEY'] = 'secret!'
socketio = SocketIO(app)

prev_count = 0;
current_count = 0;
max_length = 0;
emu_state = "STOPPED"

# Initialize the process object with a dummy program
# so that it's easy for us to check if the previous process
# is still running or not.
#
# TODO: there might be a better way to do this
emu_proc = Popen(["date"], shell=True);

#
# Normal WSGI routes
#

@app.route("/")
def index():
    return render_template('index.html')

@app.route('/assets/<path:path>')
def send_js(path):
        return send_from_directory('assets', path)


@app.route("/stdout/length")
def file_length():
    length = Popen("wc -l < emu_output.txt", shell=True, stdout=subprocess.PIPE).stdout.read()
    return length

# This route grabs new data that is written to the logfile
@app.route("/stdout")
def tail():
    tail_ptr = request.args.get("tail_ptr")
    output = Popen("tail emu_output.txt -n " + str(tail_ptr), shell=True, stdout=subprocess.PIPE).stdout.read()
    return output

@app.route("/control/state")
def state():
    global emu_state

    return emu_state

@app.route("/control/start")
def start():
    global emu_proc
    global emu_state
    firmware_build = request.args.get("firmware_build")

    if( emu_proc.poll() == None ):
        print "Process still running"
        # Return the request so that the client knows
        return "Process still running"
    else:
        # For some reason on debian, running the Popen with shell=True
        # spawns a sh/ process that then runs the given command. It doesn't do
        # this in Arch. So when we attempt to terminate the emulator model process
        # doesn't terminate properly.
        #
        # So running exec (which will replace the current running process) will
        # maintain compatability with debian.
        cmd = "exec python2 ../core/run_emu.py {fw}".format(fw=firmware_build)
        emu_proc = Popen([cmd], shell=True)

    emu_state = "RUNNING"
    return "Process started"

@app.route("/control/stop")
def stop():
    global emu_proc
    global emu_state

    print "terminating emulator proc"
    emu_proc.terminate()

    emu_state = "STOPPED"
    return "stop"

@app.route("/control/clear")
def clear_txt():
    call(["cat /dev/null > emu_output.txt"], shell=True)

    return "clear"


#
# Websocket Interface
#

@socketio.on('connect')
def handle_connect():
    socketio.send("Hello, client!")

def background_emit():
    global socketio
    global app

    output = Popen("tail -F emu_output.txt", shell=True, stdout=PIPE)

    time.sleep(1)
    while True:
        bufsize = 4
        d = output.stdout.read(bufsize)
        socketio.emit("message", {'data': d}, broadcast=True)


#
# Execute server
#

t = Thread(target=background_emit).start()
socketio.run(app)

