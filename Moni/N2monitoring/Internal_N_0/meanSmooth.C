#include "../Codes/Signals.C"
#include "../Codes/utilities.h"
#include "../Codes/RunGlobals.h"
#include "../Codes/finder.C"
#include "../Codes/LXeutils.h"

Double_t findSlow(std::string inF);

void meanSmooth(){
  setLXe();
  
  // std::string inF("02Dec2019_Vbias=47_CosmicIntTrig_Ch11-2019-12-02_12-52-16_copy.root");

  
  //  findSlow(inF);
  
  std::vector<std::string> glass, noglass;  
  GetFilenames(glass, noglass);

  double meanSlow(0), slow;
  int added(0);
  for(int i=0; i<noglass.size()-1; i++){
    
    slow= findSlow(noglass[i]);
    std::cout << "\n \n t_slow_" << i <<" = " << slow <<"\n \n";
    meanSlow+=slow;
    added++;

    
  }

  std::cout<< "\n \n Mean t_slow = " << meanSlow/added <<"\n \n";
  std::cout << "Channels added: " << added << "\n";
  
}

Double_t findSlow(std::string inF){

  TFile *f1 = new TFile(inF.c_str(), "READ");
  TTree* t1 = (TTree*) f1->Get("t1");

  Int_t nevents=t1->GetEntries()/TestParam::linhas_evento;

  Int_t strt(0), end(2000);
  
  std::vector<Double_t> avg(end-strt), smoothAvg(end-strt), T;
  
  std::fill(avg.begin(), avg.end(), 0);
  std::fill(smoothAvg.begin(), smoothAvg.end(), 0);


  CosmicFinder f(1, 0.1);
  Int_t p1, p2;
  


  Int_t added(0);
  for(int ev=0; ev<nevents; ev++){

    Signal s(t1,ev);

    Double_t norm=s.GetHighestValue(strt, end);
    
    std::vector<Double_t> sig = s.GetVector(strt, end);
    std::vector<Double_t> smoothSig;
    SmoothMA(smoothSig, sig, 9);

    bool isN=f.isNoise(sig, strt, p1,p2);
    
    if(!isN){
      added++;
      for(int i=0; i<sig.size(); i++){
	avg[i]+=sig[i]/(norm);
	smoothAvg[i]+=smoothSig[i]/(norm);
	
      }
    }
    
  }

  if(added){
  for(int i=0; i<avg.size(); i++){
    avg[i]/=added;
    smoothAvg[i]/=added;    
    T.push_back((i)*TestParam::adc_step);
  }

  
  
  std::cout << added <<"\n";
  
  // TGraph *sgr = new TGraph(smoothAvg.size(), &T[0], &smoothAvg[0]);
  // sgr->SetLineColor(kRed);
  // sgr->SetLineWidth(2);
  // sgr->SetMarkerStyle(3);
  // sgr->SetMarkerColor(kBlue);
  // sgr->Draw("AL");

  Double_t sFit(4000), eFit(10000);
  
  TF1 *f1 = new TF1("myf", "expo(0)",sFit, eFit);
  
  TGraph *gr = new TGraph(avg.size(), &T[0], &avg[0]);
  gr->SetLineColor(kBlue-3);
  gr->Fit(f1, "", "", sFit, eFit);
  gr->Draw("AL");

  Double_t slowT=-1/f1->GetParameter(1);

  return slowT;

 }

  else
    std::cout <<" NO PEAKS SELECTED";
  
  return 0;
}
