# 传输层与网络层
## TCP(面向连接，可靠的，面向字节流)

- TCP协议字段理解
	- 16位源/目的端口号: 表示数据从那个进程中来,到那个进程去
	- 32位序号/确认序号: TCP将每个字节的数据都进行了编号称为序列号,接收端收到数据之后发送确认序号给发送端
	- 4位头部长度: 表示头部有多少个4字节,所以TCP最大长度为15*4=60字节
	- 六位保留
	- 6位标志位
	- 16位窗口大小: 无需等待确认应答可以继续发送数据的最大值
	- 16位校验和: 发送端填充,CRC校验,接收端认为校验不通过,认为数据有问题,可以直接丢弃
	- 16位紧急指针

- 为什么要三次握手?
	- 防止已经失效的连接骑牛报文段,客户端发送的请求在网络中的滞留时间长
	导致服务器为一个客户端开辟两个连接
	- 两次握手的话,服务器在接收到连接请求需要建立数据结构来维护连接请求
	如果服务器ACK丢失,就会出现SYN泛洪攻击,同时三次握手保护服务器,第三次
	ACK丢失,服务器处于半连接状态,服务器认为连接没有建立成功,只有客户端会
	建立数据结构维护连接,当客户端发送数据,TCP首部字段RST置1,重新建立连接
- 为什么要四次挥手?
	- TCP是面向连接的,断开连接是双向的,不仅要断开服务器对客户端的连接,
	还要断开客户端对服务器的连接
	- 四次挥手客户端向服务器发送FIN包,服务器知道断开连接,发送一个ACK,
	并且将自己的状态改为半连接状态,不在接收客户端数据,但是还需要把剩余
	数据发送给客户端,当数据发送完毕,服务器发送FIN包,客户端收到FIN之后
	发送给服务器ACK
	- 客户端收到FIN包之后,回复ACK,双方连接均已删除,服务器不知道FIN包是否被接收
	客户端的ACK也可能丢失,所以主动断开连接方进入`TIME_WAIT`状态
- 为什么握手三次挥手四次
	- 服务端LINSTEN状态下的socket收到SYN报文后会将ACK和SYN一起发送给对方
	但是关闭连接时,收到FIN包只是表示对方没有数据发送,但是未必自己的数据完全
	传送给对方,需要发送一些数据,之后再次发送FIN包,
- 如何理解`TIME_WAIT`
	- 主动关闭方在最后一次发送ACK时,这个ACK可能会丢掉,被动方等待一段时间之后
	没有ACK认为FIN没有发送成功然后重新发送,如果发送完ACK直接关闭,那么ACK
	丢失服务器会维持这个无效连接很长时间,浪费服务器资源,如果主动关闭方又
	重新建立socket,会对新的socket造成影响
	- 让主动方等待2个MSL时间,确认ACK已经到达对方,这个时候收到对方FIN包
	定时器重启
	- 保护主动关闭方,超过2个MSL时间之后,在次受到FIN包,这个数据被丢弃
- 什么是三次握手,四次挥手
	- TCP是一种面向连接的单播协议,	在发送数据时通信双方必须建立一条连接
	链接就是服务器和客户端保存的关于对方的信息
	- TCP提供一种可靠,面向连接,字节流的传输层服务,采用三次握手建立连接,四次挥手断开连接
