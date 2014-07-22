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
 * @brief ע������
 */


#pragma once
#include "win_utils_header.h"
#include <shlwapi.h>

namespace zl
{
namespace WinUtils
{
    /**
     * @brief �ṩ��ע���Ĵ򿪡���ȡ�����á�������ɾ������
     */
    class ZLRegister
    {
    public:
        ZLRegister()
            : hKey_(NULL)
        {
        }

        ~ZLRegister()
        {
            Close();
        }

    public:
        /**
         * @brief ��ע����
         * @param[in] hRootKey          RootKey
         * @param[in] szSubKey          SubKey
         * @param[in] bCreateIfNotExsit ����ִ�з�ʽ
         * @param[in] samDesired        key�ķ���Ȩ��
         * @return �ɹ�����TRUE��ʧ�ܷ���FALSE 
         */
        BOOL Open(HKEY hRootKey, LPCTSTR szSubKey, BOOL bCreateIfNotExsit = FALSE, REGSAM samDesired = KEY_READ | KEY_WRITE)
        {
            Close();
            LONG lRetCode = 0;
            if (bCreateIfNotExsit)
            {
                lRetCode = ::RegCreateKeyEx(hRootKey,
                    szSubKey,
                    NULL,
                    NULL,
                    REG_OPTION_NON_VOLATILE,
                    samDesired,
                    NULL, 
                    &hKey_,
                    NULL);
            }
            else
            {
                lRetCode = ::RegOpenKeyEx(hRootKey,
                    szSubKey,
                    0,
                    samDesired,
                    &hKey_);
            }
            if (lRetCode != ERROR_SUCCESS)
            {
                return FALSE;
            }
            return TRUE;
        }
        /**
         * @brief ����ע����
         * @param[in] hRootKey   RootKey
         * @param[in] szSubKey   SubKey
         * @param[in] samDesired key�ķ���Ȩ��
         * @return �ɹ�����TRUE��ʧ�ܷ���FALSE 
         */
        BOOL CreateVolatileReg(HKEY hRootKey, LPCTSTR szSubKey, REGSAM samDesired = KEY_READ | KEY_WRITE)
        {
            Close();
            if (::RegCreateKeyEx(hRootKey,
                szSubKey,
                0L,
                NULL,
                REG_OPTION_VOLATILE,
                samDesired,
                NULL,
                &hKey_,
                NULL) != ERROR_SUCCESS)
            {
                return FALSE;
            }
            return TRUE;
        }
        /**
         * @brief ѭ��ɾ��ָ�������Ӽ���ֵ
         * @param[in] pszName ����
         * @return �ɹ�����TRUE��ʧ�ܷ���FALSE 
         */
        BOOL DeleteKey(LPCTSTR pszName)
        {
            if (pszName == NULL
                || hKey_ == NULL)
            {
                return FALSE;
            }
            if (ERROR_SUCCESS == ::SHDeleteKey(hKey_, pszName))
            {
                return TRUE;
            }
            return FALSE;
        }
        /**
         * @brief ɾ��ָ������ֵ
         * @param[in] pszName ����
         * @return �ɹ�����TRUE��ʧ�ܷ���FALSE 
         */
        BOOL DeleteValue(LPCTSTR pszName)
        {
            if (pszName == NULL
                || hKey_ == NULL)
            {
                return FALSE;
            }
            if (ERROR_SUCCESS == ::RegDeleteValue(hKey_, pszName))
            {
                return TRUE;
            }
            return FALSE;
        }

