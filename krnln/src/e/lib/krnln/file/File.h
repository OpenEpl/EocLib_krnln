#pragma once
#include "BaseFile.h"
namespace e
{
    namespace lib
    {
        namespace krnln
        {
            class File : public BaseFile
            {
            private:
                intptr_t handle;

            public:
                File();
                File(intptr_t handle);
                File(File &&file) noexcept;
                File &operator=(File &&file) noexcept;
                virtual ~File();
                virtual size_t Read(void *buffer, size_t length) override;
                virtual void Write(void *buffer, size_t length) override;
                virtual unsigned long long GetLength() override;
                virtual unsigned long long GetPosition() override;
                virtual void SetPosition(unsigned long long newPosition) override;
                virtual void Flush() override;
                virtual void Seek(long long offset, SeekOrigin whence) override;
                static File Open(const e::system::string &filePath, FileAccessMode accessMode, FileShareMode shareMode);
            };
        }
    }
}