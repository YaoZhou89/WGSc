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
    std::clock_t start;
    double duration;
    
    start = std::clock();
    
    /* Your algorithm here */
    
    
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
            cout << "reading.." << endl;
            Read_depth_IN(para,inDepth);
//            outDepthFile(para,inDepth);
        }
    }
    
    duration = ( std::clock() - start ) / (double) CLOCKS_PER_SEC;
    std::cout<<"Finished in "<< duration <<" sec " << '\n';
    return 0;
}
