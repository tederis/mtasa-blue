#include "StdInc.h"

CFileValidator::CFileValidator()
{
}

CFileValidator::~CFileValidator()
{
}

void CFileValidator::LoadFromXML(CXMLFile* pXML)
{
    if (!pXML->Parse())
        return;

    auto root = pXML->GetRootNode();

    // Find existing node
    for (int i = 0; true; i++)
    {
        CXMLNode* pNode = root->FindSubNode("file", i);
        if (!pNode)
            break;            

        CXMLAttributes* pAttributes = &pNode->GetAttributes();

        CXMLAttribute* pA = NULL;
        if (pA = pAttributes->Find("name"))
        {
            SString strName = pA->GetValue();
            SString strHash;

            if (pA = pAttributes->Find("sha256"))
            {
                strHash = pA->GetValue();
                InsertEntry(SReferenceEntry{strName, strHash});
            }
        }
    }
}

void CFileValidator::InsertEntry(SReferenceEntry&& entry)
{
    m_Entries.emplace_back(std::move(entry));

    CLogger::LogPrintf("[Verification] File %s added\n", entry.strFileName.c_str());
}

bool CFileValidator::Validate(CPlayer* pPlayer, const std::vector<SString>& hashes) const
{
    if (hashes.size() != m_Entries.size())
        return false;

    bool bFailed = false;

    for (int i = 0; i < hashes.size(); ++i)
    {
        if (hashes[i] != m_Entries[i].strLargeSha256)
        {        
            CLogger::LogPrintf("[Verification] File %s sha256 %s should be %s [%s]\n", m_Entries[i].strFileName.c_str(), hashes[i].c_str(), m_Entries[i].strLargeSha256.c_str(), pPlayer->GetNick());
            bFailed = true;
        }
    }

    return !bFailed;
}
