

mainFile=/home/greg/DoppedData/CR2/copyToRoot.C
mainDir=/home/greg/DoppedData/CR2

for d in */; do
    
    cd $mainDir/$d
   # rm *.root
    cp $mainFile .
    
    root -q -b copyToRoot.C
    
done
	 
	 
