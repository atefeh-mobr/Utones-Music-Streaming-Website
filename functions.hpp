#ifndef FUNCTIONS_H
#define FUNCTIONS_H

#include <iostream>
#include <vector>
#include <string>
#include <fstream>
#include "application.hpp"

std::vector<std::vector<std::string>> readCsv(char* file);
std::vector<std::string> split(const std::string line, char delimiter);
std::vector<std::vector<std::string>> getFileInformation(char* fileName);
void run_command(std::string command, Application *application);
std::vector<std::string> splitByEnter(std::string sentences);

#endif
