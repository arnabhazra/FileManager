///////////////////////////////////////////////////////////////////////
// FileMgr.cpp - Finds files and directories on specified path       //
// Ver 1.0                                                           //
// Jim Fawcett, CSE687 - Object Oriented Design, Fall 2018           //
///////////////////////////////////////////////////////////////////////

#ifdef TEST_FILEMGR

#include "FileMgr.h"
#include <iostream>

using namespace FileManager;

struct FileHandler : IFileEventHandler
{
  void execute(const std::string& fileSpec)
  {
    std::cout << "\n  --   " << fileSpec;
  }
};

struct DirHandler : IDirEventHandler
{
  void execute(const std::string& dirSpec)
  {
    std::cout << "\n  ++ " << dirSpec;
  }
};

int main()
{
  std::cout << "\n  Testing FileMgr - uses event model";
  std::cout << "\n ====================================";

  std::string path = FileSystem::Path::getFullFileSpec("..");
  IFileMgr* pFmgr = FileMgrFactory::create(path);

  FileHandler fh;
  DirHandler dh;

  pFmgr->regForFiles(&fh);
  pFmgr->regForDirs(&dh);

  pFmgr->addPattern("*.h");
  pFmgr->addPattern("*.cpp");
  pFmgr->addPattern("*.log");

  pFmgr->search();

  std::cout << "\n\n";
  return 0;
}
#endif
