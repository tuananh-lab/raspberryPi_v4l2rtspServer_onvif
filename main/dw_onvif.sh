#!/bin/bash

# Kiểm tra xem người dùng đã cung cấp dải mạng hay chưa
if [ -z "$1" ]; then
  echo "Usage: $0 <network-prefix>"
  echo "Example: $0 192.168.0"
  exit 1
fi

# Nhận dải mạng từ tham số dòng lệnh
network="$1"

# Dải mạng từ 1 đến 254 (tùy thuộc vào subnet của bạn, có thể thay đổi nếu cần)
for ip in {1..254}; do
  # Ping địa chỉ IP một lần và chờ 1 giây để nhận phản hồi
  (
    if ping -c 1 -W 1 ${network}.${ip} > /dev/null 2>&1; then
      ./v4l2onvif/onvif-client.exe "http://${network}.${ip}:8080/onvif/device_service"
      ./v4l2onvif/onvif-client.exe "http://${network}.${ip}:10000/onvif/device_service"
      ./v4l2onvif/onvif-client.exe "http://${network}.${ip}:10001/onvif/device_service"
    fi
  ) &
done

# Chờ tất cả các lệnh ping hoàn thành
wait