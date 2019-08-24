#include <dirent.h>

#include "FileSystem.h"

namespace cpp {

std::vector<std::string> getFileNames(std::string path) {

  DIR *dir;
  std::vector<std::string> filenames_;

  if ((dir = opendir(path.c_str())) != NULL) {
    struct dirent *ent;
    if ('/' != path.back()) {
      path.push_back('/');
    }
    while ((ent = readdir(dir)) != NULL) {
      if (DT_REG == ent->d_type) {
        filenames_.push_back(path + ent->d_name);
      }
    }

    closedir (dir);
  } 
  
  return  filenames_;
}
}
