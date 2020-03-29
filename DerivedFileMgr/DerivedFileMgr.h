#pragma once
///////////////////////////////////////////////////////////////////////
// DerivedFileMgr.h - Finds files and directories on specified path  //
// Ver 1.0                                                           //
// Jim Fawcett, CSE687 - Object Oriented Design, Fall 2018           //
///////////////////////////////////////////////////////////////////////
/*
*  Package Operations:
*  -------------------
*  Recursively finds all the directories and files matching a set of patterns
*  on some specified path.  It has one template class: DerivedFileMgr<App> 
*  that overrides virtual methods in its base class FileMgr.
*  Supports only a single recipient of file and dir notifications.
*
*  Required files:
*  ---------------
*  DerivedFileMgr.h, DerivedFileMgr.cpp (cpp file just used for demo)
*  FileMgr.h
*  FileSystem.h, FileSystem.cpp
*  The application file that uses DerivedFileMgr must define an App class
*  with static doFile and doDir methods. 
*
*  Maintenance History:
*  --------------------
*  Ver 1.0 : 09 Aug 2018
*  - first release
*/

#include "../FileMgr/FileMgr.h"

namespace FileManager
{
  ///////////////////////////////////////////////////////////////////
  // DerivedFileMgr<App> is parameterized to allow a using 
  // application to specify the doFile and doDir methods.

  template<typename App>
  class DerivedFileMgr : public FileMgr
  {
  private:
    App app_;

  public:
    DerivedFileMgr(const std::string& path) : FileMgr(path) {}

    virtual void doFile(const std::string& filename)
    {
      // This virtual function is here so the framework can
      // decide to do some pre or post processing.

      app_.doFile(filename);
    }

    virtual void doDir(const std::string& dirname)
    {
      // This virtual function is here so the framework can
      // decide to do some pre or post processing.

      app_.doDir(dirname);
    }

    // Recursively finds all the dirs and files on the specified path,
    // calling doFile and doDir when finding a file or entering a directory.

    virtual void find(const std::string& path)
    {
      std::string fpath = FileSystem::Path::getFullFileSpec(path);
      doDir(fpath);

      for (auto patt : patterns_)
      {
        std::vector<std::string> files = FileSystem::Directory::getFiles(fpath, patt);
        for (auto f : files)
        {
          doFile(f);
        }
      }
      std::vector<std::string> dirs = FileSystem::Directory::getDirectories(fpath);
      for (auto d : dirs)
      {
        if (d == "." || d == "..")
          continue;
        std::string dpath = fpath + "\\" + d;
        find(dpath);  // here's the recursion
      }
    }
  };
}