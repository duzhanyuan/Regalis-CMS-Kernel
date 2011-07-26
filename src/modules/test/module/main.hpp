#ifndef _MODULE_TEST_HPP
#define _MODULE_TEST_HPP

#include "../../interface.hpp"
using namespace scms;

extern "C" {

namespace scms {
	class ModuleTest : public KernelModule {
		public:
			string getResult() const;
			void setArg(const string&, const string&);
			void ping();
	};
}

KernelModule* factory();

}
#endif
