


mainFile=/home/greg/DoppedData/Moni/Xe0_to_10ppm/basePh.C
mainDir=/home/greg/DoppedData/Moni/Xe0_to_10ppm
for d in */; do

    cd $mainDir/$d
   # rm *.root
    cp $mainFile .

    # root -q -b copyToRoot.C
    root -q -b basePh.C
done
