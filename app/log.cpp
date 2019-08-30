/*******************************************************************************
 *@file name  : main.cpp
 *@brief      :
 *@author     : yazoo.bao
 *@mail       : 1027004184@qq.com
 *@creat time : 2018年 09月 19日 星期三 14:53:10 CST
*******************************************************************************/
/*includes--------------------------------------------------------------------*/
#include "log.h"
#include <iomanip>
/*typedef---------------------------------------------------------------------*/

/*define----------------------------------------------------------------------*/
/*macro-----------------------------------------------------------------------*/
/*variables-------------------------------------------------------------------*/
port_t port;
string string_ip;
SocketHandler *shand;
UdpSocket *uskt;
char head_buf[sizeof(LogInfo_t)] = {0};
LogInfo_t *log_head;
/*function prototype----------------------------------------------------------*/
static void net_send(string line);
void log_hexdump(int level, string loggerid, int width, char *buf, int size) ;
/*variables-------------------------------------------------------------------*/

void log_init(void)
{
    uskt = NULL;
    shand = NULL;
    log_head = (LogInfo_t *)head_buf;
    log_head->stx = 0xfa05;
    memcpy(log_head->prefix, "metro", sizeof("metro"));
    log_head->type = 0;
    log_head->len = 0;
    easyloggingpp::Configurations conf("log.conf");
    easyloggingpp::Loggers::setDefaultConfigurations(conf, true);
}

void log_set_net(std::string _ip, port_t _port) {
    if (uskt && shand) {
        LOG(WARNING) << "net log created!---" << string_ip << ":" << port;
    }
    else {
        shand = new SocketHandler();
        uskt = new UdpSocket(*shand);
        easyloggingpp::Loggers::setDispatchCallback(net_send);
        string_ip = _ip;
        port = _port;
        LOG(INFO) << "net log success!---" << string_ip << ":" << port;
    }
    
}

static void net_send(string line) {
    char buffer[1024] = {0};
    log_head->len = line.length();
    memcpy(buffer, head_buf, sizeof(head_buf));
    memcpy(&buffer[sizeof(head_buf)], line.c_str(), line.length());
    if (uskt) {
        uskt->SendToBuf(string_ip, port, buffer,log_head->len+sizeof(head_buf));
    }
}

void log_set_prefix(string name) {
    memcpy(log_head->prefix, name.c_str(), name.length());
}

void log_hexdump(int width, uint8_t *buf, int size) {
    string dump_string;
    dump_string = "D/HEX:\n";
    stringstream ss;
    int count=0;
    for (int i=0;i<size;i++) {
        count++;
        ss << hex << setw(2) << left << (int)buf[i] << " ";
        if (count%width==0) {
            ss << endl;
        }
    }
    dump_string += ss.str();
    LOG(INFO) << dump_string;
}