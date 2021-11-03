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
        " --thread " << thread << " -o " << outfile  << *it << ".R1.fq.gz -O " << outfile << *it << ".R2.fq.gz" << " -h "
        << outfile  << *it << ".html -j " << outfile  << *it << ".json\n";
    }
    inf.close();
    ouf.close();
    return 1;
}

int cpFolder(parameter *para){
    string infile = (para -> inFile);
    string outfile = (para -> outFile) + "/";
    igzstream inf (infile.c_str(),ifstream::in);
    if(inf.fail()){
        cerr << "Open file error: " << infile << endl;
        return 0;
    }
    string suffix = (para -> suffix);
    string oun = "cp_"+suffix+".sh";
    ofstream ouf (oun.c_str());
    vector<string> ll;
    vector<string> files = getSubFoldfiles(infile,suffix);
    cout << "Number of files matched is:\t" << files.size() << endl;
    for(int i = 0; i < files.size(); i++){
        string str = files[i];
        ll.clear();
        split(str,ll,"/");
        string sub = ll[ll.size()-1] ;
        str = str.replace(str.find(sub),sub.length(),"");
        cout << str << endl;
        ouf << "mkdir -p " << outfile << "/" << str << "\n";
        ouf << "cp " << files[i] << " " << outfile << "/" << str << "\n";
    }
    ouf.close();
    return 0;
}
int merge_fq(parameter *para){
    string infile = (para -> inFile);
    string outfile = (para -> outFile);
    igzstream inf (infile.c_str(),ifstream::in);
    ofstream ouf (outfile.c_str());
    map<string,string> fq1;
    map<string,string> fq2;
    vector<string> ll ;
    string line;
    string path="/public4/home/sc55932/projects/hs/01_data/03_NGS/02_fastp/fastp/";
    while (!inf.eof()){
        getline(inf,line);
        if(line.length()<1) continue;
        if(line[0]=='t') continue;
        split(line,ll,"\t");
        string key = ll[2];
        string value = ll[1];
        if (fq1.count(key)==1){
            string l1 = fq1[key];
            string l2 = fq2[key];
            string l11 = l1 + path + value + "_1.fq.gz ";
            string l21 = l2 + path + value + "_2.fq.gz ";
            fq1[key] = l11;
            fq2[key] = l21;
        }else{
            string l1 = "cat " + path + value + "_1.fq.gz ";
            string l2 = "cat " + path + value + "_2.fq.gz ";
            fq1.insert(pair<string,string>(key,l1));
            fq2.insert(pair<string,string>(key,l2));
        }
    }
    map<string,string>::iterator it;
    for( it=fq1.begin(); it!=fq1.end(); it++){
        string key = it->first;
        string value = it->second;
        ouf << value << "> " << "/public4/home/sc55932/projects/hs/01_data/03_NGS/02_fastp/merged_fastp/" << key << "_1.fq.gz" << "\n";
    }
    for( it=fq2.begin(); it!=fq2.end(); it++){
        string key = it->first;
        string value = it->second;
        ouf << value << "> " << "/public4/home/sc55932/projects/hs/01_data/03_NGS/02_fastp/merged_fastp/" << key << "_2.fq.gz\n";
    }
    ouf.close();
    return 0;
}

#endif /* scripts_h */
