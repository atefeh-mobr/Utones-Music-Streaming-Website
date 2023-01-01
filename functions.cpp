#include <iostream>
#include <vector>
#include <string>
#include <sstream>
#include <fstream>
#include <algorithm>
#include "functions.hpp"
#include "application.hpp"
#include "bad_request_error.hpp"

const char CSV_DELIMITER = ',';

const std::string ID = "id";
const std::string LINK = "link";
const std::string TITLE = "title";
const std::string ARTIST = "artist";
const std::string RELEASE_YEAR = "release_year";

const std::string GET = "GET";
const std::string POST = "POST";
const std::string DELETE = "DELETE";

const int GET_SIZE = 3;
const int POST_SIZE = 4;
const int DELETE_SIZE = 6;

std::vector<std::string> split(const std::string line, char delimiter) {
    std::stringstream stream(line);
    std::vector<std::string> out_list;
    std::string block;
    while(getline(stream, block, delimiter))
        out_list.push_back(block);
    return out_list;
}

std::vector<std::vector<std::string>> readCsv(char* file) {
    std::string line;
    std::fstream fin;
    fin.open(file, std::ios::in);
    std::vector<std::vector<std::string>> table;
    while(getline(fin, line))
        table.push_back(split(line, CSV_DELIMITER));
    return table;
}

std::vector<std::vector<std::string>> getFileInformation(char* fileName) {
	std::vector<std::vector<std::string>> information = readCsv(fileName);
	return information;
}

void run_command(std::string command, Application *application) {
	BadRequestError bad_request;
	if(command.substr(0, POST_SIZE) == POST)
		application->doPostOrders(command.substr(POST_SIZE + 1));
	else if(command.substr(0, GET_SIZE) == GET)
		application->doGetOrders(command.substr(GET_SIZE + 1));
	else if(command.substr(0, DELETE_SIZE) == DELETE)
		application->doDeleteOrders(command.substr(DELETE_SIZE + 1));
	else 
		throw bad_request;
}

std::vector<std::string> splitByEnter(std::string sentences) {
    std::vector<std::string> final;
    std::stringstream ss(sentences);
    std::string to;
    while(std::getline(ss, to, '\n'))
        final.push_back(to);
    return final;
}
