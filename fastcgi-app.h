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

#ifndef FASTCGI_APP_H
#define FASTCGI_APP_H

#include <iostream>
#include <boost/shared_ptr.hpp>

namespace fastcgi {
	class app {
	public:
		typedef int status;
		typedef boost::shared_ptr<app> ptr;

		virtual ~app( ) { };
		
		virtual status accept(std::istream & in, std::ostream & out, std::ostream & err, char ** envp)=0;
	};

	extern app::ptr instantiate( );
}

#endif // FASTCGI_APP_H
