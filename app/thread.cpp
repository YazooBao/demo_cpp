/******************************************************************************
*@file   :thread.cpp
*@brief  :
*@author :yazoo.bao
*@mail   :1027004184@qq.com
*@date   :2018-09-20
******************************************************************************/

/*includes-------------------------------------------------------------------*/
#include "thread.h"
#include "easylogging++.h"
/*typedef--------------------------------------------------------------------*/
/*define---------------------------------------------------------------------*/
/*macro----------------------------------------------------------------------*/
/*variables------------------------------------------------------------------*/
/*function prototype---------------------------------------------------------*/
/*variables------------------------------------------------------------------*/

void* thread::run0(void *pvoid) {
    thread *p = (thread*)pvoid;
    p->run1();
    return p;
}

void *thread::run1(){
    thread_status = THREAD_STATUS_RUNNING;
    tid = pthread_self();
    run();
    pthread_exit(NULL);
}

thread::thread(){
    tid = 0;
    thread_status = THREAD_STATUS_NEW;
}

thread::~thread() {
    
}

bool thread::start(){
    int err = -1;
    err = pthread_create(&tid, NULL, run0, this);

    if(err != 0){
        LOG(WARNING) << "create thread failed!err=" << err;
        return false;
    }
    else{
        LOG(INFO) << "create thread success!tid=" << tid;
        return true;
    }
}

pthread_t thread::get_thread_id(){
    return tid;
}

int thread::get_state(){
    return thread_status;
}

void thread::join(){
    if(tid > 0){
        pthread_join(tid, NULL);
    }
}

void thread::join(unsigned long millistime){
    if(tid == 0){
        return;
    }
    if(millistime == 0){
        join();
    }
    else{
        unsigned long k = 0;
        while(thread_status != THREAD_STATUS_EXIT && k <= millistime){
            usleep(100);
            k++;
        }
    }
}
