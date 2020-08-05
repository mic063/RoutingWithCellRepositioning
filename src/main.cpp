#include <cstdio> // sscanf
#include <stdlib.h>
#include <stdio.h>
#include <string.h>

#include "Output.hpp"
#include "Functions.hpp"
#include "Global.h"
#include "NumMasterCell.hpp"
#include "NumCellInst.hpp"
#include "NumRoutes.hpp"
#include "NumNonDefaultSupplyGGrid.hpp"
#include "NumNeighborCellExtraDemand.hpp"
#include "NumLayers.hpp"
#include "GGridBoundaryIdx.hpp"
#include "MaxCellMove.hpp"
#include "flute.h"

int g_maxCellMove = 0;

GGridBoundaryIdx g_gridBoundaryIdx;

int g_numMasterCell = 0;
MasterCell* g_masterCells = 0;

int g_numLayers = 0;
Layer* g_layers = 0;

int g_numNonDefaultSupplyGGrid = 0;
SupplyGGrid* g_supplyGGrid = 0;

int g_numRoutes = 0;
RouteSegment* g_routeSegments = 0;

int g_numNeighborCellExtraDemand = 0;
ExtraDemand* g_neighborCellExtraDemand = 0;

int g_numCellInst = 0;
CellInst* g_cellsInstances = 0;
int g_numNets = 0;
Net* g_nets = 0;

const char* input_file = 0;
const char* output_file = 0;

void free_globals() {
    if(g_layers) free(g_layers);
    if(g_supplyGGrid) free(g_supplyGGrid);
    if(g_routeSegments) free(g_routeSegments);
    if(g_neighborCellExtraDemand) free(g_neighborCellExtraDemand);
    if(g_cellsInstances) free(g_cellsInstances);
    if(g_nets) {
        for(int i=0; i<g_numNets; i++) {
            if(g_nets[i].pins) free(g_nets[i].pins);
        }
        free(g_nets);
    }

    if(g_masterCells) {
        for(int i=0; i< g_numMasterCell; i++) {
            if(g_masterCells[i].pins) free(g_masterCells[i].pins);
            if(g_masterCells[i].blockages) free(g_masterCells[i].blockages);
        }
        free(g_masterCells);
    }
}

int main(int argc, char *argv[])
{
    Flute::readLUT();
    if(argc < 2){
      printf("Usage: cell_move_router <input_file> [<output_file>]\n");
      return 1;
    }

    input_file = argv[1];
    if(argc > 2){
      output_file = argv[2];
    } else {
      output_file = "output.txt";
    }

    FILE *file;
    file = fopen (input_file, "r");
    size_t len = 256; // numero de caracteres m?ximos pra ler por linha
    char *line = (char*)malloc(len);

    if (file == NULL){
        printf("File not found!\n");
        return 0;
    }

    while (fgets(line, len, file) != NULL) {
        readMaxCellMove(line, len, file);
        readGGridBoundaryIdx(line, len, file);
        readNumLayers(line, len, file);
        readNumNonDefaultSupplyGGrid(line, len, file);
        readNumMasterCell(line, len, file);
        readNumNeighborCellExtraDemand(line, len, file);
        readNumCellInst(line, len, file);
        readNumRoutes(line, len, file);

    }
    fclose(file);

    //    printMaxCellMove();
    //    printGGridBoundaryIdx();
    //    printLayers();
    //    printNumNonDefaultSupplyGGrid();
    //    printMasterCells();
    //    printNeighborCellExtraDemand();
    //    printCellInstances();
    //    printRoutes();

    run_fastroute();

    free(line);
    free_globals();

    return 0;
}
