//
//  FileFunctions.h
//  WGS
//
//  Created by Yao Zhou on 2018/12/4.
//  Copyright © 2018 Yao Zhou. All rights reserved.
//

#ifndef FileFunctions_h
#define FileFunctions_h
using namespace std;
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
    
//    while(!VCFIN.eof()){
//        string  line ;
//        getline(VCFIN,line);
//        if (line.length()<=0)  { continue  ; }
//        istringstream isoneLine (line,istringstream::in);
//        for (int iik=0 ; iik<Asample ; iik++){
//            isoneLine >> inf[iik];
//        }
//        Base_len=inf[3].length();
//        Alt.clear();
//        split(inf[4],Alt,",");
//        for (int ii=0 ; ii<Alt.size() ;ii++){
//            if (Alt[ii].length()>Base_len){
//                Base_len=Alt[ii].length();
//            }
//        }
//        if (Base_len>1){
//            BadIndelSite++;
//            continue ;
//        }
//        map <char,int > Count ;
//        Het_count=0;
//        Miss_count=0;
//        for (int jj=9 ; jj< Asample ;jj++ ){
//            Btmp.clear();
//            split(inf[jj], Btmp,":");
//            string Genotype=Btmp[0];
//            if ( Genotype[0] == '.' ){
//                Miss_count++ ;
//            } else{
//              if  (Genotype[0] != Genotype[2] )
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

