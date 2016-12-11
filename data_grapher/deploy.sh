#!/bin/bash
#
# A simple shell script to deploy the data-grapher application
#
# This script can be run as any user
#
# The DEPLOY_ENV variable specifies which deployment environment
# you want to push to.
#
#

# Source the deployment enviroment variables (if it is generated)
source deploy_env.sh

TEMP_DIR=/tmp/data_grapher_deploy
DEPLOY_PATH=/home/$USER/apps/data_grapher

if [ "$DEPLOY_BRANCH" == "" ]
then
    DEPLOY_BRANCH=master
fi

rm -rf $TEMP_DIR
mkdir $TEMP_DIR
git clone https://github.com/scel-hawaii/control-tower.git $TEMP_DIR

cd $TEMP_DIR && git checkout $DEPLOY_BRANCH

# Clean up the existing data_grapher directory before deploying
rm -rf $DEPLOY_PATH
cp -R $TEMP_DIR $DEPLOY_PATH
