#include <iostream>
#include <fstream>
#include <cassert>
#include "Functions.hpp"
#include "Output.hpp"
#include "Global.h"
#include "FastRoute.h"

extern const char* output_file;

void run_fastroute() {

    FastRoute::FT fastroute;

	fastroute.setVerbose(2);
	fastroute.setAllowOverflow(true);
	fastroute.setOverflowIterations(1);
	
    fastroute.setLowerLeft(g_gridBoundaryIdx.colBeginIdx, g_gridBoundaryIdx.rowBeginIdx);
    fastroute.setTileSize(1, 1);
    fastroute.setGridsAndLayers((g_gridBoundaryIdx.colEndIdx-g_gridBoundaryIdx.colBeginIdx)+1,
                                (g_gridBoundaryIdx.rowEndIdx-g_gridBoundaryIdx.rowBeginIdx)+1,
                                 g_numLayers);

    for(int i=0; i < g_numLayers; i++) {
        Layer layer = g_layers[i];

        if(layer.routingDirection == 'V') {
            fastroute.addVCapacity(layer.defaultSupplyOfOneGGrid, layer.idx);
        } else {
            fastroute.addHCapacity(layer.defaultSupplyOfOneGGrid, layer.idx);
        }

        fastroute.addMinSpacing(1, layer.idx);
        fastroute.addMinWidth(1, layer.idx);
        fastroute.addViaSpacing(1, layer.idx);
    }

    // Esse funcao depende da direcao do layer M1. Se M1 for horizontal, chama ela com 1; se for vertical, chama ela com 0
    // PDF do problema diz: "The routing direction will always be horizontal on M1"
    fastroute.setLayerOrientation(1);
    
    //fastroute.usePdRev();
    
    fastroute.setNumberNets(g_numNets);
    
//#define DEBUG_NETS
    
#ifdef DEBUG_NETS
    std::cout << "num net " << g_numNets << std::endl;
#endif
    for(int i=0; i<g_numNets; i++) {
        Net& net = g_nets[i];
#ifdef DEBUG_NETS
        std::cout << net.netName << " " << net.idx << " " << net.numPins << " " << 1 << std::endl;
#endif

        FastRoute::PIN* frPins = (FastRoute::PIN*)malloc(sizeof(FastRoute::PIN) * net.numPins);

        for(int j=0; j<net.numPins; j++) {
            NetPin& netPin = net.pins[j];
            CellInst* inst = get_cell_instance_with_name(netPin.instanceName);
            MasterCell* masterCell = get_master_cell_with_name(inst->masterCellName);

            int layer = -1;
            for(int k=0; k < masterCell->pinCount; k++) {
                MasterCellPin& mcPin = masterCell->pins[k];
                if(strcmp(mcPin.name, netPin.masterPinName) == 0) {
                    layer = get_layer_with_name(mcPin.layer)->idx;
                    break;
                }
            }

            assert(layer != -1);

            frPins[j].layer = (int)layer;
            frPins[j].x = (long)(inst->gGridRowIdx);
            frPins[j].y = (long)(inst->gGridColIdx);
#ifdef DEBUG_NETS
            std::cout << frPins[j].x << " " << frPins[j].y << " " << frPins[j].layer << std::endl;
#endif
        }

			fastroute.addNet(net.netName, net.idx, net.numPins, 1, frPins, 1.0, false);
//        fastroute.addNet(net.netName, net.idx, net.numPins, 1, frPins /*, 1.0*/);
        free(frPins);
    }

    fastroute.initEdges();

    fastroute.setNumAdjustments(g_numNonDefaultSupplyGGrid);
    for(int i=0; i<g_numNonDefaultSupplyGGrid; i++) {
        int idx = g_supplyGGrid[i].layIdx;
        Layer* layer = get_layer_with_id(idx);

        int x1 = 0;
        int y1 = 0;
        int x2 = 0;
        int y2 = 0;

        //       if(layer->routingDirection == 'V') {
                   // Se a layer for vertical, x1 = x2
        //            y1 = 1; // de onde tirar?
        //            x2 = g_supplyGGrid[i].rowIdx; // de onde tirar?
        //            y2 = g_supplyGGrid[i].colIdx; // de onde tirar?
        //            x1 = x2;
        //        } else {
        //            // Se a layer for horizontal, y1 = y2
        //            x1 = 1; // de onde tirar?
        //            x2 = g_supplyGGrid[i].rowIdx; // de onde tirar?
        //            y1 = g_supplyGGrid[i].colIdx; // de onde tirar?
        //            y2 = y1;
        //        }

        if (layer->routingDirection == 'H') {
           // se a layer for horizontal, x1 "desconta" 1
          x1 = g_supplyGGrid[i].rowIdx-1;
          y1 = g_supplyGGrid[i].colIdx;
          x2 = g_supplyGGrid[i].rowIdx;
          y2 = g_supplyGGrid[i].colIdx;
         } else {
           // se a layer for vertical, y1 "desconta" 1
          x1 = g_supplyGGrid[i].rowIdx;
          y1 = g_supplyGGrid[i].colIdx-1;
          x2 = g_supplyGGrid[i].rowIdx;
          y2 = g_supplyGGrid[i].colIdx;
         }

             x1 = std::max(1, x1);
             y1 = std::max(1, y1);
             x2 = std::max(1, x2);
             y2 = std::max(1, y2);

        int reducedCap = abs(g_supplyGGrid[i].incrOrDecrValue);
        bool isReduce = (g_supplyGGrid[i].incrOrDecrValue < 0);

        assert(layer != nullptr);

        fastroute.addAdjustment(x1, y1, layer->idx,
                                x2, y2, layer->idx,
                                reducedCap,
                                isReduce);
    }

    fastroute.initAuxVar();
    std::cout << "Running FastRoute..." << std::endl;
    std::vector<FastRoute::NET> nets = std::vector<FastRoute::NET>();
    fastroute.run(nets);
    std::cout << "Running FastRoute... Done!" << std::endl;

	int routesCnt = 0;
		for (FastRoute::NET net : nets) {
			routesCnt += net.route.size();
		}
    std::cout << "Num of routes for the design: " << routesCnt << "\n";


    fastroute.writeCongestionReport3D(output_file);

}
