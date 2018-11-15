sudo lttng create nsession --output=/home/siddesh/nsession
sudo lttng enable-event --kernel --all --syscall
sudo lttng-track-process --procname=readtest nsession
sudo lttng start
./readtest
sudo lttng stop
