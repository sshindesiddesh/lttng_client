#! /bin/bash
echo "Hello World"
sudo lttng create nsession --output=/home/siddesh/nsession
#sudo lttng enable-channel channel0 -k --discard --subbuf-size 8192 --num-subbuf 512 --output=splice
sudo lttng enable-channel channel0 -k --discard --num-subbuf 32
sudo lttng enable-event -s nsession -c channel0 --kernel --all --syscall
sudo lttng track -k --pid=$1
sudo lttng start
