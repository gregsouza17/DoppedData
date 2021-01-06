
mainFile=/home/greg/DoppedData/Moni/Xe10_to_20ppm/copyToRoot.C
mainDir=/home/greg/DoppedData/Moni/Xe10_to_20ppm

for d in */; do
    
    cd $mainDir/$d

    #cp *copy.root /home/greg/DoppedData/Run1Cal

#    mkdir Dats
 #   mv *.dat Dats/
  #  mv *.csv Dats/

    # rm -rf *.root
    # mv ./Dats/* .
    mv *og.txt $mainDir
#    rm *og.txt
#    rm *.txt
    # rm *.C
#    cp *samples.root $mainDir/
#   rm *.root
    cd $MainDir

done
	 
	 
