//////////////////////////////////////////////////////////////////////
// This file was auto-generated by codelite's wxCrafter Plugin
// wxCrafter project file: wxcrafter.wxcp
// Do not modify this file by hand!
//////////////////////////////////////////////////////////////////////

#include "wxcrafter.h"

// Declare the bitmap loading function
extern void wxC9ED9InitBitmapResources();

static bool bBitmapLoaded = false;

MainFrameBaseClass::MainFrameBaseClass(
    wxWindow* parent, wxWindowID id, const wxString& title, const wxPoint& pos, const wxSize& size, long style)
    : wxFrame(parent, id, title, pos, size, style)
{
    if(!bBitmapLoaded) {
        // We need to initialise the default bitmap handler
        wxXmlResource::Get()->AddHandler(new wxBitmapXmlHandler);
        wxC9ED9InitBitmapResources();
        bBitmapLoaded = true;
    }

    wxBoxSizer* boxSizer1 = new wxBoxSizer(wxVERTICAL);
    this->SetSizer(boxSizer1);

    m_mainPanel = new wxPanel(this, wxID_ANY, wxDefaultPosition, wxSize(-1, -1), wxTAB_TRAVERSAL);

    boxSizer1->Add(m_mainPanel, 1, wxEXPAND, 5);

    m_menuBar = new wxMenuBar(0);
    this->SetMenuBar(m_menuBar);

    m_name6 = new wxMenu();
    m_menuBar->Append(m_name6, _("File"));

    m_menuItem7 = new wxMenuItem(m_name6, wxID_EXIT, _("Exit\tAlt-X"), _("Quit"), wxITEM_NORMAL);
    m_name6->Append(m_menuItem7);

    m_name8 = new wxMenu();
    m_menuBar->Append(m_name8, _("Help"));

    m_menuItem9 = new wxMenuItem(m_name8, wxID_ABOUT, _("About..."), wxT(""), wxITEM_NORMAL);
    m_name8->Append(m_menuItem9);

    m_mainToolbar = this->CreateToolBar(wxTB_FLAT, wxID_ANY);
    m_mainToolbar->SetToolBitmapSize(wxSize(24, 24));

    m_mainToolbar->AddTool(TB_ID_COPY, _("Clone repository"), wxXmlResource::Get()->LoadBitmap(wxT("24-copy")),
        wxNullBitmap, wxITEM_NORMAL, _("Clone repository"), _("Clone repository"), NULL);
    m_mainToolbar->Realize();

    SetName(wxT("MainFrameBaseClass"));
    SetMinClientSize(wxSize(500, 300));
    SetSize(-1, -1);
    if(GetSizer()) {
        GetSizer()->Fit(this);
    }
    if(GetParent()) {
        CentreOnParent(wxBOTH);
    } else {
        CentreOnScreen(wxBOTH);
    }
#if wxVERSION_NUMBER >= 2900
    if(!wxPersistenceManager::Get().Find(this)) {
        wxPersistenceManager::Get().RegisterAndRestore(this);
    } else {
        wxPersistenceManager::Get().Restore(this);
    }
#endif
    // Connect events
    this->Connect(m_menuItem7->GetId(), wxEVT_COMMAND_MENU_SELECTED, wxCommandEventHandler(MainFrameBaseClass::OnExit),
        NULL, this);
    this->Connect(m_menuItem9->GetId(), wxEVT_COMMAND_MENU_SELECTED, wxCommandEventHandler(MainFrameBaseClass::OnAbout),
        NULL, this);
    this->Connect(
        TB_ID_COPY, wxEVT_COMMAND_TOOL_CLICKED, wxCommandEventHandler(MainFrameBaseClass::OnClone), NULL, this);
}

