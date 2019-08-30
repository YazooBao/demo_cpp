/************************************************************************************
 *@file name  : main.cpp
 *@brief      :
 *@author     : yazoo.bao
 *@mail       : 1027004184@qq.com
 *@creat time : 2018年 09月 19日 星期三 14:53:10 CST
************************************************************************************/
#ifndef __QPAPP_H__
#define __QPAPP_H__
/*includes-------------------------------------------------------------------------*/
#include "qpcpp.h"
#include "thread.h"
using namespace QP;
using namespace std;
/*typedef--------------------------------------------------------------------------*/
/*define---------------------------------------------------------------------------*/
/*macro----------------------------------------------------------------------------*/
/*variables------------------------------------------------------------------------*/
/*function prototype---------------------------------------------------------------*/

/*variables------------------------------------------------------------------------*/
enum BlinkySignals {
    TIMEOUT_SIG = Q_USER_SIG,
    MAX_SIG
};

enum { BSP_TICKS_PER_SEC = 100 };

class qpapp : public thread
{
public:
    qpapp();
    ~qpapp();
    void run();
private:
    
};
#endif