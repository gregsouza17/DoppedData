

mainFile=/home/greg/DoppedData/CosmicRun1/copyToRoot.C
mainDir=/home/greg/DoppedData/CosmicRun1

for d in */; do
    
    cd $mainDir/$d

    #cp *copy.root /home/greg/DoppedData/Run1Cal

    # rm -rf *.root
    # mv ./Dats/* .

    # rm *.C
#   mkdir Dats
    cp *samples.root $mainDir/
#   rm *.root
    cd $MainDir

done
	 
	 
