

mainDir=/home/greg/DoppedData/CosmicRun1

for d in */; do
    
    cd $mainDir/$d
    root -q -b basePh.C
    cd $MainDir

done
	 
	 
