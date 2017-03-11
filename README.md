# upload-reset
IntoRobot Atom/neutron等 从应用进入DFU升级模式，需要运行该工具.

使用方法:
./upload-reset -p /dev/ttyACM0 -b 19200 -t 2000

- p: 串口端口号
- b: 串口波特率, 默认19200
- t: 打开串口延时时间
