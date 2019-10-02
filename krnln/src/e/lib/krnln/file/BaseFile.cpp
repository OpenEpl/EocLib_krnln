#include "BaseFile.h"
#include <vector>
#include <algorithm>

bool e::lib::krnln::BaseFile::IsEndOfFile()
{
    return GetPosition() == GetLength();
}

bool e::lib::krnln::BaseFile::IsEndOfTextFile()
{
    if (IsEndOfFile())
        return true;
    uint8_t x;
    if (!Read(&x, sizeof(x)))
        return true;
    Seek(-static_cast<long long>(sizeof(x)), SeekOrigin::Current);
    if (x == 0 || x == 26)
        return true;
    return false;
}

void e::lib::krnln::BaseFile::Seek(long long offset, SeekOrigin whence)
{

    switch (whence)
    {
    case SeekOrigin::Begin:
        SetPosition(offset);
        break;
    case SeekOrigin::End:
        SetPosition(GetLength() - offset);
        break;
    case SeekOrigin::Current:
        SetPosition(GetPosition() + offset);
        break;
    }
}

void e::lib::krnln::BaseFile::SeekToBegin()
{
    return Seek(0, SeekOrigin::Begin);
}

void e::lib::krnln::BaseFile::SeekToEnd()
{
    return Seek(0, SeekOrigin::End);
}

void e::lib::krnln::BaseFile::Flush()
{
}

template <char... terminator>
static e::system::string ReadTextUntil(e::lib::krnln::BaseFile *object, unsigned long long limit = std::numeric_limits<unsigned long long>::max())
{
    std::vector<uint8_t> data;
    char terminatorArr[] = {terminator...};
    while (true)
    {
        auto bufferSize = std::min<size_t>(4096, size_t(limit - data.size()));
        if (!bufferSize)
            goto finished;

        auto start = data.size();
        data.resize(start + bufferSize);

        auto startPtr = data.data() + start;
        bufferSize = object->Read(startPtr, bufferSize);
        data.resize(start + bufferSize);
        startPtr = data.data() + start;
        if (!bufferSize)
            goto finished;

        for (size_t i = 0; i < bufferSize; i++)
        {
            for (auto iter = std::begin(terminatorArr); iter != std::end(terminatorArr); iter++)
            {
                if (startPtr[i] == *iter)
                {
                    data.resize(start + i);
                    //Do not skip the end mask byte
                    object->Seek(-static_cast<long long>(bufferSize - i), e::lib::krnln::SeekOrigin::Current);
                    goto finished;
                }
            }
        }
    }
finished:
    e::system::string result(data.size());
    memcpy(result.c_str(), data.data(), data.size());
    if (!data.empty())
        result.data[data.size()] = '\0';
    return result;
}

e::system::string e::lib::krnln::BaseFile::ReadText(unsigned long long limit)
{
    return ReadTextUntil<'\0', '\x1a'>(this, limit);
}

e::system::string e::lib::krnln::BaseFile::ReadLine()
{
    auto result = ReadTextUntil<'\r', '\n'>(this);
    uint8_t nextChar;
    if (Read(&nextChar, sizeof(nextChar)))
    {
        if (nextChar == '\r')
        {
            //Processing CRLF (Windows-style line feed)
            if (Read(&nextChar, sizeof(nextChar)))
            {
                if (nextChar != '\n')
                    Seek(-static_cast<long long>(sizeof(nextChar)), SeekOrigin::Current);
            }
        }
    }
    return result;
}

#define DefineObjectInRawFormat(type)                          \
    void e::lib::krnln::BaseFile::ReadObject(type &x)          \
    {                                                          \
        if (Read(&x, sizeof(x)) != sizeof(x))                  \
            throw std::runtime_error("Unable to read object"); \
    }                                                          \
    void e::lib::krnln::BaseFile::WriteObject(type x)          \
    {                                                          \
        Write(&x, sizeof(x));                                  \
    }

DefineObjectInRawFormat(uint8_t);
DefineObjectInRawFormat(int16_t);
DefineObjectInRawFormat(int32_t);
DefineObjectInRawFormat(int64_t);
DefineObjectInRawFormat(float);
DefineObjectInRawFormat(double);
DefineObjectInRawFormat(e::system::datetime);
DefineObjectInRawFormat(e::system::methodptr);

void e::lib::krnln::BaseFile::ReadObject(bool &x)
{
    int32_t t;
    ReadObject(t);
    x = t != 0;
}
void e::lib::krnln::BaseFile::WriteObject(bool x)
{
    WriteObject((int32_t)(x ? 0 : 1));
}

void e::lib::krnln::BaseFile::ReadObject(e::system::string &x)
{
    x = ReadTextUntil<'\0'>(this);
    uint8_t nextChar;
    Read(&nextChar, sizeof(nextChar)); //Skip \0
}
void e::lib::krnln::BaseFile::WriteObject(const e::system::string &x)
{
    auto len = x.len();
    if (len == 0)
    {
        char x = '\0';
        Write(&x, sizeof(x));
    }
    else
    {
        Write(x.c_str(), len + 1);
    }
}

void e::lib::krnln::BaseFile::ReadObject(e::system::bin &x)
{
    size_t len;
    int32_t data1;
    if (Read(&data1, sizeof(data1)) != sizeof(data1))
    {
        throw std::runtime_error("Unable to read bin object, length error");
    }
    len = (size_t)data1;
    x.Redim(false, len);
    if (Read(x.GetElemPtr(), len) != len)
    {
        throw std::runtime_error("Unable to read bin object, length mismatch");
    }
}
void e::lib::krnln::BaseFile::WriteObject(const e::system::bin &x)
{
    size_t len = x.GetSize();
    int32_t data1;
    if (len > (size_t)UINT32_MAX)
    {
        throw std::runtime_error("Unable to write bin object, length too large");
    }
    data1 = (int32_t)len;
    Write(&data1, sizeof(data1));
    Write(x.GetElemPtr(), len);
}

void e::lib::krnln::BaseFile::WriteText(const e::system::string &x)
{
    Write(x.c_str(), x.len());
}
void e::lib::krnln::BaseFile::WriteLine(const e::system::string &x)
{
    Write(x.c_str(), x.len());
    Write("\r\n", 2);
}