MainFrameBaseClass::~MainFrameBaseClass()
{
    this->Disconnect(m_menuItem7->GetId(), wxEVT_COMMAND_MENU_SELECTED,
        wxCommandEventHandler(MainFrameBaseClass::OnExit), NULL, this);
    this->Disconnect(m_menuItem9->GetId(), wxEVT_COMMAND_MENU_SELECTED,
        wxCommandEventHandler(MainFrameBaseClass::OnAbout), NULL, this);
    this->Disconnect(
        TB_ID_COPY, wxEVT_COMMAND_TOOL_CLICKED, wxCommandEventHandler(MainFrameBaseClass::OnClone), NULL, this);
}

UserNamePasswordDlgBase::UserNamePasswordDlgBase(
    wxWindow* parent, wxWindowID id, const wxString& title, const wxPoint& pos, const wxSize& size, long style)
    : wxDialog(parent, id, title, pos, size, style)
{
    if(!bBitmapLoaded) {
        // We need to initialise the default bitmap handler
        wxXmlResource::Get()->AddHandler(new wxBitmapXmlHandler);
        wxC9ED9InitBitmapResources();
        bBitmapLoaded = true;
    }

    wxBoxSizer* boxSizer15 = new wxBoxSizer(wxVERTICAL);
    this->SetSizer(boxSizer15);

    wxFlexGridSizer* flexGridSizer23 = new wxFlexGridSizer(0, 2, 0, 0);
    flexGridSizer23->SetFlexibleDirection(wxBOTH);
    flexGridSizer23->SetNonFlexibleGrowMode(wxFLEX_GROWMODE_SPECIFIED);
    flexGridSizer23->AddGrowableCol(1);

    boxSizer15->Add(flexGridSizer23, 1, wxALL | wxEXPAND, 5);

    m_staticText25 = new wxStaticText(this, wxID_ANY, _("Username:"), wxDefaultPosition, wxSize(-1, -1), 0);

    flexGridSizer23->Add(m_staticText25, 0, wxALL | wxALIGN_RIGHT | wxALIGN_CENTER_VERTICAL, 5);

    m_textCtrlUsername = new wxTextCtrl(this, wxID_ANY, wxT(""), wxDefaultPosition, wxSize(-1, -1), 0);
#if wxVERSION_NUMBER >= 3000
    m_textCtrlUsername->SetHint(wxT(""));
#endif

    flexGridSizer23->Add(m_textCtrlUsername, 0, wxALL | wxEXPAND, 5);

    m_staticText29 = new wxStaticText(this, wxID_ANY, _("Password:"), wxDefaultPosition, wxSize(-1, -1), 0);

    flexGridSizer23->Add(m_staticText29, 0, wxALL | wxALIGN_RIGHT | wxALIGN_CENTER_VERTICAL, 5);

    m_textCtrlPassword = new wxTextCtrl(this, wxID_ANY, wxT(""), wxDefaultPosition, wxSize(-1, -1), wxTE_PASSWORD);
#if wxVERSION_NUMBER >= 3000
    m_textCtrlPassword->SetHint(wxT(""));
#endif

    flexGridSizer23->Add(m_textCtrlPassword, 0, wxALL | wxEXPAND, 5);

    m_stdBtnSizer17 = new wxStdDialogButtonSizer();

    boxSizer15->Add(m_stdBtnSizer17, 0, wxALL | wxALIGN_CENTER_HORIZONTAL, 10);

    m_button19 = new wxButton(this, wxID_OK, wxT(""), wxDefaultPosition, wxSize(-1, -1), 0);
    m_button19->SetDefault();
    m_stdBtnSizer17->AddButton(m_button19);

    m_button21 = new wxButton(this, wxID_CANCEL, wxT(""), wxDefaultPosition, wxSize(-1, -1), 0);
    m_stdBtnSizer17->AddButton(m_button21);
    m_stdBtnSizer17->Realize();

    SetName(wxT("UserNamePasswordDlgBase"));
    SetSize(-1, -1);
    if(GetSizer()) {
        GetSizer()->Fit(this);
    }
    if(GetParent()) {
        CentreOnParent(wxBOTH);
    } else {
        CentreOnScreen(wxBOTH);
    }
#if wxVERSION_NUMBER >= 2900
    if(!wxPersistenceManager::Get().Find(this)) {
        wxPersistenceManager::Get().RegisterAndRestore(this);
    } else {
        wxPersistenceManager::Get().Restore(this);
    }
#endif
}

