#include "COMObject.h"
#include <unknwn.h>
namespace e::lib::krnln
{
    COMObject::COMObject() noexcept : COMObject(nullptr)
    {
    }
    COMObject::COMObject(const COMObject &that) noexcept
    {
        this->data = that.data;
        if (this->data)
        {
            auto obj = static_cast<IUnknown *>(this->data);
            obj->AddRef();
        }
    }
    COMObject::COMObject(std::nullptr_t) noexcept : data(nullptr)
    {
    }
    COMObject::COMObject(COMObject &&that) noexcept
    {
        this->data = that.data;
        that.data = nullptr;
    }
    COMObject &COMObject::operator=(const COMObject &that) noexcept
    {
        this->~COMObject();
        this->data = that.data;
        if (this->data)
        {
            auto obj = static_cast<IUnknown *>(this->data);
            obj->AddRef();
        }
        return *this;
    }
    COMObject &COMObject::operator=(COMObject &&that) noexcept
    {
        this->~COMObject();
        this->data = that.data;
        that.data = nullptr;
        return *this;
    }
    COMObject &COMObject::operator=(std::nullptr_t) noexcept
    {
        this->~COMObject();
        this->data = nullptr;
        return *this;
    }
    COMObject::~COMObject() noexcept
    {
        if (this->data)
        {
            auto obj = static_cast<IUnknown *>(this->data);
            obj->Release();
        }
    }
    void COMObject::Clear() noexcept
    {
        *this = nullptr;
    }
    bool COMObject::IsNull() noexcept
    {
        return this->data == nullptr;
    }
    bool COMObject::ReferenceEquals(const COMObject &that) noexcept
    {
        return this->data == that.data;
    }
}