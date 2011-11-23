/* 
 *
 * Copyright (c) by Patryk Jaworski
 * Contact:
 *  -> E-mail: Patryk Jaworski <skorpion9312@gmail.com>
 *  -> XMPP/Jabber: Patryk Jaworski <skorpion9312@jabber.org>
 *
*/

#ifndef _INSTALLER_HPP
#define _INSTALLER_HPP
#include "../modules/interface.hpp"
#include "../sformatter.hpp"
#include "../logger_interface.hpp"

namespace rcms {
	class Installable;
	class Installer;

	class Installable {
		protected:
			virtual bool preInstall() = 0;
			virtual bool postInstall() = 0;
			virtual bool preRemove() = 0;
			virtual bool postRemove() = 0;
			friend class Installer;
	};

	class Installer {
		public:
			Installer(Logger* logger, Installable* installable, const string& name);
			bool install();
		private:
			Logger* log;
			Installable* installable;
			string name;
			void preInstall() throw(string);
			void postInstall() throw(string);
			void preRemove() throw(string);
	};
}

#endif
