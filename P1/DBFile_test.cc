#include "DBFile.h"
#include <gtest/gtest.h>
// name of bin file and path where it should be created and also used to open .bin file
#define filepath "/mnt/c/Prajan/Sem-2/DBI/DBI/P1/bin/lineitem.bin" 
// invalid filepath for open testcase
#define invalidfilepath "/mnt/c/Prajan/Sem-2/DBI/DBI/P1/bin/lineitem1.bin" 
// error message for invalid file opening 
#define errormessage "BAD!  Open did not work for /mnt/c/Prajan/Sem-2/DBI/DBI/P1/bin/lineitem1.bin" 


// 1 Testcases for DBFile::Create

// 1.a with heap as file type it should return 1
TEST(DBFileCreateTest, TestingHeapFileType) 
    { 
    DBFile dbfile;
    ASSERT_EQ(1,dbfile.Create(filepath,heap,NULL));
    }
// 1.b with nonheap (sorted,tree) as file type it should return 0
TEST(DBFileCreateTest, TestingNonHeapFileType) 
    { 
    DBFile dbfile;
    ASSERT_EQ(0,dbfile.Create(filepath,sorted,NULL));
    }

// 2 Testcases for DBFile::Open

// 2.a with valid filepath to open so it should return 1
TEST(DBFileOpenTest, TestingValidPath) 
    { 
    DBFile dbfile;
    ASSERT_EQ(1,dbfile.Open(filepath));
    }
// 2.b with invalid file type to open, it gets exit(1) with "BAD!  Open did not work for ..." message
// validating it with ASSER_DEATH
TEST(DBFileOpenTest, TestingInvalidPath) 
    { 
    DBFile dbfile;
    ::testing::FLAGS_gtest_death_test_style = "threadsafe";
    ASSERT_DEATH(dbfile.Open(invalidfilepath),errormessage);
    }

// 3 Testcases for DBFile::Close

// 3.a testing close body  
TEST(DBFileCloseTest, TestingClosewithOpening) 
    { 
    DBFile dbfile;
    dbfile.Open(filepath);
    ASSERT_EQ(1,dbfile.Close());
    }


int main(int argc, char **argv) 
    {
    testing::InitGoogleTest(&argc, argv);
    return RUN_ALL_TESTS();
    }