UserNamePasswordDlgBase::~UserNamePasswordDlgBase() {}

SSHKeysDlgBase::SSHKeysDlgBase(
    wxWindow* parent, wxWindowID id, const wxString& title, const wxPoint& pos, const wxSize& size, long style)
    : wxDialog(parent, id, title, pos, size, style)
{
    if(!bBitmapLoaded) {
        // We need to initialise the default bitmap handler
        wxXmlResource::Get()->AddHandler(new wxBitmapXmlHandler);
        wxC9ED9InitBitmapResources();
        bBitmapLoaded = true;
    }

    wxBoxSizer* boxSizer35 = new wxBoxSizer(wxVERTICAL);
    this->SetSizer(boxSizer35);

    wxFlexGridSizer* flexGridSizer45 = new wxFlexGridSizer(0, 2, 0, 0);
    flexGridSizer45->SetFlexibleDirection(wxBOTH);
    flexGridSizer45->SetNonFlexibleGrowMode(wxFLEX_GROWMODE_SPECIFIED);
    flexGridSizer45->AddGrowableCol(1);

    boxSizer35->Add(flexGridSizer45, 1, wxALL | wxEXPAND, 5);

    m_staticText47 = new wxStaticText(this, wxID_ANY, _("SSH Private key:"), wxDefaultPosition, wxSize(-1, -1), 0);

    flexGridSizer45->Add(m_staticText47, 0, wxALL | wxALIGN_RIGHT | wxALIGN_CENTER_VERTICAL, 5);

    m_filePickerPrivateKey = new wxFilePickerCtrl(this, wxID_ANY, wxEmptyString, _("Select a file"), wxT("*"),
        wxDefaultPosition, wxSize(-1, -1), wxFLP_DEFAULT_STYLE | wxFLP_USE_TEXTCTRL | wxFLP_SMALL);
    m_filePickerPrivateKey->SetFocus();

    flexGridSizer45->Add(m_filePickerPrivateKey, 0, wxALL | wxEXPAND, 5);

    m_staticText51 = new wxStaticText(this, wxID_ANY, _("SSH Public key:"), wxDefaultPosition, wxSize(-1, -1), 0);

    flexGridSizer45->Add(m_staticText51, 0, wxALL | wxALIGN_RIGHT | wxALIGN_CENTER_VERTICAL, 5);

    m_filePickerPublicKey = new wxFilePickerCtrl(this, wxID_ANY, wxEmptyString, _("Select a file"), wxT("*"),
        wxDefaultPosition, wxSize(-1, -1), wxFLP_DEFAULT_STYLE | wxFLP_USE_TEXTCTRL | wxFLP_SMALL);

    flexGridSizer45->Add(m_filePickerPublicKey, 0, wxALL | wxEXPAND, 5);

    m_staticText55 = new wxStaticText(this, wxID_ANY, _("Passphrase:"), wxDefaultPosition, wxSize(-1, -1), 0);

    flexGridSizer45->Add(m_staticText55, 0, wxALL | wxALIGN_RIGHT | wxALIGN_CENTER_VERTICAL, 5);

    m_textCtrlPasphrase = new wxTextCtrl(this, wxID_ANY, wxT(""), wxDefaultPosition, wxSize(-1, -1), wxTE_PASSWORD);
#if wxVERSION_NUMBER >= 3000
    m_textCtrlPasphrase->SetHint(wxT(""));
#endif

    flexGridSizer45->Add(m_textCtrlPasphrase, 0, wxALL | wxEXPAND, 5);

    m_staticText59 = new wxStaticText(this, wxID_ANY, _("Remote username:"), wxDefaultPosition, wxSize(-1, -1), 0);

    flexGridSizer45->Add(m_staticText59, 0, wxALL | wxALIGN_RIGHT | wxALIGN_CENTER_VERTICAL, 5);

    m_textCtrlRemoteUsername = new wxTextCtrl(this, wxID_ANY, wxT(""), wxDefaultPosition, wxSize(-1, -1), 0);
#if wxVERSION_NUMBER >= 3000
    m_textCtrlRemoteUsername->SetHint(wxT(""));
#endif

    flexGridSizer45->Add(m_textCtrlRemoteUsername, 0, wxALL | wxEXPAND, 5);

    m_stdBtnSizer39 = new wxStdDialogButtonSizer();

    boxSizer35->Add(m_stdBtnSizer39, 0, wxALL | wxALIGN_CENTER_HORIZONTAL, 10);

    m_button41 = new wxButton(this, wxID_OK, wxT(""), wxDefaultPosition, wxSize(-1, -1), 0);
    m_button41->SetDefault();
    m_stdBtnSizer39->AddButton(m_button41);

    m_button43 = new wxButton(this, wxID_CANCEL, wxT(""), wxDefaultPosition, wxSize(-1, -1), 0);
    m_stdBtnSizer39->AddButton(m_button43);
    m_stdBtnSizer39->Realize();

    SetName(wxT("SSHKeysDlgBase"));
    SetSize(-1, -1);
    if(GetSizer()) {
        GetSizer()->Fit(this);
    }
    if(GetParent()) {
        CentreOnParent(wxBOTH);
    } else {
        CentreOnScreen(wxBOTH);
    }
#if wxVERSION_NUMBER >= 2900
    if(!wxPersistenceManager::Get().Find(this)) {
        wxPersistenceManager::Get().RegisterAndRestore(this);
    } else {
        wxPersistenceManager::Get().Restore(this);
    }
#endif
}

