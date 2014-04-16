## Launch the coordinator server..
from coordinator_recv.coordinator_recv import CoordinatorReceiver

def init_arg_parse(self):
	parser = argparse.ArgumentParser()
	parser.add_argument('--output')
	parser.add_argument('--mode')
	parser.add_argument('--tty')
	self.args = parser.parse_args()
	# Warn the user that we're using a different mode.
	if self.args.mode:
		print "Warning: Default mode disabled!!!"
		print "\t\t -- " + self.args.mode + " -- mode enabled."
	if self.args.output:
		print "Warning: Manual server select type enabled."
		print "Running with " + self.args.output
	if self.args.tty:
		print "Warning: Manual ttyUSB selected."
		print "Running with " + self.args.tty





