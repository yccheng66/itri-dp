#ifndef UTFS_H
#define UTFS_H
#include "node.h"
#include "directory.h"
#include "link.h"
#include "directory_builder.h"
#include "level_iterator.h"

class FileSystem : public ::testing::Test {
protected:
  virtual void SetUp() {
    if (getcwd(cwd, sizeof(cwd)) == NULL)
      throw string("error in fixture setup");
  }
  virtual void TearDown() {
    if (chdir(cwd) != 0)
      throw string("error in fixture teardown");
  }
  char cwd[1024];
};

TEST_F(FileSystem, file_existing) {
  File file("utFS.cpp");
  ASSERT_EQ("utFS.cpp", file.name());
  ASSERT_EQ(161,file.getCharCount());
}

TEST_F(FileSystem, file_nonexsting) {
  ASSERT_THROW(new File("file_nonexsting"), string);
}

TEST_F(FileSystem, directory) {
  Directory dir("NewDir");
  ASSERT_EQ("NewDir", dir.name());
}

TEST_F(FileSystem, dir_notexisting) {
  ASSERT_THROW(new Directory("dir_notexisting"), string);
}

TEST_F(FileSystem, node_file) {
  Node *node = new File("utFS.cpp");
  ASSERT_EQ("utFS.cpp", node->name());
  ASSERT_EQ(161, node->getCharCount());
}

TEST_F(FileSystem, node_directory) {
  Node *node = new Directory("NewDir");
  ASSERT_EQ("NewDir", node->name());
  ASSERT_THROW(node->getCharCount(), string);
}

TEST_F(FileSystem, directory_add_entry) {
  Directory *dir = new Directory("NewDir");
  Node *folder1 = new Directory("NewDir/folder1");
  Node *file = new File("NewDir/dir.cpp");
  dir->addEntry(folder1);
  ASSERT_EQ(1, dir->numEntries());
  dir->addEntry(file);
  ASSERT_EQ(2, dir->numEntries());
  ASSERT_EQ("NewDir/dir.cpp", dir->getEntry(1)->name());
}

TEST_F(FileSystem, file_add_entry){
  Node *file = new File("NewDir/dir.cpp");
  Node *folder1 = new Directory("NewDir/folder1");
  ASSERT_THROW(file->addEntry(folder1), string);
  ASSERT_THROW(file->numEntries(), string);
}
TEST_F(FileSystem, link){
  File *file = new File("NewDir/dir.cpp");
  Node *link = new Link("NewDir/lnf1",file);
  ASSERT_EQ(258,link->getCharCount());
  ASSERT_EQ("NewDir/lnf1",link->name());

}

TEST_F(FileSystem, directoryGivenName) {
  DirectoryBuilder db;
  db.buildDirectory("NewDir");
  Directory *dir = db.getDirectory();

  ASSERT_EQ(".", dir->getEntry(0)->name());
  ASSERT_EQ("..", dir->getEntry(1)->name());
  ASSERT_EQ("dir.cpp", dir->getEntry(2)->name());
  ASSERT_EQ("folder1", dir->getEntry(3)->name());
  ASSERT_EQ("lnd1", dir->getEntry(4)->name());
  ASSERT_EQ("lnf1", dir->getEntry(5)->name());
  ASSERT_EQ("lnlnf1", dir->getEntry(6)->name());
}

TEST_F(FileSystem, directoryIterator) {
  DirectoryBuilder db;
  db.buildDirectory("NewDir");
  Directory *dir = db.getDirectory();

  Iterator<Node *> *it = dir->createIterator();
  it->first();
  ASSERT_EQ(".", it->currentItem()->name());
  it->next();
  ASSERT_EQ("..", it->currentItem()->name());
  it->next();
  ASSERT_EQ("dir.cpp", it->currentItem()->name());
  it->next();
  ASSERT_EQ("folder1", it->currentItem()->name());
  it->next();
  ASSERT_EQ("lnd1", it->currentItem()->name());
  it->next();
  ASSERT_EQ("lnf1", it->currentItem()->name());
  it->next();
  ASSERT_EQ("lnlnf1", it->currentItem()->name());
  it->next();
  ASSERT_TRUE(it->isDone());
}

TEST_F(FileSystem, nullIteratorOnFile) {
  Node *node = new File("utFS.cpp");
  Iterator<Node *> *it = node->createIterator();
  ASSERT_TRUE(it->isDone());
  it->first();
  ASSERT_EQ(nullptr, it->currentItem());
}

TEST_F(FileSystem, directoryBuilder){
  DirectoryBuilder db;
  db.buildDirectory("NewDir");
  Directory *dir = db.getDirectory();
  ASSERT_EQ(".", dir->getEntry(0)->name());
  ASSERT_EQ("..", dir->getEntry(1)->name());
  ASSERT_EQ("dir.cpp", dir->getEntry(2)->name());
  ASSERT_EQ("folder1", dir->getEntry(3)->name());
  ASSERT_EQ("lnd1", dir->getEntry(4)->name());
  ASSERT_EQ("lnf1", dir->getEntry(5)->name());
  ASSERT_EQ("lnlnf1", dir->getEntry(6)->name());
}

