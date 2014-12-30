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
 *                               ZPublic                                 *
 *                  Developer: zapline(278998871@qq.com)                 *
 *               Website: https://github.com/zpublic/zpublic             *
 *                                                                       *
 ************************************************************************/
#pragma once

/*
 * ACE�Ķ�ʱ�������ṩ��heap��wheel�����飩��hash��list���ֲ��Է�ʽ
 * libeventʹ�õ���minheap
 * libuvʹ�õ���rbtree
 * �����ܡ����������ӶȵȽǶȿ��Ǻ������ʹ�õ���stl��priority_queue
 * Ҳ��ˣ�ֻ�����������ɾ������
 * ���̰߳�ȫ���ⲿ��������֤
 */

NAMESPACE_ZL_BEGIN

class TimerTaskBase;

class TimerTaskQueue
{
public:
    TimerTaskQueue() {}
    ~TimerTaskQueue() {}

public:
    bool Insert(TimerTaskBase* pTask)
    {
        queue_.push(pTask);
        return true;
    }

    TimerTaskBase* Top()
    {
        return queue_.top();
    }

    TimerTaskBase* Pop()
    {
        TimerTaskBase* pTask = queue_.top();
        queue_.pop();
        return pTask;
    }

    unsigned int Size()
    {
        return (unsigned int)queue_.size();
    }

private:
    std::priority_queue<TimerTaskBase*, std::vector<TimerTaskBase*>, TimerTaskCmp> queue_;
};

NAMESPACE_ZL_END