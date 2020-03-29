/////////////////////////////////////////////////////////////////////////
// DerivedFileMgr.cpp - Finds files and directories on specified path  //
// Ver 1.0                                                             //
// Jim Fawcett, CSE687 - Object Oriented Design, Fall 2018             //
/////////////////////////////////////////////////////////////////////////

#ifdef TEST_DERIVEDFILEMGR

#include "DerivedFileMgr.h"
#include <iostream>

using namespace::FileManager;

// Application simply provides application specific
// file and directory handling

struct Application
{
  void doFile(const std::string& filename)
  {
    std::cout << "\n  --   " << filename;
  }
  void doDir(const std::string& dirname)
  {
    std::cout << "\n  -- " << dirname;
  }
};

int main()
{
  std::cout << "\n  Testing Derived FileMgr - uses virtual model";
  std::cout << "\n ==============================================";

  DerivedFileMgr<Application> dfm("..");
  dfm.addPattern("*.h");
  dfm.addPattern("*.cpp");
  dfm.addPattern("*.log");
  dfm.search();
  std::cout << "\n\n";
  return 0;
}

#endif
