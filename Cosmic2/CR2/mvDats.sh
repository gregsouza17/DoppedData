

mainDir=/home/greg/DoppedData/Cosmic2/CR2


for d in */; do
    
    cd $mainDir/$d

    echo $mainDir/$d

    #cp *copy.root /home/greg/DoppedData/Run1Cal

    # rm -rf *.root
    # mv ./Dats/* .

    # rm *.C
    cp *lightYield.root *Log.txt /home/greg/DoppedData/Cosmic2/LYCR2/
    #$mainDir

    #cp *samples.root $mainDir/
#   rm *.root
    cd $MainDir

done
	 
	 
