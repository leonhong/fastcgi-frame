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

#include "fastcgi-app.h"

#include <iostream>
#include <exception>

#include <boost/bind.hpp>
#include <boost/thread.hpp>

#include "engine.h"

int main( int argc, char * argv[] ) {
	try {
		fastcgi::engine::init();
		if (fastcgi::engine::is_daemon()) {
			boost::thread_group threads;
			const char * THREADS = getenv("THREADS");
			for ( size_t i = THREADS && *THREADS ? atoi(THREADS) : 8 ; i > 0 ; --i )
       			threads.create_thread(
				boost::bind(&fastcgi::engine::run, boost::shared_ptr<fastcgi::engine>(new fastcgi::engine()), fastcgi::instantiate()));
			threads.join_all();
		} else {
			return 0;//fastcgi::instantiate()->accept(std::cin, std::cout, std::cerr, environ);
		}
	} catch(const std::exception & e) {
		std::cerr << "exception: " << e.what() << std::endl;
		exit(EXIT_FAILURE);
	}

	return 0;
}

//
