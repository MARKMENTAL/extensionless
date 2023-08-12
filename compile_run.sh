#!/bin/bash

gcc -o web_server web_server.c -lmicrohttpd
./web_server