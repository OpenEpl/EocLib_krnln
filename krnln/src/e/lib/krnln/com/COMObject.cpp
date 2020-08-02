#include "COMObject.h"
#include <unknwn.h>
namespace e::lib::krnln
{
    inline HRESULT CLSIDFromDescription(const e::system::string &description, CLSID *result)
    {
        auto descriptionW = e::system::ToNativeWideString(description);
        HRESULT hRet = CLSIDFromProgID(descriptionW.get(), result);
        if (FAILED(hRet))
        {
            hRet = CLSIDFromString(descriptionW.get(), result);
        }
        return hRet;
    }
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
    bool COMObjectImpl::CreateInstance(const e::system::string &description)
    {
        this->Clear();
        CLSID clsid;
        HRESULT hRet = CLSIDFromDescription(description, &clsid);
        if (FAILED(hRet))
        {
            this->last_error = hRet;
            return false;
        }
        IUnknown *lpUnknown = nullptr;
        hRet = CoCreateInstance(clsid, nullptr, CLSCTX_ALL | CLSCTX_REMOTE_SERVER, IID_IUnknown, (LPVOID *)&lpUnknown);
        if (hRet == E_INVALIDARG)
        {
            // try without CLSCTX_REMOTE_SERVER
            hRet = CoCreateInstance(clsid, nullptr, CLSCTX_ALL & ~CLSCTX_REMOTE_SERVER, IID_IUnknown, (LPVOID *)&lpUnknown);
        }
        if (FAILED(hRet))
        {
            this->last_error = hRet;
            return false;
        }
        hRet = OleRun(lpUnknown);
        if (FAILED(hRet))
        {
            this->last_error = hRet;
            return false;
        }
        this->last_error = S_OK;
        this->data = lpUnknown;
        return true;
    }
    bool COMObjectImpl::CreateInstance(const e::system::string &description, const e::system::string &typelibrary)
    {
        this->Clear();
        auto descriptionW = e::system::ToNativeWideString(description);
        auto typeLibPathW = e::system::ToNativeWideString(typelibrary);
        IUnknown *lpUnknown = nullptr;
        ITypeLib *typeLib;
        HRESULT hRet = LoadTypeLib(typeLibPathW.get(), &typeLib);
        if (SUCCEEDED(hRet))
        {
            ITypeInfo *typeInfo = nullptr;
            MEMBERID rgMemId;
            USHORT cFound = 1;
            hRet = typeLib->FindName(descriptionW.get(), 0, &typeInfo, &rgMemId, &cFound);
            if (SUCCEEDED(hRet) && cFound == 1)
            {
                if (wcschr(typeLibPathW.get(), L'\\') != nullptr)
                {
                    RegisterTypeLib(typeLib, typeLibPathW.get(), nullptr);
                }
                typeInfo->CreateInstance(nullptr, IID_IUnknown, (LPVOID *)&lpUnknown);
                typeInfo->Release();
            }
            typeLib->Release();
        }

        if (lpUnknown == nullptr)
        {
            return this->CreateInstance(description);
        }

        hRet = OleRun(lpUnknown);
        if (FAILED(hRet))
        {
            this->last_error = hRet;
            return false;
        }
        this->last_error = S_OK;
        this->data = lpUnknown;
        return true;
    }
    bool COMObjectImpl::CreateInstance(const e::system::string &description, std::optional<std::reference_wrapper<const e::system::string>> typelibrary)
    {
        if (typelibrary.has_value())
        {
            return this->CreateInstance(description, typelibrary.value().get());
        }
        else
        {
            return this->CreateInstance(description);
        }
    }
    e::system::string COMObjectImpl::GetErrorMessage()
    {
        if (SUCCEEDED(this->last_error))
        {
            return e::system::string(nullptr);
        }
        wchar_t *errorTextW = nullptr;
        DWORD ret = FormatMessageW(
            FORMAT_MESSAGE_FROM_SYSTEM | FORMAT_MESSAGE_ALLOCATE_BUFFER | FORMAT_MESSAGE_IGNORE_INSERTS,
            nullptr,
            this->last_error,
            MAKELANGID(LANG_NEUTRAL, SUBLANG_DEFAULT),
            (LPWSTR)&errorTextW,
            0,
            nullptr);
        if (ret == 0 || errorTextW == nullptr)
        {
            return EOC_STR_CONST("Unexpected error is raised when getting error message.");
        }
        e::system::string result = e::system::ReceiveNativeWideString(errorTextW);
        LocalFree(errorTextW);
        return result;
    }
}