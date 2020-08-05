#ifndef Functions_hpp
#define Functions_hpp

#include "Global.h"

CellInst* get_cell_instance_with_name(char* cell_name);

Layer* get_layer_with_id(int id);
Layer* get_layer_with_name(char* name);

MasterCell* get_master_cell_with_name(char* name);

#endif /* Functions_hpp */
