#pragma once
#include <e/system/basic_type.h>
#include <e/system/func.h>
namespace e::lib::krnln
{
    struct COMObjectImpl;
    typedef e::system::struct_ptr<COMObjectImpl> COMObject;
    struct COMObjectImpl
    {
    public:
        COMObjectImpl() noexcept;
        COMObjectImpl(const COMObjectImpl &that) noexcept;
        COMObjectImpl(std::nullptr_t) noexcept;
        COMObjectImpl(COMObjectImpl &&that) noexcept;
        ~COMObjectImpl() noexcept;
        COMObjectImpl &operator=(const COMObjectImpl &that) noexcept;
        COMObjectImpl &operator=(COMObjectImpl &&that) noexcept;
        COMObjectImpl &operator=(std::nullptr_t) noexcept;
        void Clear() noexcept;
        bool IsNull() noexcept;
        bool ReferenceEquals(const COMObject &that) noexcept;
        bool CreateInstance(const e::system::string &description);
        bool CreateInstance(const e::system::string &description, const e::system::string &typelibrary);
        bool CreateInstance(const e::system::string &description, std::optional<std::reference_wrapper<const e::system::string>> typelibrary);
    private:
        void *data;
    };
}