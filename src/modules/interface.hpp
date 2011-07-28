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
			virtual bool preInstall();
			virtual bool postInstall();
			virtual bool preRemove();
			virtual bool postRemove();
		public:
			const string& getVersion() const;
			const string& getFullName() const;
			const string& getAuthor() const;
			const string& getDescription() const;
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
