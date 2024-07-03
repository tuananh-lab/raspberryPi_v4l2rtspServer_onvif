#!/bin/bash


# Check if user provided network range
if [ -z "$1" ]; then
  echo "Usage: $0 <network-prefix>"
  echo "Example: $0 192.168.0"
  exit 1
fi

# Get network range from command line parameters
network="$1"

# Network range from 1 to 254 depend on my subnet
for ip in {1..254}; do
  # Ping to IP address once and wait 1s to receive a response
  (
    if ping -c 1 -W 1 ${network}.${ip} > /dev/null 2>&1; then
      ./v4l2onvif/onvif-client.exe "http://${network}.${ip}:8080/onvif/device_service"
      ./v4l2onvif/onvif-client.exe "http://${network}.${ip}:10000/onvif/device_service"
      ./v4l2onvif/onvif-client.exe "http://${network}.${ip}:10001/onvif/device_service"
    fi
  ) &
done

# 8080 is the default HTTP port that the server is waiting on.
# 10000 and 10001 are the ports where the virtual onvif camera is created.

# Wait ping command completed
wait
