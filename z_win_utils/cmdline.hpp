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
#include "win_utils_header.h"
#include <map>

typedef CString CCmdLineParser_String;
#define DELIMETERS   _T("-/")
#define QUOTES       _T("\"") // Can be _T("\"\'"),  for instance
#define VALUE_SEP    _T(" :") // Space MUST be in set

namespace zl
{
namespace WinUtils
{

    class ZLCmdLine
    {
    public:
        class CValsMap : public std::map<CCmdLineParser_String, CCmdLineParser_String> {};
        typedef CValsMap::const_iterator POSITION;

    public:
        ZLCmdLine(LPCTSTR sCmdLine = NULL, bool bCaseSensitive = false)
            : m_bCaseSensitive(bCaseSensitive)
        {
            if (sCmdLine) 
            {
                Parse(sCmdLine);
            }
        }

        virtual ~ZLCmdLine()
        {
            m_ValsMap.clear();
        }

        bool Parse(LPCTSTR sCmdLine)
        {
            if (!sCmdLine) 
                return false;

            m_sCmdLine = sCmdLine;
            m_ValsMap.clear();

            const CCmdLineParser_String sEmpty;

            LPCTSTR sCurrent = sCmdLine;
            while (true) 
            {
                // /Key:"arg"
                if(_tcslen(sCurrent) == 0) 
                { 
                    break; 
                } // No data left

                LPCTSTR sArg = _tcspbrk(sCurrent, DELIMETERS);
                if (!sArg) 
                    break; // No delimeters found

                sArg =  _tcsinc(sArg);
                // Key:"arg"
                if (_tcslen(sArg) == 0) 
                    break; // String ends with delimeter

                LPCTSTR sVal = _tcspbrk(sArg, VALUE_SEP);
                if (sVal == NULL) 
                { //Key ends command line
                    CCmdLineParser_String csKey(sArg);
                    if (!m_bCaseSensitive) 
                    {
                        csKey.MakeLower();
                    }
                    m_ValsMap.insert(CValsMap::value_type(csKey, sEmpty));
                    break;

                }else if(sVal[0] == _T(' ') || _tcslen(sVal) == 1 ) 
                { // Key with no value or cmdline ends with /Key:
                    CCmdLineParser_String csKey(sArg, sVal - sArg);
                    if(!csKey.IsEmpty()) 
                    { // Prevent /: case
                        if(!m_bCaseSensitive) 
                        {
                            csKey.MakeLower();
                        }

                        m_ValsMap.insert(CValsMap::value_type(csKey, sEmpty));
                    }

                    sCurrent = _tcsinc(sVal);
                    continue;
                }else 
                { // Key with value
                    CCmdLineParser_String csKey(sArg, sVal - sArg);
                    if(!m_bCaseSensitive) 
                    {
                        csKey.MakeLower();
                    }

                    sVal = _tcsinc(sVal);
                    // "arg"
                    LPCTSTR sQuote = _tcspbrk(sVal, QUOTES), sEndQuote(NULL);
                    if(sQuote == sVal) 
                    { // Quoted String
                        sQuote = _tcsinc(sVal);
                        sEndQuote = _tcspbrk(sQuote, QUOTES);
                    }else 
                    {
                        sQuote = sVal;
                        sEndQuote = _tcschr(sQuote, _T(' '));
                    }

                    if (sEndQuote == NULL) 
                    { // No end quotes or terminating space, take rest of string
                        CCmdLineParser_String csVal(sQuote);
                        if(!csKey.IsEmpty()) 
                        { // Prevent /:val case
                            m_ValsMap.insert(CValsMap::value_type(csKey, csVal));
                        }
                        break;
                    }else 
                    { // End quote or space present
                        if(!csKey.IsEmpty()) 
                        {	// Prevent /:"val" case
                            CCmdLineParser_String csVal(sQuote, sEndQuote - sQuote);
                            m_ValsMap.insert(CValsMap::value_type(csKey, csVal));
                        }

                        sCurrent = _tcsinc(sEndQuote);
                        continue;
                    }
                }
            }

            return (m_ValsMap.size() > 0);
        }

        LPCTSTR getCmdLine() const 
        { 
            return m_sCmdLine; 
        }

        void setCaseSensitive(
            bool bSensitive) 
        { 
            m_bCaseSensitive = bSensitive; 
        }

        bool getCaseSensitive() const 
        { 
            return m_bCaseSensitive; 
        }

        const CValsMap &getVals() const 
        { 
            return m_ValsMap; 
        }

        // Start iterating through keys and values
        POSITION getFirst() const
        {
            return m_ValsMap.begin();
        }

        // Get next key-value pair, returns empty sKey if end reached
        POSITION getNext(
            POSITION& pos, 
            CCmdLineParser_String &sKey, 
            CCmdLineParser_String &sValue) const
        {
            if(isLast(pos)) 
            {
                sKey.Empty();
                return pos;
            }else 
            {
                sKey = pos->first;
                sValue = pos->second;
                pos ++;
                return pos;
            }
        }

        // just helper ;)
        bool isLast(POSITION &pos) const
        {
            return (pos == m_ValsMap.end());
        }

        // TRUE if "Key" present in command line
        bool HasKey(LPCTSTR sKey) const
        {
            CValsMap::const_iterator it = findKey(sKey);
            if(it == m_ValsMap.end()) 
                return false;

            return true;
        }

        // Is "key" present in command line and have some value
        bool HasVal(LPCTSTR sKey) const
        {
            CValsMap::const_iterator it = findKey(sKey);
            if(it == m_ValsMap.end()) 
                return false;

            if(it->second.IsEmpty()) 
                return false;

            return true;
        }

        // Returns value if value was found or NULL otherwise
        LPCTSTR GetVal(LPCTSTR sKey) const
        {
            CValsMap::const_iterator it = findKey(sKey);
            if(it == m_ValsMap.end()) 
                return NULL;

            return LPCTSTR(it->second);
        }

        // Returns true if value was found
        bool GetVal(LPCTSTR sKey, CCmdLineParser_String &sValue) const
        {
            CValsMap::const_iterator it = findKey(sKey);
            if(it == m_ValsMap.end()) 
                return false;

            sValue = it->second;

            return true;
        }

    private:
        CValsMap::const_iterator findKey(LPCTSTR sKey) const
        {
            CCmdLineParser_String s(sKey);
            if(!m_bCaseSensitive) 
            {
                s.MakeLower();
            }

            return m_ValsMap.find(s);
        }

    private:
        CCmdLineParser_String m_sCmdLine;
        CValsMap m_ValsMap;
        bool m_bCaseSensitive;
    };

}
}
