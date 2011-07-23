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
			string contentType;
			vector<string> headers;

			Kernel();
			Kernel(const Kernel&);
			void printHeaders() const;
		public:
			ModulesRegistry* getModulesRegistry();
			static Kernel& get();
			static void terminator();
			void pingModule(const string& name) const;
			void ping() const;
			void addHeader(const string& name, const string& value);
			void setContentType(const string& ct);
			void flush() const;
	};
}


#endif
