#include "MainFrame.h"
#include <wx/aboutdlg.h>
#include <wx/textdlg.h>
#include <wx/msgdlg.h>

MainFrame::MainFrame(wxWindow* parent)
    : MainFrameBaseClass(parent)
{
    m_repo.Bind(wxEVT_GIT_CLONE_PROGRESS, &MainFrame::OnCloneProgress, this);
    m_repo.Bind(wxEVT_GIT_CLONE_COMPLETED, &MainFrame::OnCloneCompleted, this);
    m_repo.Bind(wxEVT_GIT_CLONE_ERROR, &MainFrame::OnCloneError, this);
}

MainFrame::~MainFrame()
{
    m_repo.Unbind(wxEVT_GIT_CLONE_PROGRESS, &MainFrame::OnCloneProgress, this);
    m_repo.Unbind(wxEVT_GIT_CLONE_COMPLETED, &MainFrame::OnCloneCompleted, this);
    m_repo.Unbind(wxEVT_GIT_CLONE_ERROR, &MainFrame::OnCloneError, this);
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
}

void MainFrame::OnCloneCompleted(GitLiteCloneEvent& event)
{
    ::wxMessageBox("Repository cloned successfully");
    m_repo.SetRepo(reinterpret_cast<git_repository*>(event.GetClientData()));
}

void MainFrame::OnCloneProgress(GitLiteCloneEvent& event) {}
