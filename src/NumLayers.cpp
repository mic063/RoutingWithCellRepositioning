#include "NumLayers.hpp"

void printLayers() {
    Layer* layers = g_layers;
    printf("NumLayer %d\n", g_numLayers);
    for(int i=0; i<g_numLayers; i++) {
        printf("Lay %s %d %c %d\n", layers[i].name, layers[i].idx, layers[i].routingDirection, layers[i].defaultSupplyOfOneGGrid);
    }
}

void readNumLayers(char* line, size_t len, FILE* file) {

    // NumLayers <LayerCount>
    // Lay <layerName> <Idx> <RoutingDirection> <defaultSupplyOfOneGGrid>
    
    int count;
    if(sscanf(line, "NumLayer %d\n", &count) == 1) {
        Layer* array = (Layer*)malloc(sizeof(Layer)*count);
        memset(array, 0, sizeof(Layer)*count);
        
        for(int i=0; i<count; i++) {
            if(fgets(line, len, file) == NULL) return;
            
            char layerName[NAME_MAX_SIZE];
            int idx, defaultSupplyOfOneGGrid;
            char routingDirection;
            
            if(sscanf(line, "Lay %s %d %c %d\n", layerName, &idx, &routingDirection, &defaultSupplyOfOneGGrid) == 4) {
                strcpy(array[idx-1].name, layerName);
                array[idx-1].idx = idx-1;
                array[idx-1].routingDirection = routingDirection;
                array[idx-1].defaultSupplyOfOneGGrid = defaultSupplyOfOneGGrid;
            }
        }
        
        g_numLayers = count;
        g_layers = array;
    }
}
