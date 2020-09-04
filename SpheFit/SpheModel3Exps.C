#include <iostream>
#include <string>
#include <vector>
//#include "SpheModel.C"

#include "/home/greg/myARPC/Codes/utilities.h"
#include "/home/greg/myARPC/Codes/LXe/LXeAnalysis.h"

Double_t model3Exps(Double_t *x, Double_t *p){
  Double_t xstart=p[6];
  Double_t xx= *x -xstart;
  // if(*x<0)
  //   return 0;

  Double_t f=0;
  f+=p[0]*TMath::Exp(-xx*p[1])+
    p[2]*TMath::Exp(-xx*p[3])-
    p[4]*TMath::Exp(-xx*p[5]);


  return f;
}


std::vector<Double_t> sphe3ExpsFit(Int_t ch=0){

  setLXe();

  std::string treeName="tCh"+std::to_string(ch);
  std::string branchName="peak";

  std::vector<Double_t> I, SphePeak=GetBranch("Sphes.root", treeName, branchName);
  for(int i=0; i<SphePeak.size(); i++)
    I.push_back(i);


  TF1 *fmodel= new TF1("fmodel", model3Exps, 0, 2000, 7);
  fmodel->SetParameters(-534.0, 0.1, 31.0 , 0.39,-496.0, 0.08,2);
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
  //g1->Draw("ALP");
  std::vector<Double_t> spheY;
  for(int i=0; i<TestParam::linhas_evento; i++)
    spheY.push_back(g1->Eval(i));

  return spheY;
}

void SpheModel3Exps(Int_t ch=0){
  setLXe();

  std::vector<Double_t> I,spheY=sphe3ExpsFit(ch);
  for(int i=0; i<spheY.size(); i++) I.push_back(i);

  TGraph *g1=new TGraph(I.size(), &I[0], &spheY[0]);
  g1->Draw();

}
