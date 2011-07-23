#ifndef _REGISTRY_HPP
#define _REGISTRY_HPP
#include <map>
#include <string>

using std::map;
using std::string;

namespace SCMS {
	template<typename T>
	class Registry {
		public:
			void add(const string& name, T element) {
				registry[name] = element;
			}
			T get(const string& name) {
				return registry[name];
			}
			virtual ~Registry() {}
		private:
			map<string, T> registry;
	};
}

#endif
