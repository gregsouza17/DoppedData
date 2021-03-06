#include <iostream>
#include <string>
#include <vector>

#include "/home/greg/myARPC/Codes/utilities.h"
#include "/home/greg/myARPC/Codes/LXe/LXeAnalysis.h"




std::vector<Double_t> getAvg(std::string inFile, std::string treeName,
            Int_t avgPos, Int_t posRange){

  std::vector<std::string> inFiles=GetFiles(".root");

  TH1I* hPeakPos = new TH1I("h1", "PeakPos", 2000, 0, 2000);
  TFile *inF= new TFile(inFile.c_str(), "READ");
      //std::cout << treeName <<"\t" << s <<"\n";

  TTree *t1 = (TTree*) inF->Get(treeName.c_str());
  Int_t nevents = t1->GetEntries()/TestParam::linhas_evento;

  Int_t added(0);
  std::vector<Double_t> I, avgSig(TestParam::linhas_evento);
  std::fill(avgSig.begin(), avgSig.end(), 0);

  for(int ev=0; ev<nevents; ev++){
    Signal sig(t1, ev);
    Int_t highPos = sig.GetHighestPeak();
    Int_t posDif=avgPos-highPos;

    //std::cout << posDif << "\t" << posRange <<"\n";

    if(std::fabs(posDif)<posRange){
      added++;
      std::vector<Double_t> sigVec=sig.GetVector();
      for(int i=0; i<sigVec.size(); i++){
        Int_t relPos=i+posDif;
        Int_t relEnd=posDif+sigVec.size();

        if(relPos<0)
          avgSig[i]+=0;
        else if(relPos>=relEnd)
          avgSig[i]+=0;
        else
          avgSig[i]+=sigVec[i];


      } //For
    } //If
  }//For


  for(Int_t i=0; i<avgSig.size(); i++){
    avgSig[i]/=added;
    I.push_back(i);
  }
  return avgSig;

  //TGraph *g1 = new TGraph(I.size(), &I[0], &avgSig[0]);
  //g1->Draw("AL");
}

void GetAvgCosmic(){
  setLXe();

  std::vector<std::string> inFiles=GetFiles("_samples.root");
  for(auto s:inFiles){
    std::string runName=s.substr(0, s.find("_samples.root"));
    std::string inFile=runName+"_samples.root";
    std::string outFile=runName+"_avg.root";

    TFile* outF = new TFile(outFile.c_str(), "RECREATE");

    for(auto ch:LXeutils::Channels){
      std::string treeName="tCh"+std::to_string(ch);
      std::vector<Double_t> I, avgSig=getAvg(inFile, treeName,
                                             380,
                                             30);

      TTree *t1 = new TTree(treeName.c_str(), treeName.c_str());
      Double_t peak, time;
      t1->Branch("peak", &peak, "peak/D");
      t1->Branch("time", &time, "time/D");
      for(int i=0; i<avgSig.size(); i++){
        peak=avgSig[i];
        time=i/0.15;
        I.push_back(i);

        t1->Fill();
      }

      TGraph *g1 = new TGraph(I.size(), &I[0], &avgSig[0]);
      std::string graphTitle = runName + "Avg Cosmic Ch"+std::to_string(ch);
      if(ch<5)
        graphTitle+=" with Glass";
      else
        graphTitle+=" no Glass";

      std::string graphName=runName+"_"+std::to_string(ch);

      outF->WriteObject(t1, treeName.c_str(), "TObject::kOverwrite");
      outF->WriteObject(g1, graphName.c_str(), "TObject::kOverwrite");
      t1->Delete();
      g1->Delete();
    }
    outF->Close();
  }

}
