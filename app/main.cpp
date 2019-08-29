/*******************************************************************************
 *@file name  : main.cpp
 *@brief      :
 *@author     : yazoo.bao
 *@mail       : 1027004184@qq.com
 *@creat time : 2018年 09月 19日 星期三 14:53:10 CST
*******************************************************************************/
/*includes--------------------------------------------------------------------*/
#include "version.h"
#include "qpapp.h"
#include "blinky.h"
#include "SocketHandler.h"
#include "TcpSocket.h"
#include "UdpSocket.h"
#include <pthread.h>
#include "easylogging++.h"
#include "log.h"
#include "tinyxml2.h"
using namespace tinyxml2;
_INITIALIZE_EASYLOGGINGPP
/*typedef---------------------------------------------------------------------*/
/*define----------------------------------------------------------------------*/
/*macro-----------------------------------------------------------------------*/
/*variables-------------------------------------------------------------------*/
/*function prototype----------------------------------------------------------*/
/*variables-------------------------------------------------------------------*/

int main(int argc, const char *argv[])
{
    argc = argc;
    argv = argv;
    // easyloggingpp::Configurations conf("log.conf");
    // easyloggingpp::Loggers::setDefaultConfigurations(conf, true);
    // SocketHandler *shand = new SocketHandler();
    // uskt = new UdpSocket(*shand);
    // // port_t port=8888;
    // // uskt->Bind(port);
    // // uskt->AddMulticastMembership("225.0.0.88", "0.0.0.0");
    // // shand->Add(uskt);
    // easyloggingpp::Loggers::setDispatchCallback(net_send);

    log_init();
    log_set_net("225.0.0.88", 8888);
    // log_set_prefix("ascu");
    
    LOG(INFO) << PRJ_NAME;
    LOG(INFO) << BUILD_TIME;
    LOG(INFO) << BUILD_VERSION;
    LOG(INFO) << "SVN VERSION:" << SVN_VERSION;
    LOG(INFO) << GIT_HASH;
    LINFO << "this is my first log";
    LOG(INFO) << "defalut logger INFO";
    LOG(INFO) << "first line\n second line\n 3th line";

uint8_t data[0xff] = {0x11,0x22,0x33,0x44,0x55,0x66,0x77,0x88,0x99,0x99};
for (int i=0;i<0x5;i++) {
    data[i] = i;
}
log_hexdump(10,data, 0x5);


    qpapp *pqpapp = new qpapp;
    pqpapp->start();

    XMLDocument *doc = new XMLDocument();
    if(doc->LoadFile("./cfg.xml")==XML_SUCCESS) {
        LOG(INFO) << "load cfg.xml success!";
    }
    else {
        LOG(INFO) << "load cfg.xml failed!";
    }
    int errorID = doc->ErrorID();
    LOG(INFO) << "error id:" << errorID;

    delete doc;

    for (;;) {
        sleep(1);
    }
    return 0;
}
