#ifndef _GETTEXT_HPP
#define _GETTEXT_HPP
#include <string>
using std::string;

namespace scms {
	
	void initGettext(const string& language);
	void bindDomain(const string& name, const string& file);

}

#endif
