/************************************************************************************
 *@file name  : main.cpp
 *@brief      :
 *@author     : yazoo.bao
 *@mail       : 1027004184@qq.com
 *@creat time : 2018年 09月 19日 星期三 14:53:10 CST
************************************************************************************/
#ifndef __BLINKY_H__
#define __BLINKY_H__
/*includes-------------------------------------------------------------------------*/
#include "qpapp.h"
/*typedef--------------------------------------------------------------------------*/
/*define---------------------------------------------------------------------------*/
/*macro----------------------------------------------------------------------------*/
/*variables------------------------------------------------------------------------*/
/*function prototype---------------------------------------------------------------*/

/*variables------------------------------------------------------------------------*/
class Blinky : public QP::QActive {
private:
    QP::QTimeEvt m_timeEvt;

public:
    Blinky();

protected:
    static QP::QState initial(Blinky * const me, QP::QEvt const * const e);
    static QP::QState off(Blinky * const me, QP::QEvt const * const e);
    static QP::QState on(Blinky * const me, QP::QEvt const * const e);
};
#endif
