#include <iostream>
#include <string>
#include <vector>

#include "/home/greg/myARPC/Codes/utilities.h"
#include "/home/greg/myARPC/Codes/LXe/LXeAnalysis.h"


void writePeak(std::string inFile, std::string inTree, std::string outName){

  std::vector<Double_t> peaks=GetBranch(inFile, inTree, "peak");
  std::vector<Double_t> times=GetBranch(inFile, inTree, "time");


  std::ofstream myfile;;

  myfile.open(outName.c_str());
  myfile<<"#peak \t \t#time \n";

  for(int i=0; i<peaks.size(); i++){
    std::string toWrite = std::to_string(peaks[i]) + "\t \t" +
      std::to_string(times[i]) + "\n";

    myfile<<toWrite;
  }

  myfile.close();

}

void writeFile(){
  //for(auto inRun:CosmicRun1::names){
  std::string inRun="Sphes";
    for(Int_t ch:LXeutils::Channels){
      std::string outName="SpheCh"+std::to_string(ch)+".txt";
      //std::string inFile = inRun+"_deconved.root";
      std::string inFile = "Sphes.root";
      std::string inTree = "tCh"+std::to_string(ch);

      writePeak(inFile,inTree, outName);
    }
    //}

}
