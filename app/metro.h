/*******************************************************************************
 *@file name  : main.cpp
 *@brief      :
 *@author     : yazoo.bao
 *@mail       : 1027004184@qq.com
 *@creat time : 2018年 09月 19日 星期三 14:53:10 CST
*******************************************************************************/
#ifndef __METRO_H__
#define __METRO_H__
/*includes--------------------------------------------------------------------*/
#include "SocketHandler.h"
#include "TcpSocket.h"
#include "UdpSocket.h"
/*typedef---------------------------------------------------------------------*/
/*define----------------------------------------------------------------------*/
/*macro-----------------------------------------------------------------------*/
/*variables-------------------------------------------------------------------*/
/*function prototype----------------------------------------------------------*/

/*variables-------------------------------------------------------------------*/
class metro : public UdpSocket, public TcpSocket {
public:
	metro(ISocketHandler& h);

	~metro();

	void OnRawData(const char *buf,size_t nRecvLen,struct sockaddr *sa,socklen_t sa_len);
};
#endif
