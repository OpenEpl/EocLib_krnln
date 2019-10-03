#include <catch2/catch.hpp>
#include <e/lib/krnln/file/FileUtils.h>
#include <e/lib/krnln/BinUtils.h>
#include <e/lib/krnln/TextUtils.h>

using namespace e::lib::krnln;
TEST_CASE("FileUtils::GetTempFile", "[FileUtils]")
{
    auto t1 = FileUtils::GetTempFile();
    auto t2 = FileUtils::GetTempFile();
    CHECK(t1 != t2);
}

void TestForFileObject(intptr_t id)
{
    int32_t postion;

    CHECK(FileUtils::WriteData(id, e::system::bin{1, 2, 3, 4, 5}));
    CHECK(FileUtils::GetLength(id) == 5);
    CHECK(FileUtils::GetPosition(id) == FileUtils::GetLength(id));
    CHECK(FileUtils::SeekToBegin(id));
    CHECK(FileUtils::GetPosition(id) == 0);
    CHECK(FileUtils::ReadData(id, 2) == e::system::bin{1, 2});
    CHECK(FileUtils::ReadData(id, 0xff) == e::system::bin{3, 4, 5});
    CHECK(FileUtils::GetLength(id) == 5);
    CHECK(FileUtils::GetPosition(id) == FileUtils::GetLength(id));
    CHECK(FileUtils::SeekToBegin(id));
    CHECK(FileUtils::WriteData(id, e::system::bin{'A', 0}));
    CHECK(FileUtils::SeekToBegin(id));
    CHECK(FileUtils::ReadData(id, 0xff) == e::system::bin{'A', 0, 3, 4, 5});
    CHECK(FileUtils::SeekToBegin(id));
    CHECK(FileUtils::ReadText(id) == "A");
    CHECK(FileUtils::ReadText(id) == "");
    CHECK_FALSE(FileUtils::IsEOF(id, false));
    CHECK(FileUtils::IsEOF(id, true));
    CHECK(FileUtils::ReadData(id, 1) == e::system::bin{0});
    CHECK(FileUtils::ReadText(id) == "\x3\x4\x5");
    CHECK(FileUtils::ReadText(id) == "");

    postion = FileUtils::GetPosition(id);
    CHECK(FileUtils::WriteData(id, BinUtils::Repeat(8200, e::system::bin{'*'})));
    CHECK(FileUtils::WriteData(id, e::system::bin{'A', 0, 3, 4, 5}));
    FileUtils::Seek(id, static_cast<int32_t>(SeekOrigin::Begin), postion);
    CHECK(FileUtils::ReadText(id) == TextUtils::Repeat(8200, "*") + "A");
    CHECK(FileUtils::ReadData(id, 1) == e::system::bin{0});
    CHECK(FileUtils::ReadText(id) == "\x3\x4\x5");

    postion = FileUtils::GetPosition(id);
    CHECK(FileUtils::WriteData(id, e::system::bin{'A', 'B', '\r', 'C', 'D', '\n', 'E', 'F', '\r', '\n', 'G', 'H'}));
    FileUtils::Seek(id, static_cast<int32_t>(SeekOrigin::Begin), postion);
    CHECK(FileUtils::ReadLine(id) == "AB");
    CHECK(FileUtils::ReadLine(id) == "CD");
    CHECK(FileUtils::ReadLine(id) == "EF");
    CHECK(FileUtils::ReadLine(id) == "GH");

    e::system::string xStr;
    xStr = "ASD\r\nDEF";
    postion = FileUtils::GetPosition(id);
    CHECK(FileUtils::WriteObject(id, xStr));
    FileUtils::Seek(id, static_cast<int32_t>(SeekOrigin::Begin), postion);
    xStr = nullptr;
    CHECK(FileUtils::ReadObject(id, xStr));
    CHECK(xStr == "ASD\r\nDEF");

    e::system::bin xBin = {'A', 'B', 'C'};
    postion = FileUtils::GetPosition(id);
    CHECK(FileUtils::WriteObject(id, xBin));
    FileUtils::Seek(id, static_cast<int32_t>(SeekOrigin::Begin), postion);
    xBin = nullptr;
    CHECK(FileUtils::ReadObject(id, xBin));
    CHECK(xBin == e::system::bin{'A', 'B', 'C'});
}

TEST_CASE("Basic I/O Test for Memory File", "[FileUtils]")
{
    intptr_t id = FileUtils::NewMemoryFile();
    TestForFileObject(id);
    FileUtils::CloseFile(id);
}

TEST_CASE("Basic I/O Test for Local File", "[FileUtils]")
{
    auto path = FileUtils::GetTempFile();
    intptr_t id = FileUtils::OpenFile(path, static_cast<int32_t>(FileAccessMode::Rewrite), static_cast<int>(FileShareMode::Unlimited));
    TestForFileObject(id);
    FileUtils::CloseFile(id);
    FileUtils::DeleteDiskFile(path);
}

TEST_CASE("Differrnt I/O Access Mode for Local File", "[FileUtils]")
{
    auto path = FileUtils::GetTempFile();

    CHECK(FileUtils::OpenFile(path, static_cast<int32_t>(FileAccessMode::ReadOnly)) == 0);
    CHECK(FileUtils::OpenFile(path, static_cast<int32_t>(FileAccessMode::ReadWrite)) == 0);
    CHECK(FileUtils::OpenFile(path, static_cast<int32_t>(FileAccessMode::WriteOnly)) == 0);

    intptr_t id;

    id = FileUtils::OpenFile(path, static_cast<int32_t>(FileAccessMode::Rewrite));
    REQUIRE(id);
    FileUtils::WriteData(id, e::system::bin{'A', 'B', 'C'});
    FileUtils::CloseFile(id);

    id = FileUtils::OpenFile(path, static_cast<int32_t>(FileAccessMode::ReadOnly));
    REQUIRE(id);
    CHECK(FileUtils::GetLength(id) == 3);
    FileUtils::SeekToEnd(id);
    FileUtils::WriteData(id, e::system::bin{'F'}); // should be failed
    FileUtils::CloseFile(id);

    id = FileUtils::OpenFile(path, static_cast<int32_t>(FileAccessMode::ReadWrite));
    REQUIRE(id);
    CHECK(FileUtils::GetLength(id) == 3);
    FileUtils::SeekToEnd(id);
    FileUtils::WriteData(id, e::system::bin{'S'}); // should be successful
    FileUtils::CloseFile(id);

    id = FileUtils::OpenFile(path, static_cast<int32_t>(FileAccessMode::ReadOnly));
    REQUIRE(id);
    CHECK(FileUtils::GetLength(id) == 4);
    FileUtils::CloseFile(id);

    id = FileUtils::OpenFile(path, static_cast<int32_t>(FileAccessMode::Rewrite));
    REQUIRE(id);
    CHECK(FileUtils::GetLength(id) == 0);
    FileUtils::CloseFile(id);

    FileUtils::DeleteDiskFile(path);

    id = FileUtils::OpenFile(path, static_cast<int32_t>(FileAccessMode::Edit));
    REQUIRE(id);
    CHECK(FileUtils::GetLength(id) == 0);
    FileUtils::WriteData(id, e::system::bin{'A', 'B', 'C'});
    FileUtils::CloseFile(id);

    id = FileUtils::OpenFile(path, static_cast<int32_t>(FileAccessMode::Edit));
    REQUIRE(id);
    CHECK(FileUtils::GetLength(id) == 3);
    FileUtils::CloseFile(id);

    FileUtils::DeleteDiskFile(path);
}