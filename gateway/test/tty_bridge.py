import subprocess
import signal
import sys
import time
from threading import Thread

class TTYBridge:
    def __init__(self):
        self.ready = False
        self.link_a = "./ttyV1"
        self.link_b = "./ttyV2"
        self._socat_proc = None
        self._socat_thread = None
        signal.signal(signal.SIGINT, self.signal_handler)

    def start_socat(self):
        command = "/usr/bin/socat -d -d pty,link=./ttyV1,raw,echo=0 pty,link=./ttyV2,raw,echo=0"
        self._socat_proc = subprocess.Popen(command, shell=True)
        self._socat_proc.wait()

    def start(self):
        self._socat_thread = Thread(target=self.start_socat)
        self._socat_thread.start()

    def wait(self):
        self._socat_thread.join()

    def kill(self):
        self._socat_proc.kill()

    def signal_handler(self, signal, frame):
        print('You pressed Ctrl+C!')

if __name__ == '__main__':
    # Usage Example
    tty_bridge = TTYBridge()
    tty_bridge.start()
    tty_bridge.wait()

