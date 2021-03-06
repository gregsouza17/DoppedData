#include <iostream>
#include <string>
#include <vector>

#include "/home/greg/myARPC/Codes/utilities.h"
#include "/home/greg/myARPC/Codes/LXe/LXeAnalysis.h"


void deconvAFile(std::string inRun){

  setLXe();
  LXeutils::iter=150000;
  LXeutils::reps=1;
  LXeutils::boost=1.0;

  std::string inFileName=inRun+"_avg.root";
  std::string foutName=inRun+"_deconved.root";

  TFile *fout = new TFile(foutName.c_str(), "RECREATE");

  for(auto treeName:LXeutils::treesNames){

    TFile *inF = new TFile(inFileName.c_str(), "READ");

    if(inF->GetListOfKeys()->Contains(treeName.c_str())){

      std::cout << treeName <<"\n";
      std::vector<Double_t> T,I,sig=GetBranch(inFileName, treeName, "peak");
      std::vector<Double_t> sphe=GetBranch("FitSphes.root", treeName, "peak");


      for(int i=0; i<sig.size(); i++){
        I.push_back(i);
        if(sphe[i]<0)
          sphe[i]=0;
      }


    deconv(sig, sphe, 1000);

    TTree* t1 = new TTree(treeName.c_str(), treeName.c_str());
    Double_t time, sphePeak, peak;
    t1->Branch("peak", &peak, "peak/D");
    t1->Branch("sphePeak", &sphePeak, "sphePeak/D");
    t1->Branch("time", &time, "time/D");

    for(int i=0; i<sig.size(); i++){
      peak=sig[i];
      sphePeak=sphe[i];
      time=i/0.15;
      T.push_back(time);

      t1->Fill();
    }

    std::string graphName=treeName+"_graph";
    std::string spheGraphName=treeName+"_SpheGraph";

    TGraph *gSig = new TGraph(T.size(), &T[0], &sig[0]);
    gSig->SetTitle(graphName.c_str());
    gSig->SetName(graphName.c_str());

    TGraph *gSphe = new TGraph(T.size(), &T[0], &sphe[0]);
    gSphe->SetTitle(spheGraphName.c_str());
    gSphe->SetName(spheGraphName.c_str());

    fout->WriteObject(gSig, graphName.c_str(), "TObject::kOverwrite");
    fout->WriteObject(gSphe, spheGraphName.c_str(), "TObject::kOverwrite");
    fout->WriteObject(t1, treeName.c_str(), "TObject::kOverwrite");
    }
    inF->Close();
  }
}

void deconvFile(){
  std::vector<std::string> inFiles=GetFiles("_avg.root");

  for(auto s:inFiles){
    std::string runName=s.substr(0, s.find("_avg.root"));
    std::cout << runName  <<" \n ";
    deconvAFile(runName);
  }
}
