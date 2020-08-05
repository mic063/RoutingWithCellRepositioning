#!/bin/bash

docker run --rm -v $(pwd)/:/host -p 10000:10000 -it cell_move_router /usr/bin/gdbserver 127.0.0.1:10000 /host/cell_move_router /host/case1.txt /host/output.txt
