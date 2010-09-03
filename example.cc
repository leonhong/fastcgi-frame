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

#include <ctemplate/template.h>

#include "fcgio.h"

static const size_t STDIN_MAX = 1000000;

static void tpl(std::ostream &out) {
	ctemplate::TemplateDictionary dict("example");
	dict.SetValue("NAME", "John Smith");
	int winnings = random() % 100000;
	dict.SetIntValue("VALUE", winnings);
	dict.SetFormattedValue("TAXED_VALUE","%.2f",winnings * 0.83);
	if (1) {
		dict.ShowSection("N_CA");
	}
	ctemplate::Template* tpl = ctemplate::Template::GetTemplate("example.tpl", ctemplate::DO_NOT_STRIP);
	std::string output;
 	tpl->Expand(&output, &dict);
	out << output;
}

static void penv(std::ostream &out, char **envp) {
	out << "<PRE>\n";
	for ( ; *envp; ++envp) {
		out << *envp << "\n";
	}
	out << "</PRE>\n";
}

static size_t get_content(std::istream &in, std::ostream &out, std::ostream &err, char **envp, char **content) {
	/*size_t len = 0;
	char * clenstr = FCGX_GetParam("CONTENT_LENGTH", envp);
	len = strtol(clenstr, &clenstr, 10);
	std::string concent;
	in >> concent;
	out << concent;*/
    
	char * clenstr = FCGX_GetParam("CONTENT_LENGTH", envp);
    size_t clen = STDIN_MAX;

    if (clenstr)
    {
        clen = strtol(clenstr, &clenstr, 10);
        if (*clenstr)
        {
            err << "can't parse \"CONTENT_LENGTH="
                 << FCGX_GetParam("CONTENT_LENGTH", envp)
                 << "\"\n";
            clen = STDIN_MAX;
        }

        // *always* put a cap on the amount of data that will be read
        if (clen > STDIN_MAX) clen = STDIN_MAX;

        *content = new char[clen];

        in.read(*content, clen);
        clen = in.gcount();
    }
    else
    {
        // *never* read stdin when CONTENT_LENGTH is missing or unparsable
        *content = 0;
        clen = 0;
    }

    // Chew up any remaining stdin - this shouldn't be necessary
    // but is because mod_fastcgi doesn't handle it correctly.

    // ignore() doesn't set the eof bit in some versions of glibc++
    // so use gcount() instead of eof()...
    do in.ignore(1024); while (in.gcount() == 1024);

    return clen;
}

class HelloWorld : public fastcgi::app {
public:
	fastcgi::app::status accept(std::istream &in, std::ostream &out, std::ostream &err, char **envp) {
 		out << "Status: 200\r\n"
 				"Content-Type: text/plain\r\n"
				"\r\n";
		/*out << "1Hello World Wide Web~!" << std::endl;
		out << "Hello World Wide Web~!" << std::endl;*/
		//out << "Content-type: text/html\r\n" "r\n";
		tpl(out);
		//penv(out, envp);
		
		char *content = NULL;
		size_t clen = get_content(in, out, err, envp, &content);
        if (clen == STDIN_MAX) out << " (STDIN_MAX)";
        out << " bytes</H4>\n";
        if (clen) out.write(content, clen);
        if (content) delete []content;
		
		/*char *query_string;
		query_string = FCGX_GetParam("QUERY_STRING", envp);
		if (query_string)
			out << query_string << std::endl;
		else
			out << "query_string is null" << std::endl;*/
		
		return 0;
	}
};

extern fastcgi::app::ptr fastcgi::instantiate(){
	return fastcgi::app::ptr(new HelloWorld());
}

//
