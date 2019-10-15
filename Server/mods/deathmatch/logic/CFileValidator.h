#pragma once

struct SReferenceEntry
{
    SString strFileName;
    SString strLargeSha256;
};

class CFileValidator
{
public:
    CFileValidator();
    ~CFileValidator();

    void LoadFromXML(CXMLFile* pXML);

    void InsertEntry(SReferenceEntry&& entry);

    bool Validate(const std::vector<SString>& hashes) const;

    unsigned int GetEntriesCount() const { return m_Entries.size(); }

    const std::vector<SReferenceEntry>& GetEntries() const { return m_Entries; }

private:
    std::vector<SReferenceEntry> m_Entries;
};
