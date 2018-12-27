//
//  FileFunctions.h
//  WGS
//
//  Created by Yao Zhou on 2018/12/4.
//  Copyright © 2018 Yao Zhou. All rights reserved.
//

#ifndef FileFunctions_h
#define FileFunctions_h

int Read_VCF_IN(parameter *para, vcf *inVCF)
{
    
    igzstream VCFIN ((para->inFile).c_str(),ifstream::in);
    
    if (VCFIN.fail())
    {
        cerr << "open VCF File IN File error: " << (para->inFile) << endl;
        return  0;
    }
        
    vector<string> inf ;
    vector<string> header;
    
    // read header
    while(!VCFIN.eof()){
        string  line ;
        getline(VCFIN,line);
        if (line.length()<=0 )  {
            continue  ;
        }else if ( line[0] == '#' && line[1] == '#' )  {
            header.push_back(line);
            continue  ;
        }else if ( line[0] == '#' && line[1] != '#' ){
            header.push_back(line);
            inf.clear();
            split(line,inf,"\t");
            if  ( inf[0]  != "#CHROM"){
                continue  ;
            }
            break ;
        }else if ( line[0] != '#' && line[1] != '#' ){
            cerr<<"wrong Line : "<<line<<endl;
            cerr<<"VCF Header same thing wrong, can find sample info before site info"<<endl;
            cerr<<"VCF Header sample info Flag : [  #CHROM  ] "<<endl;
            return  0;
            break;
        }
    }
    int BadSite=0 ;
    int Asample=inf.size();
    int SampleNum=(Asample-9);
    
    // creat map for interested SNPs
    vector<string> Alt ;
    vector<string> Btmp  ;
    int  Base_len ;
    long int Site ;
    int Het_count=0;
    int Miss_count=0;
    int BaseConut=0;
    char best_base='N';
    char sed_base='N';
    int Max=0;
    int SeD=0;
    map <char,int>  :: iterator it ;
    int ERA=0;
    vector<char>  genotype ;
    vector<BaseType>  genotypeVE ;
    
//    if (para->TF2){
//
//            while(!VCFIN.eof())
//            {
//                string  line ;
//                getline(VCFIN,line);
//                if (line.length()<=0)  { continue  ; }
//
//                istringstream isoneLine (line,istringstream::in);
//                for (int iik=0 ; iik<Asample ; iik++)
//                {
//                    isoneLine >> inf[iik];
//                }
//                Base_len=inf[3].length();
//                Alt.clear();
//                split(inf[4],Alt,",");
//
//                for (int ii=0 ; ii<Alt.size() ;ii++)
//                {
//                    if (Alt[ii].length()>Base_len)
//                    {
//                        Base_len=Alt[ii].length();
//                    }
//                }
//
//                if (Base_len>1)
//                {
//                    BadIndelSite++;
//                    continue ;
//                }
//
//                map <char,int > Count ;
//                Het_count=0;
//                Miss_count=0;
//
//                for (int jj=9 ; jj< Asample ;jj++ )
//                {
//                    Btmp.clear();
//                    split(inf[jj], Btmp,":");
//                    string Genotype=Btmp[0];
//                    if (  Genotype[0] == '.' )
//                    {
//                        Miss_count++ ;
//                    }
//                    else
//                    {
//                        if  (Genotype[0] != Genotype[2] )
//                        {
//                            Het_count++;
//                        }
//                        Count[Genotype[0]]++;
//                        Count[Genotype[2]]++;
//                    }
//                }
//
//                if ( ( (Miss_count*1.0/SampleNum)  >(para_18->Miss)  )  )
//                {
//                    continue ;
//                }
//
//                if ( ( (Het_count*1.0/SampleNum)  >(para_18->Het) )  )
//                {
//                    continue ;
//                }
//
//                BaseConut=0;
//                best_base='N';
//                sed_base='N';
//                Max=0;
//                SeD=0;
//
//                for ( it=Count.begin(); it!=Count.end(); it++ )
//                {
//                    if ( (it->first ) == 'N' )
//                    {
//                        continue ;
//                    }
//                    else if ((it->second)  > Max )
//                    {
//                        SeD=Max;
//                        sed_base=best_base;
//                        Max=(it->second);
//                        best_base=it->first;
//                    }
//                    else if ( (it->second)  >= SeD )
//                    {
//                        SeD=(it->second);
//                        sed_base=it->first;
//                    }
//                    BaseConut++;
//                }
//                if (BaseConut==1 || BaseConut >2 )
//                {
//                    BadSite++;
//                    continue ;
//                }
//
//                if ( (SeD*1.0/(SeD+Max))  < (para_18->MAF) )
//                {
//                    continue ;
//                }
//
//                genotype.clear();
//
//                for (int jj=9 ; jj< Asample ;jj++ )
//                {
//                    Btmp.clear();
//                    split(inf[jj], Btmp,":");
//                    string Genotype=Btmp[0];
//                    if (  Genotype[0] == '.' )
//                    {
//                        genotype.push_back('N');
//                        genotype.push_back('N');
//                    }
//                    else
//                    {
//                        if  (Genotype[0] != Genotype[2] )
//                        {
//                            genotype.push_back(best_base);
//                            genotype.push_back(sed_base);
//                        }
//                        else
//                        {
//                            genotype.push_back(Genotype[0]);
//                            genotype.push_back(Genotype[2]);
//                        }
//                    }
//                }
//
//
//
//                genotypeVE.clear();
//
//                BaseType  TypeA;
//
//                ERA=genotype.size();
//
//                for (int hh=0 ; hh<ERA ;hh++)
//                {
//
//                    if (genotype[hh] == best_base  )
//                    {
//                        TypeA.Value=0;
//                    }
//                    else if (genotype[hh] == sed_base )
//                    {
//                        TypeA.Value=1;
//                    }
//                    else
//                    {
//                        TypeA.Value=2;
//                    }
//                    genotypeVE.push_back(TypeA);
//                }
//
//
//
//
//
//                istringstream isone (inf[1],istringstream::in);
//                isone>> Site ;
//
//
//                map <string,map <int, vector <BaseType> > >  :: iterator itSNP=SNPList.find(inf[0]);
//
//                if (itSNP == SNPList.end())
//                {
//                    map <int, vector <BaseType> > DD;
//                    DD[Site]=genotypeVE;
//                    SNPList.insert(map <string,map <int,vector <BaseType> > > ::value_type(inf[0],DD));
//                    Flag_for_pro++;
//                }
//                else
//                {
//                    (itSNP->second).insert(map <int, vector <BaseType> >  :: value_type(Site,genotypeVE)) ;
//                    Flag_for_pro++;
//                }
//            }
//
//
//
//        }
//        else
//        {
//
//            string OUT_VCFTMP=(para->InStr2)+".vcf.filter.gz";
//            ogzstream OUTVCFFF ((OUT_VCFTMP).c_str());
//
//            while(!VCFIN.eof())
//            {
//                string  line ;
//                getline(VCFIN,line);
//                if (line.length()<=0 || line[0] == '#' )  { continue  ; }
//                int Site ;
//                //inf.clear();            split(line,inf," \t");
//                istringstream isoneLine (line,istringstream::in);
//                for (int iik=0 ; iik<Asample ; iik++)
//                {
//                    isoneLine>>inf[iik];
//                }
//                Base_len=inf[3].length();
//                Alt.clear();
//                split(inf[4],Alt,",");
//                for (int ii=0 ; ii<Alt.size() ;ii++)
//                {
//                    if (Alt[ii].length()>Base_len)
//                    {
//                        Base_len=Alt[ii].length();
//                    }
//                }
//
//                if (Base_len>1)
//                {
//                    BadIndelSite++;
//                    continue ;
//                }
//
//                map <char,int > Count;
//                Het_count=0;
//                Miss_count=0;
//
//                for (int jj=9 ; jj< Asample ;jj++)
//                {
//                    Btmp.clear();
//                    split(inf[jj], Btmp,":");
//                    string Genotype=Btmp[0];
//                    if (  Genotype[0]  == '.' )
//                    {
//                        Miss_count++ ;
//                    }
//                    else
//                    {
//                        if  (Genotype[0] != Genotype[2] )
//                        {
//                            Het_count++;
//                        }
//                        Count[Genotype[0]]++;
//                        Count[Genotype[2]]++;
//                    }
//                }
//
//                //            int SampleNum=(Asample-9);
//                if ( ( (Miss_count*1.0/SampleNum)  >(para_18->Miss)  )  )
//                {
//                    continue ;
//                }
//
//                if ( ( (Het_count*1.0/SampleNum)  >(para_18->Het) ) )
//                {
//                    continue ;
//                }
//
//                BaseConut=0;
//                best_base='N';
//                sed_base='N';
//                Max=0;
//                SeD=0;
//
//                for ( it=Count.begin(); it!=Count.end(); it++ )
//                {
//                    if ( (it->first ) == 'N' )
//                    {
//                        continue ;
//                    }
//                    else if ((it->second)  > Max )
//                    {
//                        SeD=Max;
//                        sed_base=best_base;
//                        Max=(it->second);
//                        best_base=it->first;
//                    }
//                    else if ( (it->second)  >= SeD )
//                    {
//                        SeD=(it->second);
//                        sed_base=it->first;
//                    }
//                    BaseConut++;
//                }
//                if (BaseConut==1 || BaseConut >2 )
//                {
//                    BadSite++;
//                    continue ;
//                }
//
//                //if ( (  (1-(Max*1.0/(SeD+Max)))  < (para_18->MAF) )  )
//                if ( (SeD*1.0/(SeD+Max))  < (para_18->MAF) )
//                {
//                    continue ;
//                }
//
//
//                genotype.clear();
//                for (int jj=9 ; jj< Asample ;jj++ )
//                {
//                    Btmp.clear();
//                    split(inf[jj], Btmp,":");
//                    string Genotype=Btmp[0];
//                    if (  Genotype[0] == '.' )
//                    {
//                        genotype.push_back('N');
//                        genotype.push_back('N');
//                    }
//                    else
//                    {
//                        if  (Genotype[0] != Genotype[2] )
//                        {
//                            genotype.push_back(best_base);
//                            genotype.push_back(sed_base);
//                        }
//                        else
//                        {
//                            genotype.push_back(Genotype[0]);
//                            genotype.push_back(Genotype[2]);
//                        }
//                    }
//                }
//
//
//
//                //vector<BaseType>  genotypeVE ;
//                genotypeVE.clear();
//
//                BaseType  TypeA;
//
//                ERA=genotype.size();
//                for (int hh=0 ; hh<ERA ;hh++)
//                {
//                    if (genotype[hh] == best_base  )
//                    {
//                        TypeA.Value=0;
//                    }
//                    else if (genotype[hh] == sed_base )
//                    {
//                        TypeA.Value=1;
//                    }
//                    else
//                    {
//                        TypeA.Value=2;
//                    }
//                    genotypeVE.push_back(TypeA);
//                }
//
//
//                istringstream isone (inf[1],istringstream::in);
//                isone>> Site ;
//
//
//                map <string,map <int, vector <BaseType> > >  :: iterator itSNP=SNPList.find(inf[0]);
//                if (itSNP == SNPList.end())
//                {
//                    map <int, vector <BaseType> > DD;
//                    DD[Site]=genotypeVE;
//                    SNPList.insert(map <string,map <int,vector <BaseType> > > ::value_type(inf[0],DD));
//                    Flag_for_pro++;
//                }
//                else
//                {
//                    (itSNP->second).insert(map <int, vector <BaseType> >  :: value_type(Site,genotypeVE)) ;
//                    Flag_for_pro++;
//                }
//
//                OUTVCFFF<<line<<"\n";
//
//            }
//
//
//            OUTVCFFF.close();
//
//        }
//        VCFIN.close();
//
//        if(BadIndelSite!=0)
//        {
//            cout<<"warning skip Indel site, there are total skip Indel sites number is : "<<BadIndelSite<<endl;
//        }
//        if (BadSite!=0)
//        {
//            cout<<"Warning skip non bi-allelic(Singleton/ThreeMulti allelic) site, and total skip allelic sites number is :"<<BadSite<<endl;
//        }
//
        return 1;
}

