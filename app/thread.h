/******************************************************************************
*@file   :thread.cpp
*@brief  :
*@author :yazoo.bao
*@mail   :1027004184@qq.com
*@date   :2018-09-20
******************************************************************************/
#ifndef __THREAD_h__
#define __THREAD_h__

/*includes-------------------------------------------------------------------*/
#include <pthread.h>
#include <unistd.h>

/*typedef--------------------------------------------------------------------*/
/*define---------------------------------------------------------------------*/
/*macro----------------------------------------------------------------------*/
/*variables------------------------------------------------------------------*/
/*function prototype---------------------------------------------------------*/
/*variables------------------------------------------------------------------*/
class thread
{
public:
    thread();
    ~thread();

    //线程状态
    static const int THREAD_STATUS_NEW = 0;
    static const int THREAD_STATUS_RUNNING = 1;
    static const int THREAD_STATUS_EXIT = -1;

    virtual void run() = 0;//线程的运行实体
    bool start();//开始执行线程
    pthread_t get_thread_id();//获取线程ID
    int get_state();//获取线程状态
    void join();//等待线程直至退出
    void join(unsigned long millistime);//等待线程退出或超时
private:
    pthread_t tid;//当前线程的线程ID
    int thread_status;//线程的状态
    static void *run0(void* pvoid);//获取执行方法的指针
    void *run1();//内部执行方法
};

#endif //__THREAD_h__