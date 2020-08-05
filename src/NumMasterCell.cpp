#include "NumMasterCell.hpp"

void printMasterCells() {
    MasterCell* masterCells = g_masterCells;
    printf("NumMasterCell %d\n", g_numMasterCell);
    for(int i=0; i<g_numMasterCell; i++) {
        printf("MasterCell %s %d %d\n", masterCells[i].name, masterCells[i].pinCount, masterCells[i].blockageCount);
        for(int j=0; j<masterCells[i].pinCount; j++) {
            printf("Pin %s %s\n", masterCells[i].pins[j].name, masterCells[i].pins[j].layer);
        }
        for(int j=0; j<masterCells[i].blockageCount; j++) {
            printf("Blkg %s %s %d\n", masterCells[i].blockages[j].name, masterCells[i].blockages[j].layer, masterCells[i].blockages[j].demand);
        }
    }
    
}

void readNumMasterCell(char* line, size_t len, FILE* file) {
    
    // NumMasterCell <masterCellCount>
    // MasterCell <masterCellName> <pinCount> <blockageCount>
    // Pin <pinName> <pinLayer>
    // Blkg <blockageName> <blockageLayer> <demand>
    
    int count;
    if(sscanf(line, "NumMasterCell %d", &count) == 1) {
        MasterCell* array = (MasterCell*)malloc(sizeof(MasterCell)*count);
        memset(array, 0, sizeof(MasterCell)*count);
        
        for(int i=0; i<count; i++) {
            if(fgets(line, len, file) == NULL) break;
            
            char masterCellName[NAME_MAX_SIZE];
            int pinCount;
            int blockageCount;
            
            if(sscanf(line, "MasterCell %s %d %d", masterCellName, &pinCount, &blockageCount) == 3) {
                strcpy(array[i].name, masterCellName);
                array[i].pinCount = pinCount;
                array[i].blockageCount = blockageCount;
                
                if(pinCount > 0) {
                    array[i].pins = (MasterCellPin*)malloc(sizeof(MasterCellPin)*pinCount);
                } else {
                    array[i].pins = NULL;
                }
                
                if(blockageCount > 0) {
                    array[i].blockages = (Blockage*)malloc(sizeof(Blockage)*blockageCount);
                } else {
                    array[i].blockages = NULL;
                }
                
                for(int j=0; j<pinCount; j++) {
                    if(fgets(line, len, file) == NULL) break;
                    
                    char name[NAME_MAX_SIZE];
                    char layer[NAME_MAX_SIZE];
                    if(sscanf(line, "Pin %s %s", name, layer) == 2) {
                        strcpy(array[i].pins[j].name, name);
                        strcpy(array[i].pins[j].layer, layer);
                    }
                }
                
                for(int j=0; j<blockageCount; j++) {
                    if(fgets(line, len, file) == NULL) break;
                    
                    char name[NAME_MAX_SIZE];
                    char layer[NAME_MAX_SIZE];
                    int demand;
                    if(sscanf(line, "Blkg %s %s %d", name, layer, &demand) == 3) {
                        strcpy(array[i].blockages[j].name, name);
                        strcpy(array[i].blockages[j].layer, layer);
                        array[i].blockages[j].demand = demand;
                    }
                }
            }
        }
        
        g_numMasterCell = count;
        g_masterCells = array;
    }
}
