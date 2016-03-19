#include "MainFrame.h"
#include <wx/aboutdlg.h>
#include <wx/textdlg.h>
#include <wx/msgdlg.h>

MainFrame::MainFrame(wxWindow* parent)
    : MainFrameBaseClass(parent)
{
}

MainFrame::~MainFrame() {}

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
    wxString repoPath = ::wxGetTextFromUser(_("Clone directory"));

    if(repoPath.IsEmpty() || repoURL.IsEmpty()) return;

    try {
        m_repo.Clone(repoURL, repoPath);

    } catch(GitLiteException& e) {
        ::wxMessageBox(e.What(), "GitLite", wxICON_ERROR | wxCENTER);
    }
}
