#include "wxSimpleJSON.h"
#include "cJSON.h"
#include <wx/ffile.h>

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

wxSimpleJSON::Ptr_t wxSimpleJSON::Create(cJSON* p, bool canDelete)
{
    wxSimpleJSON* obj = new wxSimpleJSON();
    obj->m_d = p;
    obj->m_canDelete = canDelete;
    wxSimpleJSON::Ptr_t ptr(obj, wxSimpleJSON::Destroy);
    return ptr;
}

void wxSimpleJSON::Destroy(wxSimpleJSON* obj)
{
    if(obj->m_canDelete && obj->m_d) {
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

size_t wxSimpleJSON::ArraySize() const { return cJSON_GetArraySize(m_d); }

wxSimpleJSON::Ptr_t wxSimpleJSON::Item(size_t index) const
{
    if(!m_d || (m_d->type != cJSON_Array)) {
        return Create((cJSON*)NULL);
    }
    cJSON* item = cJSON_GetArrayItem(m_d, index);
    return Create(item);
}

wxString wxSimpleJSON::GetValueString(const wxMBConv& conv) const
{
    if(!m_d || (m_d->type != cJSON_String)) {
        return wxEmptyString;
    }
    return wxString(m_d->valuestring, conv);
}

wxArrayString wxSimpleJSON::GetValueArrayString(const wxMBConv& conv) const
{
    if(!m_d || (m_d->type != cJSON_Array)) {
        return wxArrayString();
    }

    wxArrayString arr;
    wxSimpleJSON::Ptr_t parr = Create(m_d);
    for(size_t i = 0; i < parr->ArraySize(); ++i) {
        arr.Add(parr->Item(i)->GetValueString(conv));
    }
    return arr;
}

double wxSimpleJSON::GetValueNumber(double defaultValue) const
{
    if(!m_d || (m_d->type != cJSON_Number)) {
        return defaultValue;
    }
    return m_d->valuedouble;
}

wxSimpleJSON::Ptr_t wxSimpleJSON::GetProperty(const wxString& name) const
{
    if(!m_d || (m_d->type != cJSON_Object)) {
        return Create(NULL);
    }
    return Create(cJSON_GetObjectItem(m_d, name.mb_str(wxConvUTF8).data()));
}

wxSimpleJSON& wxSimpleJSON::ArrayAdd(bool value)
{
    if(!m_d || (m_d->type != cJSON_Array)) {
        return *this;
    }
    if(value) {
        cJSON_AddItemToArray(m_d, cJSON_CreateTrue());
    } else {
        cJSON_AddItemToArray(m_d, cJSON_CreateFalse());
    }
    return *this;
}

wxSimpleJSON& wxSimpleJSON::Add(const wxString& name, bool value)
{
    if(!m_d || (m_d->type != cJSON_Object)) {
        return *this;
    }
    cJSON_AddBoolToObject(m_d, name.mb_str(wxConvUTF8).data(), value);
    return *this;
}

bool wxSimpleJSON::GetValueBool(bool defaultValue) const
{
    if(!m_d || m_d->type != cJSON_True || m_d->type != cJSON_False) {
        return defaultValue;
    }
    // at this point, type can only be cJSON_True or cJSON_False
    return m_d->type == cJSON_True;
}

wxSimpleJSON::Ptr_t wxSimpleJSON::Create(const wxString& buffer, const wxMBConv& conv)
{
    cJSON* p = cJSON_Parse(buffer.mb_str(conv).data());
    return Create(p, true);
}

wxSimpleJSON::Ptr_t wxSimpleJSON::Create(const wxFileName& filename, const wxMBConv& conv)
{
    if(!filename.Exists()) {
        return Create(NULL);
    }
    wxFFile fp(filename.GetFullPath(), "rb");
    wxString content;
    if(fp.IsOpened() && fp.ReadAll(&content, conv)) {
        fp.Close();
        return Create(content, conv);
    }
    return Create(NULL);
}

bool wxSimpleJSON::Save(const wxFileName& filename, const wxMBConv& conv)
{
    wxFFile fp(filename.GetFullPath(), "wb");
    if(fp.IsOpened()) {
        fp.Write(Print(true, conv), conv);
        fp.Close();
        return true;
    }
    return false;
}
