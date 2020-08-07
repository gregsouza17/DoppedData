#include "/home/greg/myARPC/Codes/Signals.C"
#include "/home/greg/myARPC/Codes/finder.C"
#include "/home/greg/myARPC/Codes/PeakSearcher.h"

#include "/home/greg/myARPC/Codes/utilities.h"
#include "/home/greg/myARPC/Codes/LXe/LXeAnalysis.h"

void getTailPeaks(Int_t ch){
  /*
    What should go in:
    - Channel to be evaluated

    What Should go Out:
    - A Graph of tails found in the end of the event

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

  //Create outfile as TFile
  TFile *fout = new TFile(outFile_str.c_str(), "RECREATE");

  //Sphe and x axis size, Persistence Sample Hist
  Int_t spheSize(2000), xsize= TMath::Power(2, TestParam::digitizerBits)/100;
  TH2D* sample = new TH2D("SignalSample", "Signals Selected",
                          spheSize, 0,
                          spheSize,
                          xsize, -20,
                          xsize-20);

  //Getting Files and creating searcher
  std::vector<std::string> inFiles=GetFiles(ForSearch_str);
  SpheSearcher sear;
  sear.searchSigma=5;
  sear.hPercent=0.2;

  std::string histName="chargeHist_Ch"+std::to_string(ch);
  std::string histTitle = "Charge Histogram for Channel " + std::to_string(ch);

  TH1D* hcharge = new TH1D(histName.c_str(), histTitle.c_str(), 1000, -20000, 100000);

  //Loop thorugh events in a single file (Later add multiple files)
  for(auto file:inFiles){
    TFile *fin = new TFile(file.c_str(), "READ");
    TTree *tin = (TTree*) fin->Get("t1");
    Int_t nevents = tin->GetEntries()/TestParam::linhas_evento;

    for(int ev=0; ev<nevents; ev++){
      Signal s(tin, ev);
      std::vector<Double_t> sig=s.GetVector();

      //      hcharge->Fill(s.Integrate(1000));

      sear.Search(sig, 1000, 2000);

      std::vector<Double_t> xp=sear.GetXpeaks();
      std::vector<Double_t> yp=sear.GetYpeaks();

      Int_t pStart(0), pEnd(0);

      Finder finder(10);
      for(int i=0; i<xp.size(); i++){
        Double_t charge=finder.PeakLimits(sig, xp[i], pStart, pEnd);

        if(pStart>=1000){
          std::cout<< "Peak charge:  "<< charge<< "\n";
          hcharge->Fill(charge);
        }
      } //For Peak

    } //For Event
    tin->Reset();
    fin->Close();
  } //FOr File

  hcharge->Draw();
} //End Function

void calFunctions(){
  //Main Function

  setLXe();
  getTailPeaks(1);
}
