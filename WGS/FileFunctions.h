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
//void nrerror(char error_text[]);
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
int getOri(parameter *para){
    igzstream inf1 ((para->inFile).c_str(),ifstream::in);
    igzstream inf2 ((para->inFile2).c_str(),ifstream::in);
    ofstream ouf ((para->outFile).c_str());
    set <string> pos;
    vector<string> ll;
    string line;
    while(!inf1.eof()){
        getline(inf1,line);
        if(line.length()<1) continue;
        ll.clear();
        split(line,ll," \t");
        pos.insert(ll[1]);
    }
    while(!inf2.eof()){
        getline(inf2,line);
        if(line[0]=='C') continue;
        if(line.length()<1) continue;
        ll.clear();
        split(line,ll," \t");
        if(pos.count(ll[1])>0){
            ouf << line << "\n";
        }
    }
    ouf.close();
    inf1.close();
    inf2.close();
    return 0;
}
int pi2bed(parameter *para){
//    int binSize = para->size;
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
    string chr = (para->chr);
    string line;
    vector < string > ll;
    int** bedPos = imatrix(-1, 500000, -1, 4);
    int bedPos_i = 0;
    while(!inbed.eof()){
        getline(inbed,line);
        if(line.length() < 1) continue;
        if(line[0]=='C') continue;
        ll.clear();
        split(line,ll,"\t");
        if(ll[0] !=chr) continue;
        bedPos[bedPos_i][0] = string2Int(ll[1]); // start pos
        bedPos[bedPos_i][1] = string2Int(ll[2]); // end pos
        bedPos[bedPos_i][2] = string2Int(ll[2]) - string2Int(ll[1]) + 1 ; // length
        bedPos[bedPos_i][3] = string2Int(ll[3]); // number in this region
        bedPos_i++;
    }
    cout << "bed readed! Size is:\t" << bedPos_i << endl;
    inbed.close();
    double pi = 0.0;
    int curent_bed = bedPos[0][0];
    int startPos;
    int endPos;
    int n_bed_pos = 0;
    while(!inF.eof()){
        getline(inF, line);
        if(line.length() < 1) continue;
        if(line[0]=='C') continue;
        ll.clear();
        split(line,ll," \t");
        if(ll[0]!=chr) continue;
        int current_pos = string2Int(ll[1]);
        if (current_pos < bedPos[0][0]) {
            cerr << "please check bedFile, the first position is too small!" << endl;
            return 1;
        }
//        if (current_pos > bedPos[bedPos_i-1][1]) continue;
        if(n_bed_pos > bedPos_i){
            break;
        }
        while(bedPos[n_bed_pos][1] < current_pos ){
            startPos = bedPos[n_bed_pos][0];
            endPos = bedPos[n_bed_pos][1];
            ouf << chr << "\t" << startPos << "\t" << endPos << "\t" << pi/bedPos[n_bed_pos][3] << "\n";
            n_bed_pos++;
            if(n_bed_pos > bedPos_i){
                break;
            }
            pi = 0;
        }
        if(ll[2]=="-nan"||ll[2]=="NA"||ll[2]=="inf") ll[2] = "0";
        pi += string2Double(ll[2]);
    }
    while( n_bed_pos < bedPos_i){
        startPos = bedPos[n_bed_pos][0];
        endPos = bedPos[n_bed_pos][1];
        ouf << chr << "\t" << startPos << "\t" << endPos << "\t" << pi/bedPos[n_bed_pos][3] << "\n";
        n_bed_pos++;
        pi = 0;
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
                a += 2;
                sampleSize +=2;
            }else if(ll[samplePos[i]][0]== '1' && ll[samplePos[i]][2] == '1'){
                b +=2 ;
                sampleSize +=2;
            }else if(ll[samplePos[i]][0]== '0' && ll[samplePos[i]][2] == '1'){
                a++;
                b++;
                sampleSize +=2;
            }else{
                continue;
            }
        }
        double pi = (2*a*b)/(sampleSize*(sampleSize-1));
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
            if((line.substr(0,lh) == header) | (line[0] == '#')) {
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
        if(l1.length()<1) continue;
        if(l2.length()<1) continue;
        if(l3.length()<1) continue;
        split(l1, ll1," \t");
        split(l2, ll2," \t");
        split(l3, ll3," \t");
        
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
//        cout << l1 << endl;
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
int filterDepth_bySimulation(parameter *para){
    string input1 = (para->inFile);
    double mean = (para -> mean);
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
    ofstream log((para->outFile+".log").c_str());
    if((!log.good())){
        cerr << "open log File error" << endl;
        return  0;
    }
    string l1;
    vector < string >  ll1;
    vector <double> ll;
    int j = 0;
    map <int,vector<double>> dmm ;
    bool first = true;
    while(!f1.eof()){
        getline(f1,l1);
        
        ll1.clear();
        
        ll.clear();
        split(l1, ll1,"\t");
        
        for(int i = 2, len = ll1.size(); i < len ; ++i){
            ll.push_back(string2Double(ll1[i]));
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
        split(l1, ll1," \t");
        split(l2, ll2," \t");
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
//            cout << dmm[400][1] << endl;
//            cout << dmm[400][0]<< endl;
//            cout << "simulation process: end" << endl;
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
    ofstream  OUT((outFile).c_str());
    
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
    string output2 = (para->inFile2); // pos txt
    string output = (para->outFile); // allele txt
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
        if(line[0]=='#' ) {
            OUT << line ;
            if(line[1]=='C'){
                OUT << "\t" << "barley";
            }
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
int calibarate3(parameter *para){
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
    map <string,string> pos;
    string line;
    string outfile = (para->outFile);
    ofstream OUT (outfile.c_str());
    if(OUT.fail()){
        cerr << "Open File out error" << outfile << endl;
        return 0;
    }
    while(!f2.eof()){
        getline(f2,line);
        if(line.length()<1) continue;
        ll.clear();
        split(line,ll," \t");
        pos.insert(std::pair<string, string>(ll[0],ll[2]));
    }
    int passed = 0;
    while(!f1.eof()){
        getline(f1,line);
        if(line.length()<1) continue;
        if(line[0]=='#' ) {
            OUT << line ;
            if(line[1]=='C'){
                OUT << "\t" << "barley";
            }
            OUT << "\n";
            continue;
        };
        ll.clear();
        split(line,ll,"\t");
        if(ll.size()<2) continue;
        if(pos[ll[1]].c_str() == ll[4]){
            OUT << line ;
            OUT << "\t" << "1/1:0,10:0,0,100";
            OUT << "\n";
            passed++;
        }else if(pos[ll[1]].c_str() == ll[3]){
            OUT << line ;
            OUT << "\t" << "0/0:0,10:0,0,100";
            OUT << "\n";
            passed++;
        }else{
            continue;
        }
    }
    cout << "passed number is: " << passed << endl;
    OUT.close();
    f1.close();
    return 1;
}
int calibarate4(parameter *para){
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
    map <string,string> pos;
    string line;
    string outfile = (para->outFile);
    ofstream OUT (outfile.c_str());
    if(OUT.fail()){
        cerr << "Open File out error" << outfile << endl;
        return 0;
    }
    while(!f2.eof()){
        getline(f2,line);
        if(line.length()<1) continue;
        ll.clear();
        split(line,ll," \t");
        pos.insert(std::pair<string, string>(ll[0],ll[2]));
    }
    int passed = 0;
    while(!f1.eof()){
        getline(f1,line);
        if(line.length()<1) continue;
        if(line[0]=='#' ) {
            OUT << line ;
            if(line[1]=='C'){
                OUT << "\t" << "barley";
            }
            OUT << "\n";
            continue;
        };
        ll.clear();
        split(line,ll,"\t");
        if(ll.size()<2) continue;
        if(pos[ll[1]].c_str() == ll[4]){
            OUT << line ;
            OUT << "\t" << "1/1:0,10:100,0,0";
            OUT << "\n";
            passed++;
        }else if(pos[ll[1]].c_str() == ll[3]){
            OUT << line ;
            OUT << "\t" << "0/0:0,10:0,0,100";
            OUT << "\n";
            passed++;
        }else{
            OUT << line ;
            OUT << "\t" << "./.:0,0:0,0,0";
            OUT << "\n";
            passed++;
        }
    }
    cout << "passed number is: " << passed << endl;
    OUT.close();
    f1.close();
    return 1;
}
int calibarate5(parameter *para){
    string input1 = (para->inFile);
    string input2 = (para->inFile2);
    string name = (para->headerC);
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
    map <string,string> pos;
    string line;
    string outfile = (para->outFile);
    ofstream OUT (outfile.c_str());
    if(OUT.fail()){
        cerr << "Open File out error" << outfile << endl;
        return 0;
    }
    while(!f2.eof()){
        getline(f2,line);
        if(line.length()<1) continue;
        ll.clear();
        split(line,ll," \t");
        pos.insert(std::pair<string, string>(ll[0],ll[2]));
    }
    int passed = 0;
    while(!f1.eof()){
        getline(f1,line);
        if(line.length()<1) continue;
        if(line[0]=='#' ) {
            OUT << line ;
            if(line[1]=='C'){
                OUT << "\t" << name;
            }
            OUT << "\n";
            continue;
        };
        ll.clear();
        split(line,ll,"\t");
        if(ll.size()<2) continue;
        if(pos[ll[1]].c_str() == ll[4]){
            OUT << line ;
            OUT << "\t" << "1/1:0,10:100,0,0";
            OUT << "\n";
            passed++;
        }else if(pos[ll[1]].c_str() == ll[3]){
            OUT << line ;
            OUT << "\t" << "0/0:0,10:0,0,100";
            OUT << "\n";
            passed++;
        }else{
            OUT << line ;
            OUT << "\t" << "./.:0,0:0,0,0";
            OUT << "\n";
            passed++;
        }
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
    bool Noneg = (para->noNeg);
    while(!inf.eof()){
        getline(inf,line);
        if(line.length()<1) continue;
        if(line[0] == 'C') continue;
        ll.clear();
        split(line,ll," \t");
        if(ll[pos1]=="inf"||ll[pos1]=="Inf"||ll[pos1]=="NA"||ll[pos1]=="NaN"||ll[pos1]=="-nan"||ll[pos1] == "nan") continue;
        if(Noneg){
            value.push_back(string2Doublepos(ll[pos1]));
        }else{
            value.push_back(string2Double(ll[pos1]));
        }        
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
int merge2vcf (parameter *para){
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
    string header;
    set <string> head;
    vector <int> pos;
    while(!inf.eof()){
        getline(inf,line);
        if(line.length()<1) continue;
        if(line[0]=='#' && line[1] =='#'){
            continue;
        }
        if(line[0]=='#' && line[1] =='C'){
            ll.clear();
            split(line,ll,"\t");
            for(int i = 0; i < ll.size();++i){
                head.insert(ll[i]);
            }
            header = line;
            break;
        }
    }
    
    while(!inf2.eof())
    {
        getline(inf2,line);
        if(line.length()<1) continue;
        if(line[0]=='#' && line[1] =='#')
        {
            ouf << line << "\n" ;
            continue;
        }
        if(line[0]=='#' && line[1] =='C')
        {
            ll2.clear();
            split(line,ll2," \t");
            ouf << header ;
            for (int i = 0 ; i < ll2.size(); ++i)
            {
                if(head.count(ll2[i])!=1)
                {
                    pos.push_back(i);
                    ouf << "\t" << ll2[i];
                }
            }
            ouf << "\n";
            break;
        }
    }
    
    while(!inf.eof() && !inf2.eof())
    {
        getline(inf,line);
        getline(inf2,line2);
        if (line.length()<1) continue;
        if(line2.length()  < 1) continue;
        ll.clear();
        ll2.clear();
        split(line2,ll2," \t");
        split(line,ll," \t");
        if(ll[1]!=ll2[1]) continue;
        ouf << line ;
        for (int i = 0 ; i < pos.size(); ++i){
            ouf << "\t" << ll2[pos[i]];
        }
        ouf << "\n";
    }
    inf.close();
    inf2.close();
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
        
        if(ll2[3] == "NA"||ll2[3] == "-nan"||ll2[3] == "nan")
        {
            ouf << ll[0] << "\t" << ll[1] << "\t" << ll[2] << "\t" << "NA" << "\n";
            continue;
        }
        
        if(ll[3] == "NA"||ll[3] == "-nan"||ll[3] == "nan")
        {
            ouf << ll[0] << "\t" << ll[1] << "\t" << ll[2] << "\t" << "NA" << "\n";
            continue;
        }
        if(string2Double(ll2[3]) == 0 ) ll2[3] = "0.001";
        double pwd = string2Double(ll[3])/(string2Double(ll2[3]));
//        if(ll2[3]=="0") pwd = 10;
        ouf << ll[0] << "\t" << ll[1] << "\t" << ll[2] << "\t" << pwd << "\n";
    }
    inf.close();
    inf2.close();
    ouf.close();
    return 1;
}
int splitByChr(parameter *para){
    string inFile = (para->inFile);
    string outFile = (para->outFile);
    igzstream inf ((inFile.c_str()),fstream::in);
    
    if(inf.fail()){
        cerr << "Couldn't open inFile" << endl;
        return 0 ;
    }
    
    vector<string> header;
    vector<string> ll;
    // read header
    while(!inf.eof()){
        string  line ;
        getline(inf,line);
        if (line.length() < 1 )  {
            continue  ;
        }else if ( line[0] == '#' && line[1] == '#' )  {
            header.push_back(line);
            continue  ;
        }else if ( line[0] == '#' && line[1] != '#' ){
            header.push_back(line);
            ll.clear();
            split(line,ll,"\t");
            if  ( ll[0]  != "#CHROM"){
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
    string chr = "0";
    ofstream ouf ;
    while(!inf.eof()){
        string  line ;
        getline(inf,line);
        if (line.length() < 1 )  {
            continue  ;
        }
        ll.clear();
        split(line,ll," \t");
        if(ll[0]==chr){
            ouf << line << "\n" ;
        }else{
            ouf.close();
            string outname = outFile+chr;
//            ouf ((outname.c_str()));
//            for(int i = 0; i < header.size();i++){
//                ouf << header[i] << "\n" ;
//            }
        }
    }
    inf.close();
    ouf.close();
    
    return 1;
}
int ct3(parameter *para){
    string inFile1 = (para->inFile);
    string inFile2 = (para->inFile2);
    string inFile3 = (para->inFile3);
    string bedFile = (para->bedFile);
    string outFile = (para->outFile);
    igzstream inf1 ((inFile1).c_str(),ifstream::in);
    igzstream inf2 ((inFile2).c_str(),ifstream::in);
    igzstream inf3 ((inFile3).c_str(),ifstream::in);
    igzstream vcf ((bedFile).c_str(),ifstream::in);
    ofstream ouf ((outFile).c_str());
    set <string> g1;
    set <string> g2;
    set <string> g3;
    string line;
    while(!inf1.eof()){
        getline(inf1,line);
        if(line.length()<1) continue;
        g1.insert(line);
    }
    while(!inf2.eof()){
        getline(inf2,line);
        if(line.length()<1) continue;
        g2.insert(line);
    }
    while(!inf3.eof()){
        getline(inf3,line);
        if(line.length()<1) continue;
        g3.insert(line);
    }
    vector <string> ll;
    set<int> gi1,gi2,gi3;
    int c1 = 0, c2 = 0, c3 =0, c4 = 0,c5 = 0,c6 = 0, c7 = 0;
    while(!vcf.eof()){
        getline(vcf,line);
        if(line.length()<1) continue;
        if(line[0]=='#' && line[1]=='#') continue;
        if(line[0]=='#' && line[1]=='C') {
            ll.clear();
            split(line,ll," \t");
            for(int i = 9; i < ll.size(); ++i){
                if(g1.count(ll[i])==1){
                    gi1.insert(i);
                }else if(g2.count(ll[i])==1){
                    gi2.insert(i);
                }else if(g3.count(ll[i])==1){
                    gi3.insert(i);
                }else{
                    continue;
                }
            }
            cout << "group1 size is: " << gi1.size() << endl;
            cout << "group2 size is: " << gi2.size() << endl;
            cout << "group3 size is: " << gi3.size() << endl;
            continue;
        };
        ll.clear();
        bool s1 = false,s2 = false,s3 = false;
        int n = 0,sum = 0;
        split(line,ll," \t");
        for(set<int>::iterator it=gi1.begin() ;it!=gi1.end();it++){
            n++;
            if(ll[*it][0]=='1'){
                sum++;
            }
            if(ll[*it][2]=='1'){
                sum++;
            }
        }
        if((2*n-sum)>0 && sum > 0) s1= true;
        
        n = 0,sum = 0;
        for(set<int>::iterator it=gi2.begin() ;it!=gi2.end();it++){
            n++;
            if(ll[*it][0]=='1'){
                sum++;
            }
            if(ll[*it][2]=='1'){
                sum++;
            }
        }
        if((2*n-sum)>0 && sum > 0) s2= true;
        
        n = 0,sum = 0;
        for(set<int>::iterator it=gi3.begin() ;it!=gi3.end();it++){
            n++;
            if(ll[*it][0]=='1'){
                sum++;
            }
            if(ll[*it][2]=='1'){
                sum++;
            }
        }
        if((2*n-sum)>0 && sum > 0) s3= true;
        if(s1 && s2 && s3){
            c1++;
        }else
        if(s1 && s2 && !s3){
            c2++;
        }else
        if(s1 && !s2 && s3){
            c3++;
        }else
        if(!s1 && s2 && s3){
            c4++;
        }else
        if(s1 && !s2 && !s3){
            c5++;
        }else
        if(!s1 && s2 && !s3){
            c6++;
        }else
        if(!s1 && !s2 && s3){
            c7++;
        }else{
            c1++;
        }
    }
    ouf << "c1\t" << c1 << "\n";
    ouf << "c2\t" << c2 << "\n";
    ouf << "c3\t" << c3 << "\n";
    ouf << "c4\t" << c4 << "\n";
    ouf << "c5\t" << c5 << "\n";
    ouf << "c6\t" << c6 << "\n";
    ouf << "c7\t" << c7 << "\n";
    inf1.close();
    inf2.close();
    inf3.close();
    vcf.close();
    ouf.close();
    return 1;
}
int ct2(parameter *para){
    string inFile1 = (para->inFile);
    string inFile2 = (para->inFile2);
    string bedFile = (para->bedFile);
    string outFile = (para->outFile);
    igzstream inf1 ((inFile1).c_str(),ifstream::in);
    igzstream inf2 ((inFile2).c_str(),ifstream::in);
    igzstream vcf ((bedFile).c_str(),ifstream::in);
    ofstream ouf ((outFile).c_str());
    set <string> g1;
    set <string> g2;
    string line;
    while(!inf1.eof()){
        getline(inf1,line);
        if(line.length()<1) continue;
        g1.insert(line);
    }
    cout << "group1 readed!" << endl;
    while(!inf2.eof()){
        getline(inf2,line);
        if(line.length()<1) continue;
        g2.insert(line);
    }
    cout << "group2 readed!" << endl;
    vector <string> ll;
    set<int> gi1,gi2;
    int c1 = 0, c2 = 0, c3 =0, c4 = 0;
    while(!vcf.eof()){
        getline(vcf,line);
        if(line.length()<1) continue;
        if(line[0]=='#' && line[1]=='#') continue;
        if(line[0]=='#' && line[1]=='C') {
            cout << "headering.." << endl;
            ll.clear();
            split(line,ll," \t");
            for(int i = 9; i < ll.size(); ++i){
                if(g1.count(ll[i])==1){
                    gi1.insert(i);
                }else if(g2.count(ll[i])==1){
                    gi2.insert(i);
                }else{
                    continue;
                }
            }
            cout << "group1 size is: " << gi1.size() << endl;
            cout << "group2 size is: " << gi2.size() << endl;
            continue;
        };
        ll.clear();
        bool s1 = false,s2 = false;
        int n = 0,sum = 0;
        split(line,ll," \t");
        for(set<int>::iterator it=gi1.begin() ;it!=gi1.end();it++){
            if(ll[*it][0]=='.'){
                continue;
            }
            n++;
            if(ll[*it][0]=='1'){
                sum++;
            }
            if(ll[*it][2]=='1'){
                sum++;
            }
        }
        if((2*n-sum)>0 && sum > 0) s1= true;
        
        n = 0, sum = 0;
        for(set<int>::iterator it=gi2.begin() ;it!=gi2.end();it++){
            if(ll[*it][0]=='.'){
                continue;
            }
            n++;
            if(ll[*it][0]=='1'){
                sum++;
            }
            if(ll[*it][2]=='1'){
                sum++;
            }
        }
        if((2*n-sum)>0 && sum > 0) s2= true;
        
        
        if(s1 && s2 ){
            c1++; // shared SNPs
        }else if(s1 && !s2 ){
            c2++; // allelic in group1 but not group2
        }else if(!s1 && s2 ){
            c3++; // allelic in group2 but not group1
        }else{
//            cerr << "No cater found! sum is: " << sum << endl;
            c4++; // not allelic in both
        }
    }
    ouf << "allelic in group1 and group2: \t" << c1 << "\n";
    ouf << "allelic in group1: \t" << c2 << "\n";
    ouf << "allelic in group2: \t" << c3 << "\n";
    ouf << "non-allelic in both: \t" << c4 << "\n";
    inf1.close();
    inf2.close();
    vcf.close();
    ouf.close();
    return 1;
}

int ct1(parameter *para){
    string inFile1 = (para->inFile);
    string vcfFile = (para->bedFile);
    string outFile = (para->outFile);
    igzstream inf1 ((inFile1).c_str(),ifstream::in);
    igzstream vcf ((vcfFile).c_str(),ifstream::in);
    ofstream ouf ((outFile).c_str());
    set <string> g1;
    string line;
    while(!inf1.eof()){
        getline(inf1,line);
        if(line.length()<1) continue;
        g1.insert(line);
    }
    cout << "group1 readed!" << endl;
    
    vector <string> ll;
    set<int> gi1;
    while(!vcf.eof()){
        getline(vcf,line);
        if(line.length()<1) continue;
        if(line[0]=='#' && line[1]=='#') continue;
        if(line[0]=='#' && line[1]=='C') {
            cout << "headering.." << endl;
            ll.clear();
            split(line,ll," \t");
            for(int i = 9; i < ll.size(); ++i){
                if(g1.count(ll[i])==1){
                    gi1.insert(i);
                }else{
                    continue;
                }
            }
            cout << "group size is: " << gi1.size() << endl;
            continue;
        };
        ll.clear();
        bool s1 = false;
        int n = 0,sum = 0;
        split(line,ll," \t");
        for(set<int>::iterator it=gi1.begin() ;it!=gi1.end();it++){
            if(ll[*it][0]=='.'){
                continue;
            }
            n++;
            if(ll[*it][0]=='1'){
                sum++;
            }
            if(ll[*it][2]=='1'){
                sum++;
            }
        }
        if((2*n-sum)>0 && sum > 0) s1= true;
        ouf << s1 << "\n";
    }
    inf1.close();
    vcf.close();
    ouf.close();
    return 1;
}

int addContig(parameter *para){
    string inFile1 = (para->inFile);
    string inFile2 = (para->inFile2);
    string outFile = (para->outFile);
    igzstream inf1 ((inFile1).c_str(),ifstream::in);
    igzstream inf2 ((inFile2).c_str(),ifstream::in);
    ofstream ouf ((outFile).c_str());
    string header;
    string line;
    while(!inf1.eof()){
        line.clear();
        getline(inf1,line);
        if(line.length()<1) continue;
        header.append(line);
        header.append("\n");
    }
    inf1.close();
    while(!inf2.eof()){
        line.clear();
        getline(inf2,line);
        if(line.length() < 1) continue;
        if(line[0]=='#' & line[1] == 'C'){
            ouf << header ;
        }
        ouf << line << "\n";
    }
    inf2.close();
    ouf.close();
    return 0;
}
int subMummer4(parameter *para){
    string inFile1 = (para->inFile);
    string inFile2 = (para->inFile2);
    string outFile = (para->outFile);
    igzstream inf1 ((inFile1).c_str(),ifstream::in);
    igzstream inf2 ((inFile2).c_str(),ifstream::in);
    ofstream ouf ((outFile).c_str());
    string line;
    set <int> snpPos;
    vector<string> ll;
    while(!inf1.eof()){
        getline(inf1, line);
        if(line.length() < 1) continue;
        if(line[0]=='#') continue;
        ll.clear();
        split(line, ll," \t");
        snpPos.insert(string2Int(ll[1]));
    }
    cout << "vcf readed!" << endl;
    bool newAlignment = true;
    string s1,s2;
    int start = 0 , end = 0;
    int missingLength = 0;
//    std::size_t found ;
    string ss1, ss2;
    while(!inf2.eof()){
        line.clear();
        getline(inf2, line);
        if(line.length() < 1) continue;
        if(line[0]==' ') continue;
        if(line[0]=='\t') continue;
        if(line[0]=='=') continue;
//        found = line.find("^");
//        if (found!=std::string::npos) continue;
        ll.clear();
        split(line, ll," \t");
//        for(int i = 0; i < ll.size(); ++i){
//            cout << ll[i] << endl;
//        }
        if(ll[1]=="BEGIN"){
            s1.clear();
            s2.clear();
            newAlignment = true;
            start = string2Int(ll[5]);
            end = string2Int(ll[7]);
            continue;
        }
        if(ll[1]=="END"){
            ss1.clear();
            ss2.clear();
            for (int i =0; i < s1.length(); ++i){
//                cout << s1.substr(i,1) << endl;
                if(s1.substr(i,1) != "."){
                    ss1 += s1[i];
                    ss2 += s2[i];
                }
            }
            for(int i = start; i < end; ++i){
                if(snpPos.count(i)!=0){
                    if(ss2.substr(i-start,1)!="."){
                        ouf << i << "\t"<< (char)toupper(ss1[i-start]) <<"\t"<< (char)toupper(ss2[i-start])<<"\n";
                    }
                }
            }
        }
        if(newAlignment){
            s1.append(ll[1]);
            newAlignment = false;
            continue;
        }else{
            s2.append(ll[1]);
            newAlignment = true;
            continue;
        }
        
    }
    inf1.close();
    inf2.close();
    ouf.close();
    return 0;
}
int changeAncestralAllele(parameter *para){
    string inFile1 = (para->inFile);
    string outFile = (para->outFile);
    igzstream inf1 ((inFile1).c_str(),ifstream::in);
    ogzstream ouf ((outFile).c_str());
    string line;
    vector<string> ll;
    while(!inf1.eof()){
        getline(inf1,line);
        if(line.length()<1) continue;
        if(line[0]=='#'){
            ouf << line << "\n" ;
            continue;
        }
        ll.clear();
        split(line,ll," \t");
        ouf << ll[0];
        for(int i = 1; i < ll.size(); ++i){
            if(ll[i].substr(0,3)=="./."){
                ouf << "\t" << "./.";
            }else if (ll[i].substr(0,3)=="1/1"){
                ouf << "\t" << "0/0";
            }else if (ll[i].substr(0,3)=="0/1"){
                ouf << "\t" << "0/1";
            }else if (ll[i].substr(0,3)=="0/0"){
                ouf << "\t" << "1/1";
            }else{
                ouf << "\t" << ll[i];
            }
        }
        ouf << "\n";
    }
    inf1.close();
    ouf.close();
    return 0;
}
int getMaskRegion(parameter *para)
{
    string inFile = (para->inFile);
    string outFile = (para->outFile);
    igzstream inf ((inFile).c_str(),ifstream::in);
    ofstream ouf ((outFile).c_str());
    string line;
    int pos = 0,prePos = 0;
    int max = (para->maxLength);
    vector<string> ll;
    bool isFirst = false;
    while(!inf.eof())
    {
        getline(inf, line);
        if(line.length()<1) continue;
        ll.clear();
        split(line, ll," \t");
        pos = string2Int(ll[1]);
        if((pos-prePos)>150){
            ouf << ll[0] << "\t" << prePos+1 << "\t" << pos-1 << "\n";
        }
        prePos = pos;
    }
    if(pos < max){
        ouf << ll[0] << "\t" << pos+1 << "\t" << max << "\n";
    }
    inf.close();
    ouf.close();
    return 0;
}

int genePi(parameter *para){
    string gffFile = (para -> inFile);
    string piFile = (para -> inFile2);
    string outFile = (para -> outFile);
    string chr = (para -> chr);
    igzstream infGff ((gffFile).c_str(),ifstream::in);
    igzstream infPi ((piFile).c_str(),ifstream::in);
    ofstream ouf ((outFile).c_str());
    set<int> utr3;
    set<int> utr5;
    set<int> cds;
    set<int> intron;
    set<int> upstream;
    set<int> downstream;
    string line;
    vector<string> ll;
    set<int> withoutIntron;
    int start = 0, end = 0;
    int ps = 0, pe = 0;
    string strand = "";
    while(!infGff.eof()){
        getline(infGff,line);
        if(line.length()<1) continue;
        if(line[0]=='#' && line[2] =='#'&& withoutIntron.size() > 0) {
            if ( strand == "+"){
                for (int i = ps-2000; i < ps; ++i){
                    upstream.insert(i);
                }
                for (int i = pe+1; i < pe+2000; ++i){
                    downstream.insert(i);
                }
            }else{
                for (int i = ps-2000; i < ps; ++i){
                    downstream.insert(i);
                }
                for (int i = pe+1; i < pe+2000; ++i){
                    upstream.insert(i);
                }
            }
            for ( int i = start; i < end; ++i){
                if(withoutIntron.count(i) == 0){
                    intron.insert(i);
                }
            }
            start = 0;
            end = 0;
            withoutIntron.clear();
            ps = 0;
            pe = 0;
            continue;
        };
        if(line[0]=='#') continue;
        ll.clear();
        split(line,ll," \t");
        if(ll[0] != chr) continue;
        if(ll[2] == "gene"){
            start = string2Int(ll[3]);
            end = string2Int(ll[4]);
            strand = ll[6];
        }else if (ll[2] == "five_prime_UTR"){
            ps = string2Int(ll[3]);
            pe = string2Int(ll[4]);
            for (int i = ps; i < pe+1; ++i){
                utr5.insert(i);
                withoutIntron.insert(i);
            }
        }else if (ll[2] == "three_prime_UTR"){
            ps = string2Int(ll[3]);
            pe = string2Int(ll[4]);
            for (int i = ps; i < pe+1; ++i){
                utr3.insert(i);
                withoutIntron.insert(i);
            }
        }else if (ll[2] == "CDS"){
            ps = string2Int(ll[3]);
            pe = string2Int(ll[4]);
            for (int i = ps; i < pe+1; ++i){
                cds.insert(i);
                withoutIntron.insert(i);
            }
        }
    }
    if(withoutIntron.size() > 1) {
        for ( int i = start; i < end; ++i){
            if(withoutIntron.count(i)==0){
                intron.insert(i);
            }
        }
        withoutIntron.clear();
    }
    
    cout << "gff3 readed!" << endl;
    
    double size_upstream = 0, size_utr5 = 0, size_cds = 0, size_intron = 0;
    double size_utr3 = 0, size_downstream = 0, size_intergenic = 0;
    
    while(!infPi.eof()){
        getline(infPi,line);
        if(line.length()<1) continue;
        if(line[0]=='C') continue;
        ll.clear();
        split(line, ll," \t");
        if(ll[0]!=chr) continue;
        int pos = string2Int(ll[1]);
        if(ll.size()==3){
            if (ll[2] == "-nan" || ll[2] == "nan" || ll[2] == "na" || ll[2] == "NA") continue;
            if(upstream.count(pos)==1)
            {
                size_upstream += string2Double(ll[2]);
            }
            else if(utr5.count(pos)==1)
            {
                size_utr5 += string2Double(ll[2]);
            }
            else if(cds.count(pos)==1)
            {
                size_cds += string2Double(ll[2]);
            }
            else if(intron.count(pos)==1)
            {
                size_intron += string2Double(ll[2]);
            }
            else if(utr3.count(pos)==1)
            {
                size_utr3 += string2Double(ll[2]);
            }
            else if(downstream.count(pos)==1)
            {
                size_downstream += string2Double(ll[2]);
            }
            else
            {
                size_intergenic += string2Double(ll[2]);
            }
        }else if (ll.size()==2){
            if(upstream.count(pos)==1)
            {
                size_upstream ++;
            }
            else if(utr5.count(pos)==1)
            {
                size_utr5 ++;
            }
            else if(cds.count(pos)==1)
            {
                size_cds ++;
            }
            else if(intron.count(pos)==1)
            {
                size_intron ++;
            }
            else if(utr3.count(pos)==1)
            {
                size_utr3 ++;
            }
            else if(downstream.count(pos)==1)
            {
                size_downstream ++;
            }
            else
            {
                size_intergenic ++;
            }
        }
        
    }
    ouf << "region\tsum\n";
    ouf << "intergenic\t" << size_intergenic << "\n";
    ouf << "upstream\t" << size_upstream << "\n";
    ouf << "five-UTR\t" << size_utr5 << "\n";
    ouf << "exon\t" << size_cds << "\n";
    ouf << "intron\t" << size_intron << "\n";
    ouf << "three-UTR\t" << size_utr3 << "\n";
    ouf << "downstream\t" << size_downstream << "\n";
    infGff.close();
    infPi.close();
    ouf.close();
    return 0;
}

int gene_count(parameter *para){
    string gffFile = (para -> inFile);
    string piFile = (para -> inFile2);
    string outFile = (para -> outFile);
    string chr = (para -> chr);
    double threshold = (para -> threshold);
    igzstream infGff ((gffFile).c_str(),ifstream::in);
    igzstream infPi ((piFile).c_str(),ifstream::in);
    ofstream ouf ((outFile).c_str());
    string line;
    vector<string> ll;
    set<int> withoutIntron;
    int start = 0, end = 0;
    int ps = 0, pe = 0;
    string strand = "";
    vector<int> startP(20000);
    vector<int> endP(20000);
    vector<int> strandP(20000);
    
    vector<int> genefeaturs(500000000);
    int gene_order = 0;
    // upstream50: 1; upstream20: 2;upstream10: 3; upstream5: 4;upstream2: 5;
    // gene: 20, 5utr: 7; cds: 8; intron: 9; 3utr: 10;
    // down50: 11; down20: 12; down10: 13; down5: 14; down2: 15;
    while(!infGff.eof()){
        getline(infGff,line);
        if(line.length()<1) continue;
        if(line[0]=='#' && line[2] =='#'&& withoutIntron.size() > 0) {
            for ( int i = start; i < end; ++i){
                if(withoutIntron.count(i) == 0){
                    genefeaturs[i] = 9;
//                    intron.insert(i);
                }
            }
            start = 0;
            end = 0;
            withoutIntron.clear();
            ps = 0;
            pe = 0;
            continue;
        };
        if(line[0]=='#') continue;
        ll.clear();
        split(line,ll," \t");
        if(ll[0] != chr) continue;
        if(ll[2] == "gene"){
            start = string2Int(ll[3]);
            end = string2Int(ll[4]);
            strand = ll[6];
            startP[gene_order] = start;
            endP[gene_order] = end;
            if(strand == "+"){
                strandP[gene_order] = 0;
            }else{
                strandP[gene_order] = 1;
            }
            gene_order++;
        }else if (ll[2] == "five_prime_UTR"){
            ps = string2Int(ll[3]);
            pe = string2Int(ll[4]);
            for (int i = ps; i < pe+1; ++i){
                genefeaturs[i]= 7;
                withoutIntron.insert(i);
            }
        }else if (ll[2] == "three_prime_UTR"){
            ps = string2Int(ll[3]);
            pe = string2Int(ll[4]);
            for (int i = ps; i < pe+1; ++i){
                 genefeaturs[i] = 10;
                withoutIntron.insert(i);
            }
        }else if (ll[2] == "CDS"){
            ps = string2Int(ll[3]);
            pe = string2Int(ll[4]);
            for (int i = ps; i < pe+1; ++i){
                 genefeaturs[i] = 8;
                withoutIntron.insert(i);
            }
        }
    }
    
    if(withoutIntron.size() > 1) {
        for ( int i = start; i < end; ++i){
            if(withoutIntron.count(i)==0){
                genefeaturs[i] = 9;
            }
        }
        withoutIntron.clear();
    }
    
    cout << "gff3 readed!" << endl;
    cout << "gene number is:\t" << gene_order << endl;
//    cout << "UTR number is:\t" << gene_order << endl;
    double size_upstream = 0, size_utr5 = 0, size_cds = 0, size_intron = 0;
    double size_utr3 = 0, size_downstream = 0,size_intergenic = 0;
    double size_up5 = 0, size_up10 = 0, size_up15 = 0, size_up20 = 0, size_up50 = 0;
    double size_down5 = 0, size_down10 = 0, size_down15 = 0, size_down20 = 0, size_down50 = 0;
    int current_order = 0;
    while(!infPi.eof()){
        getline(infPi,line);
        if(line.length()<1) continue;
        if(line[0] == 'C') continue;
        ll.clear();
        split(line,ll," \t");
        if(ll[0] != chr) continue;
        int pos = string2Int(ll[1]);
//        if (ll.size()<4){
            pos = string2Int(ll[1]);
//        }else{
//            pos = string2Int(ll[2]);
//        }
        int size = ll.size()-1;
        if(size > 1){
            if (ll[size] == "-nan" || ll[size] == "nan" || ll[size] == "na" || ll[size] == "NA"|| ll[size] == "Inf"|| ll[size] == "-Inf") continue;
            double pi = string2Doublepos(ll[size]);
            if( pi > threshold){
                switch(genefeaturs[pos]){
                    case 0:
                        while ((startP[current_order] - pos) < 0){
                            if (current_order > gene_order - 1){
                                size_intergenic++;
                                genefeaturs[pos]= 20;
                                break;
                            }
                            current_order++;
                            if (current_order % 100 == 0 ){
                                cout << "currrent_order is:\t" << current_order << endl;
                            }
                        }
                        if((startP[current_order] - pos) < 2000){
                            if(strandP[current_order] == 0){
                                size_upstream += pi;
                            }else{
                                size_downstream += pi;
                            }
                            genefeaturs[pos]= 20;

                        }else if ((startP[current_order]- pos) < 5000){
                            if(strandP[current_order] == 0){
                                size_up5 += pi;
                            }else{
                                size_down5 += pi;
                            }
                            genefeaturs[pos]= 20;

                        }else if ((startP[current_order]- pos) < 10000){
                            if(strandP[current_order] == 0){
                                size_up10+= pi;
                            }else{
                                size_down10+= pi;
                            }
                            genefeaturs[pos]= 20;

                        }else if ((startP[current_order] - pos) < 20000){
                            if(strandP[current_order]== 0){
                                size_up20 += pi;
                            }else{
                                size_down20 += pi;
                            }
                            genefeaturs[pos]= 20;

                        }else if ((startP[current_order] - pos) < 50000){
                            if(strandP[current_order] == 0){
                                size_up50 += pi;
                            }else{
                                size_down50 += pi;
                            }
                            genefeaturs[pos]= 20;

                        }
                        
                        if( genefeaturs[pos]!=0) break;
                        
                        if((endP[current_order] - pos) < 2000){
                            if(strandP[current_order] == 1){
                                size_upstream += pi;
                            }else{
                                size_downstream += pi;
                            }
                            genefeaturs[pos]= 20;

                        }else if ((endP[current_order]- pos) < 5000){
                            if(strandP[current_order] == 1){
                                size_up5 += pi;
                            }else{
                                size_down5 += pi;
                            }
                            genefeaturs[pos]= 20;

                        }else if ((endP[current_order]- pos) < 10000){
                            if(strandP[current_order] == 1){
                                size_up10+= pi;
                            }else{
                                size_down10+= pi;
                            }
                            genefeaturs[pos]= 20;

                        }else if ((endP[current_order] - pos) < 20000){
                            if(strandP[current_order]== 1){
                                size_up20 += pi;
                            }else{
                                size_down20 += pi;
                            }
                            genefeaturs[pos]= 20;

                        }else if ((endP[current_order] - pos) < 50000){
                            if(strandP[current_order] == 1){
                                size_up50 += pi;
                            }else{
                                size_down50 += pi;
                            }
                            genefeaturs[pos]= 20;

                        }else{
                                size_intergenic+= pi;
                                genefeaturs[pos]= 20;
                        }
                        break;
                    case 7:
                        size_utr5 +=pi ;
                        break;
                    case 8:
                        size_cds +=pi ;
                        break;
                    case 9:
                        size_intron +=pi ;
                        break;
                    case 10:
                        size_utr3 +=pi ;
                        break;
                    default:
                        break;
                }
            }
        }else{
            switch(genefeaturs[pos]){
                case 0:
                    while ((startP[current_order]- pos) < 0){
                        if (current_order % 100 == 0 ){
                            cout << "currrent_order is:\t" << current_order << endl;
                        }
                        if (current_order > gene_order - 1){
                            size_intergenic++;
                            genefeaturs[pos]= 20;
                            break;
                        }
                        current_order++;
                    }
                    if((startP[current_order] - pos) < 2000){
                        if(strandP[current_order] == 0){
                            size_upstream++;
                        }else{
                            size_downstream++;
                        }
                        genefeaturs[pos]= 20;
                    }else if ((startP[current_order]- pos) < 5000){
                        if(strandP[current_order]== 0){
                            size_up5++;
                        }else{
                            size_down5++;
                        }
                        genefeaturs[pos]= 20;
                    }else if ((startP[current_order] - pos) < 10000){
                        if(strandP[current_order] == 0){
                            size_up10++;
                        }else{
                            size_down10++;
                        }
                        genefeaturs[pos]= 20;

                    }else if ((startP[current_order] - pos) < 20000){
                        if(strandP[current_order] == 0){
                            size_up20++;
                        }else{
                            size_down20++;
                        }
                        genefeaturs[pos]= 20;

                    }else if ((startP[current_order] - pos) < 50000){
                        if(strandP[current_order] == 0){
                            size_up50++;
                        }else{
                            size_down50++;
                        }
                        genefeaturs[pos]= 20;
                    }else{
                        
                    }
                    if( genefeaturs[pos] != 0) break;
                    if((endP[current_order] - pos) < 2000){
                        if(strandP[current_order] == 1){
                            size_upstream ++;
                        }else{
                            size_downstream ++;
                        }
                        genefeaturs[pos]= 20;
                        
                    }else if ((endP[current_order]- pos) < 5000){
                        if(strandP[current_order] == 1){
                            size_up5 ++;
                        }else{
                            size_down5 ++;
                        }
                        genefeaturs[pos]= 20;
                        
                    }else if ((endP[current_order]- pos) < 10000){
                        if(strandP[current_order] == 1){
                            size_up10 ++;
                        }else{
                            size_down10 ++;
                        }
                        genefeaturs[pos]= 20;
                        
                    }else if ((endP[current_order] - pos) < 20000){
                        if(strandP[current_order]== 1){
                            size_up20 ++;
                        }else{
                            size_down20 ++;
                        }
                        genefeaturs[pos]= 20;
                        
                    }else if ((endP[current_order] - pos) < 50000){
                        if(strandP[current_order] == 1){
                            size_up50 ++;
                        }else{
                            size_down50 ++;
                        }
                        genefeaturs[pos]= 20;
                        
                    }else{
                        size_intergenic++;
                        genefeaturs[pos]= 20;
                    }
                    break;
                case 7:
                    size_utr5 ++ ;
                    break;
                case 8:
                    size_cds ++ ;
                    break;
                case 9:
                    size_intron ++ ;
                    break;
                case 10:
                    size_utr3 ++ ;
                    break;
                default:
                    break;
            }
        }
    }
    ouf << "region\tsum\n";
    ouf << "intergenic\t" << size_intergenic << "\n";
    ouf << "upstream_20k_50k\t" << size_up50 << "\n";
    ouf << "upstream_10k_20k\t" << size_up20 << "\n";
    ouf << "upstream_5k_10k\t" << size_up10<< "\n";
    ouf << "upstream_2k_5k\t" << size_up5 << "\n";
    
    ouf << "upstream_2k\t" << size_upstream << "\n";
    ouf << "five-UTR\t" << size_utr5 << "\n";
    ouf << "exon\t" << size_cds << "\n";
    ouf << "intron\t" << size_intron << "\n";
    ouf << "three-UTR\t" << size_utr3 << "\n";
    ouf << "downstream_2k\t" << size_downstream << "\n";
    ouf << "downstream_2k_5k\t" << size_down5 << "\n";
    ouf << "downstream_5k_10k\t" << size_down10 << "\n";
    ouf << "downstream_10k_20k\t" << size_down20 << "\n";
    ouf << "downstream_20k_50k\t" << size_down50 << "\n";
  
    infGff.close();
    infPi.close();
    ouf.close();
    return 0;
}
int gene_count_gene(parameter *para){
    string gffFile = (para -> inFile);
    string piFile = (para -> inFile2);
    string outFile = (para -> outFile);
    string outFile1 = outFile + ".genes";
    string chr = (para -> chr);
    double threshold = (para -> threshold);
    igzstream infGff ((gffFile).c_str(),ifstream::in);
    igzstream infPi ((piFile).c_str(),ifstream::in);
    ofstream ouf ((outFile).c_str());
    ofstream ouf1 ((outFile1).c_str());
    string line;
    vector<string> ll;
    set<int> withoutIntron;
    int start = 0, end = 0;
    int ps = 0, pe = 0;
    string strand = "";
    vector<int> startP(20000);
    vector<int> endP(20000);
    vector<int> strandP(20000);
    vector<int> genefeaturs(500000000);
    int gene_order = 0;
    // upstream50: 1; upstream20: 2;upstream10: 3; upstream5: 4;upstream2: 5;
    // gene: 20, 5utr: 7; cds: 8; intron: 9; 3utr: 10;
    // down50: 11; down20: 12; down10: 13; down5: 14; down2: 15;
    while(!infGff.eof()){
        getline(infGff,line);
        if(line.length()<1) continue;
        if(line[0]=='#' && line[2] =='#'&& withoutIntron.size() > 0) {
            for ( int i = start; i < end; ++i){
                if(withoutIntron.count(i) == 0){
                    genefeaturs[i] = 9;
                    //                    intron.insert(i);
                }
            }
            start = 0;
            end = 0;
            withoutIntron.clear();
            ps = 0;
            pe = 0;
            continue;
        };
        if(line[0]=='#') continue;
        ll.clear();
        split(line,ll," \t");
        if(ll[0] != chr) continue;
        if(ll[2] == "gene"){
            start = string2Int(ll[3]);
            end = string2Int(ll[4]);
            strand = ll[6];
            startP[gene_order] = start;
            endP[gene_order] = end;
            if(strand == "+"){
                strandP[gene_order] = 0;
            }else{
                strandP[gene_order] = 1;
            }
            gene_order++;
        }else if (ll[2] == "five_prime_UTR"){
            ps = string2Int(ll[3]);
            pe = string2Int(ll[4]);
            for (int i = ps; i < pe+1; ++i){
                genefeaturs[i]= 7;
                withoutIntron.insert(i);
            }
        }else if (ll[2] == "three_prime_UTR"){
            ps = string2Int(ll[3]);
            pe = string2Int(ll[4]);
            for (int i = ps; i < pe+1; ++i){
                genefeaturs[i] = 10;
                withoutIntron.insert(i);
            }
        }else if (ll[2] == "CDS"){
            ps = string2Int(ll[3]);
            pe = string2Int(ll[4]);
            for (int i = ps; i < pe+1; ++i){
                genefeaturs[i] = 8;
                withoutIntron.insert(i);
            }
        }
    }
    
    if(withoutIntron.size() > 1) {
        for ( int i = start; i < end; ++i){
            if(withoutIntron.count(i)==0){
                genefeaturs[i] = 9;
            }
        }
        withoutIntron.clear();
    }
    
    cout << "gff3 readed!" << endl;
    cout << "gene number is:\t" << gene_order << endl;
    double** geneMatrix = dmatrix(-1, gene_order + 1, -1, 16);
    
    //    cout << "UTR number is:\t" << gene_order << endl;
    double size_upstream = 0, size_utr5 = 0, size_cds = 0, size_intron = 0;
    double size_utr3 = 0, size_downstream = 0,size_intergenic = 0;
    double size_up5 = 0, size_up10 = 0, size_up15 = 0, size_up20 = 0, size_up50 = 0;
    double size_down5 = 0, size_down10 = 0, size_down15 = 0, size_down20 = 0, size_down50 = 0;
    int current_order = 0;
    while(!infPi.eof()){
        getline(infPi,line);
        if(line.length()<1) continue;
        if(line[0] == 'C') continue;
        ll.clear();
        split(line,ll," \t");
        if(ll[0] != chr) continue;
        int pos = string2Int(ll[1]);
        //        if (ll.size()<4){
        pos = string2Int(ll[1]);
        //        }else{
        //            pos = string2Int(ll[2]);
        //        }
        int size = ll.size()-1;
        if(size > 1){
            if (ll[size] == "-nan" || ll[size] == "nan" || ll[size] == "na" || ll[size] == "NA"|| ll[size] == "Inf"|| ll[size] == "-Inf") continue;
            double pi = string2Doublepos(ll[size]);
            if( pi > threshold){
                switch(genefeaturs[pos]){
                    case 0:
                        while ((startP[current_order] - pos) < 0){
                            if (current_order > gene_order - 1){
                                geneMatrix[current_order][0] +=pi;
                                size_intergenic += pi;
                                genefeaturs[pos]= 20;
                                break;
                            }
                            current_order++;
                            if (current_order % 100 == 0 ){
                                cout << "currrent_order is:\t" << current_order << endl;
                            }
                        }
                        if((startP[current_order] - pos) < 2000){
                            if(strandP[current_order] == 0){
                                size_upstream += pi;
                                geneMatrix[current_order][5] += pi;
                            }else{
                                size_downstream += pi;
                                geneMatrix[current_order][10] += pi;
                            }
                            genefeaturs[pos]= 20;
                            
                        }else if ((startP[current_order]- pos) < 5000){
                            if(strandP[current_order] == 0){
                                size_up5 += pi;
                                geneMatrix[current_order][4] += pi;
                            }else{
                                size_down5 += pi;
                                geneMatrix[current_order][11] += pi;
                            }
                            genefeaturs[pos]= 20;
                            
                        }else if ((startP[current_order]- pos) < 10000){
                            if(strandP[current_order] == 0){
                                size_up10+= pi;
                                geneMatrix[current_order][3] += pi;
                            }else{
                                size_down10+= pi;
                                geneMatrix[current_order][12] += pi;
                            }
                            genefeaturs[pos]= 20;
                            
                        }else if ((startP[current_order] - pos) < 20000){
                            if(strandP[current_order]== 0){
                                size_up20 += pi;
                                geneMatrix[current_order][2] += pi;
                            }else{
                                size_down20 += pi;
                                geneMatrix[current_order][13] += pi;
                            }
                            genefeaturs[pos]= 20;
                            
                        }else if ((startP[current_order] - pos) < 50000){
                            if(strandP[current_order] == 0){
                                size_up50 += pi;
                                geneMatrix[current_order][1] += pi;
                            }else{
                                size_down50 += pi;
                                geneMatrix[current_order][14] += pi;
                            }
                            genefeaturs[pos]= 20;
                            
                        }
                        
                        if( genefeaturs[pos]!=0) break;
                        
                        if((endP[current_order] - pos) < 2000){
                            if(strandP[current_order] == 1){
                                size_upstream += pi;
                                geneMatrix[current_order][5] += pi;
                            }else{
                                size_downstream += pi;
                                geneMatrix[current_order][10] += pi;
                            }
                            genefeaturs[pos]= 20;
                            
                        }else if ((endP[current_order]- pos) < 5000){
                            if(strandP[current_order] == 1){
                                size_up5 += pi;
                                geneMatrix[current_order][4]+=pi;
                            }else{
                                size_down5 += pi;
                                geneMatrix[current_order][11]+=pi;
                            }
                            genefeaturs[pos]= 20;
                            
                        }else if ((endP[current_order]- pos) < 10000){
                            if(strandP[current_order] == 1){
                                size_up10+= pi;
                                geneMatrix[current_order][3] += pi;
                            }else{
                                size_down10+= pi;
                                geneMatrix[current_order][12] +=pi;
                            }
                            genefeaturs[pos]= 20;
                            
                        }else if ((endP[current_order] - pos) < 20000){
                            if(strandP[current_order]== 1){
                                size_up20 += pi;
                                geneMatrix[current_order][2] += pi;
                            }else{
                                size_down20 += pi;
                                geneMatrix[current_order][13] += pi;
                            }
                            genefeaturs[pos]= 20;
                            
                        }else if ((endP[current_order] - pos) < 50000){
                            if(strandP[current_order] == 1){
                                size_up50 += pi;
                                geneMatrix[current_order][1] +=pi;
                            }else{
                                size_down50 += pi;
                                geneMatrix[current_order][14] +=pi;
                            }
                            genefeaturs[pos]= 20;
                            
                        }else{
                            size_intergenic+= pi;
                            geneMatrix[current_order][0] +=pi;
                            genefeaturs[pos]= 20;
                        }
                        break;
                    case 7:
                        size_utr5 +=pi ;
                        geneMatrix[current_order][6] +=pi;
                        break;
                    case 8:
                        size_cds +=pi ;
                        geneMatrix[current_order][7] +=pi;
                        break;
                    case 9:
                        size_intron +=pi ;
                        geneMatrix[current_order][8] +=pi;
                        break;
                    case 10:
                        size_utr3 +=pi ;
                        geneMatrix[current_order][9] +=pi;
                        break;
                    default:
                        break;
                }
            }
        }else{
            switch(genefeaturs[pos]){
                case 0:
                    while ((startP[current_order]- pos) < 0){
                        if (current_order % 100 == 0 ){
                            cout << "currrent_order is:\t" << current_order << endl;
                        }
                        if (current_order > gene_order - 1){
                            size_intergenic++;
                            geneMatrix[current_order][0]++;
                            genefeaturs[pos]= 20;
                            break;
                        }
                        current_order++;
                    }
                    if((startP[current_order] - pos) < 2000){
                        if(strandP[current_order] == 0){
                            size_upstream++;
                            geneMatrix[current_order][5]++;
                        }else{
                            size_downstream++;
                            geneMatrix[current_order][10]++;
                        }
                        genefeaturs[pos]= 20;
                    }else if ((startP[current_order]- pos) < 5000){
                        if(strandP[current_order]== 0){
                            size_up5++;
                            geneMatrix[current_order][4]++;
                        }else{
                            size_down5++;
                            geneMatrix[current_order][11]++;
                        }
                        genefeaturs[pos]= 20;
                    }else if ((startP[current_order] - pos) < 10000){
                        if(strandP[current_order] == 0){
                            size_up10++;
                            geneMatrix[current_order][3]++;
                        }else{
                            size_down10++;
                            geneMatrix[current_order][12]++;
                        }
                        genefeaturs[pos]= 20;
                        
                    }else if ((startP[current_order] - pos) < 20000){
                        if(strandP[current_order] == 0){
                            size_up20++;
                            geneMatrix[current_order][2]++;
                        }else{
                            size_down20++;
                            geneMatrix[current_order][13]++;
                        }
                        genefeaturs[pos]= 20;
                        
                    }else if ((startP[current_order] - pos) < 50000){
                        if(strandP[current_order] == 0){
                            size_up50++;
                            geneMatrix[current_order][1]++;
                        }else{
                            size_down50++;
                            geneMatrix[current_order][14]++;
                        }
                        genefeaturs[pos]= 20;
                    }else{
                        
                    }
                    if( genefeaturs[pos] != 0) break;
                    if((endP[current_order] - pos) < 2000){
                        if(strandP[current_order] == 1){
                            size_upstream ++;
                            geneMatrix[current_order][5]++;
                        }else{
                            size_downstream ++;
                            geneMatrix[current_order][10]++;
                        }
                        genefeaturs[pos]= 20;
                        
                    }else if ((endP[current_order]- pos) < 5000){
                        if(strandP[current_order] == 1){
                            size_up5 ++;
                            geneMatrix[current_order][4]++;
                        }else{
                            size_down5 ++;
                            geneMatrix[current_order][11]++;
                        }
                        genefeaturs[pos]= 20;
                        
                    }else if ((endP[current_order]- pos) < 10000){
                        if(strandP[current_order] == 1){
                            size_up10 ++;
                            geneMatrix[current_order][3]++;
                        }else{
                            size_down10 ++;
                            geneMatrix[current_order][12]++;
                        }
                        genefeaturs[pos]= 20;
                        
                    }else if ((endP[current_order] - pos) < 20000){
                        if(strandP[current_order]== 1){
                            size_up20 ++;
                            geneMatrix[current_order][2]++;
                        }else{
                            size_down20 ++;
                            geneMatrix[current_order][13]++;
                        }
                        genefeaturs[pos]= 20;
                        
                    }else if ((endP[current_order] - pos) < 50000){
                        if(strandP[current_order] == 1){
                            size_up50 ++;
                            geneMatrix[current_order][1]++;
                        }else{
                            size_down50 ++;
                            geneMatrix[current_order][14]++;
                        }
                        genefeaturs[pos]= 20;
                        
                    }else{
                        size_intergenic++;
                        geneMatrix[current_order][0]++;
                        genefeaturs[pos]= 20;
                    }
                    break;
                case 7:
                    size_utr5 ++ ;
                    geneMatrix[current_order][6]++;
                    break;
                case 8:
                    size_cds ++ ;
                    geneMatrix[current_order][7]++;
                    break;
                case 9:
                    size_intron ++ ;
                    geneMatrix[current_order][8]++;
                    break;
                case 10:
                    size_utr3 ++ ;
                    geneMatrix[current_order][9]++;
                    break;
                default:
                    break;
            }
        }
    }
    ouf << "region\tsum\n";
    ouf << "intergenic\t" << size_intergenic << "\n";
    ouf << "upstream_20k_50k\t" << size_up50 << "\n";
    ouf << "upstream_10k_20k\t" << size_up20 << "\n";
    ouf << "upstream_5k_10k\t" << size_up10<< "\n";
    ouf << "upstream_2k_5k\t" << size_up5 << "\n";
    
    ouf << "upstream_2k\t" << size_upstream << "\n";
    ouf << "five-UTR\t" << size_utr5 << "\n";
    ouf << "exon\t" << size_cds << "\n";
    ouf << "intron\t" << size_intron << "\n";
    ouf << "three-UTR\t" << size_utr3 << "\n";
    ouf << "downstream_2k\t" << size_downstream << "\n";
    ouf << "downstream_2k_5k\t" << size_down5 << "\n";
    ouf << "downstream_5k_10k\t" << size_down10 << "\n";
    ouf << "downstream_10k_20k\t" << size_down20 << "\n";
    ouf << "downstream_20k_50k\t" << size_down50 << "\n";
    for (int i = 0; i < gene_order-1; i++){
        for (int j = 0; j < 14; j++){
            ouf1 << geneMatrix[i][j] << "\t";
        }
        ouf1 << geneMatrix[i][14] << "\n";
    }
    infGff.close();
    infPi.close();
    ouf.close();
    ouf1.close();
    return 0;
}
int toXPCLR(parameter *para){
    string infile = (para->inFile);
    string infile2 = (para->inFile2);
    string infile3 = (para->bedFile);
    string outfile = (para->outFile);
    string snp = outfile+".snp";
    string geno = outfile+".geno";
    igzstream invcf ((infile.c_str()),ifstream::in);
    ifstream ingroup ((infile2.c_str()),ifstream::in);
    ifstream inrec ((infile3.c_str()),ifstream::in);
    ofstream snpf (snp.c_str());
    ofstream genof (geno.c_str());
    set<string> samples;
    string line;
    vector<string> ll;
    string chr = (para->chr);
    while(!ingroup.eof()){
        getline(ingroup,line);
        if(line.length()<1) continue;
        samples.insert(line);
    }
    cout << "group readed! group size is:\t" << samples.size() << endl;
    double** value = dmatrix(-1,500000000,-1,1);
    double recvalue = 0;
    int previous = 0;
    while(!inrec.eof()){
        getline(inrec,line);
        if(line.length()<1) continue;
        if(line[0]=='c'|| line[0]=='C') continue;
        ll.clear();
        split(line,ll," \t");
        if(ll[0]!=chr) continue;
        double bin = string2Double(ll[4])/1000000;
        if (bin == 0) bin = 0.001/1000000;
        cout << "bin is:" << bin << endl;
        int begin = string2Int(ll[1]);
        int end = string2Int(ll[2]);
        for (int cp = begin; cp < end; ++cp ){
            value[cp][0] = recvalue + bin * (cp-previous);
//            if(value[cp][0]==value[cp-1][0]) value[cp][0] = value[cp][0] + 0.000001;
        }
        previous = end;
        recvalue += bin*1000000;
    }
    cout << "value is: " << value[0][0] << "\t" << value[1400010][0] << endl;
    vector<int> samplePos ;
    while(!invcf.eof()){
        getline(invcf,line);
        if (line.length()<=0 )  {
            continue  ;
        }else if ( line[0] == '#' && line[1] == '#' )  {
            continue  ;
        }else if ( line[0] == '#' && line[1] != '#' ){
            ll.clear();
            split(line,ll,"\t");
            if  ( ll[0]  != "#CHROM"){
                continue  ;
            }else{
                for (int i = 9; i< ll.size();++i){
                    if(samples.count(ll[i])==1){
                        samplePos.push_back(i);
                    }
                }
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
    cout << samplePos.size() << " sample detected!" << endl;
    
    while (!invcf.eof()){
        getline(invcf,line);
        if(line.length()<1) continue;
        ll.clear();
        split(line,ll," \t");
        for (int i = 0; i < samplePos.size()-1;++i){
            if(ll[samplePos[i]][0]=='0'&&ll[samplePos[i]][2]=='0'){
                genof << "0 0 " ;
            }else if (ll[samplePos[i]][0]=='1'&&ll[samplePos[i]][2]=='1'){
                genof << "1 1 " ;
            }else if(ll[samplePos[i]][0]=='0'&&ll[samplePos[i]][2]=='1'){
                genof << "0 1 " ;
            }else{
                genof << "9 9 " ;
            }
        }
        if(ll[samplePos[samplePos.size()-1]][0]=='0'&&ll[samplePos[samplePos.size()-1]][2]=='0'){
            genof << "0 0\n" ;
        }else if (ll[samplePos[samplePos.size()-1]][0]=='1'&&ll[samplePos[samplePos.size()-1]][2]=='1'){
            genof << "1 1\n" ;
        }else if(ll[samplePos[samplePos.size()-1]][0]=='0'&&ll[samplePos[samplePos.size()-1]][2]=='1'){
            genof << "0 1\n" ;
        }else{
            genof << "9 9\n" ;
        }
        snpf << " rs" << ll[0]<<"_" << ll[1] << "\t" << ll[0]<< "\t" << value[string2Int(ll[1])][0] << "\t" << ll[1] << "\t" << ll[3] << "\t" << ll[4] << "\n";
    }
    invcf.close();
    ingroup.close();
    inrec.close();
    snpf.close();
    genof.close();
    return 1;
}
int toXPCLRsnp(parameter *para){
    string infile = (para->inFile);
    string infile3 = (para->bedFile);
    string outfile = (para->outFile);
    string snp = outfile+".snp";
    igzstream invcf ((infile.c_str()),ifstream::in);
    ifstream inrec ((infile3.c_str()),ifstream::in);
    ofstream snpf (snp.c_str());
    string line;
    vector<string> ll;
    string chr = (para->chr);
    double** value = dmatrix(-1,500000000,-1,1);
    double recvalue = 0;
    int previous = 0;
    while(!inrec.eof()){
        getline(inrec,line);
        if(line.length()<1) continue;
        if(line[0]=='c'|| line[0]=='C') continue;
        ll.clear();
        split(line,ll," \t");
        if(ll[0]!=chr) continue;
        double bin = string2Double(ll[4])/1000000;
        if (bin == 0) bin = 0.001/1000000;
//        cout << "bin is:" << bin << endl;
        int begin = string2Int(ll[1]);
        int end = string2Int(ll[2]);
        for (int cp = begin; cp < end; ++cp ){
            value[cp][0] = recvalue + bin * (cp-previous);
            //            if(value[cp][0]==value[cp-1][0]) value[cp][0] = value[cp][0] + 0.000001;
        }
        previous = end;
        recvalue += bin*1000000;
    }
    cout << "recombination readed! Total genetic length is:\t" << recvalue << endl;
//    cout << "value is: " << value[0][0] << "\t" << value[1400010][0] << endl;
    vector<int> samplePos ;
    while(!invcf.eof()){
        getline(invcf,line);
        if (line.length()<=0 )  {
            continue  ;
        }else if ( line[0] == '#' && line[1] == '#' )  {
            continue  ;
        }else if ( line[0] == '#' && line[1] != '#' ){
            ll.clear();
            split(line,ll,"\t");
            if  ( ll[0]  != "#CHROM"){
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
    while (!invcf.eof()){
        getline(invcf,line);
        if(line.length()<1) continue;
        ll.clear();
        split(line,ll," \t");
        snpf << " rs" << ll[0]<<"_" << ll[1] << "\t" << ll[0]<< "\t" << value[string2Int(ll[1])][0] << "\t" << ll[1] << "\t" << ll[3] << "\t" << ll[4] << "\n";
    }
    invcf.close();
    inrec.close();
    snpf.close();
    return 1;
}
int toV11(parameter *para){
    string infile = (para->inFile);
    string outfile = (para->outFile);
    igzstream invcf ((infile.c_str()),ifstream::in);
    ofstream ouf (outfile.c_str());
    string line;
    vector<string> ll;
    vector<string> lll;
    while(!invcf.eof()){
        getline(invcf,line);
        if(line.length()<1) continue;
        if(line[0]=='#'){
            ouf << line ;
        }else{
            ll.clear();
            split(line,ll," \t");
            for (int i = 0; i <7; ++i){
                ouf << ll[i] << "\t";
            }
            ouf << "." ;
            ouf << "\t" << "GT:AD:GL";
            for (int i = 9; i< ll.size(); ++i){
                lll.clear();
                split(ll[i],lll,":");
                ouf << "\t" << lll[0] << ":" << lll[1]<<":"<< lll[lll.size()-1];
            }
        }
        ouf << "\n";
    }
    invcf.close();
    ouf.close();
    return 0;
}
int toSFS(parameter *para){
    string infile = (para->inFile);
    string outfile = (para->outFile);
    igzstream invcf ((infile.c_str()),ifstream::in);
    ofstream ouf (outfile.c_str());
    string line;
    vector<string> ll;
    string c = "ACGT";
    while(!invcf.eof()){
        getline(invcf,line);
        if(line.length()<1) continue;
        if(line[0]=='#') continue;
        ll.clear();
        split(line,ll," \t");
        size_t ref = c.find(ll[3]);
        size_t alt = c.find(ll[4]);
        if (ref==std::string::npos||alt==std::string::npos){
            cerr << "vcf file error!" << endl;
            return 1;
        }
        vector<int> N4(4);
        vector<int> O4(4);
        vector<int> D4(4);
        int re = static_cast<int>(ref);
        int al = static_cast<int>(alt);
        for (int i = 9; i < ll.size()-2; ++i){
            if(ll[i][0] == '0' & ll[i][2] == '0'){
                N4[re] ++;
            }else if (ll[i][0]=='1' & ll[i][2] == '1'){
                N4[al] ++;
            }else{
                continue;
            }
        }
        int p = ll.size()-2;
        if(ll[p][0]=='0' && ll[p][2]=='0'){
            O4[re] ++;
        }else if(ll[p][1]=='1' && ll[p][1]=='1') {
            O4[al] ++;
        }
        p = ll.size()-1;
        if(ll[p][0]=='0' && ll[p][2]=='0'){
            D4[re] ++;
        }else if(ll[p][1]=='1' && ll[p][1]=='1') {
            D4[al] ++;
        }
        ouf << N4[0] << "," << N4[1] << ","<< N4[2] << ","<< N4[3] << "\t"<< O4[0] << ","<< O4[1] << ","<< O4[2]  << ","<< O4[3] << "\t"<< D4[0] << ","<< D4[1] << ","<< D4[2]  << ","<< D4[3]<< "\n";
    }
    invcf.close();
    ouf.close();
    return 0;
}

int getAlleleFrequency(parameter *para){
    string infile = (para->inFile);
    string outfile = (para->outFile);
    igzstream invcf ((infile.c_str()),ifstream::in);
    ofstream ouf (outfile.c_str());
    string line;
    vector<string> ll;
    set<string> names = getSubgroup(para->subPop);
//    vector<int> pos = getSubPos(names,allNames);
    return 0;
}

int LDmean(parameter *para){
    string infile = (para->inFile);
    string outfile = (para->outFile);
    int bin = para->size;
    igzstream invcf ((infile.c_str()),ifstream::in);
    ofstream ouf (outfile.c_str());
    string line;
    vector<string> ll;
    double ** rsquare = dmatrix(-1,100001,-1,4);
    int maxBin = 1;
    while(!invcf.eof()){
        getline(invcf,line);
        if(line.length()<1) continue;
        ll.clear();
        split(line,ll," \t");
        int l = string2Int(ll[0]);
        if(l==1){
            rsquare[0][0] += string2Double(ll[1]);
            rsquare[0][1] ++;
        }else{
            int l1 = (int)ceil(string2Double(ll[0])/bin);
            if(l1 >= maxBin) maxBin = l1+1;
            rsquare[l1][0] += string2Double(ll[1]);
            rsquare[l1][1] ++;
        }
    }
    ouf << "Distance(" << bin/1000 <<" kb)\tsum\tnumber\tmean\n";
    for (int i = 0; i < maxBin;++i){
        ouf << i <<"\t" << rsquare[i][0] << "\t"<< rsquare[i][1] << "\t"<< rsquare[i][0]/rsquare[i][1] << "\n";
    }
    invcf.close();
    ouf.close();
    //    vector<int> pos = getSubPos(names,allNames);
    return 0;
}

int pwFrequence(parameter *para){
    string infile = (para->inFile);
    string gf1 = (para -> inFile2 );
    string gf2 = (para -> inFile3);
    string outfile = (para->outFile);
    igzstream invcf ((infile.c_str()),ifstream::in);
    ofstream ouf (outfile.c_str());
    string line;
    set<string> name1 = getSubgroup(gf1);
    set<string> name2 = getSubgroup(gf2);
//    set<string> name = getSubgroup(gf1);
//    name.insert(name2.begin(), name2.end());
    vector<int> na1;
    vector<int> na2;
    vector<int> na;
    vector<string> ll;
    double** maf = dmatrix(-1,51,-1,3);
    double sum = 0;
    while(!invcf.eof()){
        getline(invcf,line);
        if(line.length()<1) continue;
        if(line[0]=='#' && line[1] == '#') continue;
        ll.clear();
        split(line,ll," \t");
        if(line[0]=='#' && line[1] == 'C') {
            na1 = getPos(ll,name1);
            na2 = getPos(ll,name2);
//            na = getPos(ll,name);
            continue;
        }
        double mf1 = MAF(ll,na1);
        double mf2 = MAF(ll,na2);
        double mf = MAF(ll);
        if(mf1 > 0 && mf2 >0){
            maf[(int)ceil(mf/0.01)][0] ++;
            sum++;
        }else if (mf1 > 0 && mf2 ==0){
            maf[(int)ceil(mf/0.01)][1] ++;
            sum++;
        }else if (mf1 == 0 && mf2 > 0){
            maf[(int)ceil(mf/0.01)][2] ++;
            sum++;
        }else{
            continue;
        }
    }
    ouf << "maf\tshared\tgroup1\tgroup2\n";
    for(int i = 0; i < 51; ++i){
        ouf << 0.01*i << "\t" << maf[i][0] << "\t" << maf[i][1] <<"\t" << maf[i][2] << "\n";
    }
    invcf.close();
    ouf.close();
    return 0;
}

int writeMAF(parameter *para){
    string infile = (para->inFile);
    string gf1 = (para -> inFile2 );
    string outfile = (para->outFile);
    igzstream invcf ((infile.c_str()),ifstream::in);
    ofstream ouf (outfile.c_str());
    string line;
    set<string> name1 = getSubgroup(gf1);
    //    set<string> name = getSubgroup(gf1);
    //    name.insert(name2.begin(), name2.end());
    vector<int> na1;
    vector<string> ll;
    ouf << "chr\tpos\tmaf\n";
    while(!invcf.eof()){
        getline(invcf,line);
        if(line.length()<1) continue;
        if(line[0]=='#' && line[1] == '#') continue;
        ll.clear();
        split(line,ll," \t");
        if(line[0]=='#' && line[1] == 'C') {
            na1 = getPos(ll,name1);
            continue;
        }
        double mf1 = MAF(ll,na1);
        ouf << ll[0] << "\t" << ll[1] << "\t" << mf1 << "\n";
    }
    
    invcf.close();
    ouf.close();
    return 0;
}

int getDerivedAllele(parameter *para){
    string infile = (para->inFile);
    string outfile = (para->outFile);
    igzstream invcf ((infile.c_str()),ifstream::in);
    ofstream ouf (outfile.c_str());
    string line;
    vector<string> ll;
    while(!invcf.eof()){
        getline(invcf,line);
        if(line.length()<1) continue;
        if(line[0]=='#') {
            ouf << line << "\n";
            continue;
        };
        ll.clear();
        split(line,ll," \t");
        int size = ll.size();
        if(ll[size-2][0] != '.' && ll[size-1][0] != '.'){
            if(ll[size-2][0]!=ll[size-1][0]){
                continue;
            }else{
//                if(ll[size-2][0] == '1'){
//                    string tmp = ll[3];
//                    ll[3] = ll[4];
//                    ll[4] = tmp;
//                }
                ouf << ll[0];
                for(int i = 1; i < size; ++i){
                    ouf << "\t" << ll[i];
                }
                ouf << "\n";
            }
        }else{
            continue;
        }
        
    }
    
    invcf.close();
    ouf.close();
    return 0;
}
int cp(parameter *para){
    string infile = (para->inFile);
    string gf1 = (para -> inFile2 );
    string gf2 = (para -> inFile3);
    string outfile = (para->outFile);
    igzstream invcf ((infile.c_str()),ifstream::in);
    ofstream ouf (outfile.c_str());
    string line;
    set<string> name1 = getSubgroup(gf1);
    set<string> name2 = getSubgroup(gf2);
    vector<int> na1;
    vector<int> na2;
    vector<int> na;
    vector<string> ll;
    vector<int> number(9);
    for (int i=0; i <9; ++i){
        number[i] = 0;
    }
    int all = 0, derived = 0;
    while(!invcf.eof()){
        getline(invcf,line);
        if(line.length()<1) continue;
        if(line[0]=='#' && line[1] == '#') {
        };
        ll.clear();
        split(line,ll," \t");
        if(line[0]=='#' && line[1] == 'C') {
            na1 = getPos(ll,name1);
            na2 = getPos(ll,name2);
            if(na1.size() < 1) break;
            if(na2.size() < 1) break;
            continue;
        }
        
        if(na1.size() < 1) continue;
        if(na2.size() < 1) continue;
        
        all++;
        double mf1 = ref(ll,na1);
        double mf2 = ref(ll,na2);
        char ref = ll[ll.size()-1][0];
        if(ref == '1'){
            mf1 = 1 - mf1;
            mf2 = 1 - mf2;
        }
        if (mf1 == 0){
            if(mf2 == 0){
                number[0]++;
            }else if (mf2 == 1){
                number[2]++;
            }else{
                number[1]++;
            }
        }else if (mf1 == 1){
            if(mf2 == 0){
                number[6]++;
            }else if (mf2 == 1){
                number[8]++;
            }else{
                number[7]++;
            }
        }else{
            if(mf2 == 0){
                number[3]++;
            }else if (mf2 == 1){
                number[5]++;
            }else{
                number[4]++;
            }
        }
    }
    ouf << all << "\t" << number[0] ;
    for (int i = 1; i < 9; ++i){
        ouf << "\t" << number[i];
    }
    
    ouf << "\n";
    invcf.close();
    ouf.close();
    
    return 0;
}
double getSum(string & infile){
    double sum = 0;
    igzstream invcf ((infile.c_str()),ifstream::in);
    string line;
    vector<string> ll;
    while(!invcf.eof()){
        getline(invcf,line);
        if(line.length() < 1) continue;
        if(line[0] == 'C'||line[0]=='c') continue;
        ll.clear();
        split(line,ll," \t");
        if(ll[2]== "-nan" || ll[2]== "nan" || ll[2] == "inf" || ll[2] =="-inf" || ll[2] == "NA") continue;
        sum += string2Double(ll[2]);
    }
    invcf.close();
    return sum;
}
int DiversityReduction(parameter *para){
    string infile = (para->inFile);
    string gf1 = (para -> inFile2 );
    string gf2 = (para -> inFile3);
    string outfile = (para->outFile);
    igzstream invcf ((infile.c_str()),ifstream::in);
    igzstream g1 ((gf1.c_str()),ifstream::in);
    igzstream g2 ((gf2.c_str()),ifstream::in);
    ofstream ouf (outfile.c_str());
    string line;
    vector<string> ll;
    vector<string> file1;
    vector<string> file2;
    vector<string> sub;
    split(gf1,sub,"/");
    string folder = "" ;
    vector<int> chrSize(42);
    while(!invcf.eof()){
        getline(invcf,line);
        if(line.length() < 1) continue;
        ll.clear();
        split(line,ll," \t");
        chrSize[string2Int(ll[0])-1] = string2Int(ll[1]);
    }
    invcf.close();
    
    while(!g1.eof()){
        getline(g1,line);
        if(line.length() < 1) continue;
        file1.push_back(line);
    }
    g1.close();
    
    while(!g2.eof()){
        getline(g2,line);
        if(line.length() < 1) continue;
        file2.push_back(line);
    }
    g2.close();
    
    vector<double> gr1(file1.size());
    vector<double> gr2(file2.size());
    long int allC = 0;
    double all1 = 0, all2 = 0;
    for (int i = 0; i < gr1.size(); ++i){
        double tmp = getSum(file1[i]);
        gr1[i] = tmp;
        all1 += tmp;
        long int count = chrSize[getChr(file1[i])-1];
        gr1[i] = gr1[i]/count;
        allC += count;
//        cout << "allC is:\t" << allC << endl;
    }
    
    for (int i = 0; i < gr2.size(); ++i){
        double tmp = getSum(file2[i]);
        gr2[i] = tmp;
        all2 += tmp;
        long int count = chrSize[getChr(file1[i])-1];
        gr2[i] = gr2[i]/count;
//        cout << "all2 is: " << all2 << endl;
    }
    srand((int)time(NULL));
    for (int i = 0; i < 2000; ++i){
        int a = Random(0, gr1.size()-1);
        int b= Random(0, gr2.size()-1);
        if(gr2[b]>gr1[a]) {
            ouf << gr1[a] << "\t" << gr2[b] << "\t" <<  -gr1[a]/gr2[b] << "\n";
        }else{
            ouf << gr1[a] << "\t" << gr2[b] << "\t" << (1-gr2[b]/gr1[a]) << "\n";
        }
    }
//    cout << "all1 is: " << all1 << ";all2 is: " << all2 << endl;
    ouf << all1/allC << "\t" << all2/allC << "\t" << (1 - all2/all1) << "\n";
    ouf.close();
    return 1;
}

int getGffDensity(parameter *para){
    string infile = (para->inFile);
    string outfile = (para->outFile);
    int windowSize = (para->size );
    igzstream inbed ((infile.c_str()),ifstream::in);
    ofstream ouf (outfile.c_str());
    string line;
    vector <string> ll;
    map<string,int> chrSize;
    int sum = 0;
    int prePos = 1;
    string chr = "";
    while(!inbed.eof()){
        getline(inbed,line);
        if(line.length()<0) continue;
        if(line[0] == '#' && line[1] == '0'){
            ll.clear();
            split(line,ll," \t");
            if(ll.size() < 4) continue;
            chrSize.insert(pair<string,int>(ll[1],string2Int(ll[3])));
            continue;
        };
        ll.clear();
        split(line,ll, " \t");
        if(ll[2] != "gene") continue;
        if(chr != ll[0]){
            chr = ll[0];
            sum = 0;
            prePos = 1;
        }
        int cp = string2Int(ll[3]);
        if(cp < prePos) {
            cerr << "please check start position!" << endl;
            return 1;
        }
        while (cp > (prePos + windowSize)){
            ouf << chr << "\t" << prePos << "\t" << (prePos + windowSize) << "\t" << sum << "\n";
            sum = 0;
            prePos += windowSize;
        }
        sum++;
    }
    cout << "finished!" << endl;
    ouf << chr << "\t" << prePos << "\t" << chrSize[chr] << "\t" << sum << "\n";
    inbed.close();
    ouf.close();
    return 0;
}
#endif /* FileFunctions_h */
