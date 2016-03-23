#include "wxSimpleJSON.h"
#include "cJSON.h"

static cJSON* cJSONAllocNew()
{
    cJSON* node = (cJSON*)malloc(sizeof(cJSON));
    if(node) memset(node, 0, sizeof(cJSON));
    return node;
}

wxSimpleJSON::wxSimpleJSON()
    : m_d(NULL)
    , m_canDelete(false)
{
}

wxSimpleJSON::~wxSimpleJSON() {}

wxSimpleJSON::Ptr_t wxSimpleJSON::Create(wxSimpleJSON::eType type, bool isRoot)
{
    wxSimpleJSON* obj = new wxSimpleJSON();
    obj->m_d = cJSONAllocNew();
    obj->m_d->type = static_cast<int>(type);
    obj->m_canDelete = isRoot;
    wxSimpleJSON::Ptr_t ptr(obj, wxSimpleJSON::Destroy);
    return ptr;
}

void wxSimpleJSON::Destroy(wxSimpleJSON* obj)
{
    if(obj->m_canDelete) {
        cJSON_Delete(obj->m_d);
    }
    obj->m_d = NULL;
    wxDELETE(obj);
}

wxSimpleJSON& wxSimpleJSON::ArrayAdd(wxSimpleJSON::Ptr_t obj)
{
    cJSON_AddItemToArray(m_d, obj->m_d);
    return *this;
}

wxSimpleJSON& wxSimpleJSON::ArrayAdd(const wxString& value, const wxMBConv& conv)
{
    cJSON_AddItemToArray(m_d, cJSON_CreateString(value.mb_str(conv).data()));
    return *this;
}

wxSimpleJSON& wxSimpleJSON::ArrayAdd(double value)
{
    cJSON_AddItemToArray(m_d, cJSON_CreateNumber(value));
    return *this;
}

wxSimpleJSON& wxSimpleJSON::Add(const wxString& name, wxSimpleJSON::Ptr_t obj)
{
    cJSON_AddItemToObject(m_d, name.mb_str(wxConvUTF8).data(), obj->m_d);
    return *this;
}

wxSimpleJSON& wxSimpleJSON::Add(const wxString& name, const wxString& value, const wxMBConv& conv)
{
    cJSON_AddStringToObject(m_d, name.mb_str(wxConvUTF8).data(), value.mb_str(conv).data());
    return *this;
}

wxSimpleJSON& wxSimpleJSON::Add(const wxString& name, double value)
{
    cJSON_AddNumberToObject(m_d, name.mb_str(wxConvUTF8).data(), value);
    return *this;
}

wxSimpleJSON& wxSimpleJSON::ArrayAdd(const wxArrayString& arr, const wxMBConv& conv)
{
    wxSimpleJSON::Ptr_t parr = Create(wxSimpleJSON::kArray);
    for(size_t i = 0; i < arr.size(); ++i) {
        parr->ArrayAdd(arr.Item(i), conv);
    }
    return ArrayAdd(parr);
}

wxSimpleJSON& wxSimpleJSON::Add(const wxString& name, const wxArrayString& arr, const wxMBConv& conv)
{
    wxSimpleJSON::Ptr_t parr = Create(wxSimpleJSON::kArray);
    for(size_t i = 0; i < arr.size(); ++i) {
        parr->ArrayAdd(arr.Item(i), conv);
    }
    return Add(name, parr);
}
