#include "NumNonDefaultSupplyGGrid.hpp"

void printNumNonDefaultSupplyGGrid() {
    SupplyGGrid* grids = g_supplyGGrid;
    printf("NumNonDefaultSupplyGGrid %d\n", g_numNonDefaultSupplyGGrid);
    for(int i=0; i<g_numNonDefaultSupplyGGrid; i++) {
        if(grids[i].incrOrDecrValue > 0) {
            printf("%d %d %d +%d\n", grids[i].rowIdx, grids[i].colIdx, grids[i].layIdx, grids[i].incrOrDecrValue);
        } else {
            printf("%d %d %d %d\n", grids[i].rowIdx, grids[i].colIdx, grids[i].layIdx, grids[i].incrOrDecrValue);
        }
    }
}


void readNumNonDefaultSupplyGGrid(char* line, size_t len, FILE* file) {
    
    // NumNonDefaultSupplyGGrid <nonDefaultSupplyGGridCount>
    // <rowIdx> <colIdx> <LayIdx> <incrOrDecrValue>
    
    int count;
    if(sscanf(line, "NumNonDefaultSupplyGGrid %d", &count) == 1){
        
        SupplyGGrid* array = (SupplyGGrid*)malloc(sizeof(SupplyGGrid)*count);
        memset(array, 0, sizeof(SupplyGGrid)*count);
        
        for(int i=0; i<count; i++) {
            if(fgets(line, len, file) == NULL) return;
            
            int rowIdx, colIdx, layIdx, incrOrDecrValue;
            if(sscanf(line, "%d %d %d %d", &rowIdx, &colIdx, &layIdx, &incrOrDecrValue) == 4) {
                array[i].rowIdx = rowIdx;
                array[i].colIdx = colIdx;
                array[i].layIdx = layIdx-1;
                array[i].incrOrDecrValue = incrOrDecrValue;
            }
        }
        
        g_numNonDefaultSupplyGGrid = count;
        g_supplyGGrid = array;
    }
}
