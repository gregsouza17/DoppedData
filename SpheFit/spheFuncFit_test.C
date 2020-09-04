#include <iostream>
#include <string>
#include <vector>
//#include "SpheModel.C"

#include "/home/greg/myARPC/Codes/utilities.h"
#include "/home/greg/myARPC/Codes/LXe/LXeAnalysis.h"

Double_t modelFunc(Double_t *x, Double_t *p){
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


void spheFuncFit(){

  setLXe();

  std::string treeName="tCh0";
  std::string branchName="peak";

  std::vector<Double_t> I, SphePeak=GetBranch("Sphes.root", treeName, branchName);
  for(int i=0; i<SphePeak.size(); i++)
    I.push_back(i);


  TF1 *fmodel= new TF1("fmodel", modelFunc, 0, 2000, 7);
  fmodel->SetParameters(5.0, 0.2, 5.0 , 0.02, 0.5, 0.1,2);
  fmodel->SetNpx(1000);
  // fmodel->SetParameter(6, 15);
  TGraph *g1 = new TGraph(I.size(), &I[0], &SphePeak[0]);
  g1->Fit(fmodel);
  g1->Draw("ALP");

  //fmodel->Draw();

  TF1 *fgaus=new TF1("fgaus", "TMath::Gaus(x, 0,[0])", -250,250);
  fgaus->SetNpx(1000);
  fgaus->SetParameter(0,50);
  //fgaus->Draw();

  TF1Convolution *f_conv=new TF1Convolution(fmodel, fgaus);

  TF1 *f1 = new TF1("f1", f_conv,
                    f_conv->GetXmin(), f_conv->GetXmax(),
                    f_conv->GetNpar());
  f1->SetNpx(2000);
  //f1->SetParameters(1.0, 0.2, 0.5, 0.02, 0.4, 0.1, 5);
  //f1->Draw();

}
