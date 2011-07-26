#ifndef _INTERFACE_HPP
#define _INTERFACE_HPP
#include <string>
#include <map>
#include <vector>
using std::string;
using std::map;
using std::vector;

namespace scms {
	class KernelModule {
		protected:
			string code;
			map<string, vector<string> > args;
		public:
			virtual string getResult() const;
			virtual void ping();
			void setArg(const string& name, const string& value);

	};
}

#endif
