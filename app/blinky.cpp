/*******************************************************************************
 *@file name  : main.cpp
 *@brief      :
 *@author     : yazoo.bao
 *@mail       : 1027004184@qq.com
 *@creat time : 2018年 09月 19日 星期三 14:53:10 CST
*******************************************************************************/
/*includes--------------------------------------------------------------------*/
#include "blinky.h"
#include "easylogging++.h"

/*typedef---------------------------------------------------------------------*/

/*define----------------------------------------------------------------------*/
/*macro-----------------------------------------------------------------------*/
/*variables-------------------------------------------------------------------*/
/*function prototype----------------------------------------------------------*/
/*variables-------------------------------------------------------------------*/

//$define${AOs::Blinky} ######################################################
//${AOs::Blinky} .............................................................
//${AOs::Blinky::Blinky} .....................................................
Blinky::Blinky()
: QActive(Q_STATE_CAST(&Blinky::initial)),
    m_timeEvt(this, TIMEOUT_SIG, 0U)
{}

//${AOs::Blinky::SM} .........................................................
QP::QState Blinky::initial(Blinky * const me, QP::QEvt const * const e) {
    //${AOs::Blinky::SM::initial}
    (void)e; // unused parameter
    me->m_timeEvt.armX(BSP_TICKS_PER_SEC/2, BSP_TICKS_PER_SEC/2);

    QS_FUN_DICTIONARY(&off);
    QS_FUN_DICTIONARY(&on);

    return Q_TRAN(&off);
}
//${AOs::Blinky::SM::off} ....................................................
QP::QState Blinky::off(Blinky * const me, QP::QEvt const * const e) {
    QP::QState status_;
    switch (e->sig) {
        //${AOs::Blinky::SM::off}
        case Q_ENTRY_SIG: {
            LOG(INFO) << "LED OFF";
            status_ = Q_HANDLED();
            break;
        }
        //${AOs::Blinky::SM::off::TIMEOUT}
        case TIMEOUT_SIG: {
            status_ = Q_TRAN(&on);
            break;
        }
        default: {
            status_ = Q_SUPER(&top);
            break;
        }
    }
    return status_;
}
//${AOs::Blinky::SM::on} .....................................................
QP::QState Blinky::on(Blinky * const me, QP::QEvt const * const e) {
    QP::QState status_;
    switch (e->sig) {
        //${AOs::Blinky::SM::on}
        case Q_ENTRY_SIG: {
            LOG(INFO) << "LED ON";
            status_ = Q_HANDLED();
            break;
        }
        //${AOs::Blinky::SM::on::TIMEOUT}
        case TIMEOUT_SIG: {
            status_ = Q_TRAN(&off);
            break;
        }
        default: {
            status_ = Q_SUPER(&top);
            break;
        }
    }
    return status_;
}
//$enddef${AOs::Blinky} ######################################################