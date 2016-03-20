#include "GitCredentials.h"
#include "GitEvents.h"
#include <git2/errors.h>
#include <git2/transport.h>
#include "GitCommandBase.h"

#define __C(s) s.mb_str(wxConvUTF8).data()

GitCredentials::GitCredentials() {}

GitCredentials::~GitCredentials() {}

int GitCredentials::CloneCredentials(
    git_cred** out, const char* url, const char* username_from_url, unsigned int allowed_types, void* payload)
{
    // Ask for password from the UI
    if(allowed_types & GIT_CREDTYPE_USERPASS_PLAINTEXT) {
        // Plain text pass
        GitLiteCredEvent event(wxEVT_GIT_CRED_REQUIRED);
        event.SetUser(username_from_url);
        GitCommandBase* gitCloneObj = reinterpret_cast<GitCommandBase*>(payload);
        gitCloneObj->GetSink()->ProcessEvent(event);
        if(event.IsCancelled()) {
            return GIT_EUSER;
        }
        return git_cred_userpass_plaintext_new(
            out, event.GetUser().mb_str(wxConvUTF8).data(), event.GetPass().mb_str(wxConvUTF8).data());
    } else if(allowed_types & GIT_CREDTYPE_SSH_KEY) {
        GitLiteCredEvent event(wxEVT_GIT_CRED_SSH_KEYS_REQUIRED);
        event.SetUser(username_from_url);
        GitCommandBase* gitCloneObj = reinterpret_cast<GitCommandBase*>(payload);
        gitCloneObj->GetSink()->ProcessEvent(event);
        if(event.IsCancelled()) {
            return GIT_EUSER;
        }
        return git_cred_ssh_key_new(
            out, __C(event.GetUser()), __C(event.GetPublicKey()), __C(event.GetPrivateKey()), __C(event.GetPass()));
    } else {
        return GIT_EUSER;
    }
}
