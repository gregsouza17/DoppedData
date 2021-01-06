#include "/home/greg/myARPC/Codes/Signals.C"
#include "/home/greg/myARPC/Codes/finder.C"
#include "/home/greg/myARPC/Codes/PeakSearcher.h"
#include "/home/greg/myARPC/Codes/CalibrationCode.C"


#include "/home/greg/myARPC/Codes/utilities.h"
#include "/home/greg/myARPC/Codes/LXe/LXeAnalysis.h"


void getAvgSphe(Int_t sigmas=3){

  std::string fileName=
    "29Nov2019_Vbias=47_LED_C_test_Ch9-2019-11-29_12-26-52_copy.root";
  Int_t ch=9;
  Int_t index=LXeutils::ChToIndex(ch);

  TFile *fin = new TFile(fileName.c_str(), "READ");

  TTree *t1 = (TTree*) fin->Get("t1");
  Int_t nEvents = t1->GetEntries()/TestParam::linhas_evento;

  Int_t integralStart(610), integralEnd(900);

  Double_t spheCharge=CosmicRun1::charges[index];
  Double_t spheStdDev=CosmicRun1::vars[index];

  Double_t maxCharge=spheCharge+sigmas*spheStdDev;
  Double_t minCharge=spheCharge-sigmas*spheStdDev;

  std::vector<Double_t> avgSig(TestParam::linhas_evento);
  std::fill(avgSig.begin(), avgSig.end(), 0);

  Int_t Nsphes(0);
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

  std::vector<Double_t> I;
  for(int i=0; i<avgSig.size(); i++){
    avgSig[i]/=Nsphes;
    I.push_back(i);
  }

  TGraph *g1 = new TGraph(I.size(), &I[0], &avgSig[0]);
  g1->Draw("ALP");



}



void sphes(){
  setLXe();

  getAvgSphe();

}
