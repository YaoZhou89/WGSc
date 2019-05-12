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
class gff3 {
    
private:
    
public:
    // 了解set,map,hash_map, Multi_set等，选择合适的容器
    int geneNum;
    int transcriptNum;
    map<string, vector<int>> geneLength;
    map<string, int> transprit;
    map<string,int> exonNumber;
    map<string,int> intronNumber;
    set<string> genes;
    // 定义了一个空参数构造函数和一个有参数的构造函数；
    gff3(string inFile,string geneID){
        cout << "inFile is:\t" << inFile << endl;
        readGff(inFile);
        cout << "gene number is:\t" << geneNum << endl;
        cout << "transcript number is:\t" << transcriptNum << endl;
        cout << "Gene "<< geneID << "\texon number is:\t" << exonNumber[geneID] << endl;
    }
    
    gff3(){
        cout << "this just is a demo!" << endl;
    }
    
    //定义一个函数对gene进行初始化；
    // 这里没有进行优化，根据你们所学的知识，可以考虑对这里的gene变量进行优化
    
    // void 表示函数没有返回值；
    // 注意这里的geneNum等变量的作用范围（全局变量）；
    void readGff(string inFile){
        //        map<string, map<string,vector<int>>> gene;
        igzstream inf (inFile.c_str(),fstream::in);
        if (inf.fail()){
            cerr << "Read gff3 failed!" << endl;
        }
        string line;
        vector<string> ll;
        vector<string> name,IDa;
        
        bool geneReaded = false;
        int exonNum = 0;
        string geneIDpre;
        while (!inf.eof()){
            // 按行读取文件，读入的数据存在line里；
            getline(inf, line);
            if (line.length() < 1) continue; // 有时候会读到空行，直接跳过去，这一步以后不管有没有空行都加上；
            if (line[0] == '#') continue; //这里取的第一位，返回值是char类型，所以==后面用了单引号，不能用双引号；
            if (line.substr(0,1) == "#") continue; //这一行和上一行是同一个含义，但是substr的返回值类型是string,所以==后面用了双引号
            ll.clear(); // 循环中每次使用前，都要清空，否则上次产生的值还在
            split(line, ll," \t"); //对读入的文件进行分割，分割符为tab
            
            // 提取基因的ID，例如，ID=gene:Solyc00g005084.1; 提取后ID为Solyc00g005084
            name.clear();
            IDa.clear();
            split(ll[8],name,".");
            split(name[0],IDa,":");
            string ID = IDa[1]; // while循环里的变量，出了这个循环，就不能用了，注意变量的作用范围
            if (ll[2] == "gene"){
                if(!geneReaded){
                    geneReaded = true;
                }else{
                    exonNumber.insert(map<string,int>::value_type(geneIDpre,exonNum));
                }
                genes.insert(ID);
                exonNum = 0;
                ++geneNum;
                int length = string2Int(ll[4]) - string2Int(ll[3]) + 1;
                if (geneLength.count(ll[2])>0){
                    vector<int> lens = geneLength[ll[2]];
                    lens.push_back(length);
                    geneLength[ll[2]] = lens;
                }else{
                    vector<int> lens;
                    lens.push_back(length);
                    geneLength[ll[2]] = lens;
                }
                geneIDpre = ID;
            }else if (ll[2] == "mRNA"){
                ++transcriptNum;
                genes.insert(ID);
            }else if (ll[2] == "exon"){
                genes.insert(ID);
                exonNum ++;
            }else if (ll[2] == "cds"){
                continue;
            }else if (ll[2] == "intron"){
                continue;
            }else if (ll[2] == "five_prime_utr"){
                continue;
            }else if (ll[2] == "three_prime_utr"){
                continue;
            }else {
                continue;
            }
        }
        //        exonNumber.push_back(exonNum);
        exonNumber.insert(map<string,int>::value_type(geneIDpre,exonNum));
    }
};
#endif /* DataClass_h */
