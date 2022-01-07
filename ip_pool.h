#pragma once

#include <cassert>
#include <cstdlib>
#include <iostream>
#include <string>
#include <vector>
#include <algorithm>

#include "ip_addr.h"

vector<vector<string>>* read_ip_pool();
string print_ip_pool(vector<vector<string>>* ip_pool);

class ip_pool 
{
public:
	ip_pool() {};
	~ip_pool() {};
	
	static vector<std::string> split(const string& str, char d);

	void push_back(ip_addr ip);
	void push_back(vector<ip_addr> ip_pool);
	void reverse_sort();
	vector<ip_addr> filter(const string& mask);
	vector<ip_addr> filter_any(const string& mask);

	string to_string();
private:
	vector<ip_addr> ip_addr_pool;

	static bool comp(ip_addr a, ip_addr b);
};