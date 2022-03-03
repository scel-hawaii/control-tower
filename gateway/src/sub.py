import sys
import zmq

port = "5556"

# Socket to talk to server
context = zmq.Context()
socket = context.socket(zmq.SUB)

# print "Collecting updates from weather server..."
# socket.connect ("tcp://localhost:%s" % port)
socket.connect("ipc://tmp.socket")

# Subscribe to zipcode, default is NYC, 10001
socket.setsockopt(zmq.SUBSCRIBE, "")

while True:
    string = socket.recv()
    sys.stdout.write(string)
    sys.stdout.write('\n')
    sys.stdout.flush()