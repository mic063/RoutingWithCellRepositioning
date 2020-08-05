#!/bin/bash

docker run --rm -v $(pwd)/:/host -it cell_move_router /usr/bin/gdb --args /host/cell_move_router /host/case1.txt /host/output.txt