SSHKeysDlgBase::~SSHKeysDlgBase() {}

GitCloneDialogBase::GitCloneDialogBase(
    wxWindow* parent, wxWindowID id, const wxString& title, const wxPoint& pos, const wxSize& size, long style)
    : wxDialog(parent, id, title, pos, size, style)
{
    if(!bBitmapLoaded) {
        // We need to initialise the default bitmap handler
        wxXmlResource::Get()->AddHandler(new wxBitmapXmlHandler);
        wxC9ED9InitBitmapResources();
        bBitmapLoaded = true;
    }

    wxBoxSizer* boxSizer67 = new wxBoxSizer(wxVERTICAL);
    this->SetSizer(boxSizer67);

    wxFlexGridSizer* flexGridSizer75 = new wxFlexGridSizer(0, 2, 0, 0);
    flexGridSizer75->SetFlexibleDirection(wxBOTH);
    flexGridSizer75->SetNonFlexibleGrowMode(wxFLEX_GROWMODE_SPECIFIED);
    flexGridSizer75->AddGrowableCol(1);

    boxSizer67->Add(flexGridSizer75, 1, wxALL | wxEXPAND, 5);

    m_staticText77 = new wxStaticText(this, wxID_ANY, _("Repository URL:"), wxDefaultPosition, wxSize(-1, -1), 0);

    flexGridSizer75->Add(m_staticText77, 0, wxALL | wxALIGN_RIGHT | wxALIGN_CENTER_VERTICAL, 5);

    m_textCtrlURL = new wxTextCtrl(this, wxID_ANY, wxT(""), wxDefaultPosition, wxSize(-1, -1), 0);
#if wxVERSION_NUMBER >= 3000
    m_textCtrlURL->SetHint(_("Repository URL"));
#endif

    flexGridSizer75->Add(m_textCtrlURL, 0, wxALL | wxEXPAND, 5);

    m_staticText81 = new wxStaticText(this, wxID_ANY, _("Clone directory:"), wxDefaultPosition, wxSize(-1, -1), 0);

    flexGridSizer75->Add(m_staticText81, 0, wxALL | wxALIGN_RIGHT | wxALIGN_CENTER_VERTICAL, 5);

    m_dirPicker = new wxDirPickerCtrl(this, wxID_ANY, wxEmptyString, _("Select a folder"), wxDefaultPosition,
        wxSize(-1, -1), wxDIRP_SMALL | wxDIRP_DEFAULT_STYLE | wxDIRP_USE_TEXTCTRL | wxDIRP_DIR_MUST_EXIST);

    flexGridSizer75->Add(m_dirPicker, 0, wxALL | wxEXPAND, 5);

    m_stdBtnSizer69 = new wxStdDialogButtonSizer();

    boxSizer67->Add(m_stdBtnSizer69, 0, wxALL | wxALIGN_CENTER_HORIZONTAL, 10);

    m_button71 = new wxButton(this, wxID_OK, wxT(""), wxDefaultPosition, wxSize(-1, -1), 0);
    m_button71->SetDefault();
    m_stdBtnSizer69->AddButton(m_button71);

    m_button73 = new wxButton(this, wxID_CANCEL, wxT(""), wxDefaultPosition, wxSize(-1, -1), 0);
    m_stdBtnSizer69->AddButton(m_button73);
    m_stdBtnSizer69->Realize();

    SetName(wxT("GitCloneDialogBase"));
    SetSize(-1, -1);
    if(GetSizer()) {
        GetSizer()->Fit(this);
    }
    if(GetParent()) {
        CentreOnParent(wxBOTH);
    } else {
        CentreOnScreen(wxBOTH);
    }
#if wxVERSION_NUMBER >= 2900
    if(!wxPersistenceManager::Get().Find(this)) {
        wxPersistenceManager::Get().RegisterAndRestore(this);
    } else {
        wxPersistenceManager::Get().Restore(this);
    }
#endif
}

