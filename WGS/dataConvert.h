//
//  dataConvert.h
//  WGS
//
//  Created by Yao Zhou on 2019/1/7.
//  Copyright © 2019 Yao Zhou. All rights reserved.
//

#ifndef dataConvert_h
#define dataConvert_h

using namespace std;

int vcf2sNMF(parameter *para){
    string infs = (para->inFile);
    string infs2 = (para->subPop);
    string oufs = (para -> outFile);
    igzstream inf (infs.c_str(),ifstream::in);
    igzstream subPop (infs2.c_str(),ifstream::in);
    if(infs2!=""){
        if(subPop.fail()){
            cerr << "Can't open subPopulation file!" << endl;
            return 0;
        }
    }
    ofstream ouf (oufs.c_str());
    if(inf.fail()){
        cerr << "open inFile error! " << endl;
        return 0;
    }
    if(ouf.fail()){
        cerr << "open outFile error!" << endl;
        return 0;
    }
    string line;
    vector <string> ll;
    set <string> subNames;
    while(!subPop.eof()){
        getline(subPop,line);
        if(line.length()<1) continue;
        subNames.insert(line);
    }
    subPop.close();
    while(!inf.eof()){
        getline(inf,line);
        if(line[0] == '#') continue;
        if(line.length()<1) continue;
        ll.clear();
        split(line,ll,"\t");
        for(int i = 9; i < ll.size(); ++i){
            if(ll[i][0]=='0' && ll[i][2] == '0'){
                ouf << "0";
            }else if(ll[i][0]=='0' && ll[i][2] == '1'){
                ouf << "1";
            }else if(ll[i][0]=='1' && ll[i][2] == '1'){
                ouf << "2";
            }else{
                ouf <<"9";
            }
        }
        ouf << "\n";
    }
    inf.close();
    ouf.close();
    return 1;
}

#endif /* dataConvert_h */