int Read_depth_IN(parameter *para, depth *inDepth){
    igzstream DepthIN ((para->inFile).c_str(),ifstream::in);
    igzstream SampleList ((para->subPop).c_str(),ifstream::in);
    igzstream allSample ((para->inFile2).c_str(),ifstream::in);
    if (DepthIN.fail())
    {
        cerr << "open depth File IN File error: " << (para->inFile) << endl;
        return  0;
    }
    if (SampleList.fail())
    {
        cerr << "open sub-samples File IN File error: " << (para->subPop) << endl;
        return  0;
    }
    if (allSample.fail())
    {
        cerr << "open total samples File IN File error: " << (para->inFile2) << endl;
        return  0;
    }
    string outDepth =(para -> outFile)+".depth.passed.gz";
    ogzstream OUT ((outDepth).c_str());
    if((!OUT.good())){
        cerr << "open OUT File error: " << outDepth << endl;
        return  0;
    }
    // prepare the total sample list
    vector< string > sampleVetor;
    while(!allSample.eof())
    {
        string  line ;
        getline(allSample,line);
        if (line.length() <= 0 || line[0] == '#' )  { continue  ; }
        sampleVetor.push_back(line.substr(0,4));
    }
    allSample.close();
    
    //prepare the subpop site
    vector<int> sampleSite;
    int A = sampleVetor.size() ;
    while(!SampleList.eof()){
        string  line ;
        getline(SampleList,line);
        
        if (line.length() <= 0 || line[0] == '#' )  { continue  ; }
        for (int ii = 0 ; ii< A ; ii++){
            if(line == sampleVetor[ii]){
                sampleSite.push_back(ii+2); // get the sample position
            }
        }
    }
    
    if(sampleSite.size() ==0){
        cerr << "sub-sample size is 0! Stopped!" << endl;
        return 0;
    }
    
    // get the sample depth
    vector<string> inf ;
    map <string,map <int, vector <int> > > depthList;
    int subSize = sampleSite.size();
    
//    cout << subSize << endl;
    int passedSNP = 0;
    while(!DepthIN.eof()){
        string line;
        getline(DepthIN,line);
        if (line.length() <= 0  )  { continue  ; }
        inf.clear();
        split(line,inf,"\t");
        vector <int> dep ;
        dep.clear();
        
        int sumDepth = 0;
        for (int iik = 0 ; iik < subSize ; iik++){
            string d = inf[sampleSite[iik]];
            int pos = atoi(d.c_str());
            dep.push_back(pos);
            sumDepth += pos;
        }
        double mind = para->minDepth ;
        double maxd = para->maxDepth ;
        if(sumDepth> mind & sumDepth < maxd){
            passedSNP++;
            OUT << "rs" << inf[0] << "_" << inf[1] << "\n";
        }else{
            continue;
        }
//        cout << sumDepth << endl;
        
//        dep.push_back(sumDepth);
//        map <string,map <int, vector <int> > >  :: iterator it = depthList.find(inf[0]);
//        int pos = atoi(inf[1].c_str());
//        if (it == depthList.end()){
//            map <int, vector <int> > DD;
//            DD[pos] = dep;
//            depthList.insert(map <string,map <int,vector <int> > > ::value_type(inf[0],DD));
////            cout << dep[dep.size()-1] << endl;
//        }else{
////            cout << dep[dep.size()-1] << endl;
//            (it -> second).insert(map <int, vector <int> >  :: value_type(pos,dep)) ;
//        }
    }
    OUT.close();
    cout << "Passed SNP is: " << passedSNP << endl;
//    (inDepth->depthList) = depthList;
    return 1;
}