int toBedold (parameter *para){
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

int Depth2Bed(parameter *para){
    int binSize = para->size;
    igzstream inF ((para->inFile).c_str(),ifstream::in);
    if(inF.fail()){
        cerr << "Open file error: " << (para->inFile) << endl;
        return 0;
    }
    ofstream ouf ((para -> outFile).c_str());
    if(ouf.fail()){
        cerr << "Couldn't open outFile" << endl;
        return 0;
    }
    string line;
    vector < string > ll;
    lint startPos = 1;
    lint count = 0;
    int BinRound = 1;
    lint endPos = 1;
    while(!inF.eof()){
        getline(inF, line);
        if(line.length()<1) continue;
        ll.clear();
        split(line,ll,"\t");
        startPos = string2Int(ll[1]);
        
        while(string2Int(ll[1]) > BinRound*binSize){
            endPos = BinRound*binSize;
            startPos = (BinRound-1)*binSize +1;
            ouf << ll[0] << "\t" << startPos << "\t" << endPos << "\t" << count << "\n" ;
            ++BinRound;
            count = 0;
        }
        ++count;
    }
    if(count > 0){
        endPos = string2Int(ll[1])+1;
        startPos = (BinRound-1)*binSize +1;
        ouf << ll[0] << "\t" << startPos << "\t" << endPos << "\t" << count << "\n" ;
    }
    inF.close();
    ouf.close();
    return 1;
}
int pi2bed(parameter *para){
    int binSize = para->size;
    igzstream inF ((para->inFile).c_str(),ifstream::in);
    igzstream inbed ((para->inFile2).c_str(),ifstream::in);
    if(inF.fail()){
        cerr << "Open file error: " << (para->inFile) << endl;
        return 0;
    }
    if(inbed.fail()){
        cerr << "Open file error: " << (para->inFile2) << endl;
        return 0;
    }
    ofstream ouf ((para -> outFile).c_str());
    if(ouf.fail()){
        cerr << "Couldn't open outFile" << endl;
        return 0;
    }
    string line;
    vector < string > ll;
    lint startPos = 1;
    int BinRound = 1;
    lint endPos = 1;
    map<string,int> binNum;
    while(!inbed.eof()){
        getline(inbed,line);
        if(line.length() < 3) continue;
        
        ll.clear();
        split(line,ll,"\t");
        binNum.insert(map <string, int> :: value_type(ll[0]+"_"+ll[1],string2Int(ll[3])));
    }
    inbed.close();
//    cout << ll[0]+"_"+ll[1] << endl;
//    cout << binNum["9_453000001"] << endl;
    map<string,int>::iterator it;
    double pi = 0.0;
    int prePos = 0;
    while(!inF.eof()){
        getline(inF, line);
        if(line.length()<1) continue;
        if(line[0]=='C') continue;
        ll.clear();
        split(line,ll," \t");
        int current_pos = string2Int(ll[1]);
        if(prePos > current_pos ) {
            BinRound = 1;
        }
        while(current_pos > BinRound * binSize){
            endPos = BinRound * binSize;
            startPos = (BinRound-1) * binSize + 1;
            it = binNum.find(ll[0] + "_" + to_string(startPos));
            ++BinRound;
            if(it != binNum.end()){
                int n = binNum[ll[0] + "_" + to_string(startPos)];
                if(n == 0) continue;
                ouf << ll[0] << "\t" << startPos << "\t" << endPos << "\t" << pi/n << "\n" ;
                pi = 0;
            }
            prePos = current_pos;
        }
        
        if(ll[2]=="-nan"||ll[2]=="NA"||ll[2]=="inf") ll[2] = '0';
        pi += string2Double(ll[2]);
    }
    if(pi > 0){
        endPos = string2Int(ll[1]);
        startPos = (BinRound-1)*binSize +1;
        int n = binNum[ll[0]+"_"+to_string(startPos)];
        if(n!=0) {
             ouf << ll[0] << "\t" << startPos << "\t" << endPos << "\t" << pi/n << "\n" ;
        }
    }
    inF.close();
    ouf.close();
    return 1;
}

int pi(parameter *para){
    //site pi
    igzstream inF ((para->inFile).c_str(),ifstream::in);
    igzstream subFile ((para->inFile2).c_str(),ifstream::in);
    if(inF.fail()){
        cerr << "Open file error: " << (para->inFile) << endl;
        return 0;
    }
    if(subFile.fail()){
        cerr << "Open file error: " << (para->inFile2) << endl;
        return 0;
    }
    ofstream ouf ((para -> outFile).c_str());
    if(ouf.fail()){
        cerr << "Couldn't open outFile" << endl;
        return 0;
    }
    string line;
    vector < string > ll;
    set <string> Samples;
    vector<int> samplePos;
    while(!subFile.eof()){
        getline(subFile,line);
        if(line.length()<1) continue;
        Samples.insert(line);
    }
    subFile.close();
//    set<string>::iterator it;
//    for(it = Samples.begin() ; it != Samples.end() ; ++it){
//                    cout<<*it<<endl;
//    }
    while(!inF.eof()){
        double a = 0, b= 0,c=0;
        int sampleSize = 0;
        getline(inF,line);
        if(line[0]=='#' && line[1]=='#') continue;
        if(line[0] == '#' && line[1] == 'C'){
//            set<int>::iterator it;
            ll.clear();
            split(line,ll,"\t");
            for(int i = 9; i < ll.size(); ++i){
                if(Samples.count(ll[i])==1) {
                    samplePos.push_back(i);
//                    cout << ll[i] << endl;
                }
            }
            continue;
        }
        if(line.length()<1) continue;
        ll.clear();
        split(line,ll,"\t");
        for(int i = 0; i< samplePos.size() ;++i){
            if(ll[samplePos[i]][0] == '0' && ll[samplePos[i]][2] == '0'){
                ++a;
                sampleSize++;
            }else if(ll[samplePos[i]][0]== '1' && ll[samplePos[i]][2] == '1'){
                ++b;
                sampleSize++;
//            }else if(ll[samplePos[i]][0]== '0' && ll[samplePos[i]][2] == '1'){
//                ++c;
//                sampleSize++;
            }else{
                continue;
            }
        }
        double pi = 2*(a+b)/(sampleSize*(sampleSize-1));
        ouf << ll[0] << "\t" << ll[1] << "\t" << pi << endl;
    }
    inF.close();
    ouf.close();
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
            if((line.substr(0,lh) == header) | line[0] == '#') {
                OUT << line ;
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

int chr2num(parameter *para){
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
            if((line.substr(0,lh) == header) | line[0] == '#') {
                OUT << line ;
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
//    string input3 = (para -> bedFile);
    igzstream f1 (input1.c_str(),ifstream::in);
    igzstream f2 (input2.c_str(),ifstream::in);
//    igzstream f3 (input3.c_str(),ifstream::in);
    if(f1.fail()){
        cerr << "open File IN error: " << input1 << endl;
        return 0;
    }
    if(f2.fail()){
        cerr << "open File IN error: " << input2 << endl;
        return 0;
    }
//    if(f2.fail()){
//        cerr << "open File IN error: " << input2 << endl;
//        return 0;
//    }
    
    string outFile =(para -> outFile);
    ogzstream  OUT((outFile).c_str());
    if((!OUT.good())){
        cerr << "open OUT File error: " << outFile << endl;
        return  0;
    }
    
    string l1, l2;
    vector < string >  ll2;
    
    while(!f1.eof()&&!f2.eof()){
        getline(f1,l1);
        getline(f2,l2);
        OUT << l1;
        OUT << "\t";
        OUT << l2;
//        cout << ll2.size() <<endl;
        for(int i = 2; i < ll2.size(); i++){
            OUT << "\t";
            OUT << ll2[i];
        }
        OUT << "\n";
    }
//    cout << ll2.size()  << endl;
    f1.close();
    f2.close();
    OUT.close();
    return 1;
}

int filterDepth3(parameter *para){
    string input1 = (para->inFile);
    string input2 = (para->inFile2);
    string input3 = (para -> inFile3);
    igzstream f1 (input1.c_str(),ifstream::in);
    igzstream f2 (input2.c_str(),ifstream::in);
    igzstream f3 (input3.c_str(),ifstream::in);
    if(f1.fail()){
        cerr << "open File IN error: " << input1 << endl;
        return 0;
    }
    if(f2.fail()){
        cerr << "open File IN error: " << input2 << endl;
        return 0;
    }
    if(f3.fail()){
        cerr << "open File IN error: " << input3 << endl;
        return 0;
    }
//    cout << input1 << endl;
//    cout << input2 << endl;
//    cout << input3 << endl;
    string outFile =(para -> outFile);
    ofstream  OUT((outFile).c_str());
    if((!OUT.good())){
        cerr << "open OUT File error: " << outFile << endl;
        return  0;
    }
    ofstream log((para->outFile+".log").c_str());
    if((!log.good())){
        cerr << "open log File error" << endl;
        return  0;
    }
    string l1, l2,l3;
    vector < string >  ll1,ll2,ll3;
    vector <double> ll;
    int j = 0;
    while(!f1.eof()&&!f2.eof()&&!f3.eof()){
        getline(f1,l1);
        getline(f2,l2);
        getline(f3,l3);
        ll1.clear();
        ll2.clear();
        ll3.clear();
        ll.clear();
        split(l1, ll1,"\t");
        split(l2, ll2,"\t");
        split(l3, ll3,"\t");

        for(int i = 2, len = ll1.size(); i < len ; ++i){
            ll.push_back(string2Double(ll1[i]));
        }
        for(int i = 2, len = ll2.size(); i < len ; ++i){
           ll.push_back(string2Double(ll2[i]));
        }
        for(int i = 2, len = ll3.size(); i < len ; ++i){
           ll.push_back(string2Double(ll3[i]));
        }
        
//        cout << ll.size() << endl;
//        for(int a = 250; a < 272;a++){
//            cout<< ll[a] << "\t";
//        }
//        cout << "\n" << endl;
        bool pass = depthTest(ll,para->a,para->b,para->minDepth,para-> maxDepth,para->depthSD);
        if(pass){
            j++;
            OUT << ll1[0];
            OUT << "\t";
            OUT << ll1[1];
            OUT << "\n";
        }
//        if(lineNum % 100 ==0){
//            cout << lineNum << endl;
//        }
        
    }
    cout << para->logFile << endl;
    log << "passed sites is: " << j ;
    f1.close();
    f2.close();
    f3.close();
    OUT.close();
    log.close();
    return 1;
}

int filterDepth_bySimulation3(parameter *para){
    string input1 = (para->inFile);
    string input2 = (para->inFile2);
    string input3 = (para -> inFile3);
    double mean = (para -> mean);
    igzstream f1 (input1.c_str(),ifstream::in);
    igzstream f2 (input2.c_str(),ifstream::in);
    igzstream f3 (input3.c_str(),ifstream::in);
    if(f1.fail()){
        cerr << "open File IN error: " << input1 << endl;
        return 0;
    }
    if(f2.fail()){
        cerr << "open File IN error: " << input2 << endl;
        return 0;
    }
    if(f3.fail()){
        cerr << "open File IN error: " << input3 << endl;
        return 0;
    }
    
    string outFile =(para -> outFile);
    ofstream  OUT((outFile).c_str());
    if((!OUT.good())){
        cerr << "open OUT File error: " << outFile << endl;
        return  0;
    }
    ofstream log((para->outFile+".log").c_str());
    if((!log.good())){
        cerr << "open log File error" << endl;
        return  0;
    }
    string l1, l2,l3;
    vector < string >  ll1,ll2,ll3;
    vector <double> ll;
    int j = 0;
    map <int,vector<double>> dmm ;
    bool first = true;
    while(!f1.eof()&&!f2.eof()&&!f3.eof()){
        getline(f1,l1);
        getline(f2,l2);
        getline(f3,l3);
        ll1.clear();
        ll2.clear();
        ll3.clear();
        ll.clear();
        split(l1, ll1,"\t");
        split(l2, ll2,"\t");
        split(l3, ll3,"\t");
        
        for(int i = 2, len = ll1.size(); i < len ; ++i){
            ll.push_back(string2Double(ll1[i]));
        }
        for(int i = 2, len = ll2.size(); i < len ; ++i){
            ll.push_back(string2Double(ll2[i]));
        }
        for(int i = 2, len = ll3.size(); i < len ; ++i){
            ll.push_back(string2Double(ll3[i]));
        }
        if(first){
            cout << "simulation process: start" <<endl;
            dmm = depth_min_max (ll.size(),mean);
            first = false;
            cout << "simulation process: end" <<endl;
        }
        bool pass = depthFilter(ll,dmm);
        if(pass){
            j++;
            OUT << ll1[0];
            OUT << "\t";
            OUT << ll1[1];
            OUT << "\n";
        }
    }
    cout << para->logFile << endl;
    log << "passed sites is: " << j ;
    f1.close();
    f2.close();
    f3.close();
    OUT.close();
    log.close();
    return 1;
}

int filterDepth2(parameter *para){
    string input1 = (para->inFile);
    string input2 = (para->inFile2);
    igzstream f1 (input1.c_str(),ifstream::in);
    igzstream f2 (input2.c_str(),ifstream::in);
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
    ofstream log((para->outFile+".log").c_str());
    if((!OUT.good())){
        cerr << "open OUT File error: " << outFile << endl;
        return  0;
    }
    if((!log.good())){
        cerr << "open log File error" << endl;
        return  0;
    }
    
    string l1, l2;
    vector < string >  ll1,ll2;
    vector <double> ll;
    int j = 0;
    while(!f1.eof()&&!f2.eof()){
        getline(f1,l1);
        getline(f2,l2);
        ll1.clear();
        ll2.clear();
        ll.clear();
        split(l1, ll1,"\t");
        split(l2, ll2,"\t");
        for(int i = 2, len = ll1.size(); i < len ; ++i){
            ll.push_back(string2Double(ll1[i]));
        }
        for(int i = 2, len = ll2.size(); i < len ; ++i){
            ll.push_back(string2Double(ll2[i]));
        }
        bool pass =depthTest(ll,para->a,para->b,para->minDepth,para-> maxDepth,para->depthSD);
        if(pass){
            j++;
            OUT << ll1[0];
            OUT << "\t";
            OUT << ll1[1];
            OUT << "\n";
        }
    }
    
    log << "passed sites is: " << j  ;
    f1.close();
    f2.close();
    OUT.close();
    log.close();
    return 1;
}
int filterDepth_bySimulation2(parameter *para){
    string input1 = (para->inFile);
    string input2 = (para->inFile2);
    double mean = (para->mean);
    igzstream f1 (input1.c_str(),ifstream::in);
    igzstream f2 (input2.c_str(),ifstream::in);
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
    ofstream log((para->outFile+".log").c_str());
    if((!OUT.good())){
        cerr << "open OUT File error: " << outFile << endl;
        return  0;
    }
    if((!log.good())){
        cerr << "open log File error" << endl;
        return  0;
    }
    
    string l1, l2;
    vector < string >  ll1,ll2;
    vector <double> ll;
    int j = 0;
    map <int,vector<double>> dmm ;
    bool first = true;
    while(!f1.eof()&&!f2.eof()){
        getline(f1,l1);
        getline(f2,l2);
        ll1.clear();
        ll2.clear();
        ll.clear();
        split(l1, ll1,"\t");
        split(l2, ll2,"\t");
        for(int i = 2, len = ll1.size(); i < len ; ++i){
            ll.push_back(string2Double(ll1[i]));
        }
        for(int i = 2, len = ll2.size(); i < len ; ++i){
            ll.push_back(string2Double(ll2[i]));
        }
        if(first){
            cout << "simulation process: start" << endl;
            dmm = depth_min_max (ll.size(),mean);
            first = false;
            cout << dmm[400][1] << endl;
            cout << dmm[400][0]<< endl;
            cout << "simulation process: end" << endl;
        }
        bool pass = depthFilter(ll,dmm);
        if(pass){
            j++;
            OUT << ll1[0];
            OUT << "\t";
            OUT << ll1[1];
            OUT << "\n";
        }
    }
    
    log << "passed sites is: " << j  ;
    f1.close();
    f2.close();
    OUT.close();
    log.close();
    return 1;
}
int randChoose(parameter *para){
    double r = (para->r);
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
    double ra = 1 /double(RAND_MAX) ;
    int chosed = 0;
    while(!f1.eof()){
        getline(f1,l);
        if(l.length()<1) continue;
        if(l[0]=='#') {
            OUT << l ;
            OUT << "\n";
            continue;
        };
        if(rand() * ra < r){
            OUT << l;
            OUT << "\n";
            ++chosed;
        }
    }
    f1.close();
    OUT.close();
    cout << "chosen number is: " << chosed << endl;
    return 1;
}

int intersectFile(parameter *para){
    /* Object: intersect file, if the position in File2 are also contained in File1
     output the content in file2
     */
    string input1 = (para->inFile);
    string input2 = (para->inFile2);
    igzstream f1 (input1.c_str(),ifstream::in);
    if(f1.fail()){
        cerr << "open File IN error: " << input1 << endl;
        return 0;
    }
    igzstream f2 (input2.c_str(),ifstream::in);
    if(f1.fail()){
        cerr << "open File IN error: " << input2 << endl;
        return 0;
    }
    string outFile =(para -> outFile);
    ogzstream  OUT((outFile).c_str());
    
    string logFile =(para -> outFile) + ".log";
    ofstream log ((logFile).c_str());
    set < string > pos;
    string l1;
    vector<string> ll1;
    while(!f1.eof()){
        getline(f1, l1);
        if(l1.length() < 1) continue;
        ll1.clear();
        split(l1,ll1,"\t");
        pos.insert(ll1[0]+"_"+ll1[1]);
    }
    f1.close();
    int lineNum = 0;
    while(!f2.eof()){
        getline(f2, l1);
        if(l1.length() < 1) continue;
        if(l1[0] == '#'){
            if(para->recode){
                OUT << l1;
                OUT << "\n";
            }
        }else{
            ll1.clear();
            split(l1, ll1,"\t");
            if(pos.count(ll1[0]+"_"+ll1[1])==1){
                ++lineNum;
                if(para->recode){
                    OUT << l1;
                    OUT << "\n";
                }
            }
        }
    }
    log << "SNP number is: " << lineNum << "\n";
    log.close();
    f2.close();
    OUT.close();
    return 1;
}
int getPos(parameter *para){
    string input1 = (para->inFile);
    string output2 = (para->inFile2);
    string output = (para->outFile);
    igzstream f1 (input1.c_str(),ifstream::in);
    if(f1.fail()){
        cerr << "open File IN error: " << input1 << endl;
        return 0;
    }
    ofstream outf (output.c_str());
    if(outf.fail()){
        cerr << "open File IN error: " << output << endl;
        return 0;
    }
    ofstream outf2 (output2.c_str());
    if(outf.fail()){
        cerr << "open File IN error: " << output2 << endl;
        return 0;
    }
    string line;
    vector <string> ll;
    outf << "Chr\t" << "Pos\t" << "Ref\t" << "Alt\n";
    while(!f1.eof()){
        getline(f1,line);
        if(line.length()<1) continue;
        if(line[0]=='#') continue;
        ll.clear();
        split(line,ll,"\t");
        outf << ll[0] << "\t" << ll[1] << "\t" << ll[3] << "\t" << ll[4] << "\n";
        outf2 << ll[0] << "\t" << ll[1] << "\n";
    }
    f1.close();
    outf.close();
    outf2.close();
    return 1;
}
int calibarate(parameter *para){
    string input1 = (para->inFile);
    igzstream f1 (input1.c_str(),ifstream::in);
    if(f1.fail()){
        cerr << "open File IN error: " << input1 << endl;
        return 0;
    }
    vector <string> taxa ;
    vector <string> ll;
    string line;
    string outfile = (para->outFile);
    ogzstream OUT (outfile.c_str());
    if(OUT.fail()){
        cerr << "Open File out error" << outfile << endl;
        return 0;
    }
    int passed = 0;
    while(!f1.eof()){
        getline(f1,line);
        if(line.length()<1) continue;
        if(line[0]=='#') {
            OUT << line ;
            OUT << "\n";
            continue;
        };
        ll.clear();
        split(line,ll,"\t");
        if(ll[ll.size()-1][0] == '.'){
            continue;
        }
        if(ll[ll.size()-1][0] == '0'){
            continue;
        }
        ++passed;
        OUT << line ;
        OUT << "\n";
    }
    cout << "passed number is: " << passed << endl;
    OUT.close();
    f1.close();
    return 1;
}

int calibarate2(parameter *para){
    string input1 = (para->inFile);
    string input2 = (para->inFile2);
    igzstream f2 (input2.c_str(),ifstream::in);
    igzstream f1 (input1.c_str(),ifstream::in);
    if(f1.fail()){
        cerr << "open File IN error: " << input1 << endl;
        return 0;
    }
    if(f2.fail()){
        cerr << "open File2 IN error: " << input2 << endl;
        return 0;
    }
    vector <string> taxa ;
    vector <string> ll;
    string line;
    string outfile = (para->outFile);
    ogzstream OUT (outfile.c_str());
    if(OUT.fail()){
        cerr << "Open File out error" << outfile << endl;
        return 0;
    }
    set <string> pos;
    while(!f2.eof()){
        getline(f2,line);
        if(line.length()<1) continue;
        ll.clear();
        split(line,ll,"\t");
        pos.insert(ll[0]);
    }
    int passed = 0;
    while(!f1.eof()){
        getline(f1,line);
        if(line.length()<1) continue;
        if(line[0]=='#') {
            OUT << line ;
            OUT << "\t" << "barley";
            OUT << "\n";
            continue;
        };
        ll.clear();
        split(line,ll,"\t");
        if(ll.size()<2) continue;
        if(pos.count(ll[1])!=1) continue;
        ++passed;
        OUT << line ;
        OUT << "\t" << "1/1:0,10:0,0,100";
        OUT << "\n";
    }
    cout << "passed number is: " << passed << endl;
    OUT.close();
    f1.close();
    return 1;
}

int toFasta(parameter *para){
    string inFile1 = (para->inFile);
    string outFile = (para->outFile);
    
    return 1;
}

int getV8(parameter *para){
    string inFile1 = (para -> inFile); // file of scanned
    string inFile2 = (para -> inFile2); // file of V6
    igzstream inf1 (inFile1.c_str(),fstream::in);
    igzstream inf2 (inFile2.c_str(),fstream::in);
    if(inf1.fail()){
        cerr << "Couldn't open file: " << inFile1 << endl;
    }
    if(inf2.fail()){
        cerr << "Couldn't open file: " << inFile2 << endl;
        return 0;
    }
    string outFile = (para->outFile);
    ofstream ouf (outFile.c_str());
    if(ouf.fail()){
        cerr << "Couldn't open file: " << outFile << endl;
        return 0;
    }
    string line1;
    string line2;
    vector <string> ll1, ll2;
    map <string,int> name;
    vector<int> replace_pos;
    while(!inf1.eof()){
        getline(inf1, line1);
        if(line1[0]=='#' && line1[1] == 'C') {
            ll1.clear();
            split(line1,ll1,"\t");
            for(int i = 0 ; i < ll1.size(); ++i){
                name.insert(std::pair<string, int>(ll1[i],i));
            }
            ouf << line1 << "\n" ;
            break;
        }else{
            ouf << line1 << "\n";
        }
    }
    while(!inf2.eof()){
        getline(inf2,line2);
        if(line2[0]=='#' && line2[1] == 'C') {
            ll2.clear();
            split(line2,ll2,"\t");
            for (int i = 0; i < ll2.size(); ++i){
                if(name.count(ll2[i]) < 1){
//                    cerr << "Names in file2 are not present in file1:" << ll2[i] << endl;
                    replace_pos.push_back(-1);
//                    return 0;
                }else{
                    replace_pos.push_back(name[ll2[i]]);
                }
            }
            break;
        }
    }
//    for(int i = 0 ; i < replace_pos.size(); ++i){
//        cout << replace_pos[i] << endl;
//    }
    vector <string> geno;
    while(!inf1.eof() && !inf2.eof()){
        getline(inf1,line1);
        getline(inf2, line2);
        if(line1.length()<1) continue;
        if(line2.length()<1) continue;
        ll1.clear();
        ll2.clear();
        split(line1,ll1,"\t");
        split(line2,ll2,"\t");
        if(ll1[1]!=ll2[1]) {
            cout << line1 << endl;
            cout << line2 << endl;
            cerr << "input files are not mactch!" << endl;
            return 0;
        }
        
        for (int i = 9 ; i < ll2.size(); ++i){
            if(replace_pos[i]<0) continue;
            if(ll2[i][0] == '.'){
                ll2[i] = "./.";
            }else{
                geno.clear();
                split(ll2[i],geno,":");
                
                ll2[i] = geno[0]+":"+geno[1]+":"+geno[geno.size()-1];
            }
            
            ll1[replace_pos[i]] = ll2[i];
        }
        for (int i = 0; i < ll1.size() - 1; ++i){
            ouf << ll1[i] << "\t" ;
        }
        ouf << ll1[ll1.size()-1] << "\n";
    }
    inf1.close();
    inf2.close();
    ouf.close();
    return 1;
}

int Q2CLUMPP(parameter *para){
    string inFile = (para ->inFile);
    igzstream inf ((inFile.c_str()),fstream::in);
    if(inf.fail()){
        cerr << "Couldn't open inFile" << endl;
        return 0;
    }
    string outFile = (para ->outFile);
    ofstream ouf (outFile.c_str());
    string line;
    vector <string> ll;
    int i = 1;
    while (!inf.eof()){
        getline(inf,line);
        if(line.length()<1) continue;
        ll.clear();
        split(line,ll," ");
        ouf << i << "\t" << i << "\t" << "(x)\t1\t:";
        for (int j = 0; j < ll.size(); ++j){
            ouf << "\t" << ll[j];
        }
        ++i;
        ouf << endl;
    }
    inf.close();
    ouf.close();
    return 1;
}
int CLUMPP2R(parameter *para){
    string inFile = (para->inFile);
    igzstream inf ((inFile.c_str()),fstream::in);
    if(inf.fail()){
        cerr << "Couldn't open inFile" << endl;
        return 0;
    }
    ofstream ouf ((para->outFile).c_str());
    if(ouf.fail()){
        cerr << "Couldn't opne outFile" << endl;
        return 1;
    }
    string line;
    vector <string> ll;
    while(!inf.eof()){
        getline(inf,line);
        if(line.length() < 1) continue;
        ll.clear();
        split(line,ll," \t");
        ouf << ll[5];
        for (int i = 6; i < ll.size(); ++i){
            ouf << "\t" << ll[i] ;
        }
        ouf << endl;
    }
    inf.close();
    ouf.close();
    return 1;
}
int getHeader(parameter *para){
    string inFile = (para->inFile);
    igzstream   inf ((inFile.c_str()),fstream::in);
    if(inf.fail()){
        cerr << "Couldn't open inFile" << endl;
        return 0 ;
    }
    ofstream ouf ((para->outFile).c_str());
    string line;
    vector <string> ll;
    int order = 0;
    while(!inf.eof()){
        getline(inf,line);
        if(line.length() < 1) continue;
        if(line[0] == '#' && line[1] == 'C'){
            split(line, ll,"\t");
            for (int i = 9 ; i < ll.size(); ++i){
                ++order;
                ouf << order << "\t";
                ouf << ll[i] << endl;
            }
            break;
        }
       
    }
    inf.close();
    ouf.close();
    return 1;
}
int changePhy (parameter *para){
    string inFile = (para->inFile);
    igzstream inf ((inFile.c_str()),fstream::in);
    if(inf.fail()){
        cerr << "Couldn't open inFile" << endl;
        return 0 ;
    }
    ofstream ouf ((para->outFile).c_str());
    string line;
    vector <string> ll;
    while(!inf.eof()){
        getline(inf,line);
        if(line.length() < 1) continue;
        ll.clear();
        ouf << line <<endl;
    }
    inf.close();
    ouf.close();
    return 1;
}
int fasta2Phylip(parameter *para){
    string inFile = (para->inFile);
    igzstream inf ((inFile.c_str()),fstream::in);
    if(inf.fail()){
        cerr << "Couldn't open inFile" << endl;
        return 0 ;
    }
    ofstream ouf ((para->outFile).c_str());
    string line;
    vector <string> ll;
    vector <string> names;
    vector <string> seqs;
    return 1;
}
int readCDS(parameter *para){
    
    return 1;
}
int getMaximum(parameter *para){
    double m = 0;
    string inFile = (para->inFile);
    igzstream inf ((inFile.c_str()),fstream::in);
    if(inf.fail()){
        cerr << "Couldn't open inFile" << endl;
        return 0 ;
    }
    ofstream ouf ((para->outFile).c_str());
    string line;
    vector<string> ll;
    set<int> pos = (para->pos);
    int pos1 = *pos.begin();
    vector<double> value;
   
    while(!inf.eof()){
        getline(inf,line);
        if(line.length()<1) continue;
        ll.clear();
        split(line,ll," \t");
        if(ll[pos1]=="inf"||ll[pos1]=="Inf"||ll[pos1]=="NA"||ll[pos1]=="NaN"||ll[pos1]=="-nan"||ll[pos1] == "nan") continue;
        value.push_back(string2Double(ll[pos1]));
    }
    sort(value.begin(),value.end());
    double mean = avg(value);
    int c95 = value.size()*0.95;
    int c99 = value.size()*0.99;
    int c999 = value.size()*0.999;
    ouf << mean << "\t" << value[c95] << "\t" << value[c99] << "\t" << value[c999] << "\t" << value[value.size()-1] << "\n";
    inf.close();
    ouf.close();
    return 1;
}
int pwpd(parameter *para){
    string inFile = (para->inFile);
    string inFile2 = (para->inFile2);
    string outFile = (para->outFile);
    igzstream inf ((inFile.c_str()),fstream::in);
    igzstream inf2  ((inFile2.c_str()),fstream::in);
    ofstream ouf ((outFile.c_str()));
    if(inf.fail()){
        cerr << "Couldn't open inFile" << endl;
        return 0 ;
    }
    if(inf2.fail()){
        cerr << "Couldn't open inFile2" << endl;
        return 0 ;
    }
    if(ouf.fail()){
        cerr << "Couldn't open outFile" << endl;
        return 0 ;
    }
    string line,line2;
    vector<string> ll,ll2;
    string header = (para->headerC);
    int lh = header.length();
   
    while(!inf.eof()&&!inf2.eof()){
        getline(inf,line);
        getline(inf2,line2);
        if(line.length()<1) continue;
        if(line2.length()<1) continue;
        if((line.substr(0,lh) == header)) {
            ouf << line << "\n";
            continue;
        }
        ll.clear();
        ll2.clear();
        split(line,ll," \t");
        split(line2,ll2," \t");
        
        double pwd = string2Double(ll[3])/(string2Double(ll2[3])+0.000000001);
//        if(ll2[3]=="0") pwd = 10;
        ouf << ll[0] << "\t" << ll[1] << "\t" << ll[2] << "\t" << pwd << "\n";
    }
    inf.close();
    inf2.close();
    ouf.close();
    return 1;
}
#endif /* FileFunctions_h */
