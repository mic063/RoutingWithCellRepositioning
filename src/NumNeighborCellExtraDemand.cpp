#include "NumNeighborCellExtraDemand.hpp"

void printNeighborCellExtraDemand() {
    ExtraDemand* extra = g_neighborCellExtraDemand;
    printf("NumNeighborCellExtraDemand %d\n", g_numNeighborCellExtraDemand);
    for(int i=0; i<g_numNeighborCellExtraDemand; i++) {
        if(extra[i].same) {
            printf("sameGGrid %s %s %s %d\n", extra[i].masterCellName1, extra[i].masterCellName2, extra[i].layerName, extra[i].demand);
        } else {
            printf("adjHGGrid %s %s %s %d\n", extra[i].masterCellName1, extra[i].masterCellName2, extra[i].layerName, extra[i].demand);
        }
    }
}

void readNumNeighborCellExtraDemand(char* line, size_t len, FILE* file) {
    
    // NumNeighborCellExtraDemand <count>
    // sameGGrid <masterCellName1> <masterCellName2> <layerName> <demand>
    // adjHGGrid <masterCellName1> <masterCellName2> <layerName> <demand>
    
    int count;
    if(sscanf(line, "NumNeighborCellExtraDemand %d\n", &count) == 1) {
        
        ExtraDemand* array = (ExtraDemand*)malloc(sizeof(ExtraDemand)*count);
        memset(array, 0, sizeof(ExtraDemand)*count);
        
        for(int i=0; i<count; i++) {
            if(fgets(line, len, file) == NULL) return;
            
            char masterCellName1[NAME_MAX_SIZE];
            char masterCellName2[NAME_MAX_SIZE];
            char layerName[NAME_MAX_SIZE];
            int demand;
            
            if(sscanf(line, "sameGGrid %s %s %s %d", masterCellName1, masterCellName2, layerName, &demand) == 4) {
                strcpy(array[i].masterCellName1, masterCellName1);
                strcpy(array[i].masterCellName2, masterCellName2);
                strcpy(array[i].layerName, layerName);
                array[i].demand = demand;
                array[i].same = true;
            } else if(sscanf(line,"adjHGGrid %s %s %s %d", masterCellName1, masterCellName2, layerName, &demand) == 4) {
                strcpy(array[i].masterCellName1, masterCellName1);
                strcpy(array[i].masterCellName2, masterCellName2);
                strcpy(array[i].layerName, layerName);
                array[i].demand = demand;
                array[i].same = false;
            }
            
        }
        
        g_numNeighborCellExtraDemand = count;
        g_neighborCellExtraDemand = array;
    }
}