inline int outDepthFile(parameter *para, depth *inDepth){
    string outDepth =(para -> outFile)+".depth.passed.gz";
    ogzstream OUT ((outDepth).c_str());
    if((!OUT.good())){
        cerr << "open OUT File error: " << outDepth << endl;
        return  0;
    }
    
    map <string, map <int, vector <int> > > depthList = (inDepth->depthList);
    map <string, map <int, vector <int> > >  :: iterator it;
    double minDepth = (para->minDepth);
    double maxDepth = (para->maxDepth);
//    cout << "....." << it->first << " ...." << endl;
    for (it = depthList.begin();  it!=depthList.end();   ++it) {
//        cout << it->first << endl;
        map <int, vector <int> > ::iterator itt;
        map <int, vector <int> > depthVector = (it->second);
        for (itt = depthVector.begin();  itt!=depthVector.end();   ++itt) {
//            cout << itt->first << endl;
            vector<int> dep = itt->second;
            int len = dep.size() - 1;
            if((dep[len] > minDepth) & (dep[len] < maxDepth)){
//                cout << itt->first << endl;
                int pos = itt->first;
                OUT << "rs" << it->first <<"_" << pos << "\n";
            }
        }
    }
    OUT.close();
    return 1;
}

int toBed (parameter *para){
    cout << "toBed..." << endl;
    igzstream DepthIN ((para->inFile).c_str(),ifstream::in);
    if (DepthIN.fail())
    {
        cerr << "open depth File IN File error: " << (para->inFile) << endl;
        return  0;
    }
    string outDepth = (para -> outFile)+".bed";
    ofstream OUT ;
    OUT.open(outDepth.c_str());
    if((!OUT.good())){
        cerr << "open OUT File error: " << outDepth << endl;
        return  0;
    }
    vector<string> inf ;
    int begin = 0;
    int end = 0;
    bool start = true;
    int pre = 0;
    string chr;
    while(!DepthIN.eof()){
        string line;
        getline(DepthIN,line);
        if (line.length() <= 0  )  { continue  ; }
        inf.clear();
        split(line,inf,"_");
        chr = inf[0].substr(2);
        if(start) {
            begin = atoi(inf[1].c_str()) - 1 ;
            pre = begin;
            start = false;
        }
        end = atoi(inf[1].c_str());
        if((end - pre) > 20){
            int len = (pre -begin );
            if( len > 150){
                OUT << chr << "\t" << begin << "\t" << pre << "\t" << len << "\n";
            }
            start = true;
        }
        pre = end;
    }
    if(!start){
        int len = (end - begin);
        if(len > 150){
            OUT << chr << "\t" << begin << "\t" << end << "\t" << len << "\n";
        }
    }
    OUT.close();
    return 1;
}
int changePos(parameter *para){
    cout << "Change file chromosome position..." << endl;
    string input =(para->inFile);
    string ext;
    ext = input.substr(input.rfind('.') ==string::npos ? input.length() : input.rfind('.') + 1);
    //
    if (ext == "gz"){
        igzstream inFile (input.c_str(),ifstream::in);
        if (inFile.fail()){
            cerr << "open File IN error: " << (para->inFile) << endl;
            return  0;
        }
        ifstream posFile(para->inFile2);
        if((!posFile.good())){
            cerr << "open pos File error: " << para->inFile2 << endl;
            return  0;
        }
        string outFile =(para -> outFile);
//    ofstream OUT ((outFile).c_str());
//    cout << ext << endl;
   
        ogzstream OUT ((outFile).c_str());
        if((!OUT.good())){
            cerr << "open OUT File error: " << outFile << endl;
            return  0;
        }
        map<string, vector<string>> pos ;
        string line;
        vector <string> chr;
        while (getline(posFile,line)){
            chr.clear();
            split(line,chr,"\t");
            pos.insert(map <string, vector<string>> :: value_type(chr[0],chr));
        }
        posFile.close();
        string header = (para->headerC);
        int lh = header.length() - 1;
        bool isBed = para->isBed;
        while (!inFile.eof()){
            chr.clear();
            getline(inFile, line);
            if((line.substr(0,lh) == header)) {
                OUT << line << "\n";
            }else {
                chr.clear();
                if(line.size()  < 1) {continue ;};
                split(line,chr,"\t");
                int lchr = chr.size();
                vector<string> info = pos[chr[0]];
                set<int> posChange = (para->pos);
                OUT << info[3];
                for (int iil = 1; iil < lchr; iil ++){
                    OUT << "\t";
                    if(posChange.count(iil) == 1){
                        OUT << (atoi(chr[iil].c_str()) + atoi(info[4].c_str()));
                    }else{
                        OUT << chr[iil];
                    }
                }
            }
            OUT << "\n";
        }
        inFile.close();
        OUT.close();
    }else{
        ifstream inFile (input.c_str());
        if (inFile.fail())
        {
            cerr << "open File IN error: " << (para->inFile) << endl;
            return  0;
        }
        ifstream posFile(para->inFile2);
        if((!posFile.good())){
            cerr << "open pos File error: " << para->inFile2 << endl;
            return  0;
        }
        string outFile =(para -> outFile);
        ofstream  OUT((outFile).c_str());
        if((!OUT.good())){
            cerr << "open OUT File error: " << outFile << endl;
            return  0;
        }
        map<string, vector<string>> pos ;
        string line;
        vector <string> chr;
        while (getline(posFile,line)){
            chr.clear();
            split(line,chr,"\t");
            pos.insert(map <string, vector<string>> :: value_type(chr[0],chr));
        }
        posFile.close();
        string header = (para->headerC);
        int lh = header.length();
        bool isBed = para->isBed;
        while (!inFile.eof()){
            chr.clear();
            getline(inFile, line);
//            cout << "testing ..." << endl;
//            cout << line.substr(0,3) << endl;
            if((line.substr(0,lh) == header)) {
                OUT << line ;
            }else {
                chr.clear();
                if(line.size()  < 1) {continue ;};
                split(line,chr,"\t");
                lint lchr = chr.size();
                vector<string> info = pos[chr[0]];
                set<int> posChange = (para->pos);
                OUT << info[3];
                for (int iil = 1; iil < lchr; iil ++){
                    OUT << "\t";
                    if(posChange.count(iil) == 1){
                        OUT << (atoi(chr[iil].c_str()) + stoi(info[4].c_str()));
                    }else{
                        OUT << chr[iil];
                    }
                }
            }
            OUT << "\n";
        }
        inFile.close();
        OUT.close();
    }
    return 1;
}

