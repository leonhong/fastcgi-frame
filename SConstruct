#########################
# Copyright 2008 Derrick Pallas. All rights reserved.
#
# This file is part of fastcgi-app.
#
# fastcgi-app is free software: you can redistribute it and/or modify
# it under the terms of the GNU Lesser General Public License as published by
# the Free Software Foundation, either version 3 of the License, or
# (at your option) any later version.
#
# fastcgi-app is distributed in the hope that it will be useful,
# but WITHOUT ANY WARRANTY; without even the implied warranty of
# MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
# GNU Lesser General Public License for more details.
#
# You should have received a copy of the GNU Lesser General Public License
# along with fastcgi-app.  If not, see <http://www.gnu.org/licenses/>.
#

from os.path import join

env  = Environment( CXXFLAGS='-pipe -Os -Wall -DFORTIFY=2',
                    LINKFLAGS='-L.' )
lib  = 'fastcgi-app'
srcs = map( lambda file : file + '.cc', Split('''
    fastcgi-app
    request
    engine
''') )

libs = ['fcgi','fcgi++','boost_thread-mt']

lib = env.SharedLibrary( 'fastcgi-app', srcs, LIBS=libs )


prefix = "/usr"

env.Alias( target='install',
           source=env.Install( join( prefix, "lib" ), lib ) )
env.Alias( target='install',
           source=env.Install( join( prefix, "include" ), "fastcgi-app.h" ) )

env.Program( 'example', [ 'example.cc' ], LIBS=libs+lib )

#
