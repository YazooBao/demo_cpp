/************************************************************************************
 *@file name  : qp.cpp
 *@brief      :
 *@author     : yazoo.bao
 *@mail       : 1027004184@qq.com
 *@creat time : 2018年 09月 19日 星期三 14:53:10 CST
************************************************************************************/
/*includes-------------------------------------------------------------------------*/
#include "qpapp.h"
#include "easylogging++.h"
#include <pthread.h>
#include "blinky.h"
/*typedef--------------------------------------------------------------------------*/
/*define---------------------------------------------------------------------------*/
/*macro----------------------------------------------------------------------------*/
/*variables------------------------------------------------------------------------*/
/*function prototype---------------------------------------------------------------*/
/*variables------------------------------------------------------------------------*/

extern "C" void Q_onAssert(char const * const module, int loc) {
    cout << "Assertion failed in " << module << ':' << loc << endl;
    exit(-1);
}
void QF::onStartup(void) {}
void QF::onCleanup(void) {}
void QP::QF_onClockTick(void) {
    QF::TICK_X(0U, (void *)0);  // perform the QF clock tick processing
}
qpapp::qpapp() {

}
qpapp::~qpapp() {
    
}
void qpapp::run(void) {
    Blinky *pblinky = new Blinky;
    // statically allocate event queue buffer for the Blinky AO
    static QEvt const *blinky_queueSto[10];

    QF::init(); // initialize the framework
    pblinky->start(1U, // priority
                     blinky_queueSto, Q_DIM(blinky_queueSto),
                     (void *)0, 0U); // no stack
    QF::run(); // run the QF application
}




