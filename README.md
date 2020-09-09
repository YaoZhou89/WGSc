# WGS: Wheat genome sequencing analysis tool
This was primarily coded for our wheat genus level sequencing [manuscript](https://www.biorxiv.org/content/10.1101/2020.03.21.001362v1).
## Installation:
    git clone https://github.com/YaoZhou89/WGSc.git
    cd WGSc
    make
the executable file is bin/WGS. Please add this into environmental path firslty.
   
## Functions
### Handling vcf file
#### SNPs filtering pipeline

#### estimate diversity 
    WGS --model diversity --type window-pi --file chr1.vcf.gz --windowSize 1000000 --out chr1.window.pi
    
####  change the position from numeric to character
    WGS --model pos --type changePos --file chr1.vcf.gz --file2 pos.txt --out changed.vcf.gz --pos 2,3
    
### Handling general file

#### random subtract lines from a file with certain rate
    WGS --model file --type random --file all.depth.txt.gz --out test.txt.gz --r 0.001
    
#### Change the bam site depth to bed file
    WGS --model depth --type toBed --file chr1.txt --out chr1.bed --windowSize 1000000
    
### Handlling fasta file
#### subtract given chromosomes from the genome
```
WGS --model fasta --type getChrs --file genome.fasta --file2 candidateChr.txt --out genome.selected.fasta
```
