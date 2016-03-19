#include "GitLiteRepo.h"
#include <wx/dir.h>
#include <wx/filename.h>
#include <git2/global.h>
#include "GitClone.h"

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
    GitClone* cloneRequest = new GitClone(this, url, targetFolder);
    m_thread.Add(cloneRequest);
}
