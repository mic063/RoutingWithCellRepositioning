
//  Functions.cpp

#include "Functions.hpp"

CellInst* get_cell_instance_with_name(char* instanceName) {
    for(int i=0; i<g_numCellInst; i++) {
        if(strcmp(g_cellsInstances[i].instName, instanceName) == 0) {
            return &(g_cellsInstances[i]);
        }
    }
    return nullptr;
}

Layer* get_layer_with_id(int id) {
    for(int i=0; i<g_numLayers; i++){
        if(g_layers[i].idx == id) {
            return &(g_layers[i]);
        }
    }
    return nullptr;
}

Layer* get_layer_with_name(char* name) {
    for(int i=0; i<g_numLayers; i++){
        if(strcmp(g_layers[i].name, name) == 0) {
            return &(g_layers[i]);
        }
    }
    return nullptr;
}

MasterCell* get_master_cell_with_name(char* name) {
    for(int i=0; i<g_numMasterCell; i++) {
        if(strcmp(g_masterCells[i].name, name) == 0) {
            return &(g_masterCells[i]);
        }
    }
    return nullptr;
}
