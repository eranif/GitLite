#include "GitLiteRepo.h"
#include <wx/dir.h>
#include <wx/filename.h>
#include <git2/global.h>
#include "GitClone.h"
#include "GitBranch.h"

//====================================
// Git repository
//====================================
GitLiteRepo::GitLiteRepo()
    : m_repo(NULL)
{
    m_thread.Start();
}

GitLiteRepo::~GitLiteRepo() { m_thread.Stop(); }

void GitLiteRepo::Initialize() { git_libgit2_init(); }

void GitLiteRepo::Shutdown() { git_libgit2_shutdown(); }

void GitLiteRepo::Clone(const wxString& url, const wxString& targetFolder)
{
    GitCommandBase::Ptr_t command(new GitClone(this, url, targetFolder));
    command->Process();
}

void GitLiteRepo::GetBranches(wxArrayString& localBranches, wxArrayString& remoteBranches)
{
    GitCommandBase::Ptr_t command(new GitBranch(this, GitBranch::kListBranches));
    command->Process();
    localBranches = command->Cast<GitBranch>()->GetLocalBranches();
    remoteBranches = command->Cast<GitBranch>()->GetRemoteBranches();
}
