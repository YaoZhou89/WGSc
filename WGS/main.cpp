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
            Read_VCF_IN(para, inVCF);
        }else if((para -> model) == "depth"){
            if((para->type)=="site"){
                cout << "get Site.." << endl;
                Read_depth_IN(para,inDepth);
            }else if((para->type) == "toBed"){
                toBedold(para);
            }else if ((para->type) == "merge"){
                mergeDepth(para);
            }
//            outDepthFile(para,inDepth);
        }else if ((para->model) == "pos"){
            if ((para->type) == "changePos"){
                changePos(para);
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
            }else if((para->type) == "intersect"){
                intersectFile(para);
            }else if ((para->type) == "getPos"){
                getPos(para);
            }
        }
    }
    
    duration = ( clock() - start ) / (double) CLOCKS_PER_SEC;
    cout<<"Finished in "<< duration <<" sec " << '\n';
    return 0;
}
