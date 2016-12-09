#
# A simple shell script to deploy the data-grapher application
#
# This script can be run as any user

rm /tmp/master.zip
rm -rf /tmp/control-tower-master
cd /tmp && wget https://github.com/scel-hawaii/control-tower/archive/master.zip
cd /tmp && unzip master.zip

DEPLOY_PATH=/home/$USER/apps/data_grapher

rm -rf $DEPLOY_PATH
mv /tmp/control-tower-master $DEPLOY_PATH
