

mainFile=/home/greg/DoppedData/CosmicRun1/copyToRoot.C
mainDir=/home/greg/DoppedData/CosmicRun1

for d in */; do
    
    cd $mainDir/$d
    cp *copy.root /home/greg/DoppedData/DataRun1/
    # rm *.C
#   mkdir Dats
 #  mv *.dat Dats/
#   rm *.root
#    cd $MainDir

done
	 
	 
