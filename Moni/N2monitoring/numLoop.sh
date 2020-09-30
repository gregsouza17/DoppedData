

mainFile=/home/greg/DoppedData/Monitoring/N2monitoring/makeCosmicSample.C
mainDir=/home/greg/DoppedData/Monitoring/N2monitoring

for n in {0..20}
do
    inFile="Internal_N_"$n
    outFile=$inFile"_samples.root"
    cd $mainDir/$inFile
    # echo $outFile
    # pwd

#     cd $mainDir/$d
#    # rm *.root
#     cp $mainFile .

#     # root -q -b copyToRoot.C
    root -q -b "makeCosmicSample.C( $outFile )"
    #echo
 done
