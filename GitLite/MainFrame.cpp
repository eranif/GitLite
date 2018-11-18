#include "MainFrame.h"
#include <wx/aboutdlg.h>
#include <wx/textdlg.h> 
#include <wx/msgdlg.h>
#include "UserNamePasswordDlg.h"
#include "SSHKeysDlg.h"
#include "GitConfig.h"
#include "GitCloneDialog.h"
#include <wx/choicdlg.h>
#include "GitCloneProgressDlg.h"

MainFrame::MainFrame(wxWindow* parent)
    : MainFrameBaseClass(parent)
    , m_cloneProgress(NULL)
{
    m_repo.Bind(wxEVT_GIT_CLONE_PROGRESS, &MainFrame::OnCloneProgress, this);
    m_repo.Bind(wxEVT_GIT_CLONE_COMPLETED, &MainFrame::OnCloneCompleted, this);
    m_repo.Bind(wxEVT_GIT_CLONE_ERROR, &MainFrame::OnCloneError, this);
    m_repo.Bind(wxEVT_GIT_CLONE_STARTED, &MainFrame::OnCloneStart, this);
    m_repo.Bind(wxEVT_GIT_CRED_REQUIRED, &MainFrame::OnGitCredentials, this);
    m_repo.Bind(wxEVT_GIT_CRED_SSH_KEYS_REQUIRED, &MainFrame::OnGitSshKeysCredentials, this);
}

MainFrame::~MainFrame()
{
    m_repo.Unbind(wxEVT_GIT_CLONE_PROGRESS, &MainFrame::OnCloneProgress, this);
    m_repo.Unbind(wxEVT_GIT_CLONE_COMPLETED, &MainFrame::OnCloneCompleted, this);
    m_repo.Unbind(wxEVT_GIT_CLONE_ERROR, &MainFrame::OnCloneError, this);
    m_repo.Unbind(wxEVT_GIT_CLONE_STARTED, &MainFrame::OnCloneStart, this);
    m_repo.Unbind(wxEVT_GIT_CRED_REQUIRED, &MainFrame::OnGitCredentials, this);
    m_repo.Unbind(wxEVT_GIT_CRED_SSH_KEYS_REQUIRED, &MainFrame::OnGitSshKeysCredentials, this);
}

void MainFrame::OnExit(wxCommandEvent& event)
{
    wxUnusedVar(event);
    Close();
}

void MainFrame::OnAbout(wxCommandEvent& event)
{
    wxUnusedVar(event);
    wxAboutDialogInfo info;
    info.SetCopyright(_("My MainFrame"));
    info.SetLicence(_("GPL v2 or later"));
    info.SetDescription(_("Short description goes here"));
    ::wxAboutBox(info);
}

void MainFrame::OnClone(wxCommandEvent& event)
{
    GitCloneDialog dlg(this);
    GitConfig conf;
    conf.Load();

    wxString url, path;
    conf.GetLastCloneInfo(url, path);
    dlg.GetTextCtrlURL()->ChangeValue(url);
    dlg.GetDirPicker()->SetPath(path);
    if(dlg.ShowModal() == wxID_OK) {
        url = dlg.GetTextCtrlURL()->GetValue();
        path = dlg.GetDirPicker()->GetPath();
        conf.AddLastCloneInfo(url, path);
        conf.Save();
        m_repo.Clone(url, path);
    }
}

void MainFrame::OnCloneError(GitLiteEvent& event)
{
    ::wxMessageBox(event.GetMessage(), "GitLite", wxICON_ERROR | wxCENTER);
    if(m_cloneProgress) {
        m_cloneProgress->Destroy();
        m_cloneProgress = NULL;
    }
}

void MainFrame::OnCloneCompleted(GitLiteCloneEvent& event)
{
    event.Skip();
    m_repo.SetRepo(reinterpret_cast<git_repository*>(event.GetClientData()));
    m_cloneProgress->Destroy();
    m_cloneProgress = NULL;

    // List all branches
    wxArrayString branchesArr;
    GitBranch::List_t branches;
    m_repo.GetBranches(branches);

    std::for_each(branches.begin(), branches.end(), [&](const GitBranch& branch) {
        if(branch.IsLocal()) {
            branchesArr.Add(branch.GetName());
        }
    });

    // Prompt the user to checkout the proper branch
    wxString branchName =
        ::wxGetSingleChoice(_("Select Branch to checkout"), _("Checkout branch"), branchesArr, 0, this);
    if(branchName.IsEmpty()) {
        return;
    }

    // Checkout branchName
    m_repo.Checkout(branchName);
}

void MainFrame::OnCloneProgress(GitLiteCloneEvent& event)
{
    if(m_cloneProgress) {
        m_cloneProgress->Update(event);
    }
}

void MainFrame::OnCloneStart(GitLiteCloneEvent& event)
{
    wxString message;
    message << _("Cloning repository: ") << event.GetUrl();
    m_cloneProgress = new GitCloneProgressDlg(this, &m_repo);
    m_cloneProgress->ShowModal();
}

void MainFrame::OnGitCredentials(GitLiteCredEvent& event)
{
    event.Skip();
    UserNamePasswordDlg dlg(this);
    dlg.GetTextCtrlUsername()->ChangeValue(event.GetUser());
    if(dlg.ShowModal() == wxID_OK) {
        event.SetUser(dlg.GetTextCtrlUsername()->GetValue());
        event.SetPass(dlg.GetTextCtrlPassword()->GetValue());
    } else {
        event.SetCancelled(true);
    }
}

void MainFrame::OnGitSshKeysCredentials(GitLiteCredEvent& event)
{
    event.Skip();
    SSHKeysDlg dlg(this);
    GitConfig conf;
    conf.Load();

    // Load settings
    wxString publicKey, privateKey, remoteUser, passphrase;
    conf.GetSshKeys(publicKey, privateKey, remoteUser, passphrase);
    dlg.GetTextCtrlPasphrase()->ChangeValue(passphrase);

    if(event.GetUser().IsEmpty()) {
        dlg.GetTextCtrlRemoteUsername()->ChangeValue(remoteUser);
    } else {
        dlg.GetTextCtrlRemoteUsername()->Enable(false);
        dlg.GetTextCtrlRemoteUsername()->ChangeValue(event.GetUser());
    }
    dlg.GetFilePickerPrivateKey()->SetPath(privateKey);
    dlg.GetFilePickerPublicKey()->SetPath(publicKey);
    if(dlg.ShowModal() == wxID_OK) {
        // Store the values
        conf.AddSshKeys(dlg.GetFilePickerPublicKey()->GetPath(), dlg.GetFilePickerPrivateKey()->GetPath(),
            dlg.GetTextCtrlRemoteUsername()->GetValue(), dlg.GetTextCtrlPasphrase()->GetValue());
        conf.Save();
        // Return the values to the user
        event.SetUser(dlg.GetTextCtrlRemoteUsername()->GetValue());
        event.SetPass(dlg.GetTextCtrlPasphrase()->GetValue());
        event.SetPrivateKey(dlg.GetFilePickerPrivateKey()->GetPath());
        event.SetPublicKey(dlg.GetFilePickerPublicKey()->GetPath());
    } else {
        event.SetCancelled(true);
    }
}
