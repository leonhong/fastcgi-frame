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

class HelloWorld : public fastcgi::app {
public:
	fastcgi::app::status accept(std::istream & in, std::ostream & out, std::ostream & err, char ** envp) {
 		out << "Status: 200\r\n"
 				"Content-Type: text/plain\r\n"
				"\r\n";
		out << "Hello World Wide Web!" << std::endl;
		return 0;
	}
};

extern fastcgi::app::ptr fastcgi::instantiate(){
	return fastcgi::app::ptr(new HelloWorld());
}

//
