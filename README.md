# WGSc
## 1. Installation:
    git clone https://github.com/YaoZhou89/WGSc.git
#### For mac users:
    open the project directly, and add the libz.tbz in the linked Frameworks and libraries
#### For linux users:
    sh compile.sh
## 2. Functions   
### 2.1 count lines for a .gz file (gzip compressed)
    WGS --model wc --file depth.1.txt.gz
### 2.2 random choose from a file
    WGS --model file --type random --file all.depth.txt.gz --out test.txt.gz
### 2.3 select barley  as calibrate
    WGS --model vcf --type calibrate --file chr1.vcf.gz --out chr1.cal.vcf.gz
