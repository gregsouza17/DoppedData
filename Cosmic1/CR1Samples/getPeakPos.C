#include <iostream>
#include <string>
#include <vector>

#include "/home/greg/myARPC/Codes/utilities.h"
#include "/home/greg/myARPC/Codes/LXe/LXeAnalysis.h"

//PreN2 Position: 432 +-3


void getPeakPos(std::string inFile="SeSyncAfternoon2_samples.root"){
  setLXe();

  TH1I* hPeakPos = new TH1I("h1", "PeakPos", 2000, 0, 2000);

  TFile *inF= new TFile(inFile.c_str(), "READ");
  for(Int_t i:LXeutils::Channels){
    std::string treeName="tCh"+std::to_string(i);
    //std::cout << treeName <<"\t" << s <<"\n";

    TTree *t1 = (TTree*) inF->Get(treeName.c_str());
    Int_t nevents = t1->GetEntries()/TestParam::linhas_evento;

    for(int ev=0; ev<nevents; ev++){
      Signal sig(t1, ev);
      hPeakPos->Fill(sig.GetHighestPeak());
    }
    t1->Delete();

  }
  hPeakPos->Draw();

}
