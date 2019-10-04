#pragma once
#include <e/system/basic_type.h>
#include <e/system/func.h>
#include <limits>
namespace e
{
    namespace lib
    {
        namespace krnln
        {
            enum class SeekOrigin
            {
                Begin = 1,
                End,
                Current
            };

            enum class FileAccessMode
            {
                ReadOnly = 1,
                WriteOnly,
                ReadWrite,
                Rewrite,
                WriteAlways,
                Edit
            };

            enum class FileShareMode
            {
                Unlimited = 1,
                ShareWrite,
                ShareRead,
                Exclusive
            };

            class BaseFile
            {
            public:
                virtual ~BaseFile() = default;
                virtual size_t Read(void *buffer, size_t length) = 0;
                virtual void Write(const void *buffer, size_t length) = 0;
                virtual unsigned long long GetLength() = 0;
                virtual unsigned long long GetPosition() = 0;
                virtual void SetPosition(unsigned long long position) = 0;
                virtual bool IsEndOfFile();
                virtual bool IsEndOfTextFile();
                virtual void Seek(long long offset, SeekOrigin whence);
                virtual void SeekToBegin();
                virtual void SeekToEnd();
                virtual void Flush();
                virtual e::system::string ReadText(unsigned long long limit = std::numeric_limits<unsigned long long>::max());
                virtual e::system::string ReadLine();
                virtual void WriteText(const e::system::string &x);
                virtual void WriteLine(const e::system::string &x);
                virtual void ReadObject(bool &x);
                virtual void ReadObject(uint8_t &x);
                virtual void ReadObject(int16_t &x);
                virtual void ReadObject(int32_t &x);
                virtual void ReadObject(int64_t &x);
                virtual void ReadObject(float &x);
                virtual void ReadObject(double &x);
                virtual void ReadObject(e::system::datetime &x);
                virtual void ReadObject(e::system::methodptr &x);
                virtual void ReadObject(e::system::string &x);
                virtual void ReadObject(e::system::bin &x);
                virtual void WriteObject(bool x);
                virtual void WriteObject(uint8_t x);
                virtual void WriteObject(int16_t x);
                virtual void WriteObject(int32_t x);
                virtual void WriteObject(int64_t x);
                virtual void WriteObject(float x);
                virtual void WriteObject(double x);
                virtual void WriteObject(e::system::datetime x);
                virtual void WriteObject(e::system::methodptr x);
                virtual void WriteObject(const e::system::string &x);
                virtual void WriteObject(const e::system::bin &x);
                template <typename T>
                void WriteObject(const e::system::array<T> &x)
                {
                    for (auto i = x.begin(); i != x.end(); ++i)
                    {
                        WriteObject(x);
                    }
                }
            };
        }
    }
}