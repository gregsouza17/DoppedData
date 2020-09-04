#include "/home/greg/myARPC/Codes/Signals.C"
#include "/home/greg/myARPC/Codes/finder.C"
#include "/home/greg/myARPC/Codes/PeakSearcher.h"

#include "/home/greg/myARPC/Codes/utilities.h"
#include "/home/greg/myARPC/Codes/LXe/LXeAnalysis.h"

void getTailPeaks(Int_t ch, Int_t sigmas=3){
  /*
    What should go in:
    - Channel to be evaluated

    What Should go Out:
    - TH1D in a fout with charge, sample
    and Searcher Samples

    What Should:

    - Go thorugh every file for a certain channel
    - For each event, get the peaks at the last 1000 entries
    - If the peaks is isolated and agreeable as by the Searcher,
    add the peak to a sample histogram,
    and the charge to a charge histogram
    - Add the possibility to save a number of searcher samples
    for presentation purpose
   */

  //Create Outfile Naming
  std::string CH_str = "Ch" + std::to_string(ch);
  std::string outFile_str = CH_str+"sphes.root";
  //String used for searching
  std::string ForSearch_str = "Ch" + std::to_string(ch) +
    "-";

  std::vector<std::string> inFiles=GetFiles(ForSearch_str);
  //Create outfile as TFile
  //  TFile *fout = new TFile(outFile_str.c_str(), "RECREATE");

  Int_t index=LXeutils::ChToIndex(ch);

  Int_t integralStart(610), integralEnd(900);

  Double_t spheCharge=CosmicRun1::charges[index];
  Double_t spheStdDev=CosmicRun1::vars[index];

  Double_t maxCharge=spheCharge+sigmas*spheStdDev;
  Double_t minCharge=spheCharge-sigmas*spheStdDev;

  std::vector<Double_t> avgSig(TestParam::linhas_evento);
  std::fill(avgSig.begin(), avgSig.end(), 0);

  Int_t Nsphes(0);
  for(auto fileName:inFiles){
    TFile *fin = new TFile(fileName.c_str(), "READ");

    TTree *t1 = (TTree*) fin->Get("t1");
    Int_t nEvents = t1->GetEntries()/TestParam::linhas_evento;

    for(int ev=0; ev<nEvents; ev++){
      Signal s(t1, ev);
      Double_t charge=s.Integrate(610, 900);

      if(charge<maxCharge && charge>minCharge){
        std::vector<Double_t> sig=s.GetVector();

        for(int i=0; i<avgSig.size(); i++){
          avgSig[i]+=sig[i];
          Nsphes++;
        }
      }
    }

  }

  std::vector<Double_t> I;
  for(int i=0; i<avgSig.size(); i++){
    avgSig[i]/=Nsphes;
    I.push_back(i);
  }

  TGraph *g1 = new TGraph(I.size(), &I[0], &avgSig[0]);
  g1->Draw("ALP");


}


void calSphes(){
  //Main Function

  setLXe();
  getTailPeaks(0);
}
