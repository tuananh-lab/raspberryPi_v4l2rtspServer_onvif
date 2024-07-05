# DỰ ÁN XÂY DỰNG HỆ THỐNG MÁY CHỦ PHÁT VIDEO TRỰC TUYẾN SỬ DỤNG RTSP VÀ PHÁT HIỆN CAMERA ONVIF  TRONG MẠNG LAN TRÊN RASPBERY PI

## Giới thiệu dự án
Dự án "Xây dựng hệ thống máy chủ phát video trực tuyến và phát hiện camera onvif cục bộ trong mạng LAN trên Raspberry Pi" nhằm mục tiêu tạo ra một giải pháp phát trực tuyến video chất lượng cao và tiết kiệm chi phí bằng cách sử dụng Raspberry Pi. Bằng cách tích hợp các thư viện,submodules như V4L2RTSP và WS-DISCOVERY, dự án này sẽ tận dụng khả năng của Raspberry Pi để trở thành một máy chủ phát video mạnh mẽ, có thể truyền tải video qua giao thức RTSP và tương thích với chuẩn ONVIF.Cùng với việc truyền tải video thì hệ thống cũng cung cấp giải pháp tìm kiếm server chứa dịch vụ yêu cầu từ onvif client,tìm kiếm danh sách thiết bị camera onvif từ đó giúp việc quản lí camera một cách dễ dàng và hiệu quả. Điều này không chỉ mở ra khả năng giám sát an ninh hiệu quả mà còn ứng dụng rộng rãi trong nhiều lĩnh vực như giáo dục, phát thanh truyền hình, và các hệ thống IoT. Dự án hứa hẹn mang lại một giải pháp phát video trực tuyến linh hoạt, dễ triển khai và quản lý, đồng thời tối ưu hóa chi phí cho người dùng.

Người thực hiện: Trần Tuấn Anh
## 1. Cấu hình cho Raspberry Pi
Yêu cầu phần cứng:  
* Board Raspbery Pi 4 với Raspberry Pi OS (Debian Bullseye)  
* Camera Raspberry Pi v1.3

Trong các phiên bản hệ điều hành mới của Raspberry Pi đã sử dụng thư viện libcamera thay cho thư viện raspistill cũ.
Thư viện libcamera không hỗ trợ trực tiếp lấy dữ liệu H264, JPEG mà chúng ta chỉ có thể lấy được data video dạng YUV420
Trên những hệ điều hành mới của Rasberry Pi chúng ta có thể sử dụng những công cụ,thư viện tích hợp để chuyển đổi luồng dữ liệu thô YUV420 sang H264 để đẩy vào server để trình phát như libx264 hay libyuv.

Thay đổi nội dung file config.txt để sử dụng thư viện camera raspistill
```
$ nano /boot/config.txt
```

```
#camera_auto_detect=1

start_x=1
gpu_mem=128
```
Kiểm tra các định dạng hình ảnh được hỗ trợ
```
$ v4l2-ctl -d /dev/video0 --list-formats-ext
ioctl: VIDIOC_ENUM_FMT
        Type: Video Capture

        [0]: 'YU12' (Planar YUV 4:2:0)
                Size: Stepwise 32x32 - 2592x1944 with step 2/2
        [1]: 'YUYV' (YUYV 4:2:2)
                Size: Stepwise 32x32 - 2592x1944 with step 2/2
        [2]: 'RGB3' (24-bit RGB 8-8-8)
                Size: Stepwise 32x32 - 2592x1944 with step 2/2
        [3]: 'JPEG' (JFIF JPEG, compressed)
                Size: Stepwise 32x32 - 2592x1944 with step 2/2
        [4]: 'H264' (H.264, compressed)
                Size: Stepwise 32x32 - 2592x1944 with step 2/2
        [5]: 'MJPG' (Motion-JPEG, compressed)
                Size: Stepwise 32x32 - 2592x1944 with step 2/2
```
Máy chủ RTSP này hoạt động với máy ảnh Raspberry Pi bằng cách sử dụng trình điều khiển V4L2 mã nguồn mở bcm2835-v4l2
```
sudo nano /etc/modules
```
```
# at boot time, one per line. Lines beginning with "#" are ignored.

i2c-dev
bcm2835-v4l2
```

## 2. V4L2RstpServer
### 2.1. Giới thiệu
Đây là nguồn cấp dữ liệu truyền phát từ:
- thiết bị Video4Linux hỗ trợ ghi hình H264, HEVC, JPEG, VP8 hoặc VP9.  
- thiết bị ALSA hỗ trợ PCM S16_BE, S16_LE, S32_BE hoặc S32_LE
Máy chủ RTSP hỗ trợ:
- RTP/UDP đơn hướng
- Phát đa hướng RTP/UDP
- RTP/TCP
- RTP/RTSP/HTTP

