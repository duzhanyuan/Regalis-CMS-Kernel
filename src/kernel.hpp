#ifndef _KERNEL_HPP
#define _KERNEL_HPP
#include <string>
#include "exceptions.hpp"
#include "modules/interface.hpp"
#include "utils/registry.hpp"
using std::string;
using namespace scms;

typedef Registry<KernelModule*> ModulesRegistry;

namespace scms {
	class Kernel {
		private:
			ModulesRegistry* modules;
			string contentType;
			vector<string> headers;

			Kernel();
			Kernel(const Kernel&);
			void printHeaders() const;
			bool loadModule(const string& name);
		public:
			ModulesRegistry* getModulesRegistry();
			static Kernel& get();
			static void terminator();
			void pingModule(const string& name) const;
			void ping() const;
			void addHeader(const string& name, const string& value);
			void setContentType(const string& ct);
			void flush() const;
			KernelModule* getModule(const string& name);
			KernelModule* operator[](const string& name);
	};
}


#endif
