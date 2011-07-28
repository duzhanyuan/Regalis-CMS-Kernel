#include "time.hpp"
#include <cstdlib>
using namespace std;
using namespace scms;

string Time::format(time_t* time, const string& pattern) {
	int max_buffer_size = pattern.size() + 1024;
	tm* time_info = localtime(time); 
	char* time_buffer = new char[max_buffer_size];
	strftime(time_buffer, max_buffer_size, pattern.c_str(), time_info);
	string out(time_buffer);
	free(time_buffer);
	return out;
}

string Time::format(time_t* time) {
	return Time::format(time, "%d-%m-%Y %H:%M:%S");
}

string Time::format() {
	time_t t = time(NULL);
	return Time::format(&t);
}
