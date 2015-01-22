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

/************************************************************************/
/*  ��Ҫ��Ե����⣺
/*      �������������c++���첽ִ�д��룿
/*      �����������ڽ����߳��Ҫ��һ��ʵʱ�������ϱ�
/*  ��Ҫ�ĵ㣺
/*      1�������̳߳���ƣ�ÿ��taskһ���߳�
/*      2����Ҫִ�еĴ���ŵ��첽�߳�ȥִ��֮�󣬲��ᳫ��ѯ״̬�ķ���
/*      3��task manager�̰߳�ȫ
/*      3��task manager����taskִ�����Զ��ͷ���Դ
/*      4��task manager�ܵȴ����ͷ�����task
/*      5��ͬһ��task���ܼ����Σ������� obj.PostTask(new taskA);
/**************************************************************************/

#include <map>
#include <windows.h>
#include <process.h>
#include "../thread_sync/thread_sync.h"

#ifndef NAMESPACE_ZL_BEGIN
#define NAMESPACE_ZL_BEGIN      namespace zl {
#define NAMESPACE_ZL_END        }
#endif

#include "z_asyn_task_base.h"
#include "z_asyn_task_for_static_function.h"
#include "z_asyn_task_for_member_function.h"
#include "z_asyn_task_mgr.h"
