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
    
//    for(i=nrl+1;i<=nrh;i++) m[i]=m[i-1]+ncol;
    for(i = nrl;i<nrh;i++){
        for (long j = ncl;j < nch;++j){
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
    
//    for(i=nrl+1;i<=nrh;i++) m[i]=m[i-1]+ncol;
    for(i = nrl; i < nrh;i++){
        for (long j = ncl;j < nch; ++j){
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

#endif /* DataClass_h */
