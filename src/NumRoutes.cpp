#include "NumRoutes.hpp"
#include "Global.h"

void printRoutes() {
    RouteSegment* routes = g_routeSegments;
    printf("NumRoutes %d\n", g_numRoutes);
    for(int i=0; i<g_numRoutes; i++) {
        printf("%d %d %d %d %d %d %s\n", routes[i].sRowIdx, routes[i].sColIdx, routes[i].sLayIdx, routes[i].eRowIdx, routes[i].eColIdx, routes[i].eLayIdx, routes[i].netName);
    }
}

void readNumRoutes(char* line, size_t len, FILE* file) {
    
    // NumRoutes <routeSegmentCount>
    // <sRowIdx> <sColIdx> <sLayIdx> <eRowIdx> <eColIdx> <eLayIdx> <netName>
    
    int count;
    if(sscanf(line, "NumRoutes %d\n", &count) == 1){
        
        RouteSegment* array = (RouteSegment*)malloc(sizeof(RouteSegment)*count);
        memset(array, 0, sizeof(RouteSegment)*count);
        
        for(int i=0; i<count; i++) {
            if(fgets(line, len, file) == NULL) return;
            
            int sRowIdx, sColIdx, sLayIdx, eRowIdx, eColIdx, eLayIdx;
            char netName[NAME_MAX_SIZE];
            if(sscanf(line, "%d %d %d %d %d %d %s", &sRowIdx, &sColIdx, &sLayIdx, &eRowIdx, &eColIdx, &eLayIdx, netName) == 7) {
                array[i].sRowIdx = sRowIdx;
                array[i].sColIdx = sColIdx;
                array[i].sLayIdx = sLayIdx;
                array[i].eRowIdx = eRowIdx;
                array[i].eColIdx = eColIdx;
                array[i].eLayIdx = eLayIdx;
                strcpy(array[i].netName, netName);
            }
        }
        
        g_numRoutes = count;
        g_routeSegments = array;
    }
}
