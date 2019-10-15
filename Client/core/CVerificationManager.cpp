#include "StdInc.h"
#include <game/CGame.h>

CVerificationManager::CVerificationManager() : m_State(VERIFY_DEFAULT)
{
    ScanForLibraries();
}

CVerificationManager::~CVerificationManager()
{
}

bool CVerificationManager::BuildList(const char* szCmdLine)
{
    CConsoleInterface* pConsole = g_pCore->GetConsole();

    char* szError = "* Syntax: verifylist [<arguments>]";
    if (szCmdLine == NULL)
    {
        pConsole->Print(szError);
        return false;
    }

    // Copy the buffer
    char* szTemp = new char[strlen(szCmdLine) + 16];
    strcpy(szTemp, szCmdLine);

    // Split it up into bind key, command and arguments
    char* szKey = strtok(szTemp, " ");

    SString strCurrentDir = PathConform(GetMTASABaseDir());
    SString path1, path2;
    strCurrentDir.Split("\\", &path1, &path2, -1);

    std::vector<SString> files;

    // Parse args
    while (szKey != NULL)
    {
        FindFilesRecursive(PathJoin(strCurrentDir, szKey), files, 99);
        szKey = strtok(NULL, " ");
    }

    // Create a file list
    auto xml = g_pCore->GetXML()->CreateXML(CalcMTASAPath("mta/config/verifylist.xml"));
    if (xml)
    {
        auto root = xml->CreateRootNode("files");

        for (const auto& filename : files)
        {
            auto            node = root->CreateSubNode("file");
            CXMLAttributes* pAttributes = &node->GetAttributes();

            CXMLAttribute* pA = NULL;
            pA = pAttributes->Create("name");
            pA->SetValue(PathMakeRelative(strCurrentDir, filename));

            pA = pAttributes->Create("sha256");
            pA->SetValue(GenerateSha256HexStringFromFile(filename));

            pConsole->Print(PathMakeRelative(strCurrentDir, filename).c_str());
        }

        xml->Write();
        delete xml;
    }

    delete[] szTemp;

    return true;
}

void CVerificationManager::ScanForLibraries()
{
    SString strCurrentDir = PathConform(GetMTASABaseDir());
    SString path1, path2;
    strCurrentDir.Split("\\", &path1, &path2, -1);

    m_Libraries.clear();

    FindFilesRecursive(PathJoin(strCurrentDir, "*.dll"), m_Libraries, 99);
    FindFilesRecursive(PathJoin(strCurrentDir, "*.asi"), m_Libraries, 99);
    FindFilesRecursive(PathJoin(strCurrentDir, "*.exe"), m_Libraries, 99);
}

void CVerificationManager::FindFilesRecursive(const SString& strPathMatch, std::vector<SString>& outFileList, uint uiMaxDepth)
{
    SString strPath, strMatch;
    strPathMatch.Split("\\", &strPath, &strMatch, -1);

    std::list<SString> toDoList;
    toDoList.push_back(strPath);
    while (toDoList.size())
    {
        SString strPathHere = toDoList.front();
        toDoList.pop_front();

        std::vector<SString> fileListHere = FindFiles(strPathHere + "\\" + strMatch, true, false);
        std::vector<SString> dirListHere = FindFiles(strPathHere + "\\", false, true);

        for (unsigned int i = 0; i < fileListHere.size(); i++)
        {
            SString filePathName = strPathHere + "\\" + fileListHere[i];

            if (std::find(outFileList.begin(), outFileList.end(), filePathName) == outFileList.end())
                outFileList.push_back(filePathName);
        }
        for (unsigned int i = 0; i < dirListHere.size(); i++)
        {
            SString dirPathName = strPathHere + "\\" + dirListHere[i];
            toDoList.push_back(dirPathName);
        }
    }
}
