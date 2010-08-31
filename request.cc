/******************************************************
// Copyright 2008 Derrick Pallas. All rights reserved.
//
// This file is part of fastcgi-app.
//
// fastcgi-app is free software: you can redistribute it and/or modify
// it under the terms of the GNU Lesser General Public License as published by
// the Free Software Foundation, either version 3 of the License, or
// (at your option) any later version.
//
// fastcgi-app is distributed in the hope that it will be useful,
// but WITHOUT ANY WARRANTY; without even the implied warranty of
// MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
// GNU Lesser General Public License for more details.
//
// You should have received a copy of the GNU Lesser General Public License
// along with fastcgi-app.  If not, see <http://www.gnu.org/licenses/>.
*/

#include "request.h"

#include <boost/thread.hpp>

using namespace fastcgi;

void request::init(type *_) { 
	::FCGX_InitRequest(_, 0, 0);
}

bool request::accept(type *_) {
#ifdef USE_LOCKING
	static boost::mutex mutex;
	boost::mutex::scoped_lock lock(mutex);
#endif // USE_LOCKING
	return 0 == ::FCGX_Accept_r(_);
}

void request::status(type *_, int status) { 
	::FCGX_SetExitStatus(status, _->out);
}

void request::finish(type *_) { 
	::FCGX_Finish_r(_);
}

void request::free(type *_) { 
	::FCGX_Free(_, true);
}

//
