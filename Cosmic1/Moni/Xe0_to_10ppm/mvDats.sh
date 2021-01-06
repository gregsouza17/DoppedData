
mainFile=/home/greg/DoppedData/Moni/Xe0_to_10ppm/copyToRoot.C
mainDir=/home/greg/DoppedData/Moni/Xe0_to_10ppm

for d in */; do
    
    cd $mainDir/$d

    #cp *copy.root /home/greg/DoppedData/Run1Cal

#    mkdir Dats
 #   mv *.dat Dats/
  #  mv *.csv Dats/

    # rm -rf *.root
    # mv ./Dats/* .
    mv *og.txt $mainDir
#    rm *.txt
#    cp *samples.root $mainDir/
#   rm *.root
    cd $MainDir

done
	 
	 
