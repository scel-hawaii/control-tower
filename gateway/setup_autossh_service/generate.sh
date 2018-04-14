#!/bin/bash
#
# Generates the system files
#
echo "Requesting sudo access..."
sudo pwd

MAC_ADDRESS=$(/sbin/ifconfig | grep Ethernet | awk '{print $5}')


# Reverse SSH will take one port on the main system
declare -A reverse_ssh_ports
reverse_ssh_ports['b8:27:eb:8d:99:9c']=2222

# Remote deployment port
reverse_ssh_ports['b8:27:eb:73:63:4e']=2223

# reserved for other raspberry pi's
# reverse_ssh_ports['b8:27:eb:8d:99:9c']=2224

# Iterate through the associate array
for i in "${!reverse_ssh_ports[@]}"
do
    echo "key  : $i"
    echo "value: ${reverse_ssh_ports[$i]}"
done


exit 1

if [ "$MAC_ADDRESS" == "" ]; then
    echo "ERROR: MAC address could not be detected"
    exit 1
fi

echo "The MAC address is $MAC_ADDRESS"

if [ "$MAC_ADDRESS" == "b8:27:eb:8d:99:9c" ]; then
    echo "COOL"
else
    echo "ERROR you have an unregistered device."
    exit 1
fi

exit 0

BIND_PORT=1111
cp base_files/* generated_files
sed -i "s/{{LOCAL_BIND_PORT}}/$BIND_PORT/" generated_files/autossh-postgres


