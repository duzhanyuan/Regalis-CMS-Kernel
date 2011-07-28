#ifndef _KERNEL_HPP
#define _KERNEL_HPP
#include <string>
#include <fstream>
#include "exceptions.hpp"
#include "sformatter.hpp"
#include "modules/interface.hpp"
#include "utils/registry.hpp"
using std::string;
using std::ofstream;
using namespace scms;

typedef Registry<KernelModule*> ModulesRegistry;

namespace scms {
	class Kernel {
		private:

			class Logger {
				private:
					Logger();
					Logger(const string& name);
					Logger(const Logger&);
					Logger& operator=(const Logger&);
					ofstream out;
				public:
					enum Type {
						OK,
						WARNING,
						ERROR
					};
					static Logger* get(const string& name);
					void msg(const string& msg);
					void msg(const string& msg, Type type);
					Logger& operator<<(const string& msg);
					void flush();
					virtual ~Logger();
			};

			class Logger;
			ModulesRegistry modules;
			string contentType;
			vector<string> headers;
			Kernel();
			Logger* log;
			Kernel(const Kernel&);
			void printHeaders() const;
			void loadModule(const string& name);
			void abort(const string& name, Exception& e);
			static void printBacktrace();
		public:
			static Kernel& get();
			static void terminator();
			void operate();
			void pingModule(const string& name);
			void ping() const;
			void addHeader(const string& name, const string& value);
			void setContentType(const string& ct);
			void flush() const;
			KernelModule* getModule(const string& name);
			KernelModule* operator[](const string& name);
	};
}


#endif