GitCloneDialogBase::~GitCloneDialogBase() {}

GitCloneProgressBaseDlg::GitCloneProgressBaseDlg(
    wxWindow* parent, wxWindowID id, const wxString& title, const wxPoint& pos, const wxSize& size, long style)
    : wxDialog(parent, id, title, pos, size, style)
{
    if(!bBitmapLoaded) {
        // We need to initialise the default bitmap handler
        wxXmlResource::Get()->AddHandler(new wxBitmapXmlHandler);
        wxC9ED9InitBitmapResources();
        bBitmapLoaded = true;
    }

    wxBoxSizer* boxSizer89 = new wxBoxSizer(wxVERTICAL);
    this->SetSizer(boxSizer89);

    wxFlexGridSizer* flexGridSizer91 = new wxFlexGridSizer(0, 3, 0, 0);
    flexGridSizer91->SetFlexibleDirection(wxBOTH);
    flexGridSizer91->SetNonFlexibleGrowMode(wxFLEX_GROWMODE_SPECIFIED);
    flexGridSizer91->AddGrowableCol(1);

    boxSizer89->Add(flexGridSizer91, 1, wxALL | wxEXPAND, 5);

    m_staticText99 = new wxStaticText(this, wxID_ANY, _("Objects Received:"), wxDefaultPosition, wxSize(-1, -1), 0);

    flexGridSizer91->Add(m_staticText99, 0, wxALL | wxALIGN_RIGHT | wxALIGN_CENTER_VERTICAL, 5);

    m_gaugeObjRecv = new wxGauge(this, wxID_ANY, 100, wxDefaultPosition, wxSize(-1, -1), wxGA_HORIZONTAL);
    m_gaugeObjRecv->SetValue(10);

    flexGridSizer91->Add(m_gaugeObjRecv, 0, wxALL | wxEXPAND, 5);

    m_staticTextRecvObjects = new wxStaticText(this, wxID_ANY, wxT(""), wxDefaultPosition, wxSize(100, -1), 0);

    flexGridSizer91->Add(m_staticTextRecvObjects, 0, wxALL | wxEXPAND | wxALIGN_LEFT | wxALIGN_CENTER_VERTICAL, 5);

    m_staticText103 = new wxStaticText(this, wxID_ANY, _("Objects Indexed:"), wxDefaultPosition, wxSize(-1, -1), 0);

    flexGridSizer91->Add(m_staticText103, 0, wxALL | wxALIGN_RIGHT | wxALIGN_CENTER_VERTICAL, 5);

    m_gaugeObjIndexed = new wxGauge(this, wxID_ANY, 100, wxDefaultPosition, wxSize(-1, -1), wxGA_HORIZONTAL);
    m_gaugeObjIndexed->SetValue(10);

    flexGridSizer91->Add(m_gaugeObjIndexed, 0, wxALL | wxEXPAND, 5);

    m_staticTextIndexedObjects = new wxStaticText(this, wxID_ANY, wxT(""), wxDefaultPosition, wxSize(100, -1), 0);

    flexGridSizer91->Add(m_staticTextIndexedObjects, 0, wxALL | wxEXPAND | wxALIGN_LEFT | wxALIGN_CENTER_VERTICAL, 5);

    m_staticText107 = new wxStaticText(this, wxID_ANY, _("Deltas Indexed:"), wxDefaultPosition, wxSize(-1, -1), 0);

    flexGridSizer91->Add(m_staticText107, 0, wxALL | wxALIGN_RIGHT | wxALIGN_CENTER_VERTICAL, 5);

    m_gaugeDeltasIndexed = new wxGauge(this, wxID_ANY, 100, wxDefaultPosition, wxSize(-1, -1), wxGA_HORIZONTAL);
    m_gaugeDeltasIndexed->SetValue(10);

    flexGridSizer91->Add(m_gaugeDeltasIndexed, 0, wxALL | wxEXPAND, 5);

    m_staticTextIndexedDeltas = new wxStaticText(this, wxID_ANY, wxT(""), wxDefaultPosition, wxSize(100, -1), 0);

    flexGridSizer91->Add(m_staticTextIndexedDeltas, 0, wxALL | wxEXPAND | wxALIGN_LEFT | wxALIGN_CENTER_VERTICAL, 5);

    m_stdBtnSizer93 = new wxStdDialogButtonSizer();

    boxSizer89->Add(m_stdBtnSizer93, 0, wxALL | wxALIGN_CENTER_HORIZONTAL, 10);

    m_button95 = new wxButton(this, wxID_CANCEL, wxT(""), wxDefaultPosition, wxSize(-1, -1), 0);
    m_button95->SetDefault();
    m_stdBtnSizer93->AddButton(m_button95);
    m_stdBtnSizer93->Realize();

    SetName(wxT("GitCloneProgressBaseDlg"));
    SetSize(-1, -1);
    if(GetSizer()) {
        GetSizer()->Fit(this);
    }
    if(GetParent()) {
        CentreOnParent(wxBOTH);
    } else {
        CentreOnScreen(wxBOTH);
    }
#if wxVERSION_NUMBER >= 2900
    if(!wxPersistenceManager::Get().Find(this)) {
        wxPersistenceManager::Get().RegisterAndRestore(this);
    } else {
        wxPersistenceManager::Get().Restore(this);
    }
#endif
    // Connect events
    m_button95->Connect(
        wxEVT_COMMAND_BUTTON_CLICKED, wxCommandEventHandler(GitCloneProgressBaseDlg::OnCancel), NULL, this);
}

GitCloneProgressBaseDlg::~GitCloneProgressBaseDlg()
{
    m_button95->Disconnect(
        wxEVT_COMMAND_BUTTON_CLICKED, wxCommandEventHandler(GitCloneProgressBaseDlg::OnCancel), NULL, this);
}