int count(parameter *para){
    string input =(para->inFile);
//    string ext;
//    ext = input.substr(input.rfind('.') ==string::npos ? input.length() : input.rfind('.') + 1);
//    //
    igzstream inFile (input.c_str(),ifstream::in);
    if (inFile.fail()){
        cerr << "open File IN error: " << (para->inFile) << endl;
        return  0;
    }
    
    
    int line = 0;
    string l;
    while (!inFile.eof()){
        getline(inFile,l,'\n');
        line++;
//        if( line > 10000) break;
    }
    inFile.close();
    cout << line << endl;
    return 1;
}
int mergeDepth(parameter *para){
    string input1 = (para->inFile);
    string input2 = (para->inFile2);
    igzstream f1 (input1.c_str(),ifstream::in);
    igzstream f2 (input1.c_str(),ifstream::in);
    if(f1.fail()){
        cerr << "open File IN error: " << input1 << endl;
        return 0;
    }
    if(f2.fail()){
        cerr << "open File IN error: " << input2 << endl;
        return 0;
    }
    
    string outFile =(para -> outFile);
    ofstream  OUT((outFile).c_str());
    if((!OUT.good())){
        cerr << "open OUT File error: " << outFile << endl;
        return  0;
    }
    
    string l1, l2;
    vector < string >  ll2;
    
    while(!f1.eof()&&!f2.eof()){
        getline(f1,l1);
        getline(f2,l2);
        ll2.clear();
        split(l2,ll2,"\t");
        OUT << l1;
        
        for(int i = 2; i < ll2.size(); i++){
        
            OUT << " \t";
            OUT << ll2[i];
        }
        OUT << "\n";
    }
    cout << ll2.size()  << endl;
    f1.close();
    f2.close();
    OUT.close();
    return 1;
}
int randChoose(parameter *para){
    double r = 0.0001;
    string input1 = (para->inFile);
    igzstream f1 (input1.c_str(),ifstream::in);
    if(f1.fail()){
        cerr << "open File IN error: " << input1 << endl;
        return 0;
    }
    
    string outFile =(para -> outFile);
    ofstream  OUT((outFile).c_str());
    if((!OUT.good())){
        cerr << "open OUT File error: " << outFile << endl;
        return  0;
    }
    
    string l;
    while(!f1.eof()){
        getline(f1,l);
        if(rand()/ double(RAND_MAX) < r){
            OUT << l;
            OUT << "\n";
        }
    }
    f1.close();
    OUT.close();
    return 1;
}
    
#endif /* FileFunctions_h */
