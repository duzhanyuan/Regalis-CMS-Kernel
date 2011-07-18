#ifndef _KERNEL_HPP
#define _KERNEL_HPP
#include <string>
#include "modules/interface.hpp"
#include "utils/registry.hpp"
using std::string;
using namespace SCMS;

typedef Registry<KernelModule*> ModulesRegistry;

namespace SCMS {
	class Kernel {
		private:
			ModulesRegistry* modules;
			vector<string> headers;
			Kernel();
			Kernel(const Kernel&);
			void printHeaders();
		public:
			ModulesRegistry* getModulesRegistry();
			void pingModule(const string& name);
			static Kernel& get();
			void ping();
			static void terminator();
			void addHeader(const string& name, const string& value);
	};
}


#endif
