#pragma once

#include <core/CVerificationManagerInterface.h>

enum eVerificationState
{
    VERIFY_DEFAULT = 0,
    VERIFY_HASHING
};

class CVerificationManager : public CVerificationManagerInterface
{
public:
    CVerificationManager();
    ~CVerificationManager();

    bool BuildList(const char* szParameters); 

private:
    void ScanForLibraries();
    void FindFilesRecursive(const SString& strPathMatch, std::vector<SString>& outFileList, uint uiMaxDepth);

    eVerificationState m_State;
    std::vector<SString> m_FileNames;
    std::vector<SString> m_Libraries;
};
