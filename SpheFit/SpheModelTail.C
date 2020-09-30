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


std::vector<Double_t> sphe3ExpsFit(Int_t ch=0){

  setLXe();

  std::string treeName="tCh"+std::to_string(ch);
  std::string branchName="peak";

  std::vector<Double_t> I, SphePeak=GetBranch("Sphes.root", treeName, branchName);
  for(int i=0; i<SphePeak.size(); i++)
    I.push_back(i);


  TF1 *fmodel= new TF1("fmodel", model3Exps, 0, 2000, 9);
  //fmodel->SetParameters(-534.0, 0.1, 31.0 , 0.39,-496.0, 0.08,2);
  fmodel->SetNpx(1000);
  if(ch>4)
    fmodel->SetParameter(8, 15);
  else
    fmodel->SetParameter(8, 13);
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

void SpheModelTail(Int_t ch=0){
  setLXe();

  TFile *fitSphes = new TFile("FitTail.root", "RECREATE");

  for(auto chNum : LXeutils::Channels){
    Double_t peak, time;
    std::string treeName="tCh"+std::to_string(chNum);
    TTree *t1 = new TTree(treeName.c_str(), treeName.c_str());
    t1->Branch("peak",&peak ,"peak/D");
    t1->Branch("time",&time , "time/D");
    std::vector<Double_t> I,spheY=sphe3ExpsFit(chNum);
    for(int i=0; i<spheY.size(); i++){
      peak=spheY[i];
      time=i/0.15;
      I.push_back(i);

      t1->Fill();
    }
    TGraph *g1=new TGraph(I.size(), &I[0], &spheY[0]);
    std::string graphTitle="Fitted Sphe of Ch"+std::to_string(chNum);
    std::string graphName="FitCh"+std::to_string(chNum);
    g1->SetTitle(graphTitle.c_str());
    g1->SetName(graphName.c_str());

    fitSphes->WriteObject(t1, treeName.c_str(), "TObject::kOverwrite");
    fitSphes->WriteObject(g1, graphName.c_str(), "TObject::kOverwrite");

    g1->Delete();
    t1->Delete();
  }
}
