//
//  initialization.h
//  WGS
//
//  Created by Yao Zhou on 2018/12/4.
//  Copyright © 2018 Yao Zhou. All rights reserved.
//

#ifndef initialization_h
#define initialization_h

using namespace std;

int WGS_initialization(int argc, char **argv , parameter * para)
{
    if (argc <2 ) {WGS_help0();return 0;}
    
    for(int i = 0; i < argc ; i++)
    {
       
//        if(argv[i][1] != '-')
//        {
//            cout << argv[1] << endl;
//            cerr << "command option error! please check." << endl;
//            return 0;
//        }
        string flag = argv[i] ;
        flag=replace_all(flag,"--","");
//        cout << flag << endl;
        if (flag  == "InVCF" ||  flag  == "i" || flag == "inFile" || flag == "file")
        {
            if(i + 1 == argc) {LogLackArg(flag); return 0;}
            i++;
            para -> inFile = argv[i];
            
        }
        else if (flag  == "InGenotype")
        {
            if(i + 1 == argc) {LogLackArg(flag); return 0;}
            i++;
            para -> inFile = argv[i];
        }
        else if (flag  == "inFile2")
        {
            if(i + 1 == argc) {LogLackArg(flag); return 0;}
            i++;
            para -> inFile2 = argv[i];
        }
        else if (flag  == "subPop"  ||  flag  == "s" )
        {
            if(i + 1 == argc) {LogLackArg(flag); return 0;}
            i++;
            para -> subPop = argv[i];
        }
        else if (flag  ==  "outFile" ||  flag  == "o" || flag == "out")
        {
            if(i + 1 == argc) {LogLackArg(flag); return 0;}
            i++;
            para -> outFile = argv[i];
        }
        else if (flag  == "model")
        {
            if(i + 1 == argc) {LogLackArg(flag); return 0;}
            i++;
            para -> model = argv[i];
        }
        else if (flag  == "type")
        {
            if(i + 1 == argc) {LogLackArg(flag); return 0;}
            i++;
            para -> type = argv[i];
        }
        else if (flag  == "MQ" )
        {
            if(i + 1 == argc) {LogLackArg(flag); return 0;}
            i++;
            para -> MQ = atof(argv[i]);
        }
        else if (flag == "FS")
        {
            if(i + 1== argc) {LogLackArg(flag);return 0;}
            i++;
            para -> FS = atof(argv[i]);
        }
        else if (flag == "MQRankSum")
        {
            if(i + 1 == argc) {LogLackArg(flag);return 0;}
            i++;
            para -> MQRankSum = atof(argv[i]);
        }
        else if (flag == "ReadPosRankSum" )
        {
            if(i + 1 == argc) {LogLackArg(flag);return 0;}
            i++;
            para -> ReadPosRankSum = atof(argv[i]);
        }
        else if (flag == "BSQRankSum")
        {
            if(i + 1 == argc) {LogLackArg(flag);return 0;}
            i++;
            para -> BSQRankSum =atof(argv[i]);
        }
        else if (flag == "SOR")
        {
            if(i + 1 == argc) {LogLackArg(flag);return 0;}
            i++;
            para -> SOR = atof(argv[i]);
        }
        else if (flag == "minDepth")
        {
            if(i + 1 == argc) {LogLackArg(flag);return 0;}
            i++;
            para -> minDepth = atof(argv[i]);
        }
        else if (flag == "maxDepth")
        {
            if(i + 1 == argc) {LogLackArg(flag);return 0;}
            i++;
            para -> maxDepth = atof(argv[i]);
        }else if (flag == "size"){
            if(i + 1 == argc) {LogLackArg(flag);return 0;}
            i++;
            para -> size = atoi(argv[i]);
        }else if (flag == "isBed"){
            para ->isBed = true ;
        }else if (flag == "header"){
            if(i + 1 == argc) {LogLackArg(flag);return 0;}
            i++;
            para -> headerC = argv[i];
        }else if (flag == "pos"){
            if(i + 1 == argc) {LogLackArg(flag);return 0;}
            i++;
            vector<string> p;
            split(argv[i], p, " ");
            set<int> po;
            for (int j = 0; j < p.size(); j ++){
                po.insert(atoi(p[j].c_str()));
            }
            (para->pos) = po;
        }
        
        else if (flag == "help"  ||  flag == "h")
        {
            WGS_Help1();return 0;
        }
        else
        {
//            cerr << "UnKnow argument -"<<flag<<endl;
//            return 0;
        }
    }
    if  ( (para -> inFile).empty() ||( (para -> model).empty() &&  (para->type).empty() )  )
    {
        cerr << "lack argument for the must" << endl ;
        return 0;
    }
    
    // suffix and prefix
//    string inFile = (para -> inFile);
//    string ext =inFile.substr(inFile.rfind('.') ==string::npos ? inFile.length() : inFile.rfind('.') + 1);
//    if (ext == "gz")
//    {
//        (para -> inFile) = (para -> inFile).substr(0,(para->inFile).length()-3);
//    }
    
    //    inFile = (para -> inFile);
    //    ext = inFile.substr(inFile.rfind('/') ==string::npos ? inFile.length() : inFile.rfind('/') + 1);
    //
    //    if (ext != "stat")
    //    {
    //        ext =Stat.substr(Stat.rfind('.') ==string::npos ? Stat.length() : Stat.rfind('.') + 1);
    //        if (ext == "stat")
    //        {
    //            (para->InStr2)=(para->InStr2).substr(0,(para->InStr2).length()-5);
    //        }
    //    }
    return 1 ;
}

#endif /* initialization_h */
