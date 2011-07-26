#ifndef _EXCEPTIONS_HPP
#define _EXCEPTIONS_HPP
#include <string>
using std::string;

namespace scms {
	class Exception {
		protected:
			char* message;
			int num;
		public:
			Exception(const char* msg, int n) throw();
			Exception(const string& msg, int n) throw();
			Exception(const char* msg) throw();
			Exception(const string& msg) throw();
			const int number() const throw();
			const char* what() const throw();
			virtual ~Exception();
	};

	class KernelException : public Exception {
		public:
			KernelException(const char* msg) throw();
			KernelException(const string& msg) throw();
	};

	class ModuleException : public Exception {
		public:
			ModuleException(const char* msg) throw();
			ModuleException(const string& msg) throw();
	};

}

#endif
