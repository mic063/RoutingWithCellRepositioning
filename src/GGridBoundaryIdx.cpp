#include "GGridBoundaryIdx.hpp"

void printGGridBoundaryIdx() {
    printf("GGridBoundaryIdx %d %d %d %d\n", g_gridBoundaryIdx.rowBeginIdx, g_gridBoundaryIdx.colBeginIdx, g_gridBoundaryIdx.rowEndIdx, g_gridBoundaryIdx.colEndIdx);
}

void readGGridBoundaryIdx(char* line, size_t len, FILE* file) {
    
    // GGridBoundaryIdx <rowBeginIdx> <colBeginIdx> <rowEndIdx> <colEndIdx>
    
    int rowBeginIdx, colBeginIdx, rowEndIdx, colEndIdx;
    if(sscanf(line, "GGridBoundaryIdx %d %d %d %d", &rowBeginIdx, &colBeginIdx, &rowEndIdx, &colEndIdx) == 4) {
        g_gridBoundaryIdx.rowBeginIdx = rowBeginIdx;
        g_gridBoundaryIdx.colBeginIdx = colBeginIdx;
        g_gridBoundaryIdx.rowEndIdx = rowEndIdx;
        g_gridBoundaryIdx.colEndIdx = colEndIdx;
    }
    
}
