#ifndef Global_h
#define Global_h

#include <cstdio> // sscanf
#include <stdlib.h>
#include <stdio.h>
#include <string.h>

#define NAME_MAX_SIZE 16

typedef struct {
    int rowBeginIdx;
    int colBeginIdx;
    int rowEndIdx;
    int colEndIdx;
} GGridBoundaryIdx;

typedef struct {
    int idx;
    char name[NAME_MAX_SIZE];
    char routingDirection;
    int defaultSupplyOfOneGGrid;
} Layer;

typedef struct {
    int rowIdx;
    int colIdx;
    int layIdx;
    int incrOrDecrValue;
} SupplyGGrid;

typedef struct {
    char name[NAME_MAX_SIZE];
    char layer[NAME_MAX_SIZE];
} MasterCellPin;

typedef struct {
    char instanceName[NAME_MAX_SIZE];
    char masterPinName[NAME_MAX_SIZE];
} NetPin;

typedef struct {
    char name[NAME_MAX_SIZE];
    char layer[NAME_MAX_SIZE];
    int demand;
} Blockage;

typedef struct {
    char name[NAME_MAX_SIZE];
    
    int pinCount;
    MasterCellPin* pins;
    
    int blockageCount;
    Blockage* blockages;
} MasterCell;

typedef struct {
    bool same;
    char masterCellName1[NAME_MAX_SIZE];
    char masterCellName2[NAME_MAX_SIZE];
    char layerName[NAME_MAX_SIZE];
    int demand;
} ExtraDemand;

typedef struct {
    char instName[NAME_MAX_SIZE];
    char masterCellName[NAME_MAX_SIZE];
    char movableCstr[NAME_MAX_SIZE];
    int gGridRowIdx;
    int gGridColIdx;
} CellInst;

typedef struct {
    char netName[NAME_MAX_SIZE];
    int idx;
    int numPins;
    NetPin* pins;
    char minRoutingLayConstraint[NAME_MAX_SIZE];
} Net;

typedef struct {
    int sRowIdx;
    int sColIdx;
    int sLayIdx;
    int eRowIdx;
    int eColIdx;
    int eLayIdx;
    char netName[NAME_MAX_SIZE];
} RouteSegment;


// ============================

extern int g_maxCellMove;
extern GGridBoundaryIdx g_gridBoundaryIdx;

extern int g_numLayers;
extern Layer* g_layers;

extern int g_numNonDefaultSupplyGGrid;
extern SupplyGGrid* g_supplyGGrid;

extern int g_numRoutes;
extern RouteSegment* g_routeSegments;

extern int g_numNeighborCellExtraDemand;
extern ExtraDemand* g_neighborCellExtraDemand;

extern int g_numCellInst;
extern CellInst* g_cellsInstances;
extern int g_numNets;
extern Net* g_nets;

extern int g_numMasterCell;
extern MasterCell* g_masterCells;

#endif /* Struct_h */
