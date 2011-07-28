/* 
 *
 * Copyright (c) by Patryk Jaworski
 * Contact:
 *  -> E-mail: Patryk Jaworski <skorpion9312@gmail.com>
 *  -> XMPP/Jabber: Patryk Jaworski <skorpion9312@jabber.org>
 *
*/

#ifndef _INTERFACE_HPP
#define _INTERFACE_HPP
#include <string>
#include <map>
#include <vector>
#include <sstream>
#include "../logger_interface.hpp"
#include "../exceptions.hpp"
using std::string;
using std::map;
using std::vector;
using std::ostringstream;

namespace rcms {

	class KernelModule {
		protected:
			string version;
			string author;
			string description;
			string full_name;
			rcms::Logger* log;
			virtual bool preInstall();
			virtual bool postInstall();
			virtual bool preRemove();
			virtual bool postRemove();
			//friend class Installer;
		public:
			const string& getVersion() const;
			const string& getFullName() const;
			const string& getAuthor() const;
			const string& getDescription() const;
			void setLogger(rcms::Logger* logger);
			virtual bool init() = 0;
			virtual void ping();
			virtual ~KernelModule();
	};

	class KernelTemplateModule : public KernelModule {
		protected:
			ostringstream code;
			map<string, vector<string> > args;
		public:
			string getResult() const;
			void setArg(const string& name, const string& value);
			virtual void run() = 0;
			virtual ~KernelTemplateModule();
	};
}

typedef rcms::KernelModule* factory_t();

#endif
