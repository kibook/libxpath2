#!/bin/sh

set -e

cd "$(dirname "$0")"

make -C .. all

cc -g -Wall -Werror -pedantic-errors `pkg-config --cflags libxml-2.0` -I . -o tests tests.c `pkg-config --libs libxml-2.0` -L .. -l xpath2

LD_LIBRARY_PATH=$LD_LIBRARY_PATH:.. ./tests

rm tests
