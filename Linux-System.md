# Linux系统编程
- GDB常用命令
	- 命令|命令缩写|说明
	  :-: | :-: | :-:
	  list| l | 显示多行代码
	  break| b | 设置断点
	  info | i | 描述程序状态
	  run | r | 开始运行程序
	  display | disp | 跟踪查看某个变量值, 每次停下来都显示他的值
	  step | s | 执行下一条语句, 如果为函数调用, 则进入函数内部
	  next | n | 执行下一条语句, 不进入函数内部
	  print | p | 打印内部变量
	  continue | c | 继续运行程序, 直到下一个断点
	  set var name = value | | 设置变量的值
	  start | st | 开始执行, 在main函数的第一条语句前面停下来
	  file | | 装入需要调试的程序
	  kill | k | 终止正在调试的程序
	  watch  |  | 监事变量值的变化
	  backtrace | bt | 查看函数调用栈
	  frame | f | 查看栈桢
	  quit | q | 退出gdb
	  info threads | | 显示所有正在调试的线程
	  thread id | | 切换当前调试的线程为指定id的线程
	  break thread | | 在id线程设置断点
	  thread apply id1 id2 | | 让一个或者多个线程执行命令command
	  thread apply all command | | 让所有线程执行命令command
- tcpdump
	- n : 使用ip表示主机, 使用数字表示端口
	- i : 表示要监听的网卡信息
	- v : 输出一个较为详细的信息
	- t : 不打印时间戳
	- e : 显示以太网帧头部信息
	- c : 仅抓取指定数量的数据包
	- x : 以16进制显示数据包内容
	- s : 设置抓包长度
	- w : 输出以特殊格式定向到某一个文件
