//
//  main.cpp
//  WGS
//
//  Created by Yao Zhou on 2018/12/4.
//  Copyright © 2018 Yao Zhou. All rights reserved.
//

#include "HeaderIns.h"
#include "DataClass.h"
#include "baseFunctions.h"
#include "help.h"
#include "initialization.h"
#include "checkers.h"
#include "FileFunctions.h"
#include "dataConvert.h"
int main(int argc, char * argv[]) {
    clock_t start;
    double duration;
   
    start = clock();
    
    parameter *para = new parameter;
    if ( (WGS_initialization(argc, argv, para) == 0) )
    {
        delete para;
        return 1 ;
    }
//    checkOUT(para);
    vcf *inVCF = new vcf;
    depth *inDepth = new depth;
    if (!(para->inFile).empty())
    {
        if ((para -> model).empty()){
            cerr << "model should be specified! Please check" << endl; ;
        }else if((para -> model) == "vcf"){
            if((para->type)==""){
                Read_VCF_IN(para, inVCF);
            }else if((para->type)=="toFasta"){
                
            }else if((para->type) == "calibrate"){
                calibarate(para);
            }else if((para->type) == "calibrate2"){
                calibarate2(para);
            }else if((para->type) == "calibarate3"){
                calibarate3(para);
            }else if((para->type) == "calibarate4"){
                calibarate4(para);
            }else if((para->type) == "calibarate5"){
                calibarate5(para);
            }else if((para->type)=="toV8"){
                cout << "toV8..." << endl;
                getV8(para);
            }else if ((para->type)=="site-pi"){
                pi(para);
            }else if((para->type) == "vcf2sNMF"){
                vcf2sNMF(para);
            }else if ((para->type) == "getHeader"){
                getHeader(para);
            }else if((para->type) == "depthFilter"){
                
            }else if((para->type) == "ct3"){
                ct3(para); // snps shared among three groups
            }else if((para->type) == "ct2"){
                ct2(para); // snps shared in two groups
            }else if((para->type) == "ct1"){
                ct1(para); // allelic or not
            }else if((para->type) == "addContig"){
                addContig(para);
            }else if((para -> type) == "ANC"){
                changeAncestralAllele(para);
            }else if ((para->type) == "merge2vcf"){
                merge2vcf(para);
            }
            else if ((para->type) == "toXPCLR"){
                toXPCLR(para);
            }else if((para->type) =="toXPCLRsnp") {
                toXPCLRsnp(para);
            }else if ((para->type)=="toV11"){
                toV11(para);
            }else if ((para->type) == "toSFS"){
                toSFS(para);
            }else if ((para->type) == "pwMAF"){
                pwFrequence(para);
            }else if((para->type) =="maf"){
                writeMAF(para);
            }else if ((para->type) =="Derived"){
                getDerivedAllele(para);
            }else if ((para->type) == "incp"){
                cp(para);
            }
        }else if((para -> model) == "depth"){
            if((para->type)=="site"){
                cout << "get Site.." << endl;
                Read_depth_IN(para,inDepth);
            }else if((para->type) == "toBed"){
                Depth2Bed(para);
            }else if ((para->type) == "merge"){
                mergeDepth(para);
            }else if((para->type) == "mask"){
                getMaskRegion(para);
            }else if ((para->type) == "UnMapped"){
                getUnMapped(para);
            }
//            outDepthFile(para,inDepth);
        }else if ((para->model) == "pos"){
            if ((para->type) == "changePos"){
                changePos(para);
            }else if((para->type) =="change2num"){
                chr2num(para);
            }
        }else if((para->model) == "wc"){
            count(para);
        }else if((para->model) == "file"){
            if ((para->type) == "merge"){
                mergeDepth(para);
            }else if((para -> type)=="random"){
                randChoose(para);
            }else if((para -> type)=="merge3"){
                filterDepth3(para);
            }else if((para -> type)=="merge2"){
                filterDepth2(para);
            }else if((para -> type)=="filterBySim3"){
                filterDepth_bySimulation3(para);
            }else if((para -> type)=="filterBySim"){
                filterDepth_bySimulation(para);
            }else if((para -> type)=="filterBySim2"){
//                cout <<"testing..."<<endl;
                filterDepth_bySimulation2(para);
            }else if((para->type) == "intersect"){
                intersectFile(para);
            }else if ((para->type) == "getPos"){
                getPos(para);
            }else if((para->type) =="getMax"){
                getMaximum(para);
            }else if((para->type) =="pwpd"){
                pwpd(para);
            }else if((para->type) == "mumer4"){
                subMummer4(para);
            }else if((para->type) == "LDmean"){
                LDmean(para);
            }else if ((para->type) =="TEdensity"){
                TEdensity(para);
            }else if ((para->type) == "cleanBed"){
                cleanBed(para);
            }else if ((para->type) =="BestHit"){
                BestHit(para);
            }
        }else if((para->model) == "gff3"){
            if ((para->type) == "density"){
                getGffDensity(para);
            }else if ((para->type) == "gff2bed"){
                gff2bed(para);
            }else if ((para->type) == "gff3thin"){
                gff2thin(para);
            }
        }else if((para->model) == "diversity"){
            if((para->type)=="bedPi"){
                pi2bed(para);
            }else if((para->type) == "syn"){
                getOri(para);
            }else if ((para -> type) =="genePi"){
                genePi(para);
            }else if ((para->type) == "overCount"){
                gene_count(para);
            }else if((para->type) == "CountByGene"){
                gene_count_gene(para);
            }else if((para->type) == "reduction"){
                DiversityReduction(para);
            }
        }else if((para -> model) == "structure"){
            if((para -> type) == "Q2CLUMPP"){
                Q2CLUMPP(para);
            }else if((para->type) == "CLUMPP2R"){
                CLUMPP2R(para);
            }
        }else if((para->model) == "tree"){
            if((para->type) == "phy"){
                changePhy(para);
            }
        }else if ((para->model) == "fasta"){
            if((para->type) == "toMCscanGff"){
                getGffMCscan(para);
            }else if((para->type) =="changeGff"){
                getGffMCscanChr(para);
            }
        }
    }
    
    duration = ( clock() - start ) / (double) CLOCKS_PER_SEC;
    cout<<"Finished in "<< duration <<" sec " << '\n';
    return 0;
}
