#include "/home/greg/myARPC/Codes/LXe/LXeAnalysis.h"
#include "/home/greg/myARPC/Codes/utilities.h"

void makeCosmicSample(){

  gROOT->SetBatch(true);

  std::vector<std::string> inFiles=GetFiles("copy.root");

  TFile *fout = new TFile("10ppm.root", "RECREATE");

  for(std::string s:inFiles){
    MakeCosmicSample(s, GetCh(s), fout);
  }

  gROOT->SetBatch(false);
}
