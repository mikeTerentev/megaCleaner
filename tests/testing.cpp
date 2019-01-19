//
// Created by Михаил Терентьев on 2018-12-21.
//
#include <tests/gtest/gtest.h>
#include <QObject>
#include <dataparser.h>
#include <QByteArray>
const QString dir = "/Users/miketerentyev/itmo/2-year/MegaCleaner/tests/test_dir";

TEST(easy, three_equals){
    DataParser parser(dir + "/three-same-files");
    parser.find_dublicate();
    EXPECT_TRUE(parser.getDuplicateMap().size() == 1);
    EXPECT_TRUE(parser.getDuplicateMap().begin()->size() == 3);
}

TEST(easy, three_different){
    DataParser parser(dir + "/three-different-files");
    parser.find_dublicate();
    EXPECT_TRUE(parser.getDuplicateMap().isEmpty());
}

TEST(easy, several_groups){
    DataParser parser(dir + "/several-groups");
    parser.find_dublicate();
    EXPECT_TRUE(parser.getDuplicateMap().size() == 2);
    auto data = parser.getDuplicateMap();
    for(auto i = data.begin(); i != data.end(); i++){
        EXPECT_TRUE(i->size() == 3);
    }
}

TEST(correctness,tree_with_subdirs_equals){
    DataParser parser(dir + "/tree");
    parser.find_dublicate();
    EXPECT_TRUE(parser.getDuplicateMap().size() == 1 );
    EXPECT_TRUE(parser.getDuplicateMap().begin()->size() == 4);
}

TEST(correctness,tree_with_subdirs_diff){
    DataParser parser(dir + "/tree-diff");
    parser.find_dublicate();
    EXPECT_TRUE(parser.getDuplicateMap().isEmpty());
}


TEST(correctness, empty) {
    DataParser parser(dir + "/empty");
    parser.find_dublicate();
    EXPECT_TRUE(parser.getDuplicateMap().size() == 1);
    EXPECT_TRUE(parser.getDuplicateMap().begin()->size() == 2 );
}

TEST(correctness, end_test){
    DataParser parser(dir + "/end-test");
    parser.find_dublicate();
    EXPECT_TRUE(parser.getDuplicateMap().size() == 1);
    EXPECT_TRUE(parser.getDuplicateMap().begin()->size() == 2 );
}

TEST(correctness, hidden_files){
    DataParser parser(dir + "/hidden-files");
    parser.find_dublicate();
    EXPECT_TRUE(parser.getDuplicateMap().size() == 1);
    EXPECT_TRUE(parser.getDuplicateMap().begin()->size() == 2 );
}

TEST(correctness, symlink){
    DataParser parser(dir + "/symlink");
    parser.find_dublicate();
    EXPECT_TRUE(parser.getDuplicateMap().isEmpty());
}

TEST(correctness, recursion_symlink){
    DataParser parser(dir + "/symlink-recurs");
    parser.find_dublicate();
    EXPECT_TRUE(parser.getDuplicateMap().isEmpty());
}