TEST_F(FileSystem, fullDirectoryBuilder) {
  DirectoryBuilder db;
  db.buildDirectory("NewDir");
  Directory *dir = db.getDirectory();

  Iterator<Node *> *it = dir->createIterator();
  it->first();
  ASSERT_EQ(".", it->currentItem()->name());
  it->next();
  ASSERT_EQ("..", it->currentItem()->name());
  it->next();
  ASSERT_EQ("dir.cpp", it->currentItem()->name());
  it->next();
  ASSERT_EQ("folder1", it->currentItem()->name());

  Iterator<Node *> *it2 = it->currentItem()->createIterator();
  it2->first();
  ASSERT_EQ(".", it2->currentItem()->name());
  it2->next();
  ASSERT_EQ("..", it2->currentItem()->name());
  it2->next();
  ASSERT_EQ("file2", it2->currentItem()->name());
  it2->next();
  ASSERT_EQ("lnf2", it2->currentItem()->name());

  it->next();
  ASSERT_EQ("lnd1", it->currentItem()->name());
  it->next();
  ASSERT_EQ("lnf1", it->currentItem()->name());
  it->next();
  ASSERT_EQ("lnlnf1", it->currentItem()->name());
  it->next();
  ASSERT_TRUE(it->isDone());
}

TEST_F(FileSystem, levelIterator) {
  DirectoryBuilder db;
  db.buildDirectory("NewDir");
  Directory *dir = db.getDirectory();

  Iterator<Node *> *it = new LevelIterator<Node *>(dir);
  it->first();
  ASSERT_EQ(".", it->currentItem()->name());
  it->next();
  ASSERT_EQ("..", it->currentItem()->name());
  it->next();
  ASSERT_EQ("dir.cpp", it->currentItem()->name());
  it->next();
  ASSERT_EQ("folder1", it->currentItem()->name());

  it->next();
  ASSERT_EQ("lnd1", it->currentItem()->name());
  it->next();
  ASSERT_EQ("lnf1", it->currentItem()->name());
  it->next();
  ASSERT_EQ("lnlnf1", it->currentItem()->name());
  it->next();

  ASSERT_EQ(".", it->currentItem()->name());
  it->next();
  ASSERT_EQ("..", it->currentItem()->name());
  it->next();
  ASSERT_EQ("file2", it->currentItem()->name());
  it->next();
  ASSERT_EQ("lnf2", it->currentItem()->name());
  it->next();

  ASSERT_TRUE(it->isDone());
}

/*
TEST_F(FileSystem, Link_pathToSource) {
  Link *link = new Link("NewDir/lnf1");
  ASSERT_EQ("NewDir/lnf1",link->name());
  ASSERT_EQ("dir.cpp", link->pathToSource("./")[0]);
  Link *link2 = new Link("NewDir/folder1/lnf2");
  ASSERT_EQ("..", link2->pathToSource("./")[0]);
  ASSERT_EQ("dir.cpp", link2->pathToSource("./")[1]);
}
*/
#include <iostream>
using namespace std;

TEST_F(FileSystem, DirectoryBuilder_makeOneLinkToSource) {
  DirectoryBuilder db;
  db.buildDirectory("NewDir");
  Directory * dir = db.getDirectory();

  Iterator<Node *> * it = new LevelIterator<Node *>(dir);
  it->first();
  ASSERT_EQ(".", it->currentItem()->name()); it->next();
  ASSERT_EQ("..", it->currentItem()->name()); it->next();
  ASSERT_EQ("dir.cpp", it->currentItem()->name());
  ASSERT_EQ(258, it->currentItem()->getCharCount()); it->next();
  ASSERT_EQ("folder1", it->currentItem()->name()); it->next();
  ASSERT_EQ("lnd1", it->currentItem()->name());
  db.makeOneLinkToSource(dynamic_cast<Link *>(it->currentItem()));
  it->next();
  ASSERT_EQ("lnf1", it->currentItem()->name());
  db.makeOneLinkToSource(dynamic_cast<Link *>(it->currentItem()));
  ASSERT_EQ(258, it->currentItem()->getCharCount());
  it->next();
  ASSERT_EQ("lnlnf1", it->currentItem()->name());
  db.makeOneLinkToSource(dynamic_cast<Link *>(it->currentItem()));
  ASSERT_EQ(258, it->currentItem()->getCharCount());
  it->next();
  ASSERT_EQ(".", it->currentItem()->name()); it->next();
  ASSERT_EQ("..", it->currentItem()->name()); it->next();
  ASSERT_EQ("file2", it->currentItem()->name()); it->next();
  ASSERT_EQ("lnf2", it->currentItem()->name());
  db.makeOneLinkToSource(dynamic_cast<Link *>(it->currentItem()));
  ASSERT_EQ(258, it->currentItem()->getCharCount());
  it->next();
  ASSERT_TRUE(it->isDone());
}


TEST_F(FileSystem, LinkConnector) {
  DirectoryBuilder db;
  db.buildDirectory("NewDir");
  Directory * dir = db.getDirectory();
  ASSERT_TRUE(db.connectLinksToSources());
  Iterator<Node *> * it = new LevelIterator<Node *>(dir);
  it->first();
  ASSERT_EQ(".", it->currentItem()->name()); it->next();
  ASSERT_EQ("..", it->currentItem()->name()); it->next();
  ASSERT_EQ("dir.cpp", it->currentItem()->name());
  ASSERT_EQ(258, it->currentItem()->getCharCount()); it->next();
  ASSERT_EQ("folder1", it->currentItem()->name()); it->next();
  ASSERT_EQ("lnd1", it->currentItem()->name());
  it->next();
  ASSERT_EQ("lnf1", it->currentItem()->name());
  ASSERT_EQ(258, it->currentItem()->getCharCount());
  it->next();
  ASSERT_EQ("lnlnf1", it->currentItem()->name());
  ASSERT_EQ(258, it->currentItem()->getCharCount());
  it->next();
  ASSERT_EQ(".", it->currentItem()->name()); it->next();
  ASSERT_EQ("..", it->currentItem()->name()); it->next();
  ASSERT_EQ("file2", it->currentItem()->name()); it->next();
  ASSERT_EQ("lnf2", it->currentItem()->name());
  ASSERT_EQ(258, it->currentItem()->getCharCount());
  it->next();
  ASSERT_TRUE(it->isDone());
}

#endif
