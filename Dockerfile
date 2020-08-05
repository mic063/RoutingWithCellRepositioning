FROM ubuntu:20.10
RUN export DEBIAN_FRONTEND=noninteractive && apt-get update && apt-get install git make cmake g++ bison swig tcl tcl-dev libboost-all-dev gdb -y && apt-get clean
WORKDIR /host
CMD rm -rf build && mkdir build && cd build && cmake .. && make && cp ./cell_move_router /host/
