

mainFile=/home/greg/DoppedData/CR2/copyToRoot.C
mainDir=/home/greg/DoppedData/CR2

for d in */; do
    
    cd $mainDir/$d

    #cp *copy.root /home/greg/DoppedData/Run1Cal

    # rm -rf *.root
    # mv ./Dats/* .

    # rm *.C
    mkdir Dats
    mv *.dat Dats/
    #cp *samples.root $mainDir/
#   rm *.root
    cd $MainDir

done
	 
	 
