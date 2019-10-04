#include "MemoryFile.h"

size_t e::lib::krnln::MemoryFile::Read(void *buffer, size_t length)
{
    size_t numOfRead = std::min(length, data.size() - position);
    memcpy(buffer, data.data() + position, numOfRead);
    position += numOfRead;
    return numOfRead;
}
void e::lib::krnln::MemoryFile::Write(const void *buffer, size_t length)
{
    if (position + length > data.size())
        data.resize(position + length);
    memcpy(data.data() + position, buffer, length);
    position += length;
}
unsigned long long e::lib::krnln::MemoryFile::GetLength()
{
    return data.size();
}
unsigned long long e::lib::krnln::MemoryFile::GetPosition()
{
    return position;
}
void e::lib::krnln::MemoryFile::SetPosition(unsigned long long newPosition)
{
    if (newPosition > std::numeric_limits<size_t>::max())
        throw std::invalid_argument("new position is too large");
    if ((size_t)newPosition > data.size())
        data.resize((size_t)newPosition);
    position = (size_t)newPosition;
}