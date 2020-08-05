#include "NumCellInst.hpp"
#include "Global.h"

void printCellInstances() {
    
    CellInst* cells = g_cellsInstances;
    Net* nets = g_nets;
    
    printf("NumCellInst %d\n", g_numCellInst);
    for(int i=0; i<g_numCellInst; i++) {
        printf("CellInst %s %s %d %d %s\n", cells[i].instName, cells[i].masterCellName, cells[i].gGridRowIdx, cells[i].gGridColIdx, cells[i].movableCstr);
    }
    
    printf("NumNets %d\n", g_numNets);
    for(int i=0; i<g_numNets; i++) {
        printf("Net %s %d %s\n", nets[i].netName, nets[i].numPins, nets[i].minRoutingLayConstraint);
        for(int j=0; j<nets[i].numPins; j++) {
            printf("Pin %s/%s\n", nets[i].pins[j].instanceName, nets[i].pins[j].masterPinName);
        }
    }
}

void readNumCellInst(char* line, size_t len, FILE* file) {
    
    // NumCellInst <cellInstCount>
    // CellInst <instName> <masterCellName> <gGridRowIdx> <gGridColIdx> <movableCstr>
    // NumNets <netCount>
    // Net <netName> <numPins> <minRoutingLayConstraint>
    // Pin <instName>/<masterPinName>
    
    int numCells;
    if(sscanf(line,"NumCellInst %d\n", &numCells) == 1) {

        CellInst* cellArray = (CellInst*)malloc(sizeof(CellInst)*numCells);
        memset(cellArray, 0, sizeof(CellInst)*numCells);

        for(int i=0; i<numCells; i++) {
            if(fgets(line, len, file) == NULL) break;

            char instName[NAME_MAX_SIZE];
            char masterCellName[NAME_MAX_SIZE];
            char movableCstr[NAME_MAX_SIZE];
            int gGridRowIdx;
            int gGridColIdx;

            if(sscanf(line,"CellInst %s %s %d %d %s\n", instName, masterCellName, &gGridRowIdx, &gGridColIdx, movableCstr) == 5) {
                strcpy(cellArray[i].instName, instName);
                strcpy(cellArray[i].masterCellName, masterCellName);
                strcpy(cellArray[i].movableCstr, movableCstr);
                cellArray[i].gGridRowIdx = gGridRowIdx;
                cellArray[i].gGridColIdx = gGridColIdx;
            }

        }

        if(fgets(line, len, file) == NULL) return;

        int numNets;
        if(sscanf(line,"NumNets %d\n", &numNets) == 1) {
            Net* netArray = (Net*)malloc(sizeof(Net) * numNets);
            memset(netArray, 0, sizeof(Net) * numNets);

            for(int i=0; i<numNets; i++) {
                if(fgets(line, len, file) == NULL) return;

                char netName[NAME_MAX_SIZE];
                int numPins;
                char minRoutingLayConstraint[NAME_MAX_SIZE];

                if(sscanf(line, "Net %s %d %s\n", netName, &numPins, minRoutingLayConstraint) == 3) {
                    netArray[i].idx = i;
                    strcpy(netArray[i].netName, netName);
                    strcpy(netArray[i].minRoutingLayConstraint, minRoutingLayConstraint);
                    netArray[i].numPins = numPins;
                    if(numPins > 0) {
                        netArray[i].pins = (NetPin*)malloc(sizeof(NetPin) * numPins);
                    }

                    for(int j=0; j<numPins; j++) {
                        if(fgets(line, len, file) == NULL) break;

                        char instanceName[NAME_MAX_SIZE];
                        char masterPinName[NAME_MAX_SIZE];
                        
                        if(sscanf(line, "Pin %[^/]/%[^/\n]\n", instanceName, masterPinName) == 2) {
                            strcpy(netArray[i].pins[j].instanceName, instanceName);
                            strcpy(netArray[i].pins[j].masterPinName, masterPinName);
                        }
                    }
                }
            }

            g_numCellInst = numCells;
            g_numNets = numNets;
            g_cellsInstances = cellArray;
            g_nets = netArray;
            
        }
    }
    
}

