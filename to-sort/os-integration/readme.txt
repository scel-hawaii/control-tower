coordinator-recv-db.py Operating System Integration

This shell script and upstart script allow coordinator-recv-db.py to
be run under our enterprise rack server's RHEL 6.4 Upstart 0.6.5. To
use this feature, first install these files to the indicated
locations:

  coordinator-recv-db: Shell script that lives in /usr/local/libexec
  to run the collection service as the unpriviliged user sensornet and
  log output to syslog.

  coordinator-recv-db.conf: Upstart configuration file that lives in
  /etc/init that describes how to start and stop the aforementioned
  shell script. This file further specifies that the data collection
  service should be started when the box's networking comes up.

  coordinator-recv-db.py: The Python program that does the lab work --
  connects to the XBee, processes incoming packets, and commits data
  to the database.

(install-coordinator.sh is a short shell script to copy these files to
the appropriate locations.)

Now, to manipulate coordinator-recv-db, issue the following commands:

  initctl start coordinator-recv-db
  initctl stop coordinator-recv-db
  initctl restart coordinator-recv-db
