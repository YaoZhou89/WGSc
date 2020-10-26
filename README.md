# WGS: Wheat genome sequencing data analysis
This was primarily coded for our wheat genus level sequencing [manuscript](https://www.biorxiv.org/content/10.1101/2020.03.21.001362v1).
## Installation:
    git clone https://github.com/YaoZhou89/WGSc.git
    cd WGSc
    make
### Quality control of SNPs 

The multiple polyploid levels and low coverage of depth may cause false positives in SNP calling due to misalignment and sequencing errors, so we applied a specific pipeline with six filters to eliminate low-confidence SNPs. The low-confidence SNPs were identified and removed by either technological or genetic filters. Technically, SNPs with low mapping quality, biased depth distribution or potential sequencing error were discarded. Genetically, SNPs that broke genetic laws, such as linkage disequilibrium or identity by descent (IBD), were discarded.

#### Quality filter

Usage:

```shell
java -jar WGS.jar --model vcf --type quality --MQ 30 --FS 60 --MQRankSum -12.5 --ReadPosRankSum --BSQRankSum 0 --SOR 3 --file in.vcf --out out.vcf
```

Parameters:

```
MQ: MQ tag in vcf file, if the value less than the threshold, the SNP will be eliminated.
FS： FS tag in vcf file, if the value larger than the threshold, the SNP will be eliminated.
MQRankSum: MQRankSum in vcf file, if the value less than the threshold, the SNP will be eliminated.
ReadPosRankSum: ReadPosRankSum tag,in vcf file, if the value less than the threshold, the SNP will be eliminated.
BSQRankSum: BSQRankSum tag in vcf file, if the value less than the threshold, the SNP will be eliminated.
SOR: SOR tag in vcf file, if the value larger than the threshold, the SNP will be eliminated.
```

#### Depth filter

Usage:

```shell
java -jar WGS.jar --model vcf --type DepthFilter --maxSD 3 --min-depth 10 --max-depth 50 --file in.vcf --out out.vcf
```

Parameters:

```shell
maxSD: standard deviation(SD) of the depth for all individuals, if the SD larger than the threshold, the SNP will be eliminated.
min-depth: minimum depth allowed for the total depth.
max-depth: maximum depth allowed for the total depth.
```

Tips:  Manually determine the appropriate value for these parameters based on the distribution of total depth would be a nice way.

#### Segregation test filter

Usage:

```shell
java -jar WGS.jar --model vcf --type ST --file in.vcf.gz --out out.vcf
```

Tips： the input file should be compressed format and also indexed with tabix.

#### Linkage disequilibrium (LD) filter

Usage:

```shell
java -jar WGS.jar --model vcf --type LDfilter --windowSize 50 --threshold 0.01 --file in.vcf.gz --out out.vcf
```

Parameters:

```shell
windowSize: number of SNPs consider;
threshold: SNPs with mean correlation less than the threshold will be eliminated.
```

Tips： the input file should be compressed format and also indexed with tabix.

#### IBD filter

Usage:

```

```

#### Minor allele count filter

Usage: This was 

```

```

