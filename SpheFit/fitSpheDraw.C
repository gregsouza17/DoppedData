#include <iostream>
#include <string>
#include <vector>
//#include "SpheModel.C"

#include "/home/greg/myARPC/Codes/utilities.h"
#include "/home/greg/myARPC/Codes/LXe/LXeAnalysis.h"

Double_t model3Exps(Double_t *x, Double_t *p){
  Double_t xstart=p[8];
  Double_t xx= *x -xstart;
  if(xx<0)
    return 0;

  Double_t f=0;
  f+=std::fabs(p[0])*TMath::Exp(-xx*p[1])+
    std::fabs(p[2])*TMath::Exp(-xx*p[3])+
    std::fabs(p[4])*TMath::Exp(-xx*p[5])-
    std::fabs(p[6])*TMath::Exp(-xx*p[7]);

  return f;
}


void sphe3ExpsFit(Int_t ch=0){

  setLXe();

  std::string treeName="tCh"+std::to_string(ch);
  std::string branchName="peak";

  std::vector<Double_t> I, SphePeak=GetBranch("Sphes.root", treeName, branchName);
  for(int i=0; i<SphePeak.size(); i++)
    I.push_back(i);


  TF1 *fmodel= new TF1("fmodel", model3Exps, 0, 2000, 12);
  //fmodel->SetParameters(20.0, 0.1, 20.0 , 0.39,496.0, 0.08,12);
  fmodel->SetParameter(8,13);
  fmodel->SetNpx(1000);
  // fmodel->SetParameter(6, 15);
  TGraph *g1 = new TGraph(I.size(), &I[0], &SphePeak[0]);
  g1->Fit(fmodel);

  for(int i=0; i<6; i+=1){
    if(i%2==0)
      fmodel->SetParameter(i, fmodel->GetParameter(i));
    else
      fmodel->FixParameter(i, fmodel->GetParameter(i));
  }

  g1->Fit(fmodel);
  g1->SetTitle("Fitted Single Photon Electron");
  g1->SetMarkerStyle(2);
  g1->SetMarkerColor(kBlue);
  g1->SetMarkerSize(1);
  g1->GetXaxis()->SetTitle("ticks (6.667ns)");
  g1->GetYaxis()->SetTitle("adc units");
  g1->Draw("AP");
  std::vector<Double_t> spheY;
  for(int i=0; i<TestParam::linhas_evento; i++)
    spheY.push_back(g1->Eval(i));

  // return spheY;
}

void fitSpheDraw(Int_t ch=0){
  setLXe();

  sphe3ExpsFit(ch);

}
