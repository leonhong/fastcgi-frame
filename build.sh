# !/bin/sh
#cgi-fcgi -start -connect /tmp/hello.sock ./app 

#nignx
#server {
#	listen       8803;
#	location / {
#		root   html;
#		#index  hello;
#		#fastcgi_pass 192.168.6.7:9000;
#		#fastcgi_index  example.fcgi;
#		fastcgi_index  index.php;
#		fastcgi_pass    unix:/tmp/hello.sock;
#		include         /home/hongliang/usr/nginx/conf/fastcgi_params;
#		}
#}

#location ~ \.cgi$ {
#	root   html;
#	fastcgi_pass    unix:/tmp/hello.sock;
#	fastcgi_index  app.cgi;
#	fastcgi_param  SCRIPT_FILENAME  /home/hongliang/usr/nginx/html$fastcgi_script_name;
#	include         /home/hongliang/usr/nginx/conf/fastcgi_params;
#}

g++ fastcgi-app.cc engine.cc request.cc example.cc -L/home/hongliang/usr/lib -lfcgi++ -L/home/hongliang/usr/lib -lctemplate -pthread  -I/home/hongliang/usr/include/ -Wall -I. -I./c-ptr/ -I/home/hongliang/usr/boost-1.43.0/include/ -L /home/hongliang/usr/boost-1.43.0/lib/ -lboost_thread -o app.cgi
