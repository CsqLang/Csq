#ifndef _FILES_HPP_
#define _FILES_HPP_

#include <filesystem>
#include <iostream>

std::string abs_path(std::string filename);
bool file_exists(std::string filename);
void pass(void);
std::string remove_ext(std::string filename);

#endif
