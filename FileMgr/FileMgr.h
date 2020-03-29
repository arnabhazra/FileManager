#ifndef FILEMGR_H
#define FILEMGR_H
///////////////////////////////////////////////////////////////////////
// FileMgr.h - Finds files and directories on specified path         //
// Ver 1.0                                                           //
// Jim Fawcett, CSE687 - Object Oriented Design, Fall 2018           //
///////////////////////////////////////////////////////////////////////
/*
*  Package Operations:
*  -------------------
*  Recursively finds all the directories and files matching a set of patterns
*  on some specified path.  It uses registered event handling to allow
*  applications to specify what happens when a file or dir are encountered.
*  Supports one or more subscribers who are notified by file and dir events.
*
*  Required files:
*  ---------------
*  FileMgr.h, FileMgr.cpp (cpp file just used for demo)
*  FileSystem.h, FileSystem.cpp
*  The application file that uses DerivedFileMgr must define event handlers
*  that implement the IFileMgr interface.
*
*  Maintenance History:
*  --------------------
*  Ver 1.0 : 09 Aug 2018
*  - first release
*/

#include "IFileMgr.h"
#include "FileSystem.h"
#include <iostream>

namespace FileManager
{
  class FileMgr : public IFileMgr
  {
  public:
    using patterns = std::vector<std::string>;
    using fileSubscribers = std::vector<IFileEventHandler*>;
    using dirSubscribers = std::vector<IDirEventHandler*>;

    FileMgr(const std::string& path) : path_(path)
    {
      patterns_.push_back("*.*");
    }

    void addPattern(const std::string& patt)
    {
      if (patterns_.size() == 1 && patterns_[0] == "*.*")
        patterns_.pop_back();
      patterns_.push_back(patt);
    }

    void search()
    {
      find(path_);
    }

    // Recursively finds all the dirs and files on the specified path,
    // executing an event handler when finding a file or entering a directory.

    virtual void find(const std::string& path)
    {
      std::string fpath = FileSystem::Path::getFullFileSpec(path);
      for (auto pEvtHandler : dirSubscribers_)
      {
        pEvtHandler->execute(fpath);
      }
      for (auto patt : patterns_)
      {
        std::vector<std::string> files = FileSystem::Directory::getFiles(fpath, patt);
        for (auto f : files)
        {
          for (auto pEvtHandler : fileSubscribers_)
          {
            pEvtHandler->execute(f);
          }
        }
      }
      std::vector<std::string> dirs = FileSystem::Directory::getDirectories(fpath);
      for (auto d : dirs)
      {
        if (d == "." || d == "..")
          continue;
        std::string dpath = fpath + "\\" + d;
        find(dpath);
      }
    }

    void regForFiles(IFileEventHandler* pHandler)
    {
      fileSubscribers_.push_back(pHandler);
    }

    void regForDirs(IDirEventHandler* pHandler)
    {
      dirSubscribers_.push_back(pHandler);
    }

    void doFile(const std::string& filename)
    {
      std::cout << "\n  --   " << filename;
    }

    void doDir(const std::string& dirname)
    {
      std::cout << "\n  ++ " << dirname;
    }

  protected:
    std::string path_;
    patterns patterns_;
  private:
    fileSubscribers fileSubscribers_;
    dirSubscribers dirSubscribers_;
  };

  inline IFileMgr* FileMgrFactory::create(const std::string& path)
  {
    return new FileMgr(path);
  }
}
#endif
