
mainFile=/home/greg/DoppedData/Moni/N2monitoring/copyToRoot.C
mainDir=/home/greg/DoppedData/Moni/N2monitoring

for d in */; do
    
    cd $mainDir/$d

    #cp *copy.root /home/greg/DoppedData/Run1Cal

#    mkdir Dats
 #   mv *.dat Dats/
  #  mv *.csv Dats/

    # rm -rf *.root
    # mv ./Dats/* .
    #rm *.txt

    mv *Log.txt $mainDir
#     rm *.txt
#    cp *samples.root $mainDir/
#   rm *.root
    cd $MainDir

done
	 
	 
