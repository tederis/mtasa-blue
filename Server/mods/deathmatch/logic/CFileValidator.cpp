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
}

bool CFileValidator::Validate(const std::vector<SString>& hashes) const
{
    if (hashes.size() != m_Entries.size())
        return false;

    for (int i = 0; i < hashes.size(); ++i)
    {
        if (hashes[i] != m_Entries[i].strLargeSha256)
            return false;
    }

    return true;
}
