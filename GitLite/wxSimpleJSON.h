#ifndef WX_SIMPLE_JSON_H
#define WX_SIMPLE_JSON_H

#include <wx/sharedptr.h>
#include "cJSON.h"
#include <wx/string.h>
#include <wx/arrstr.h>

class wxSimpleJSON
{
protected:
    cJSON* m_d;
    bool m_canDelete;

public:
    // NOTE: the order here matters!
    // it matches the definitions in cJSON.h
    enum eType {
        kFalse,  // 0
        kTrue,   // 1
        kNull,   // 2
        kNumber, // 3
        kString, // 4
        kArray,  // 5
        kObject, // 6
    };
    virtual ~wxSimpleJSON();

private:
    // Constructor is private. The way to create an object is by using the ::Create method
    wxSimpleJSON();
    
    /**
     * @brief the deleter pointer
     */
    static void Destroy(wxSimpleJSON* obj);

public:
    typedef wxSharedPtr<wxSimpleJSON> Ptr_t;

public:
    // Custom object generators
    /**
     * @brief create a new JSON node.
     * @param type the node type
     * @param isRoot
     * @return
     */
    static wxSimpleJSON::Ptr_t Create(wxSimpleJSON::eType type, bool isRoot = false);

    // Array manipulation
    wxSimpleJSON& ArrayAdd(wxSimpleJSON::Ptr_t obj);
    wxSimpleJSON& ArrayAdd(const wxString& value, const wxMBConv& conv = wxConvUTF8);
    wxSimpleJSON& ArrayAdd(double value);
    wxSimpleJSON& ArrayAdd(const wxArrayString& arr, const wxMBConv& conv = wxConvUTF8);

    // Object manipulation
    wxSimpleJSON& Add(const wxString& name, wxSimpleJSON::Ptr_t obj);
    wxSimpleJSON& Add(const wxString& name, const wxString& value, const wxMBConv& conv = wxConvUTF8);
    wxSimpleJSON& Add(const wxString& name, double value);
    wxSimpleJSON& Add(const wxString& name, const wxArrayString& arr, const wxMBConv& conv = wxConvUTF8);

    /**
     * @brief convert this JSON object to string
     * @param pretty apply indentations + spacing
     * @param conv string conversion object
     * @return JSON object as string
     */
    inline wxString ToString(bool pretty = true, const wxMBConv& conv = wxConvUTF8) const
    {
        char* b = pretty ? cJSON_Print(m_d) : cJSON_PrintUnformatted(m_d);
        wxString s(b, conv);
        free(b);
        return s;
    }
};

#endif // WX_SIMPLE_JSON_H
