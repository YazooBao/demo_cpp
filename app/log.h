/*******************************************************************************
 *@file name  : main.cpp
 *@brief      :
 *@author     : yazoo.bao
 *@mail       : 1027004184@qq.com
 *@creat time : 2018年 09月 19日 星期三 14:53:10 CST
*******************************************************************************/
#ifndef __LOG_H__
#define __LOG_H__
/*includes--------------------------------------------------------------------*/
#include "SocketHandler.h"
#include "TcpSocket.h"
#include "UdpSocket.h"
#include "easylogging++.h"
using namespace std;
/*typedef---------------------------------------------------------------------*/
#pragma pack(push, 1)
typedef struct
{
    unsigned short stx;    /* [1]起始符 0xFA05  */
    char prefix[8];        /* [2]前缀 PECU设备为DPECU;电话设备为DPHONE    */
    unsigned char type;    /* [3]日志类型 字符串:0;二进制:1*/
    unsigned short len;    /* [4]数据长度 长度不超过500*/
    // char data[1];          /* [5]数据     */
}LogInfo_t;
#pragma pack(pop)
/*define----------------------------------------------------------------------*/
/*macro-----------------------------------------------------------------------*/
/*variables-------------------------------------------------------------------*/
/*function prototype----------------------------------------------------------*/

/*variables-------------------------------------------------------------------*/
void log_init(void);
void log_set_net(std::string _ip, port_t _port);
void log_set_prefix(char *name);
void log_hexdump(int width, uint8_t *buf, int size);


#endif
