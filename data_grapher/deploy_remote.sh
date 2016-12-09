#
# remotely deploy data-grapher application
#
#
# for this to correctly work make sure you have
# scelserver-1 as an alias in your SSH config
HOST=control_tower@scelserver-1

scp deploy.sh $HOST:/tmp/
ssh $HOST 'cd /tmp && bash deploy.sh'
