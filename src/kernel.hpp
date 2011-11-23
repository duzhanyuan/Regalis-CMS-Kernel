/* 
 *
 * Copyright (c) by Patryk Jaworski
 * Contact:
 *  -> E-mail: Patryk Jaworski <skorpion9312@gmail.com>
 *  -> XMPP/Jabber: Patryk Jaworski <skorpion9312@jabber.org>
 *
*/

#ifndef _KERNEL_HPP
#define _KERNEL_HPP
#define _(String) gettext(String)

#include <string>
#include <fstream>
#include <mysql++.h>
#include "exceptions.hpp"
#include "sformatter.hpp"
#include "modules/interface.hpp"
#include "utils/registry.hpp"
#include "logger_interface.hpp"
using std::string;
using std::ofstream;
using namespace rcms;

typedef Registry<KernelModule*> ModulesRegistry;

namespace rcms {
	class Kernel {
		private:

			class KLogger : public Logger {
				private:
					KLogger();
					KLogger(const string& name);
					KLogger(const KLogger&);
					KLogger& operator=(const KLogger&);
					ofstream out;
				public:
					static Logger* get(const string& name);
					void msg(const string& msg);
					void msg(const string& msg, Logger::Type type);
					Logger& operator<<(const string& msg);
					void flush();
					virtual ~KLogger();
			};

			class MySQL {
				private:
					mysqlpp::Connection* connection;
					Logger* log;
					MySQL(const MySQL&);
					MySQL& operator=(const MySQL&);
				public:
					MySQL(Logger* logger) throw (KernelException);
					mysqlpp::Query* getQuery();
			};

			ModulesRegistry modules;
			string contentType;
			vector<string> headers;
			Logger* log;
			MySQL* mysql;
			Kernel();
			Kernel(const Kernel&);
			Kernel& operator=(const Kernel&);
			void printHeaders() const;
			void getModuleDependencies(const string& name, vector<string>& deps);
			void* loadSymbol(const string& path, const string& name);
			void loadModule(const string& name);
			void abort(const string& name, Exception* e);
			void checkInstallation() throw(KernelException);
			static void copyright();
			static void printBacktrace();
		public:
			static Kernel& get();
			static void terminator();
			mysqlpp::Query* getQuery();
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
