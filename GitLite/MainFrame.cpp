#include "MainFrame.h"
#include <wx/aboutdlg.h>
#include <wx/textdlg.h>
#include <wx/msgdlg.h>

MainFrame::MainFrame(wxWindow* parent)
    : MainFrameBaseClass(parent)
    , m_cloneProgress(NULL)
{
    m_repo.Bind(wxEVT_GIT_CLONE_PROGRESS, &MainFrame::OnCloneProgress, this);
    m_repo.Bind(wxEVT_GIT_CLONE_COMPLETED, &MainFrame::OnCloneCompleted, this);
    m_repo.Bind(wxEVT_GIT_CLONE_ERROR, &MainFrame::OnCloneError, this);
    m_repo.Bind(wxEVT_GIT_CLONE_STARTED, &MainFrame::OnCloneStart, this);
}

MainFrame::~MainFrame()
{
    m_repo.Unbind(wxEVT_GIT_CLONE_PROGRESS, &MainFrame::OnCloneProgress, this);
    m_repo.Unbind(wxEVT_GIT_CLONE_COMPLETED, &MainFrame::OnCloneCompleted, this);
    m_repo.Unbind(wxEVT_GIT_CLONE_ERROR, &MainFrame::OnCloneError, this);
    m_repo.Unbind(wxEVT_GIT_CLONE_STARTED, &MainFrame::OnCloneStart, this);
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
    wxString repoURL = ::wxGetTextFromUser(_("Repository URL"));
    if(repoURL.IsEmpty()) return;

    wxString repoPath = ::wxGetTextFromUser(_("Clone directory"));
    if(repoPath.IsEmpty()) return;
    m_repo.Clone(repoURL, repoPath);
}

void MainFrame::OnCloneError(GitLiteCloneEvent& event)
{
    ::wxMessageBox(event.GetMessage(), "GitLite", wxICON_ERROR | wxCENTER);
    if(m_cloneProgress) {
        m_cloneProgress->Destroy();
        m_cloneProgress = NULL;
    }
}

void MainFrame::OnCloneCompleted(GitLiteCloneEvent& event)
{
    m_repo.SetRepo(reinterpret_cast<git_repository*>(event.GetClientData()));
    m_cloneProgress->Destroy();
    m_cloneProgress = NULL;
    ::wxMessageBox("Repository cloned successfully");
}

void MainFrame::OnCloneProgress(GitLiteCloneEvent& event)
{
    // report progress
    double total = event.GetTotal();
    double current = event.GetCurrent();
    double progress = ((current / total) * 100.0);
    if(m_cloneProgress) {
        // Important note about Update()
        // this functions call wxYield, this means
        // that another event might be processed (e.g. wxEVT_GIT_CLONE_COMPLETED which destroys m_cloneProgress)
        // so we need to check for m_cloneProgress again after the call to Update()
        m_cloneProgress->Update(progress);
        if(m_cloneProgress && m_cloneProgress->WasCancelled()) {
            // The clone was cancelled - notify the worker thread
            m_repo.GetHelperThread().SetCancel(true);
        }
    }
}

void MainFrame::OnCloneStart(GitLiteCloneEvent& event)
{
    wxString message;
    message << _("Cloning repository: ") << event.GetUrl();
    m_cloneProgress =
        new wxProgressDialog(_("Git Clone"), message, 100, this, wxPD_APP_MODAL | wxPD_CAN_ABORT | wxPD_ELAPSED_TIME);
    m_cloneProgress->Show();
}
