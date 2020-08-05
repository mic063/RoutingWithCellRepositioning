#include "MaxCellMove.hpp"

void printMaxCellMove() {
    printf("MaxCellMove %d\n", g_maxCellMove);
}

void readMaxCellMove(char* line, size_t len, FILE* file) {
    
    // MaxCellMove <maxMoveCount>
    
    int maxMoveCount;
    if(sscanf(line, "MaxCellMove %d", &maxMoveCount) == 1) {
        g_maxCellMove = maxMoveCount;
    }
    
}
