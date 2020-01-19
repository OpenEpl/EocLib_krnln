#pragma once
#include "BaseFile.h"
#include <vector>
#include <algorithm>
namespace e
{
    namespace lib
    {
        namespace krnln
        {
            class MemoryFile : public BaseFile
            {
            private:
                [[maybe_unused]] intptr_t reserve = -1;
                size_t position = 0;
                std::vector<uint8_t> data;

            public:
                virtual size_t Read(void *buffer, size_t length) override;
                virtual void Write(const void *buffer, size_t length) override;
                virtual unsigned long long GetLength() override;
                virtual unsigned long long GetPosition() override;
                virtual void SetPosition(unsigned long long newPosition) override;
                virtual void SetLength(unsigned long long length) override;
            };
        }
    }
}