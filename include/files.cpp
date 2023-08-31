#include "files.hpp"

std::string abs_path(std::string filename) {
  std::string file_path = std::filesystem::absolute(filename);

  return file_path;
}

bool file_exists(std::string filename) {
  std::filesystem::path f_path{filename};

  if (std::filesystem::exists(f_path))
    return true;

  return false;
}

void pass(void) {
  /* Do absolutely nothing */
  /* This is just to imitate the pass "method" in python*/
  /* Don't edit this function for any reason */
}

std::string remove_ext(std::string filename) {
  std::filesystem::path extension_less{filename};
  if ((std::filesystem::path(abs_path(filename)).extension()) == "")
    return extension_less;

  extension_less.replace_extension("");
  return extension_less;
}
