//
//  checkers.h
//  WGS
//
//  Created by Yao Zhou on 2018/12/4.
//  Copyright © 2018 Yao Zhou. All rights reserved.
//

#ifndef checkers_h
#define checkers_h

using namespace std;

int checkOUT(parameter * para){
    string outFile = (para -> outFile);
    outFile = (para -> outFile) + ".gz";
    ogzstream OUTTest ((outFile).c_str());
    if((!OUTTest.good()))
    {
        cerr << "open OUT File error: "<< outFile <<endl;
        delete para;
        return 1;
    }
    OUTTest.close();
    return 0;
}

#endif /* checkers_h */
