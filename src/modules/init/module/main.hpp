#ifndef _MODULE_INIT_HPP
#define _MODULE_INIT_HPP
#include "../../module.hpp"

namespace rcms {
	class InitModule : public KernelModule {
		public:
			bool init() throw(ModuleException);
	};
}

#endif
