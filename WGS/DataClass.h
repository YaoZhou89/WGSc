//
//  DataClass.h
//  WGS
//
//  Created by Yao Zhou on 2018/12/4.
//  Copyright © 2018 Yao Zhou. All rights reserved.
//

#ifndef DataClass_h
#define DataClass_h

using namespace std;
class parameter {
public:
    string inFile;
    string outFile;
    string bedFile;
    string inFile2;
    string model;
    string type;
    string subPop;
    string logFile;
    double  MQ;
    double FS;
    double MQRankSum;
    double ReadPosRankSum;
    double BSQRankSum;
    double SOR;
    double minDepth;
    double maxDepth;
    double depthSD;
    int size;
    bool isBed;
    string headerC;
    set<int> pos; // used for change chromosome pos;
    parameter()
    {
        inFile = "";
        inFile2 = "";
        outFile = "";
        subPop = "";
        bedFile = "";
        MQ = 30.0;
        MQRankSum = -12.5;
        FS = 60.0;
        ReadPosRankSum = -8;
        BSQRankSum  = 0.0;
        SOR = 3.0;
        model = "wc";
        type = "qualityFilter";
        logFile = outFile + ".log";
        isBed = false;
        pos;
        headerC = "#";
    }
};

struct BaseType
{
    unsigned short int Value:2 ;
};

class vcf {
public:
    vector <string> header;
    vector <bool> filter; // passed or not, for writing and statistic
    map <string,map <int, vector <BaseType> > >  SNPList ; // transform the type to numeric
    map <string, map <int, vector < int > > > depth; // store the depth of each; the last two columns are total depth and depth sd
    map <string, map <int, vector < double > > > FS;
    map <string, map <int, vector < double > > > MQ;
    map <string, map <int, vector < double > > > MQRankSum;
    map <string, map <int, vector < double > > > ReadPosRankSum;
    map <string, map <int, vector < double > > > SOR;
    map <string, map <int, vector < double > > > BSQRankSum;
    long int TotalNumber;
    long int passedNumber;
    long int badNumber;
    int sampleSize;
    vcf()
    {
        SNPList ;
        depth ;
        FS ;
        MQ ;
        MQRankSum ;
        ReadPosRankSum ;
        MQRankSum ;
        ReadPosRankSum ;
        SOR ;
        BSQRankSum ;
        TotalNumber = 0;
        passedNumber = 0;
        badNumber = 0;
        sampleSize = 0;
    }
};
class depth {
public:
    map <string, map <int, vector < int > > > depthList;
    depth(){
        depthList;
    }
};
#endif /* DataClass_h */
