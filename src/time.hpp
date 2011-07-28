/* 
 *
 * Copyright (c) by Patryk Jaworski
 * Contact:
 *  -> E-mail: Patryk Jaworski <skorpion9312@gmail.com>
 *  -> XMPP/Jabber: Patryk Jaworski <skorpion9312@jabber.org>
 *
*/

#ifndef _TIME_HPP
#define _TIME_HPP
#include <ctime>
#include <string>
using namespace std;

namespace rcms {
	
	class Time {
		public:
			static string format();
			static string format(time_t* time);
			static string format(time_t* time, const string& pattern);
	};

}

#endif
