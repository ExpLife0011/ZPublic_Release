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

NAMESPACE_ZL_BEGIN

///> ���ʱ��������������ִ�е㣬��bootʱ��ͳ���ִ��ʱ�䶼�ǿ��Ե�
inline unsigned int TimerGetTime()
{
    return ::GetTickCount();
}

inline unsigned int TimerCalcMilliseconds(
    unsigned int h,
    unsigned int m,
    unsigned int s)
{
    return h * 3600000 + m * 60000 + s * 1000;
}

inline unsigned int TimerCalcMilliseconds(
    unsigned int m,
    unsigned int s)
{
    return m * 60000 + s * 1000;
}

inline unsigned int TimerCalcMilliseconds(
    unsigned int s)
{
    return s * 1000;
}

///> ����ִ�д���Ϊ99999�������ظ�
#define TaskRepeatDef 99999

NAMESPACE_ZL_END