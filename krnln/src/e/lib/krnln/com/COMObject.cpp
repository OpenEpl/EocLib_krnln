#include "COMObject.h"
#include <unknwn.h>
namespace e::lib::krnln
{
    COMObjectImpl::COMObjectImpl() noexcept : COMObjectImpl(nullptr)
    {
    }
    COMObjectImpl::COMObjectImpl(const COMObjectImpl &that) noexcept
    {
        this->data = that.data;
        if (this->data)
        {
            auto obj = static_cast<IUnknown *>(this->data);
            obj->AddRef();
        }
    }
    COMObjectImpl::COMObjectImpl(std::nullptr_t) noexcept : data(nullptr)
    {
    }
    COMObjectImpl::COMObjectImpl(COMObjectImpl &&that) noexcept
    {
        this->data = that.data;
        that.data = nullptr;
    }
    COMObjectImpl &COMObjectImpl::operator=(const COMObjectImpl &that) noexcept
    {
        this->~COMObjectImpl();
        this->data = that.data;
        if (this->data)
        {
            auto obj = static_cast<IUnknown *>(this->data);
            obj->AddRef();
        }
        return *this;
    }
    COMObjectImpl &COMObjectImpl::operator=(COMObjectImpl &&that) noexcept
    {
        this->~COMObjectImpl();
        this->data = that.data;
        that.data = nullptr;
        return *this;
    }
    COMObjectImpl &COMObjectImpl::operator=(std::nullptr_t) noexcept
    {
        this->~COMObjectImpl();
        this->data = nullptr;
        return *this;
    }
    COMObjectImpl::~COMObjectImpl() noexcept
    {
        if (this->data)
        {
            auto obj = static_cast<IUnknown *>(this->data);
            obj->Release();
        }
    }
    void COMObjectImpl::Clear() noexcept
    {
        *this = nullptr;
    }
    bool COMObjectImpl::IsNull() noexcept
    {
        return this->data == nullptr;
    }
    bool COMObjectImpl::ReferenceEquals(const COMObject &that) noexcept
    {
        return this->data == that->data;
    }
}