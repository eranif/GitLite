#include "GitLiteRepo.h"
#include <wx/dir.h>
#include <wx/filename.h>

// Include libgit headers only in the C++ file to avoid their need when building against this object
#include <git2/clone.h>
#include <git2/global.h>
#include <git2/errors.h>

//====================================
// Git repository
//====================================
GitLiteRepo::GitLiteRepo()
    : m_repo(NULL)
{
}

GitLiteRepo::~GitLiteRepo() {}

void GitLiteRepo::Initialize() { git_libgit2_init(); }

void GitLiteRepo::Shutdown() { git_libgit2_shutdown(); }

void GitLiteRepo::Clone(const wxString& url, const wxString& targetFolder) throw(GitLiteException)
{
    // Check to see if the target folder exists
    if(wxFileName::DirExists(targetFolder)) {
        throw GitLiteException(_("Git error: target directory already exists"));
    }
    git_clone_options clone_opts = GIT_CLONE_OPTIONS_INIT;
    clone_opts.checkout_opts.checkout_strategy = GIT_CHECKOUT_RECREATE_MISSING | GIT_CHECKOUT_SAFE;
    clone_opts.checkout_opts.progress_cb = GitLiteRepo::CheckoutProgress;
    clone_opts.checkout_opts.progress_payload = this;
    clone_opts.checkout_opts = GIT_CHECKOUT_OPTIONS_INIT;
    clone_opts.fetch_opts.callbacks.transfer_progress = GitLiteRepo::FetchProgress;
    clone_opts.fetch_opts.callbacks.payload = this;
    giterr_clear();
    int error = git_clone(&m_repo, url.mb_str(wxConvUTF8).data(), targetFolder.mb_str(wxConvUTF8).data(), &clone_opts);
    if(error != 0) {
        wxString errmsg;
        errmsg << _("Git clone error:(") << giterr_last()->klass << "): " << giterr_last()->message;
        throw GitLiteException(errmsg);
    }
}

int GitLiteRepo::FetchProgress(const git_transfer_progress* stats, void* payload) { return 0; }

void GitLiteRepo::CheckoutProgress(const char* path, size_t completed_steps, size_t total_steps, void* payload) {}
