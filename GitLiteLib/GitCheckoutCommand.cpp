#include "GitCheckoutCommand.h"
#include <git2.h>
#include "GitLiteRepo.h"
#include "GitEvents.h"

GitCheckoutCommand::GitCheckoutCommand(GitLiteRepo* repo, const wxString& branch)
    : GitCommandBase(repo)
    , m_branchName(branch)
{
}

GitCheckoutCommand::~GitCheckoutCommand() {}

void GitCheckoutCommand::Process()
{
    git_object* treeish = NULL;
    git_checkout_options opts;
    git_checkout_init_options(&opts, GIT_CHECKOUT_OPTIONS_VERSION);
    opts.checkout_strategy = GIT_CHECKOUT_SAFE | GIT_CHECKOUT_RECREATE_MISSING;
    int error = git_revparse_single(&treeish, GetRepo()->GetRepoHandler(), m_branchName.mb_str(wxConvUTF8).data());
    if(git_checkout_tree(GetRepo()->GetRepoHandler(), treeish, &opts) != 0) {
        GitLiteEvent event(wxEVT_GIT_CHECKOUT_ERROR);
        event.SetMessage(wxString() << _("Checkout error:\n") << giterr_last()->message);
        GetRepo()->AddPendingEvent(event);
    } else {
        GitLiteEvent event(wxEVT_GIT_CHECKOUT_COMPLETED);
        GetRepo()->AddPendingEvent(event);
    }
}
