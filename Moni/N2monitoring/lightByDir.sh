

mainFile=/home/greg/DoppedData/Monitoring/N2monitoring/basePh.C
mainDir=/home/greg/DoppedData/Monitoring/N2monitoring

for d in */; do

    cd $mainDir/$d
   # rm *.root
    cp $mainFile .

    # root -q -b copyToRoot.C
    root -q -b basePh.C
done
