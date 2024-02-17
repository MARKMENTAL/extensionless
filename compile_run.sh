#!/bin/bash

#old one that used microhttpd
#gcc -o web_server web_server.c -lmicrohttpd
gcc -o web_server web_server.c && ./web_server
