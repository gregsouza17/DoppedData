#include "/home/greg/myARPC/Codes/LXe/LXeAnalysis.h"
#include "/home/greg/myARPC/Codes/utilities.h"

Int_t monitorNumber(std::string searString="_N_"){
  system("pwd >> readFolder.txt");

  std::string folderName;
  std::ifstream file;
  file.open("readFolder.txt");
  file>>folderName;

  std::string chNum=folderName.substr(folderName.find(searString)+
                                      searString.size());

  system("rm readFolder.txt");

  return std::stoi(chNum);

}


void basePh(Int_t runIndex=7, Int_t rebin=10){

  //std::string runName=CosmicRun1::names[runIndex];

  int num=monitorNumber("_N_");
  std::string runName="N2Mon"+std::to_string(num);

  std::string outName = runName + "_lightYield.root";
  TFile *fout = new TFile(outName.c_str(), "Recreate");

  TCanvas *c1 = new TCanvas("c1", "Light Yield Hists", 800,600);
  TPad *pad = new TPad("pad","",0,0,1,1);

  std::vector<std::string> Glass, noGlass;

  GetFilenames(Glass, noGlass);

  //Glass Hist
  std::string GhistName=runName+"phHist_glass";
  std::string GhistTile = "Light Seen in " + runName + "w/ Glass";

  int range=5000;
  int nbins=range;

  TH1D *hg = new TH1D(GhistName.c_str(), GhistTile.c_str(),
                      nbins,0,range);
  int gphotons(0);
  for(auto s:Glass){
    gphotons+=makePhotonHist(s, hg, 1.2);
  }


  std::string NhistName=runName+"phHist_Noglass";
  std::string NhistTile = "No Glass";

  TH1D *hn = new TH1D(NhistName.c_str(), NhistTile.c_str(),
                      nbins,0,range);
  int nphotons(0);
  for(auto s:noGlass){
    nphotons+=makePhotonHist(s, hn);
  }

  //Getting qunatities
  Int_t nquantiles(4);
  Double_t probs[]={0.5, 0.7, 0.9, 0.99}, quants[4], quantsN[4];
  hg->GetQuantiles(nquantiles, quants, probs);
  hn->GetQuantiles(nquantiles, quantsN, probs);

  double gint=gphotons/hg->GetEntries() ;
  double nint=nphotons/hn->GetEntries() ;

  std::string outTxt=runName+"Log.txt";
  std::ofstream myfile;
  myfile.open(outTxt);

  myfile << "\t \t Glass \t No Glass \n"
            << "Mean \t" << hg->GetMean() << "\t" << hn->GetMean() <<"\n"
            << "Light/Events \t " << gint << "\t" << nint << "\n"
            << "Median \t " << quants[0] << "\t" << quantsN[0]  << "\n";

  for(int i=1; i<nquantiles; i++){
    myfile << "N# < " << probs[i] << "\t" << quants[i] << "\t"
              << quantsN[i] << "\n";
  }

  //pad->cd();

  fout->WriteObject(hg, GhistName.c_str(),"TObject::kOverwrite");
  fout->WriteObject(hn, NhistName.c_str(),"TObject::kOverwrite");

  hg->Scale(1/hg->Integral());
  hn->Scale(1/hn->Integral());


  hg->Rebin(rebin);
  hn->Rebin(rebin);

  hg->Draw("HIST");
  hg->SetStats(0);

  hg->GetXaxis()->SetRangeUser(0,(int) quantsN[1]*2);
  hg->GetXaxis()->SetTitle("N# Photons");
  hg->GetYaxis()->SetTitle("Frequency");

  hg->SetLineWidth(2);
  hg->SetLineColor(kRed);

  hn->Draw("same HIST");
  hn->SetStats(0);
  hn->SetLineWidth(2);

  TLegend *legend = new TLegend(0.48,0.7,0.68,0.9);
  legend->SetHeader("Light Yield","C");
  legend->AddEntry(NhistName.c_str(), "No Glass", "l");
  legend->AddEntry(GhistName.c_str(), "With Glass", "l");
  legend->Draw("same");

  fout->WriteObject(c1, "YieldCompare", "TObject::kOverwrite");

}