### 2.2. Xây dựng
Cài đặt các thành phần phụ trợ
```
sudo apt-get update && sudo apt-get upgrade
sudo apt-get install cmake liblog4cpp5-dev libv4l-dev libssl-dev git raspberrypi-kernel-headers autoconf libtool -y
```
Xây dựng
```
git clone https://github.com/mpromonet/v4l2rtspserver.git
    
cd v4l2rtspserver/
cmake .
make
sudo make install
```
## 2.3. Sử dụng
Lệnh *./v4l2rtspserver - h* để xem các tùy chọn khi tạo máy chủ
```
./v4l2rtspserver [-v[v]] [-Q queueSize] [-O file] \
		       [-I interface] [-P RTSP port] [-p RTSP/HTTP port] [-m multicast url] [-u unicast url] [-M multicast addr] [-c] [-t timeout] \
		       [-r] [-s] [-W width] [-H height] [-F fps] [device1] [device2]
	 -v       : verbose
	 -vv      : very verbose
	 -Q length: Number of frame queue  (default 10)
	 -O output: Copy captured frame to a file or a V4L2 device
	 
	 RTSP options :
	 -I addr  : RTSP interface (default autodetect)
	 -P port  : RTSP port (default 8554)
	 -p port  : RTSP over HTTP port (default 0)
	 -U user:password : RTSP user and password
	 -R realm  : use md5 password 'md5(<username>:<realm>:<password>')
	 -u url   : unicast url (default unicast)
	 -m url   : multicast url (default multicast)
	 -M addr  : multicast group:port (default is random_address:20000)
	 -c       : don't repeat config (default repeat config before IDR frame)
	 -t secs  : RTCP expiration timeout (default 65)
	 -S[secs] : HTTP segment duration (enable HLS & MPEG-DASH)
	 -x <sslkeycert>  : enable RTSPS & SRTP
```
Ví dụ khởi tạo 1 server đơn giản để stream từ camera với độ phân giải 640x480, fps 25, port 8554
```
v4l2rtspserver -W 640 -H 480 -F 15 -P 8554 /dev/video0
```
Xem luồng stream qua vlc
```
vlc rtsp://192.168.x.x:8554/unicast
```
## 3. Tích hợp 
### 3.1. Giới thiệu
Đây là nỗ lực triển khai máy chủ ONVIF:

- dành cho thiết bị chụp V4L2 (NVT/NVS),
- cho các thiết bị đầu ra V4L2 (NVD).
### 3.2. Xây dựng
Tải source code dự án từ GitHub:
```
git clone https://github.com/tuananh-lab/raspberrypi_onvif_rtspServer.git
cd raspberrypi_onvif_rtspServer
make
```
Cài đặt các thành phần phụ trợ
```
sudo apt-get update && sudo apt-get upgrade
sudo apt-get install -y gsoap libgsoap-dev
sudo apt-get install cmake liblog4cpp5-dev libv4l-dev libssl-dev git raspberrypi-kernel-headers autoconf libtool -y
```
Xây dựng bằng Makefile
```
make
```

Sau đó các file source chứa các dịch vụ ONVIF sẽ được build ra từ các file WSDL và được lưu trong thư mục gen
### 3.3. Sử dụng
Tạo một máy chủ onvif
```
onvif-server.exe [-H http port] [-R rtsp port] [-u username] [-p password] [-i v4l2 input device] [-o v4l2 output device]
```
ví dụ
```ONVIF
cd /raspberrypi_onvif_rtspServer 
./onvif-server -i /dev/video0
```
Kết quả
```
$ ./onvif-server.exe -i /dev/video0
Http:8080 rtsp:8554
Published URL:http://127.0.1.1:8080/onvif/device_service
[NOTICE] /home/hust/raspberrypi_onvif_rtspServer/v4l2rtspserver/src/V4l2RTSPServer.cpp:37
        Create V4L2 Source.../dev/video0
[NOTICE] /home/hust/raspberrypi_onvif_rtspServer/v4l2rtspserver/libv4l2cpp/src/V4l2Device.cpp:133
        driver:bcm2835 mmal capabilities:85200005 mandatory:4000001
[NOTICE] /home/hust/raspberrypi_onvif_rtspServer/v4l2rtspserver/libv4l2cpp/src/V4l2Device.cpp:136
        /dev/video0 support capture
[NOTICE] /home/hust/raspberrypi_onvif_rtspServer/v4l2rtspserver/libv4l2cpp/src/V4l2Device.cpp:138
        /dev/video0 support read/write
[NOTICE] /home/hust/raspberrypi_onvif_rtspServer/v4l2rtspserver/libv4l2cpp/src/V4l2Device.cpp:139
        /dev/video0 support streamingcall soap_wsdd_Hello
```
Bây giờ mấy chủ onvif đã được xuất bản, có thể tìm thấy nó thông qua dịch vụ phát hiện thiết bị onvif trong mạng LAN
```
cd main
```
```
./dw_onvif.sh {IP}
```
thay thế **IP** bằng dải địa chỉ mạng LAN ví dụ: 192.168.137
Kết quả:
```$ ./dw_onvif.sh 192.168.137
Connecting to http://192.168.137.254:8080/onvif/device_service
=>Device::GetDeviceInformation
        Manufacturer:6.1.21-v8+
        Model:Linux
        FirmwareVersion:a59b554-dirty
        SerialNumber:#1642 SMP PREEMPT Mon Apr  3 17:24:16 BST 2023
        HardwareId:aarch64
=>Device::GetHostname
        Hostname:raspberrypi
=>Device::GetDNS
        DNS:192.168.137.1
=>Device::GetNetworkInterfaces
        wlan0 dc:a6:32:a2:e5:d3
        IP:192.168.137.254/24
```
### 3.4.Tạo nhiều camera ảo để có thể kiểm chứng hoạt động của server
Mở 3 terminal truy cập vào giao diện của Rasberry Pi
Mở 1 cửa sổ chạy server
```
./onvif-server.exe -i /dev/video0
```
Mở 1 cửa sổ chạy client khám phá toàn bộ dải IP và các port khác nhau
```
./dw_onvif.sh 192.168.137
```
Mở cửa sổ chạy các camera ảo 
```
cd virtual-camera/
./start.sh
```
Mọi người có thể so sánh kết quả của server với những công cụ phần mềm sẵn có như ONVIF Device Manager
## DOCKER
V4L2RtspServer
```
  docker run --device=/dev/video0 -p 8554:8554 -it mpromonet/v4l2rtspserver -u "" -H640 -W480 
```
Raspberrypi_onvif_rtspServer
```
docker run --device=/dev/video0 -p 8080:8080 -it raspberrypi_onvif_rtspServer
```
