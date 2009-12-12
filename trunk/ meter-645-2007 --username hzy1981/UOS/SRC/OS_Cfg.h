#ifndef OS_CFG_H
#define OS_CFG_H

#define OS_TASK_NUM       3 //最大任务个数,最大不能超过32
#define OS_EVENT_NUM      6 //最大事件个数
//注意：本系统最多支持32个任务和16个事件,如果需要支持更多个数，需要修改OS_Core.h文件中的Tcb和OS_Event中的变量

#define OS_TICK_ISR_EN    1 //0表示使用OS_Check_Tick()查询定时器的方式产生时基，1表示使用中断OS_Tick_ISR产生时基
#define OS_TICK_HOOK_EN   0 //Tick钩子使能
#define OS_MS_PER_TICK    10 //每个Tick间隔多少ms

#define OS_TASK_NAME_EN   1 //0表示不增加任务名字功能,1表示增加
#define OS_TASK_NAME_SIZE 10 //任务名字大小

#define OS_TASK_SWITCH_HOOK_EN 0

#define OS_TASK_SUSPEND_EN 0 //任务挂起功能

#define OS_CS_EN      1 //操作系统是否采用内存变量CS校验
#define OS_CS_BYTES       1 //校验和大小
#define OS_CS_TYPE        CS_CRC16_1//采用和校验方式,包括三种方式CS_SUM、CS_CRC16_0和CS_CRC16_1

#define OS_STK_GROWTH     1 //设置堆栈增长方向，1表示由高地址向低地址递减，0相反

#define OS_TRACE_EN       0
#define OS_TRACE_CTRL_EN  1 //定义断言的开关功能，1表示允许开关。0表示不允许开关，一直打开
                              //如果需要获取异常复位前的调用流程信息，需要在复位后马上关闭断言。然后在初始化
                              //调试串口后马上调用OS_ASSERT_FAILED()输出
#define OS_TRACE_NUM       1 //断言函数跟踪的个数
#define OS_TRACE_BUF_LEN   10 //每个断言记录内容长度
#define OS_TRACE_HOOK_EN    0 //断言函数内是否允许钩子函数，1表示允许

#define OS_ASSERT_EN      1 //1表示断言功能开启，0表示关闭
#define OS_ASSERT_HOOK_EN 1

#define OS_MUTEX_EN      1  //使用互斥信号量
#define OS_MUTEX_LOCK_CHK_EN      1 //1表示支持事件锁死检查，0表示不支持,只有互斥型信号量才有此功能
#define OS_MUTEX_WAIT_WARN_TIME   1 //申请信号量超时时间，超过该时间仍然申请不到，则进行锁死检查,单位为s

#define OS_MSG_EN        0  //使用消息
#define OS_MSG_WAIT_WARN_TIME 1 //消息等待超时报警时间，单位为s

#define OS_MSG_Q_EN      0 //使用消息队列
#define OS_MSG_Q_WAIT_WARN_TIME 1//消息队列等待超时报警时间，单位为s

#define OS_SEM_EN        0  //使用普通信号量
#define OS_SEM_WAIT_WARN_TIME 1 //信号量等待超时报警时间，单位s

#define OS_MEM_EN        0  //使用动态内存管理
#define OS_MEM_WAIT_WARN_TIME 1 //申请到的内存块的最长使用时间单位为s

#define OS_SHELL_EN      1

