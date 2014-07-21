# Setup a slave box's tunnel to the scel lab

# SPECIFY an RSA key location (one with no passwd)
RSA_KEY=""

# The port you'll be connecting to on the master
REMOTE_PORT=19998

# Local port which the master port forwards to, usually SSH
LOCAL_PORT=22

# Hostname 
HOSTNAME="reis1remote"

autossh -f -i -R $REMOTE_PORT:localhost:$LOCAL_PORT $HOSTNAME -N
