
#pragma once
// IFileMgr.h

#include <string>

namespace FileManager
{
  struct IFileEventHandler
  {
    virtual void execute(const std::string& fileSpec) = 0;
  };

  struct IDirEventHandler
  {
    virtual void execute(const std::string& dirSpec) = 0;
  };

  struct IFileMgr
  {
    virtual ~IFileMgr() {}
    virtual void addPattern(const std::string& patt) = 0;
    virtual void search() = 0;
    virtual void find(const std::string& path) = 0;
    virtual void regForFiles(IFileEventHandler* pEventHandler) = 0;
    virtual void regForDirs(IDirEventHandler* pEventHandler) = 0;
    virtual void doFile(const std::string& filename) = 0;
    virtual void doDir(const std::string& dirname) = 0;
  };

  struct FileMgrFactory
  {
    static IFileMgr* create(const std::string& path);
  };
}