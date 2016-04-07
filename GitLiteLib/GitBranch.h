#ifndef GITBRANCH_H
#define GITBRANCH_H

#include "GitCommandBase.h"
#include "GitLiteExports.h"
#include <list>

class GitLiteRepo;
class WXDLLIMPEXP_LIBGIT GitBranch
{
public:
    enum eBranchType {
        kLocal,
        kRemote,
    };

private:
    wxString m_name;
    GitBranch::eBranchType m_type;
    wxString m_upstreamName;

public:
    typedef std::list<GitBranch> List_t;
    
    GitBranch(const wxString& name, GitBranch::eBranchType type)
        : m_name(name)
        , m_type(type)
    {
    }
    
    // Accessors
    void SetName(const wxString& name) { this->m_name = name; }
    void SetType(const GitBranch::eBranchType& type) { this->m_type = type; }
    const wxString& GetName() const { return m_name; }
    const GitBranch::eBranchType& GetType() const { return m_type; }
    bool IsLocal() const { return m_type == kLocal; }
    bool IsRemote() const { return m_type == kRemote; }
    void SetUpstreamName(const wxString& upstreamName) { this->m_upstreamName = upstreamName; }
    const wxString& GetUpstreamName() const { return m_upstreamName; }
};

class WXDLLIMPEXP_LIBGIT GitBranchCommand : public GitCommandBase
{
public:
    enum eBranchCommandType {
        kListBranches = (1 << 0),
    };

protected:
    GitLiteRepo* m_gitRepo;
    size_t m_command;
    GitBranch::List_t m_branches;

public:
    GitBranchCommand(GitLiteRepo* repo, size_t command);
    ~GitBranchCommand();

    virtual void Process(wxThread* thread = nullptr);
    const GitBranch::List_t& GetBranches() const { return m_branches; }
};

#endif // GITBRANCH_H
