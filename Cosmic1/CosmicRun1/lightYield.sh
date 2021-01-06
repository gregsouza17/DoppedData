
mainDir=/home/greg/DoppedData/CosmicRun1
mainFile=/home/greg/DoppedData/CosmicRun1/basePh.C

for d in */; do
    
    cd $mainDir/$d
    cp $mainFile .
    root -q -b basePh.C
    cd $MainDir

done
	 
	 
