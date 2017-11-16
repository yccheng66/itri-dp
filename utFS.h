#ifndef UTFS_H
#define UTFS_H
#include "node.h"

TEST(FileSystem, file_existing) {
  File file("utFS.cpp");
  ASSERT_EQ("utFS.cpp", file.name());
  ASSERT_EQ(161,file.getCharCount());
}

TEST(FileSystem, file_nonexsting) {
  ASSERT_THROW(new File("file_nonexsting"), string);
}

TEST(FileSystem, directory) {
  Directory dir("NewDir");
  ASSERT_EQ("NewDir", dir.name());
}

TEST(FileSystem, dir_notexisting) {
  ASSERT_THROW(new Directory("dir_notexisting"), string);
}

TEST(FileSystem, node_file) {
  Node *node = new File("utFS.cpp");
  ASSERT_EQ("utFS.cpp", node->name());
  ASSERT_EQ(161, node->getCharCount());
}

TEST(FileSystem, node_directory) {
  Node *node = new Directory("NewDir");
  ASSERT_EQ("NewDir", node->name());
  ASSERT_THROW(node->getCharCount(), string);
}

TEST(FileSystem, directory_add_entry) {
  Node *dir = new Directory("NewDir");
  Node *folder1 = new Directory("NewDir/folder1");
  Node *file = new File("NewDir/dir.cpp");
  dir->addEntry(folder1);
  ASSERT_EQ(1, dir->numEntries());
  dir->addEntry(file);
  ASSERT_EQ(2, dir->numEntries());
}

TEST(FileSystem, file_add_entry){
  Node *file = new File("NewDir/dir.cpp");
  Node *folder1 = new Directory("NewDir/folder1");
  ASSERT_THROW(file->addEntry(folder1), string);
  ASSERT_THROW(file->numEntries(), string);
}
#endif
