

mainFile=/home/greg/DoppedData/Moni/Xe10_to_20ppm/makeCosmicSample.C
mainDir=/home/greg/DoppedData/Moni/Xe10_to_20ppm

for d in */; do

    cd $mainDir/$d
   # rm *.root
    cp $mainFile .

    # root -q -b copyToRoot.C
    root -q -b makeCosmicSample.C
done
