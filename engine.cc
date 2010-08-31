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

#include "engine.h"

#include <csignal>
#include <iostream>
#include <boost/thread.hpp>

#include <fcgiapp.h>
#include <fcgio.h>

#include "c-ptr/c_ptr.h"

using namespace fastcgi;

void engine::run(app::ptr instance) {
	ptr::c<request::type,request::free> guard(&request);

	for (request::init(&request); 
		request::accept(&request);
		request::finish(&request)) {
		
		fcgi_istream  in(request.in);
		fcgi_ostream out(request.out);
		fcgi_ostream err(request.err);
		request::status(&request, instance->accept(in, out, err, request.envp));
	}
}

const char* engine::unable_to_init::what() const throw() {
	return "FCGX_Init(...) FAILED";
}

void engine::init( ) throw (unable_to_init) {
	if(FCGX_Init())
		throw engine::unable_to_init();
	signal(SIGHUP,engine::shutdown);
}

void engine::shutdown(int){
	FCGX_ShutdownPending();
}

bool engine::is_daemon() { 
	return !FCGX_IsCGI();
}

//
