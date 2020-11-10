## Bionano analysis

### Assembly

1. Filtering 

   ```shell
    cd /vol1/agis/huangsanwen_group/zhouyao/projects/potato/C88/bionano
    export PATH=$PATH:/public/home/zhouyao/softwares/bionano2/tools/pipeline/1.0/RefAligner/1.0
    perl /public/home/zhouyao/softwares/bionano2/tools/pipeline/1.0/cohortQC/1.0/filter_SNR_dynamic.pl -i C88_RawMolecules.bnx -o C88_CleanMolecules.bnx
   ```

2. In-slico splicing for cmap

   ```shell
   perl /public/home/zhouyao/softwares/bionano2/tools/pipeline/1.0/HybridScaffold/1.0/scripts/fa2cmap_multi_color.pl -i /vol3/agis/huangsanwen_group/zhouyao/data/potato/BAC400/assembly/canu/all/C88_1/C88_1.contigs.fasta -e CACGAG 1 -M 20
   ```

   Out file located at: /vol3/agis/huangsanwen_group/zhouyao/data/potato/BAC400/assembly/canu/all/C88_1/

3. assembly

   ```
   conda activate py2
   python /public/home/zhouyao/softwares/bionano2/tools/pipeline/1.0/Pipeline/1.0/pipelineCL.py -T 12 -j 12 -N 4 -f 0.2 -i 5 -y -b C88_CleanMolecules.bnx -l /vol1/agis/huangsanwen_group/zhouyao/projects/potato/C88/bionano/hicanu -t /public/home/zhouyao/softwares/bionano2/tools/pipeline/1.0/RefAligner/1.0 -a /public/home/zhouyao/softwares/bionano2/tools/pipeline/1.0/RefAligner/1.0/optArguments_nonhaplotype_BG_saphyr.xml -r /vol3/agis/huangsanwen_group/zhouyao/data/potato/BAC400/assembly/canu/all/C88_1/C88_1.contigs_CACGAG_20kb_0labels.cmap 
   ```

   

4. Output

   ```
   
   ```

5. 
