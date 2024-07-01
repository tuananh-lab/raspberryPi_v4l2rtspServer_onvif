#! /bin/sh

CUR=$PWD

if [ ! -f $CUR/libavcodec.so.58 ]; then 
ln -s $CUR/libavcodec.so.58.18.100 $CUR/libavcodec.so.58
fi

if [ ! -f $CUR/libavcodec.so ]; then 
ln -s $CUR/libavcodec.so.58.18.100 $CUR/libavcodec.so
fi

if [ ! -f $CUR/libavdevice.so.58 ]; then 
ln -s $CUR/libavdevice.so.58.3.100 $CUR/libavdevice.so.58
fi

if [ ! -f $CUR/libavdevice.so ]; then
ln -s $CUR/libavdevice.so.58.3.100 $CUR/libavdevice.so
fi

if [ ! -f $CUR/libavfilter.so.7 ]; then
ln -s $CUR/libavfilter.so.7.16.100 $CUR/libavfilter.so.7
fi

if [ ! -f $CUR/libavfilter.so ]; then
ln -s $CUR/libavfilter.so.7.16.100 $CUR/libavfilter.so
fi

if [ ! -f $CUR/libavformat.so.58 ]; then
ln -s $CUR/libavformat.so.58.12.100 $CUR/libavformat.so.58
fi

if [ ! -f $CUR/libavformat.so ]; then
ln -s $CUR/libavformat.so.58.12.100 $CUR/libavformat.so
fi

if [ ! -f $CUR/libavutil.so.56 ]; then
ln -s $CUR/libavutil.so.56.14.100 $CUR/libavutil.so.56
fi

if [ ! -f $CUR/libavutil.so ]; then 
ln -s $CUR/libavutil.so.56.14.100 $CUR/libavutil.so
fi

if [ ! -f $CUR/libpostproc.so.55 ]; then 
ln -s $CUR/libpostproc.so.55.1.100 $CUR/libpostproc.so.55
fi

if [ ! -f $CUR/libpostproc.so ]; then 
ln -s $CUR/libpostproc.so.55.1.100 $CUR/libpostproc.so
fi

if [ ! -f $CUR/libswresample.so.3 ]; then 
ln -s $CUR/libswresample.so.3.1.100 $CUR/libswresample.so.3
fi

if [ ! -f $CUR/libswresample.so ]; then 
ln -s $CUR/libswresample.so.3.1.100 $CUR/libswresample.so
fi

if [ ! -f $CUR/libswscale.so.5 ]; then 
ln -s $CUR/libswscale.so.5.1.100 $CUR/libswscale.so.5
fi

if [ ! -f $CUR/libswscale.so ]; then 
ln -s $CUR/libswscale.so.5.1.100 $CUR/libswscale.so
fi

if [ ! -f $CUR/libopus.so.0 ]; then 
ln -s $CUR/libopus.so.0.8.0 $CUR/libopus.so.0
fi

if [ ! -f $CUR/libopus.so ]; then 
ln -s $CUR/libopus.so.0.8.0 $CUR/libopus.so
fi

if [ ! -f $CUR/libx264.so ]; then 
ln -s $CUR/libx264.so.161 $CUR/libx264.so
fi

if [ ! -f $CUR/libx265.so ]; then 
ln -s $CUR/libx265.so.116 $CUR/libx265.so
fi

if [ ! -f $CUR/libssl.so ]; then 
ln -s $CUR/libssl.so.1.1 $CUR/libssl.so
fi

if [ ! -f $CUR/libcrypto.so ]; then 
ln -s $CUR/libcrypto.so.1.1 $CUR/libcrypto.so
fi

if [ ! -f $CUR/libz.so.1 ]; then 
ln -s $CUR/libz.so.1.2.11 $CUR/libz.so.1
fi

if [ ! -f $CUR/libz.so ]; then 
ln -s $CUR/libz.so.1.2.11 $CUR/libz.so
fi

if [ ! -f $CUR/libsrt.so.1.5 ]; then 
ln -s $CUR/libsrt.so.1.5.0 $CUR/libsrt.so.1.5
fi

if [ ! -f $CUR/libsrt.so ]; then 
ln -s $CUR/libsrt.so.1.5 $CUR/libsrt.so
fi

echo "make symbolic link finish!"
