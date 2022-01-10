#pragma once

#include <string>
#include <vector>

using namespace std;

class ip_addr
{
public:
	ip_addr() {};
	~ip_addr() {};

	bool parse(string str_addr);
	bool match(const string& mask);

	friend bool operator== (const ip_addr& a, const ip_addr& b);
	friend bool operator!= (const ip_addr& a, const ip_addr& b) { return !(b == a); };

	friend bool operator< (const ip_addr& a, const ip_addr& b);
	friend bool operator> (const ip_addr& a, const ip_addr& b) { return b < a; }
	friend bool operator<=(const ip_addr& a, const ip_addr& b) { return !(a > b); }
	friend bool operator>=(const ip_addr& a, const ip_addr& b) { return !(a < b); }

	unsigned char octet0;
	unsigned char octet1;
	unsigned char octet2;
	unsigned char octet3;

	vector<string> str_octets;

	string str_addr;
};