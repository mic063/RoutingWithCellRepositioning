#!/bin/bash

CASE_NUMBER="$1"

docker run --rm -v $(pwd)/:/host -it cell_move_router /host/cell_move_router /host/case${CASE_NUMBER}.txt /host/output_case${CASE_NUMBER}.txt