        void Close(void)
        {
            if (hKey_)
            {
                ::RegCloseKey(hKey_);
                hKey_ = NULL;
            }
        }
        /**
         * @brief ��ȡ��ֵ����
         * @param[in]  pszValueName ��ֵ����
         * @param[out] dwValue      ��ֵ����
         * @return �ɹ�����TRUE��ʧ�ܷ���FALSE 
         */
        BOOL Read(LPCTSTR pszValueName, DWORD& dwValue)
        {
            if (pszValueName == NULL
                || hKey_ == NULL)
            {
                return FALSE;
            }

            DWORD dwDest = 0;
            DWORD dwType = 0;
            DWORD dwSize = sizeof (DWORD);
            if (::RegQueryValueEx(hKey_,
                pszValueName,
                NULL,
                &dwType,
                (BYTE *)&dwDest,
                &dwSize) == ERROR_SUCCESS)
            {
                if (dwType == REG_DWORD)
                {
                    dwValue = dwDest;
                    return TRUE;
                }
            }
            return FALSE;
        }
        /**
         * @brief ��ȡ��ֵ����
         * @param[in]  pszValueName ��ֵ����
         * @param[out] strValue     ��ֵ����
         * @return �ɹ�����TRUE��ʧ�ܷ���FALSE 
         */
        BOOL Read(LPCTSTR pszValueName, CString& strValue)
        {
            if (pszValueName == NULL
                || hKey_ == NULL)
            {
                return FALSE;
            }

            BOOL bReturn = FALSE;
            DWORD dwType;
            DWORD dwSize = 0;
            do
            {
                if (::RegQueryValueEx(hKey_,
                    pszValueName,
                    NULL,
                    &dwType,
                    NULL,
                    &dwSize) != ERROR_SUCCESS)
                {
                    break;
                }
                if (dwType != REG_SZ
                    && dwType != REG_EXPAND_SZ)
                {
                    break;
                }
                strValue.Empty();
                LPTSTR pBuffer = strValue.GetBuffer(dwSize / 2 + 1);
                if (!pBuffer)
                {
                    break;
                }
                if (::RegQueryValueEx(hKey_,
                    pszValueName,
                    NULL,
                    &dwType,
                    (BYTE*)pBuffer,
                    &dwSize) == ERROR_SUCCESS)
                {
                    pBuffer[dwSize / 2] = 0;
                    bReturn = TRUE;
                }
                strValue.ReleaseBuffer();
            } while (FALSE);
            return bReturn;
        }
        /**
         * @brief ��ȡ��ֵ����
         * @param[in] pszValueName ��ֵ����
         * @param[in] pBuffer      ��ż�ֵ���ݵĻ�����
         * @param[in] dwSize       ��������С
         * @return �ɹ�����TRUE��ʧ�ܷ���FALSE 
         */
        BOOL Read(LPCTSTR pszValueName, BYTE* pBuffer, DWORD& dwSize)
        {
            if (pszValueName == NULL
                || hKey_ == NULL)
            {
                return FALSE;
            }

            BOOL bReturn = FALSE;
            LONG lRetCode = 0;
            DWORD dwType = 0;
            if (::RegQueryValueEx(hKey_,
                pszValueName,
                NULL,
                &dwType,
                pBuffer,
                &dwSize) != ERROR_SUCCESS)
            {
                return FALSE;
            }
            return TRUE;
        }
        /**
         * @brief ���ü�ֵ����
         * @param[in] pszValueName ��ֵ����
         * @param[in] dwValue      Ҫ���õ�����
         * @return �ɹ�����TRUE��ʧ�ܷ���FALSE 
         */
        BOOL Write(LPCTSTR pszValueName, DWORD dwValue)
        {
            if (pszValueName == NULL
                || hKey_ == NULL)
            {
                return FALSE;
            }

            BOOL bReturn = FALSE;
            if (::RegSetValueEx(hKey_,
                pszValueName,
                NULL,
                REG_DWORD,
                (CONST BYTE*)&dwValue,
                sizeof(DWORD)) != ERROR_SUCCESS)
            {
                return FALSE;
            }
            return TRUE;
        }
        /**
         * @brief ���ü�ֵ����
         * @param[in] pszValueName ��ֵ����
         * @param[in] dwValue      Ҫ���õ�����
         * @return �ɹ�����TRUE��ʧ�ܷ���FALSE 
         */
        BOOL Write(LPCTSTR pszValueName, LPCTSTR pszValue)
        {
            if (pszValueName == NULL
                || hKey_ == NULL
                || pszValue == NULL)
            {
                return FALSE;
            }
            if (::RegSetValueEx(hKey_,
                pszValueName,
                NULL,
                REG_SZ,
                (CONST BYTE*) pszValue,
                ((int)_tcslen(pszValue) + 1) * sizeof(TCHAR)) != ERROR_SUCCESS)
            {
                return FALSE;
            }
            return TRUE;
        }
        /**
         * @brief ���ü�ֵ����ΪREG_EXPAND_SZ��ֵ����
         * @param[in] pszValueName ��ֵ����
         * @param[in] pszValue     Ҫ���õ�����
         * @return �ɹ�����TRUE��ʧ�ܷ���FALSE 
         */
        BOOL WriteExpandString(LPCTSTR pszValueName, LPCTSTR pszValue)
        {
            if (pszValueName == NULL
                || hKey_ == NULL
                || pszValue == NULL)
            {
                return FALSE;
            }
            if (::RegSetValueEx(hKey_,
                pszValueName,
                NULL,
                REG_EXPAND_SZ,
                (CONST BYTE*) pszValue,
                ((int)_tcslen(pszValue) + 1) * sizeof(TCHAR)) != ERROR_SUCCESS)
            {
                return FALSE;
            }
            return TRUE;
        }
        /**
         * @brief ���ü�ֵ����ΪREG_BINARY��ֵ����
         * @param[in] pszValueName ��ֵ����
         * @param[in] pBuffer      ����Ҫ�������ݵĻ�����
         * @param[in] dwSize       ��������С
         * @return �ɹ�����TRUE��ʧ�ܷ���FALSE 
         */
        BOOL Write(LPCTSTR pszValueName, BYTE* pBuffer, DWORD dwSize)
        {
            if (pszValueName == NULL
                || hKey_ == NULL
                || pBuffer == NULL)
            {
                return FALSE;
            }
            if (::RegSetValueEx(hKey_,
                pszValueName,
                NULL,
                REG_BINARY,
                pBuffer,
                dwSize) != ERROR_SUCCESS)
            {
                return FALSE;
            }
            return TRUE;
        }

    private:
        HKEY hKey_;
    };

}
}