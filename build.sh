# !/bin/sh
g++ fastcgi-app.cc engine.cc request.cc example.cc -L/home/hongliang/usr/lib -lfcgi++ -I/home/hongliang/usr/include/ -Wall -I. -I./c-ptr/ -I/home/hongliang/usr/boost-1.43.0/include/ -L /home/hongliang/usr/boost-1.43.0/lib/ -lboost_thread -o app
