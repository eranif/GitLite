#include "GitLiteRepo.h"
#include <wx/dir.h>
#include <wx/filename.h>
#include <git2/global.h>
#include "GitClone.h"
#include "GitBranch.h"
#include "GitCheckoutCommand.h"

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
    m_thread.Add(new GitCloneCommand(this, url, targetFolder));
}

void GitLiteRepo::GetBranches(GitBranch::List_t& branches)
{
    GitCommandBase::Ptr_t command(new GitBranchCommand(this, GitBranchCommand::kListBranches));
    command->Process();
    branches = command->Cast<GitBranchCommand>()->GetBranches();
}

void GitLiteRepo::Checkout(const wxString& branchName)
{
    GitCommandBase::Ptr_t command(new GitCheckoutCommand(this, branchName));
    command->Process();
}
