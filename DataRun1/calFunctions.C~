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
    - TH1D in a fout with charge, sample
    and Searcher Samples

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

  //Charge Histogram (NEED TO BE CALIBRATED IN TESTING)
  TH1D* hcharge = new TH1D("charges", "Sampled Charge Histis", 10000, -10000, 100000);

  //Getting Files and creating searcher
  std::vector<std::string> inFiles=GetFiles(ForSearch_str);
  SpheSearcher sear;
  sear.searchSigma=5;
  sear.hPercent=0.2;


  //Loop thorugh events in a single file (Later add multiple files)

  TFile *fin = new TFile(inFiles[10].c_str(), "READ");
  fin->Print();
  TTree *tin = (TTree*) fin->Get("t1");

  // Signal s(tin, 202);
  // s.Draw();

  //Add sample searcher graphs


}


void calFunctions(){
  //Main Function

  setLXe();
  getTailPeaks(0);
}
