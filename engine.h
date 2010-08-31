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

#ifndef ENGINE_H
#define ENGINE_H

#include <stdexcept>
#include <boost/noncopyable.hpp>

#include "fastcgi-app.h"
#include "request.h"

namespace fastcgi {
	class engine : private boost::noncopyable {
	private:
		request::type request;

	public:
		void run(app::ptr);
  
		class unable_to_init : public std::exception { 
			virtual const char* what() const throw(); 
		};

 		static void init() throw(unable_to_init);
 		static void shutdown(int = 0);
		static bool is_daemon();
	};
}

#endif // ENGINE_H
