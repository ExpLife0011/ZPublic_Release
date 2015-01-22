/*************************************************************************
*                                                                       *
*  I|*j^3Cl|a   "+!*%                  qt          Nd   gW              *
*  l]{y+l?MM*  !#Wla\NNP               NW          MM   I|              *
*        PW    ?E|    tWg              Wg  sC!     AW           ~@v~    *
*       NC     ?M!    yN|  WW     MK   MW@K1Y%M@   RM   #Q    QP@tim    *
*     CM|      |WQCljAE|   MD     Mg   RN     cM~  NM   WQ   MQ         *
*    #M        aQ?         MW     M3   Mg      Q(  HQ   YR  IM|         *
*   Dq         {Ql         MH    iMX   Mg     MM   QP   QM   Eg         *
* !EWNaPRag2$  +M"          $WNaHaN%   MQE$%EXW    QQ   CM    %M%a$D    *
*                                                                       *
*               Website: https://github.com/zpublic/zpublic             *
*                                                                       *
************************************************************************/
#pragma once

#include "z_timer_def.h"

NAMESPACE_ZL_BEGIN

class TimerTaskBase
{
public:
    TimerTaskBase(
        unsigned int taskid = 0,
        unsigned int tasktype = 0,
        unsigned int timeout = 1,
        unsigned int times = 1)
    {
        taskid_         = taskid;
        tasktype_       = tasktype;
        timeout_        = timeout;
        times_          = times;
        executed_       = 0;
        starttime_      = TimerGetTime();
        invalid_        = false;
        release_        = true;
    }
    virtual ~TimerTaskBase() {}

public:
    virtual void DoWork() = 0;

    ///> ִ�и�������Ҫ�ȴ���ʱ��
    int WaitTime()
    {
        return (timeout_ * (executed_ + 1)) - (TimerGetTime() - starttime_);
    }

    unsigned int Taskid() const { return taskid_; }
    void Taskid(unsigned int val) { taskid_ = val; }

    unsigned int Tasktype() const { return tasktype_; }
    void Tasktype(unsigned int val) { tasktype_ = val; }

    unsigned int Timeout() const { return timeout_; }
    void Timeout(unsigned int val) { timeout_ = val; }

    unsigned int Times() const { return times_; }
    void Times(unsigned int val) { times_ = val; }
    bool Repeat() const { return (times_ == TaskRepeatDef); }
    void Repeat(bool val) { times_ = val ? TaskRepeatDef : 0; }

    unsigned int Executed() const { return executed_; }
    void ExecutedAdd() { executed_++; }

    bool Invalid() const { return invalid_; }
    void SetInvalid() { invalid_ = true; }

    bool Release() const { return release_; }
    void Release(bool val) { release_ = val; }

protected:
    unsigned int taskid_;            ///> ����id���Լ�����
    unsigned int tasktype_;          ///> ����������������飬�Լ�����
    unsigned int timeout_;           ///> ��ʱʱ��
    unsigned int times_;             ///> ִ�д���(99999Ϊrepeat���޴���)
    unsigned int executed_;          ///> ��ִ�д���
    unsigned int starttime_;         ///> ����ʼʱ��
    bool         invalid_;           ///> �Ƿ���Ч��һ����ǣ����úǺ�
    bool         release_;           ///> �Ƿ��ɵ�������delete��Ĭ��true
};

struct TimerTaskCmp
{
    bool operator()(TimerTaskBase* k1, TimerTaskBase* k2) const
    {
        return k1->WaitTime() > k2->WaitTime();
    }
};

typedef void (* PTimerTaskFunc)(TimerTaskBase* pTask);
typedef void (* PTimerTaskFunc2)();
class TimerTaskNolmal : public TimerTaskBase
{
public:
    TimerTaskNolmal(PTimerTaskFunc pfunc = NULL) : pfunc_(pfunc)
    {
        pfunc2_ = NULL;
    }
    TimerTaskNolmal(PTimerTaskFunc2 pfunc) : pfunc2_(pfunc)
    {
        pfunc_ = NULL;
    }
    virtual ~TimerTaskNolmal() {}
    virtual void DoWork()
    {
        if (pfunc_)
        {
            pfunc_((TimerTaskBase*)this);
        }
        else if (pfunc2_)
        {
            pfunc2_();
        }
    }
    void set(PTimerTaskFunc pfunc)
    {
        pfunc_ = pfunc;
        pfunc2_ = NULL;
    }
    void set(PTimerTaskFunc2 pfunc)
    {
        pfunc2_ = pfunc;
        pfunc_ = NULL;
    }

protected:
    PTimerTaskFunc  pfunc_;
    PTimerTaskFunc2 pfunc2_;
};

NAMESPACE_ZL_END