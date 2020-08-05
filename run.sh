#!/bin/bash

docker run --rm -v $(pwd)/:/host -it cell_move_router /host/cell_move_router /host/case1.txt /host/output_case1.txt
