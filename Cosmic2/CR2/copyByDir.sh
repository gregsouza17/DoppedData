

#mainFile=/home/greg/DoppedData/Cosmic2/CR2/copyToRoot.C
mainDir=/home/greg/DoppedData/Cosmic2/CR2
mainFile=basePh.C
#makeCosmicSample.C

for d in */; do
    
    cd $mainDir/$d
   # rm *.root
    cp $mainDir/$mainFile .
    
    root -q -b $mainFile
    
done
	 
	 
