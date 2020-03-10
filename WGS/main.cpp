//
//  main.cpp
//  WGS
//
//  Created by Yao Zhou on 2018/12/4.
//  Copyright © 2018 Yao Zhou. All rights reserved.
//

#include "HeaderIns.h"
#include "baseFunctions.h"
#include "DataClass.h"
#include "help.h"
#include "initialization.h"
#include "checkers.h"
#include "FileFunctions.h"
#include "scripts.h"
#include "vcf.h"
#include "dataConvert.h"
int main(int argc, char * argv[]) {
    clock_t start;
    double duration;
//    cout << encode("CCTCTAATTGTGATAATGCCAAATTTCTGACT") << endl;
    start = clock();
    parameter *para = new parameter;
    if ( (WGS_initialization(argc, argv, para) == 0) )
    {
        delete para;
        return 1 ;
    }
//    checkOUT(para);
    vcf *inVCF = new vcf;
    depth *inDepth = new depth;
    // testing:
    
    if (!(para->inFile).empty())
    {
        if ((para -> model).empty()){
            cerr << "model should be specified! Please check" << endl; ;
        }else if((para -> model) == "vcf"){
            if((para->type)==""){
                Read_VCF_IN(para, inVCF);
            }else if((para->type)=="toFasta"){
                
            }else if((para->type)=="filterBarley"){
                filterBarley(para);
            }else if((para->type) == "calibrate"){
                calibarate(para);
            }else if((para->type) == "calibrate2"){
                calibarate2(para);
            }else if((para->type) == "calibarate3"){
                calibarate3(para);
            }else if((para->type) == "calibarate4"){
                calibarate4(para);
            }else if((para->type) == "calibarate5"){
                calibarate5(para);
            }else if((para->type)=="toV8"){
                cout << "toV8..." << endl;
                getV8(para);
            }else if ((para->type)=="site-pi"){
                pi(para);
            }else if((para->type) == "vcf2sNMF"){
                vcf2sNMF(para);
            }else if ((para->type) == "getHeader"){
                getHeader(para);
            }else if ((para->type) == "get2vcf"){
                get2vcf(para);
            }else if((para->type) == "depthFilter"){
                
            }else if((para->type) == "ct3"){
                ct3(para); // snps shared among three groups
            }else if((para->type) == "ct2"){
                ct2(para); // snps shared in two groups
            }else if((para->type) == "ct1"){
                ct1(para); // allelic or not
            }else if((para->type) == "addContig"){
                addContig(para);
            }else if((para -> type) == "ANC"){
                changeAncestralAllele(para);
            }else if ((para->type) == "merge2vcf"){
                merge2vcf(para);
            }else if ((para->type) == "addOutgroup"){
                add2vcf(para);
            }else if ((para->type) == "toXPCLR"){
                toXPCLR(para);
            }else if((para->type) =="toXPCLRsnp") {
                toXPCLRsnp(para);
            }else if ((para->type)=="toV11"){
                toV11(para);
            }else if ((para->type) == "toSFS"){
                toSFS(para);
            }else if ((para->type) == "pwMAF"){
                pwFrequence(para);
            }else if((para->type) =="maf"){
                writeMAF(para);
            }else if ((para->type) =="Derived"){
                getDerivedAllele(para);
            }else if ((para->type) == "incp"){
                cp(para);
            }else if ((para->type) == "getExtream"){
                getExtream(para);
            }else if((para->type) =="DAF"){
                daf(para);
            }else if ((para->type)=="getReg"){
                getRegulation(para);
            }else if ((para->type) =="changePos"){
                changeVcfPos(para);
            }else if ((para->type) =="smoothIndel"){
                smoothIndel(para);
            }else if ((para->type) == "toDstatistic"){
                vcf2Dstat(para);
            }else if ((para->type)=="IS"){
                IScore(para);
            }else if ((para->type) == "GeneticDistance"){
                getGeneticDistance(para);
            }else if ((para->type) == "GeneticDistanceRef"){
                getGeneticDistanceRef(para);
            }else if((para->type) =="intersect"){
                getIntersectVcf(para);
            }else if((para->type) =="unintersect"){
                getUnIntersectVcf(para);
            }else if ((para->type) == "toEigenStrat"){
                toEigenStrat(para);
            }else if((para->type) == "getSummary"){
                getSummary(para);
            }else if ((para->type) == "overlap"){
                vcfoverlap(para);
            }else if ((para->type) =="toAncestral"){
                vcf2ancestral(para);
            }else if ((para->type) == "DPvsGATK"){
                DPvsGATK(para);
            }else if ((para->type) == "het2depth"){
                het2depth(para);
            }else if ((para->type) == "vcf2RleateMap"){
                vcf2RleateMap(para);
            }else if ((para->type) == "vcf2bed"){
                vcf2bed(para);
            }else if ((para->type) == "addBarley"){
                V11_barley(para);
            }else if ((para->type) == "substract"){
                substract(para);
            }else if ((para->type) == "vcf2Major"){
                vcf2Major(para);
            }else if ((para->type) == "vcfAddID"){
                vcfAddID(para);
            }
        }else if((para -> model) == "depth"){
            if((para->type)=="site"){
                Read_depth_IN(para);
            }else if((para->type) == "toBed"){
                Depth2Bed(para);
            }else if ((para->type) == "merge"){
                mergeDepth(para);
            }else if((para->type) == "mask"){
                getMaskRegion(para);
            }else if ((para->type) == "UnMapped"){
                getUnMapped(para);
            }else if ((para->type) == "Mapped"){
                getMapped(para);
            }else if ((para->type) == "siteDepth"){
                siteDepth(para);
            }else if ((para->type) == "getsynteny"){
                getsynteny(para);
            }else if ((para->type) == "divided2synteny"){
                divided2synteny(para);
            }else if ((para->type) == "filterByDepth"){
                filterByDepth(para);
            }
//            outDepthFile(para,inDepth);
        }else if ((para->model) == "pos"){
            if ((para->type) == "changePos"){
                changePos(para);
            }else if((para->type) =="change2num"){
                chr2num(para);
            }else if ((para->type) == "toEigenStrat"){
                changeEigenStratPos(para);
            }
        }else if((para->model) == "wc"){
            count(para);
        }else if((para->model) == "file"){
            if ((para->type) == "merge"){
                mergeDepth(para);
            }else if((para -> type)=="random"){
                randChoose(para);
            }else if((para -> type)=="merge3"){
                filterDepth3(para);
            }else if((para -> type)=="synteny"){
                filterDepth(para);
            }else if((para -> type)=="mergeSynteny"){
                mergeSynteny(para);
            }else if((para -> type)=="Syn2HapScan"){
                Syn2HapScan(para);
            }else if((para -> type)=="merge2"){
                filterDepth2(para);
            }else if((para -> type)=="filterBySim3"){
                filterDepth_bySimulation3(para);
            }else if((para -> type)=="filterBySim"){
                filterDepth_bySimulation(para);
            }else if((para -> type)=="filterBySim2"){
//                cout <<"testing..."<<endl;
                filterDepth_bySimulation2(para);
            }else if((para->type) == "intersect"){
                intersectFile(para);
            }else if ((para->type) == "getPos"){
                getPos(para);
            }else if((para->type) =="getMax"){
                getMaximum(para);
            }else if((para->type) =="pwpd"){
                pwpd(para);
            }else if((para->type) == "mumer4"){
                subMummer4(para);
            }else if((para->type) == "LDmean"){
                LDmean(para);
            }else if ((para->type) =="TEdensity"){
                TEdensity(para);
            }else if ((para->type) == "cleanBed"){
                cleanBed(para);
            }else if ((para->type) =="BestHit"){
                BestHit(para);
            }else if((para->type) == "geneToGff3"){
                FstGenes(para);
            }else if((para->type) =="pairedMAF"){
                getPairAlleleFrequency(para);
            }else if((para->type)=="ByChr"){
                splitByChr(para);
            }else if((para->type) =="mummer2vcf"){
                mummer2vcf(para);
            }else if ((para->type) =="mummerCountInDel"){
                mummerCountInDel(para);
            }else if((para->type)=="blast2Gene"){
                blast2Gene(para);
            }else if((para->type)=="changeBlast"){
                changeBlast(para);
            }else if ((para->type) == "sog"){
                getSOG(para);
            }else if ((para->type)=="getKaKs"){
                getKaKs(para);
            }else if ((para->type) == "RemoveDot"){
                RemoveDot(para);
            }else if((para->type) =="pairOrtho"){
                pairOrtho(para);
            }else if ((para->type) =="summaryBeast"){
                summaryBeast(para);
            }else if ((para->type) =="summary2Beast"){
                summary2Beast(para);
            }else if ((para->type)=="mergeDgeno"){
                mergeDgeno(para);
            }else if ((para->type) == "DtoBed"){
                DtoBed(para);
            }else if ((para->type) == "DtoBed2"){
                DtoBed2(para);
            }else if ((para->type) == "meanBed"){
                meanBedpi(para);
            }else if ((para->type) == "GeoDistance"){
                getGeoDistance(para);
            }else if ((para->type)== "DistanceAll"){
                getDistanceAll(para);
            }else if ((para->type) == "tof4"){
                getSubTreemix(para);
            }else if ((para->type) =="checkFile"){
                checkFile(para);
            }else if ((para->type) == "getOrtholog"){
                getOrtholog(para);
            }else if ((para->type) == "HapToVCF"){
                riceHapToVCF(para);
            }else if ((para->type) == "getMean"){
                getMean(para);
            }else if ((para->type) == "getSum"){
                getSum(para);
            }else if ((para->type) == "wc"){
                wc(para);
            }else if ((para->type) =="ABBAstat"){
                ABBAstat(para);
            }else if ((para->type) == "ABBAsim"){
                ABBAsim(para);
            }else if ((para->type) == "depthEvaluation"){
                depthEvaluation(para);
            }else if ((para->type) == "rice"){
                getRiceGenes(para);
            }else if ((para->type)=="test"){
//                readtest(para);
            }else if ((para->type) == "snpID"){
                snpID(para);
            }else if ((para->type) == "maf2pos"){
                maf2pos(para);
            }else if ((para->type) =="checkPos"){
                checkPos(para);
            }else if ((para->type) == "blast2maf"){
                blast2maf(para);
            }else if ((para -> type) == "bed2single"){
                bed2single(para);
            }else if ((para -> type) == "BSAseq") {
                BSAseq(para);
            }else if ((para -> type) =="checkNumber"){
                checkNumber(para);
            }
        }else if((para->model) == "gff3"){
            if ((para->type) == "density"){
                getGffDensity(para);
            }else if ((para->type) == "gff2bed"){
                gff2bed(para);
            }else if ((para->type) == "gff3thin"){
                gff2thin(para);
            }else if ((para->type) =="ToGene"){
                getUniqueGene(para);
            }else if ((para->type) == "changePos"){
                changeGffPos(para);
            }else if((para->type) == "stat"){
                statGff(para);
            }else if((para -> type) == "gff2genic"){
                gff2genicsite(para);
            }else if ((para->type) == "gff2exon"){
                gff2exon(para);
            }else if ((para->type) == "gff2geneBed"){
                getGeneBed(para);
            }else if ((para->type) == "filterMakerGff"){
                filterMakerGff(para);
            }
        }else if((para->model) == "bed"){
            if ((para->type) == "changePos"){
                changeBedPos(para);
            }else if ((para->type) == "density"){
                getBedDensity(para);
            }
        
        }else if((para->model) == "diversity"){
            if((para->type)=="bedPi"){
                pi2bed(para);
            }else if((para->type) == "syn"){
                getOri(para);
            }else if ((para -> type) =="genePi"){
                genePi(para);
            }else if ((para->type) == "overCount"){
                gene_count(para);
            }else if((para->type) == "CountByGene"){
                gene_count_gene(para);
            }else if ((para->type)== "slicedByGene"){
                slicedFunction(para);
            }else if((para->type) == "reduction"){
                DiversityReduction(para);
            }
        }else if((para -> model) == "structure"){
            if((para -> type) == "Q2CLUMPP"){
                Q2CLUMPP(para);
            }else if((para->type) == "CLUMPP2R"){
                CLUMPP2R(para);
            }
        }else if((para->model) == "tree"){
            if((para->type) == "phy"){
                changePhy(para);
            }
        }else if ((para->model) == "fasta"){
            if((para->type) == "toMCscanGff"){
                getGffMCscan(para);
            }else if((para->type) =="changeGff"){
                getGffMCscanChr(para);
            }else if((para->type)=="pepTofasta"){
                pepTofasta(para);
            }else if((para->type)=="getContig"){
                getContig(para);
            }else if((para->type)=="writeContig"){
                writeContig(para);
            }else if((para->type)=="getScaffold"){
                getScaffold(para);
            }else if ((para->type) =="formatFasta"){
                formatFasta(para);
            }else if((para->type) =="formatFasta2"){
                formatFasta2(para);
            }else if((para->type) =="formatFasta3"){
                formatFasta3(para);
            }else if ((para->type) == "toPhy"){
                toPhy(para);
            }else if((para->type)=="getCDS"){
                getCDS(para);
            }else if((para->type)=="getSeq"){
                getSeq(para);
            }else if((para->type)=="keepLongest"){
                keepLongest(para);
            }else if ((para->type) =="RC"){
                changeGenomePos(para);
            }else if ((para->type) == "getRegion"){
                getRegion(para);
            }else if ((para->type) == "getKmerOrder"){
                getKmerOrder(para);
            }else if ((para->type) =="getKmerOrder2"){
                getKmerOrder2(para);
            }else if ((para->type) == "GenomeStatistic"){
                GenomeStatistic(para);
            }else if ((para -> type) == "getChr"){
                getFasta(para);
            }else if ((para-> type) =="splitByN"){
                splitByN(para);
            }else if ((para-> type) =="splitByNAll"){
                splitByNAll(para);
            }else if ((para-> type) =="GPM"){
                GPMm(para);
            }else if ((para-> type) =="GPM1"){
                GPMm1(para);
            }else if ((para->type) == "gene2Single"){
                gene2Single(para);
            }else if ((para->type) == "toPEfastq"){
                toPEfastq(para);
            }
        }else if ((para->model) == "assembly"){
            if((para->type) == "fastq"){
                getKmer(para);
            }
        }else if ((para->model) == "scripts"){
            if ((para -> type) == "SRA1"){
                SRA1(para);
            }else if ((para -> type) == "SRA2"){
                SRA2(para);
            }else if ((para -> type) == "SRA3"){
                SRA3(para);
            }else if ((para -> type) == "SRA4"){
                SRA4(para);
            }else if ((para -> type) == "SRA5"){
                SRA5(para);
            }else if ((para -> type) == "SRA6"){
                SRA6(para);
            }else if ((para -> type) == "SRA7"){
                SRA7(para);
            }else if ((para -> type) == "SRA8"){
                SRA8(para);
            }else if ((para -> type) == "SRA9"){
                SRA9(para);
            }else if ((para -> type) == "SRA10"){
                SRA10(para);
            }else if ((para -> type) == "SRA11"){
                SRA11(para);
            }else if ((para -> type) == "SRA12"){
                SRA12(para);
            }else if ((para -> type) == "SRA13"){
                SRA13(para);
            }else if ((para -> type) == "SRA14"){
                SRA14(para);
            }else if ((para -> type) == "fastp"){
                getFastp(para);
            }
        }
    }
    
    duration = ( clock() - start ) / (double) CLOCKS_PER_SEC;
    cout<<"Finished in "<< duration <<" sec " << '\n';
    return 0;
}
