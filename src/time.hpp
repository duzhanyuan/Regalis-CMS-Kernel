#ifndef _TIME_HPP
#define _TIME_HPP
#include <ctime>
#include <string>
using namespace std;

namespace scms {
	
	class Time {
		public:
			static string format();
			static string format(time_t* time);
			static string format(time_t* time, const string& pattern);
	};

}

#endif
