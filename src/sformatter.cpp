#include "sformatter.hpp"
#include <sstream>
using namespace std;

string& operator%(string& str, const string& replace) {
	size_t pos;
	if((pos = str.find("%s")) == string::npos)
		return str;
	str = str.substr(0, pos) + replace + str.substr(pos + 2);
	return str;
}

string& operator%(string& str, const int* replace) {
	size_t pos;
	if((pos = str.find("%d")) == string::npos)
		return str;
	stringstream ss;
	ss << str.substr(0, pos) << *replace << str.substr(pos + 2);
	str = ss.str();
	return str;
}

string& operator%(string& str, const long long unsigned int* replace) {
	size_t pos;
	if((pos = str.find("%l")) == string::npos)
		return str;
	stringstream ss;
	ss << str.substr(0, pos) << *replace << str.substr(pos + 2);
	str = ss.str();
	return str;
}

string& operator%(string& str, long long unsigned int replace) {
	return operator%(str, &replace);
}

string& operator%(string& str, int replace) {
	return operator%(str, &replace);
}

string operator%(string str, const string& replace) {
	size_t pos;
	if((pos = str.find("%s")) == string::npos)
		return str;
	str = str.substr(0, pos) + replace + str.substr(pos + 2);
	return str;
}

string& operator%(string& str, const char* replace) {
	size_t pos;
	if((pos = str.find("%s")) == string::npos)
		return str;
	stringstream ss;
	ss << str.substr(0, pos) << replace << str.substr(pos + 2);
	str = ss.str();
	return str;
}
