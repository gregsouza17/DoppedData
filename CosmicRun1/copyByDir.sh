

mainFile=/home/greg/DoppedData/CosmicRun1/copyToRoot.C
mainDir=/home/greg/DoppedData/CosmicRun1

for d in */; do
    
    cd $mainDir/$d
   # rm *.root
    cp $mainFile .
    
    root -q -b makeCosmicSample.C
    
done
	 
	 
