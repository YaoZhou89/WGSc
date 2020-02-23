//
//  vcf.h
//  WGS
//
//  Created by Yao Zhou on 2020/2/22.
//  Copyright © 2020 Yao Zhou. All rights reserved.
//

#ifndef vcf_h
#define vcf_h

int vcf2IL (parameter *para){
    string input =(para->inFile);
    igzstream inf (input.c_str(),ifstream::in);
    if (inf.fail()){
        cerr << "open File IN error: " << (para->inFile) << endl;
        return  0;
    }
    
    string outFile =(para -> outFile);
    ofstream ouf (outFile.c_str());
    if((!ouf.good())){
        cerr << "open OUT File error: " << outFile << endl;
        return  0;
    }
    map<string,string> sg;
    map<string,int> group;
   
    string line;
    vector <string> ll;
    
    return 0;
}

#endif /* vcf_h */
