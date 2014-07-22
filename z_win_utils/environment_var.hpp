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

/**
 * @file
 * @brief �����������
 */


#pragma once
#include "win_utils_header.h"
#include "register.hpp"
#include "usid.hpp"

namespace zl
{
namespace WinUtils
{
    /**
     * @brief �����������ò���
     */
    class ZLEnvironmentVar
    {
    public:
        enum EnvironmentType { SYSTEM_ENV, USER_ENV };

        /**
         * @brief ���һ����������
         * @param[in] t         ָ���ǻ�����������, ϵͳ��������(SYSTEM_ENV)���û���������(USER_ENV)
         * @param[in] lpVarName ����������
         * @param[in] lpVar     ��������ֵ
         * @return �ɹ�����TRUE, ʧ�ܷ���FALSE
         */
        static BOOL Add(EnvironmentType t, LPCTSTR lpVarName, LPCTSTR lpVar)
        {
            if (!lpVarName || !lpVar)
                return FALSE;

            BOOL bReturn = FALSE;
            switch (t)
            {
            case SYSTEM_ENV:
                bReturn = _AddSysEnv(lpVarName, lpVar);
                break;
            case USER_ENV:
                bReturn = _AddUserEnv(lpVarName, lpVar);
                break;
            }
            return bReturn;
        }

        /**
         * @brief ɾ��ָ����������
         * @param[in] t         ָ���ǻ�����������, ϵͳ��������(SYSTEM_ENV)���û���������(USER_ENV)
         * @param[in] lpVarName ����������
         * @return �ɹ�����TRUE, ʧ�ܷ���FALSE
         */
        static BOOL Del(EnvironmentType t, LPCTSTR lpVarName)
        {
            BOOL bReturn = FALSE;
            switch (t)
            {
            case SYSTEM_ENV:
                bReturn = _DelSysEnv(lpVarName);
                break;
            case USER_ENV:
                bReturn = _DelUserEnv(lpVarName);
                break;
            }
            return bReturn;
        }

    private:
        static BOOL _AddSysEnv(LPCTSTR lpVarName, LPCTSTR lpVar)
        {
            BOOL bReturn = FALSE;

            ZLRegister reg;
            if (reg.Open(
                HKEY_LOCAL_MACHINE,
                L"System\\CurrentControlSet\\Control\\Session Manager\\Environment",
                TRUE,
                KEY_WRITE))
            {
                bReturn = reg.WriteExpandString(lpVarName, lpVar);
                reg.Close();
            }
            return bReturn;
        }

        static BOOL _DelSysEnv(LPCTSTR lpVarName)
        {
            BOOL bReturn = FALSE;
            ZLRegister reg;
            if (reg.Open(
                HKEY_LOCAL_MACHINE,
                L"System\\CurrentControlSet\\Control\\Session Manager\\Environment",
                FALSE,
                KEY_WRITE))
            {
                bReturn = reg.DeleteValue(lpVarName);
                reg.Close();
            }
            return bReturn;
        }

        static BOOL _AddUserEnv(LPCTSTR lpVarName, LPCTSTR lpVar)
        {
            BOOL bReturn = FALSE;

            CString sSid;
            if (ZLUsid::GetCurrentUserSID(sSid))
            {
                CString sSubKey = sSid + L"\\Environment";
                ZLRegister reg;
                if (reg.Open(HKEY_USERS, sSubKey, TRUE, KEY_WRITE))
                {
                    bReturn = reg.WriteExpandString(lpVarName, lpVar);
                    reg.Close();
                }
            }
            return bReturn;
        }

        static BOOL _DelUserEnv(LPCTSTR lpVarName)
        {
            BOOL bReturn = FALSE;

            CString sSid;
            if (ZLUsid::GetCurrentUserSID(sSid))
            {
                CString sSubKey = sSid + L"\\Environment";
                ZLRegister reg;
                if (reg.Open(HKEY_USERS, sSubKey, FALSE, KEY_WRITE))
                {
                    bReturn = reg.DeleteValue(lpVarName);
                    reg.Close();
                }
            }
            return bReturn;
        }
    };
}
}
