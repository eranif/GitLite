#include "GitClone.h"
#include <wx/filename.h>
#include "GitEvents.h"
#include "GitErrors.h"
#include "GitCredentials.h"
// Include libgit headers only in the C++ file to avoid their need when building against this object
#include <git2/clone.h>
//#include <git2/global.h>
#include <git2/errors.h>
#include <git2/transport.h>

GitClone::GitClone(wxEvtHandler* sink, const wxString& url, const wxString& targetFolder)
    : GitCommandBase(sink)
    , m_url(url)
    , m_folder(targetFolder)
    , m_startEventSent(false)
{
}

GitClone::~GitClone() {}

int GitClone::FetchProgress(const git_transfer_progress* stats, void* payload)
{
    // Notify about the progress
    GitClone* gitCloneObj = reinterpret_cast<GitClone*>(payload);
    if(!gitCloneObj->m_startEventSent) {
        // repory start
        GitLiteCloneEvent event(wxEVT_GIT_CLONE_STARTED);
        event.SetUrl(gitCloneObj->m_url);
        event.SetPath(gitCloneObj->m_folder);
        gitCloneObj->GetSink()->ProcessEvent(event);
        gitCloneObj->m_startEventSent = true;
    }

    GitLiteCloneEvent event(wxEVT_GIT_CLONE_PROGRESS);
    event.SetTotal(stats->total_objects);
    event.SetCurrent(stats->indexed_objects);
    gitCloneObj->GetSink()->ProcessEvent(event);
    if(event.IsCancelled()) {
        return kGitCloneCancelled;
    }

    return 0;
}

void GitClone::CheckoutProgress(const char* path, size_t completed_steps, size_t total_steps, void* payload) {}

void GitClone::Process()
{
    // Check to see if the target folder exists
    if(wxFileName::DirExists(m_folder)) {
        GitLiteCloneEvent event(wxEVT_GIT_CLONE_ERROR);
        event.SetMessage(_("Git error: target directory already exists"));
        GetSink()->AddPendingEvent(event);
        return;
    }

    git_clone_options clone_opts = GIT_CLONE_OPTIONS_INIT;
    clone_opts.checkout_opts.checkout_strategy = GIT_CHECKOUT_SAFE;
    clone_opts.checkout_opts.progress_cb = GitClone::CheckoutProgress;
    clone_opts.checkout_opts.progress_payload = this;
    clone_opts.checkout_opts = GIT_CHECKOUT_OPTIONS_INIT;
    clone_opts.fetch_opts.callbacks.payload = this;
    clone_opts.fetch_opts.callbacks.transfer_progress = GitClone::FetchProgress;
    clone_opts.fetch_opts.callbacks.credentials = GitCredentials::CloneCredentials;
    giterr_clear();
    git_repository* repo = NULL;

    int rc = git_clone(&repo, m_url.mb_str(wxConvUTF8).data(), m_folder.mb_str(wxConvUTF8).data(), &clone_opts);
    if(rc != 0) {
        wxString errmsg;
        if(rc == GIT_EUSER) {
            // User cancel
            errmsg << _("Git clone cancelled by user");
        } else {
            errmsg << _("Git clone error:(") << giterr_last()->klass << "): " << giterr_last()->message;
        }
        GitLiteCloneEvent event(wxEVT_GIT_CLONE_ERROR);
        event.SetMessage(errmsg);
        GetSink()->AddPendingEvent(event);
    } else {
        GitLiteCloneEvent event(wxEVT_GIT_CLONE_COMPLETED);
        event.SetClientData(repo); // Send back the repository to the main thread
        GetSink()->AddPendingEvent(event);
    }
}
