//
//  DataClass.h
//  WGS
//
//  Created by Yao Zhou on 2018/12/4.
//  Copyright © 2018 Yao Zhou. All rights reserved.
//

#ifndef DataClass_h
#define DataClass_h
#define NR_END 1
#define FREE_ARG char*
using namespace std;
void nrerror(char error_text[]);
class parameter {
public:
    string inFile;
    string outFile;
    string bedFile;
    string inFile2;
    string inFile3;
    string model;
    string type;
    string subPop;
    string logFile;
    string chr;
    string flag;
    double  MQ;
    double FS;
    double MQRankSum;
    double ReadPosRankSum;
    double BSQRankSum;
    double SOR;
    double minDepth;
    double maxDepth;
    double depthSD;
    double a;
    double b; // y = a + bx
    int size;
    int headLine;
    double threshold;
    int maxLength;
    double r;
    bool isBed;
    bool recode;
    double mean;
    bool noNeg;
    string headerC;
    set<int> pos; // used for change chromosome pos;
    parameter()
    {
        inFile = "";
        inFile2 = "";
        inFile3 = "";
        outFile = "";
        subPop = "";
        bedFile = "";
        flag = "";
        MQ = 30.0;
        MQRankSum = -12.5;
        FS = 60.0;
        ReadPosRankSum = -8;
        BSQRankSum  = 0.0;
        SOR = 3.0;
        model = "wc";
        type = "qualityFilter";
        logFile = "";
        isBed = false;
        pos;
        headLine = 0;
        noNeg = false;
        size = 1000000;
        headerC = "#";
        recode = false;
        mean = 0.0;
        r = 0.01;
        a = 0.0;
        b = 0.0;
        maxLength = 500000000;
        chr = "chr1";
        threshold = -0.00001;
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
class cds {
public:
    map < string ,map <string,vector < vector <int> >>> CDS; // cds_map(gene_map(transcript_vector(pos_vecotrlength)))
    cds(){
        
    }
};

int **imatrix(long nrl, long nrh, long ncl, long nch)
/* allocate a int matrix with subscript range m[nrl..nrh][ncl..nch] */
{
    long i, nrow=nrh-nrl+1,ncol=nch-ncl+1;
    int **m;
    
    /* allocate pointers to rows */
    m=(int **) malloc((size_t)((nrow+NR_END)*sizeof(int*)));
    if (!m) cerr << "allocation failure 1 in matrix()" << endl;
    m += NR_END;
    m -= nrl;
    /* allocate rows and set pointers to them */
    m[nrl]=(int *) malloc((size_t)((nrow*ncol+NR_END)*sizeof(int)));
    if (!m[nrl]) cerr << "allocation failure 2 in matrix()" << endl;
    m[nrl] += NR_END;
    m[nrl] -= ncl;
    
    for(i=nrl+1;i<=nrh;i++) m[i]=m[i-1]+ncol;
    for(i=nrl+1;i<=nrh;i++){
        for (long j = ncl;j<=nch;++j){
            m[i][j] = 0;
        }
    }
    /* return pointer to array of pointers to rows */
    return m;
}

 double **dmatrix(long nrl, long nrh, long ncl, long nch)
/* allocate a int matrix with subscript range m[nrl..nrh][ncl..nch] */
{
    long i, nrow=nrh-nrl+1,ncol=nch-ncl+1;
     double **m;
    
    /* allocate pointers to rows */
    m=(double **) malloc((size_t)((nrow+NR_END)*sizeof(double*)));
    if (!m) cerr << "allocation failure 1 in matrix()" << endl;
    m += NR_END;
    m -= nrl;
    /* allocate rows and set pointers to them */
    m[nrl]=(double *) malloc((size_t)((nrow*ncol+NR_END)*sizeof(double)));
    if (!m[nrl]) cerr << "allocation failure 2 in matrix()" << endl;
    m[nrl] += NR_END;
    m[nrl] -= ncl;
    
    for(i=nrl+1;i<=nrh;i++) m[i]=m[i-1]+ncol;
    for(i=nrl+1; i <=nrh;i++){
        for (long j = ncl;j<=nch;++j){
            m[i][j] = 0;
        }
    }
    /* return pointer to array of pointers to rows */
    return m;
}


void free_imatrix(int **m, long nrl, long nrh, long ncl, long nch)
/* free an int matrix allocated by imatrix() */
{
    free((FREE_ARG) (m[nrl]+ncl-NR_END));
    free((FREE_ARG) (m+nrl-NR_END));
}

class gene{
// 1-based, and inclusive on both side
public:
    int start;
    int end;
    int length;
    string ID;
    string strand;
    string chr;
    gene(string line){
        vector<string> ll;
        ll.clear();
        split(line,ll,"\t");
        start = string2Int(ll[3]);
        end = string2Int(ll[4]);
        chr = ll[0];
        strand = ll[6];
        vector<string> tmp;
        split(ll[8], tmp,";");
        ll.clear();
        split(tmp[0],ll,"=");
        ID = ll[1];
        ll.clear();
        tmp.clear();
        length = end - start + 1;
    }
};
class transcript{
// 1-based, and inclusive on both side
public:
    int start;
    int end;
    int length;
    string ID;
    string strand;
    string chr;
    string parent;
    void getTranscript(string line){
        vector<string> ll;
        split(line,ll,"\t");
        start = string2Int(ll[3]);
        end = string2Int(ll[4]);
        chr = ll[0];
        strand = ll[6];
        vector<string> tmp;
        split(ll[8], tmp,";Parent=");
        ll.clear();
        split(tmp[1],ll,";");
        parent = ll[0];
        ll.clear();
        split(tmp[0],ll,"=");
        ID = ll[1];
        ll.clear();
        tmp.clear();
        length = end - start + 1;
    }
};
class exon{
    // 1-based, and inclusive on both side
public:
    int start;
    int end;
    int length;
    string ID;
    string strand;
    string chr;
    string parent;
    void getexon(string line){
        vector<string> ll;
        split(line,ll,"\t");
        start = string2Int(ll[3]);
        end = string2Int(ll[4]);
        chr = ll[0];
        strand = ll[6];
        vector<string> tmp;
        split(ll[8], tmp,";Parent=");
        ll.clear();
        split(tmp[1],ll,";");
        parent = ll[0];
        ll.clear();
        split(tmp[0],ll,"=");
        ID = ll[1];
        ll.clear();
        tmp.clear();
        length = end - start + 1;
    }
};
class CDS{
    // 1-based, and inclusive on both side
public:
    int start;
    int end;
    int length;
    string ID;
    string strand;
    string chr;
    string parent;
    void getCDS(string line){
        vector<string> ll;
        split(line,ll,"\t");
        start = string2Int(ll[3]);
        end = string2Int(ll[4]);
        chr = ll[0];
        strand = ll[6];
        vector<string> tmp;
        split(ll[8], tmp,";Parent=");
        ll.clear();
        split(tmp[1],ll,";");
        parent = ll[0];
        ll.clear();
        split(tmp[0],ll,"=");
        ID = ll[1];
        ll.clear();
        tmp.clear();
        length = end - start + 1;
    }
};
class utr5{
    // 1-based, and inclusive on both side
public:
    int start;
    int end;
    int length;
    string ID;
    string strand;
    string chr;
    string parent;
    void getUtr5(string line){
        vector<string> ll;
        split(line,ll,"\t");
        start = string2Int(ll[3]);
        end = string2Int(ll[4]);
        chr = ll[0];
        strand = ll[6];
        vector<string> tmp;
        split(ll[8], tmp,";Parent=");
        ll.clear();
        split(tmp[1],ll,";");
        parent = ll[0];
        ll.clear();
        split(tmp[0],ll,"=");
        ID = ll[1];
        ll.clear();
        tmp.clear();
        length = end - start + 1;
    }
};
class utr3{
    // 1-based, and inclusive on both side
public:
    int start;
    int end;
    int length;
    string ID;
    string strand;
    string chr;
    string parent;
    void getUtr3(string line){
        vector<string> ll;
        split(line,ll,"\t");
        start = string2Int(ll[3]);
        end = string2Int(ll[4]);
        chr = ll[0];
        strand = ll[6];
        vector<string> tmp;
        split(ll[8], tmp,";Parent=");
        ll.clear();
        split(tmp[1],ll,";");
        parent = ll[0];
        ll.clear();
        split(tmp[0],ll,"=");
        ID = ll[1];
        ll.clear();
        tmp.clear();
        length = end - start + 1;
    }
};
class intron{
public:
    int start;
    int end;
    int length;
    string ID;
    string strand;
    string chr;
    string parent;
    void getIntron(int starts, int ends, string IDs, string strands,string chrs, string parents){
        start = starts;
        end = ends;
        ID = IDs;
        strand = strands;
        chr = chrs;
        parent = parents;
        length = end - start + 1;
    }
};

class gff3 {
private:
public:
    map<string,gene> genes;
    map<string,vector<transcript>> transcripts;
    map<string,transcript> long_transcripts;
    map<string,vector<utr5>> utr5s;
    map<string,vector<utr3>> utr3s;
    map<string,vector<exon>> exons;
//    map<string,vector<intron>> introns;
    map<string,vector<CDS>> CDSs;
    gff3(string inFile,string chr){
        readGff(inFile,chr);
    }
    
    gff3(){
        cout << "No gff3 file!" << endl;
    }
    
    void readGff(string inFile,string chr){
        igzstream inf (inFile.c_str(),fstream::in);
        if (inf.fail()){
            cerr << "Read gff3 failed!" << endl;
        }
        string line;
        vector<string> ll;
        vector<string> name,IDa;
        bool geneReaded = false;
        int exonNum = 0;
        while (!inf.eof()){
            getline(inf, line);
            if (line.length() < 1) continue;
            if (line[0] == '#') continue;
            if (line.substr(0,1) == "#") continue;
        
            ll.clear();
            cout << line << endl;
            split(line,ll,"\t");
            if(ll[0]!=chr) continue;
            if (ll[2] == "gene"){
                gene g(line);
                genes.insert(pair<string,gene>(g.ID,g));
            }else if (ll[2] == "mRNA"){
                transcript g;
                g.getTranscript(line);
                vector<transcript> t;
                if(transcripts.count(g.parent)==1){
                    t = transcripts[g.parent];
                }
                t.push_back(g);
                transcripts.insert(pair<string,vector<transcript>>(g.parent,t));
            }else if (ll[2] == "exon"){
                exon g;
                g.getexon(line);
                vector<exon> t;
                if(exons.count(g.parent)==1){
                    t = exons[g.parent];
                }
                t.push_back(g);
                exons.insert(pair<string,vector<exon>>(g.parent,t));
                
            }else if (ll[2] == "CDS"){
                CDS g;
                g.getCDS(line);
                vector<CDS> t;
                if(CDSs.count(g.parent)==1){
                    t = CDSs[g.parent];
                }
                t.push_back(g);
                CDSs.insert(pair<string,vector<CDS>>(g.parent,t));
            }else if (ll[2] == "five_prime_UTR"){
                utr5 g;
                g.getUtr5(line);
                vector<utr5> t;
                if(utr5s.count(g.parent)==1){
                    t = utr5s[g.parent];
                }
                t.push_back(g);
                utr5s.insert(pair<string,vector<utr5>>(g.parent,t));
            }else if (ll[2] == "three_prime_UTR"){
                utr3 g;
                g.getUtr3(line);
                vector<utr3> t;
                if(utr3s.count(g.parent)==1){
                    t = utr3s[g.parent];
                }
                t.push_back(g);
                utr3s.insert(pair<string,vector<utr3>>(g.parent,t));
            }else {
                cout << line << endl;
                cerr << "pattern failed" << endl;
            }
        }
        map<string,gene>::iterator it;
        it = genes.begin();
        while(it!= genes.end()){
            string IDs = it->first;
            gene g = it->second;
            transcript trans;
            vector<transcript> tl = transcripts[IDs] ;
            if(tl.size()>1){
                int len = tl[0].length;
                int p = 0;
                for(int i = 1; i < tl.size();++i){
                    if(tl[i].length > len){
                        len = tl[i].length;
                        p = i;
                    }
                }
                trans = tl[p];
            }else{
                trans = tl[0];
            }
            long_transcripts.insert(pair<string,transcript>(IDs,trans));
            it++;
        }
        inf.close();
    }
    
};
#endif /* DataClass_h */
