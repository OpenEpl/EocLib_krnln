#pragma once
#include <e/system/basic_type.h>
#include <e/system/func.h>
namespace e::lib::krnln
{
    struct COMObject
    {
    public:
        COMObject() noexcept;
        COMObject(const COMObject &that) noexcept;
        COMObject(std::nullptr_t) noexcept;
        COMObject(COMObject &&that) noexcept;
        ~COMObject() noexcept;
        COMObject &operator=(const COMObject &that) noexcept;
        COMObject &operator=(COMObject &&that) noexcept;
        COMObject &operator=(std::nullptr_t) noexcept;
        void Clear() noexcept;
        bool IsNull() noexcept;
        bool ReferenceEquals(const COMObject &that) noexcept;

    private:
        void *data;
    };
}