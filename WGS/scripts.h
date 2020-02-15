//
//  scripts.h
//  WGS
//
//  Created by Yao Zhou on 2020/2/16.
//  Copyright © 2020 Yao Zhou. All rights reserved.
//

#ifndef scripts_h
#define scripts_h
using namespace std;

int getFastp(parameter *para){
    string infile = (para -> inFile);
    string outfile = (para -> outFile) + "/";
    igzstream inf (infile.c_str(),ifstream::in);
    if(inf.fail()){
        cerr << "Open file error: " << infile << endl;
        return 0;
    }
    string oun = "fastp.sh";
    ofstream ouf (oun.c_str());
    if(ouf.fail()){
        cerr << "Couldn't open outFile" << endl;
        return 0;
    }
    string line;
    string suffix = (para -> suffix);
    string middle = ( para -> headerC );
    int thread = (para -> thread);
    vector <string> ll;
    set<string> names;
    while(!inf.eof()){
        getline(inf, line);
        if(line.length() < 1) continue;
        ll.clear();
        split(line,ll,"_");
        names.insert(ll[0]);
    }
    set<string>::iterator it;
    ouf << "#!/bin/bash\n";
    for (it = names.begin(); it != names.end(); it++){
        ouf << "fastp -i " << *it << "_" <<  middle << "1." << suffix << " -I " << *it << "_" <<  middle <<  "2." << suffix <<
        " --thread " << thread << " -o " << outfile  << *it << ".R1.fq.gz -O " << outfile << *it << ".R2.fq.gz\n";
    }
    inf.close();
    ouf.close();
    return 1;
}

#endif /* scripts_h */