#if OS_MEM_EN>0 //定义动态内存的每个Block的大小
/*
#define MEM_BLOCK2_SIZE 200
#define MEM_BLOCK1_SIZE 400

#define MEM_BLOCK3_SIZE 600
#define MEM_BLOCK4_SIZE 800
#define MEM_BLOCK5_SIZE 1000
#define MEM_BLOCK6_SIZE 1200
#define MEM_BLOCK7_SIZE 1400
#define MEM_BLOCK8_SIZE 1600
#define MEM_BLOCK9_SIZE 1800
#define MEM_BLOCK10_SIZE 2000
#define MEM_BLOCK11_SIZE 2000
#define MEM_BLOCK12_SIZE 2000
#define MEM_BLOCK13_SIZE 2000
#define MEM_BLOCK14_SIZE 2000
#define MEM_BLOCK15_SIZE 2000
#define MEM_BLOCK16_SIZE 2000
#define MEM_BLOCK17_SIZE 2000
#define MEM_BLOCK18_SIZE 2000
#define MEM_BLOCK19_SIZE 2000
#define MEM_BLOCK20_SIZE 2000
#define MEM_BLOCK21_SIZE 2000
#define MEM_BLOCK22_SIZE 2000
#define MEM_BLOCK23_SIZE 2000
#define MEM_BLOCK24_SIZE 2000
#define MEM_BLOCK25_SIZE 2000
#define MEM_BLOCK26_SIZE 2000
#define MEM_BLOCK27_SIZE 2000
#define MEM_BLOCK28_SIZE 2000
#define MEM_BLOCK29_SIZE 2000
#define MEM_BLOCK30_SIZE 2000
*/
#endif

//#define OS_VERSION 106 //2008.03.29
//#define OS_VERSION 107 //2008.04.08
//#define OS_VERSION 108 //2008.04.19
//#define OS_VERSION 109 //2008.05.06
//#define OS_VERSION 110 //2008.06.12
//#define OS_VERSION 111 //2008.06.29
//#define OS_VERSION 112 //2008.07.25
//#define OS_VERSION 113 //2008.09.28
//#define OS_VERSION 114 //2008.10.12
//#define OS_VERSION 115 //2008.10.16
//#define OS_VERSION 116 //2008.10.23
//#define OS_VERSION 117 //2008.10.25

//#define OS_VERSION 118 
//2008.11.02 增加了信号量的锁死的分析和报警,同时将时间模块独立成OS_Time.c和OS_Time.h两个文件
//2008.11.03 修改了信号量申请函数中的一个bug(没有写设置校验域).

//#define OS_VERSION 119
//2008.11.04 增加了互斥信号量、信号量和消息机制

//#define OS_VERSION 120
//2008.11.05 增加了消息机制中的等待消息为空和无等待发送消息两个函数

//#define OS_VERSION 121
//2008.11.13 增加了带Head和Tail的结果体类型定义

//#define OS_VERSION 122
//2008.11.14 修改打印函数和任务id和任务数的类型等

//#define OS_VERSION 123081123
//增加动态内存管理，同时独立出OS_Event模块，修改部分宏

//#define OS_VERSION 124081124
//完善部分细节

//#define OS_VERSION 125081127
//完善部分细节

//#define OS_VERSION 126081209
//增加消息队列功能

//#define OS_VERSION 127081211
//去掉断言的返回值功能,更加规范断言的用法，不能引用断言的返回值

//#define OS_VERSION 128081211
//增加了预先定义动态内存块大小的宏

//#define OS_VERSION 129081214
//增加了定义消息队列信息块的宏

//#define OS_VERSION 130081217
//修改了消息队列信息块宏不能在VC下编译通过的问题

//#define OS_VERSION 132081221
//增加CRC校验算法

//#define OS_VERSION 133081222
//将CRC常量数组放到函数外部,防止占用堆栈空间

//#define OS_VERSION 134081224
//校验和算法增加一个与常数的异或,防止数据全为0的情况下校验也为0.释放内存时增加内存块检验.

//#define OS_VERSION 135090204
//OS_Pub.c中的断言函数在条件不成立的情况下才进入
//增加了断言内存的头尾检验
//修改了部分变量和宏名

//#define OS_VERSION 136090314
//修改断言为记录文件名和行号作为轨迹
//增加头尾变量定义的宏

//#define OS_VERSION 138090323
//将任务环境切换代码放到OS_Port中

//#define OS_VERSION 139090408
//将函数轨迹跟踪功能独立出来

//#define OS_VERSION 140090408
//将函数轨迹跟踪功能独立出来--一些改进

//#define OS_VERSION 141090409
//一些小改进

//#define OS_VERSION 142090415
//增加宏OS_ASSERT_FAILED()，替换OS_ASSERT(0)，可节省程序空间

//#define OS_VERSION 143090417
//修改消息发送函数，以及操作系统的各组件的信息输出函数

#define OS_VERSION 145090824
//增加任务的挂起功能
#endif
