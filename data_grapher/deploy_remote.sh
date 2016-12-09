#
# remotely deploy data-grapher application
#
#
# for this to correctly work make sure you have
# scelserver-1 as an alias in your SSH config
HOST=control_tower@scelserver-1
DEPLOY_BRANCH=$(git rev-parse --abbrev-ref HEAD)

echo " DEPLOY_BRANCH=$DEPLOY_BRANCH " > deploy_env.sh

scp deploy.sh $HOST:/tmp/
scp deploy_env.sh $HOST:/tmp/
ssh $HOST 'cd /tmp && bash deploy.sh'

# Right now the deployment wipes away the old data - this
# is a hack that re-generates the gnuplot based graphs after
# a deployment.
#
# TODO: find out a better way to handle this later on.
#
ssh $HOST 'cd /home/control_tower/apps/data_grapher/data_grapher/ && bash plot_gnuplot.sh'
