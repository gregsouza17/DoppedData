#include "/home/greg/myARPC/Codes/Signals.C"
#include "/home/greg/myARPC/Codes/finder.C"
#include "/home/greg/myARPC/Codes/PeakSearcher.h"
#include "/home/greg/myARPC/Codes/CalibrationCode.C"


#include "/home/greg/myARPC/Codes/utilities.h"
#include "/home/greg/myARPC/Codes/LXe/LXeAnalysis.h"

void getTailPeaks(Int_t ch, Calibration &cal, Int_t searSigma=3,
                  Double_t searPerc=0.15){
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
  std::string outFile_str = CH_str+"_Cal.root";
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
  TH1D* hcharge = new TH1D("ChargeHist", "Sampled Charge Histis", 10000, -20000, 100000);

  //Getting Files and creating searcher
  std::vector<std::string> inFiles=GetFiles(ForSearch_str);
  Int_t firstEntry(0), lastEntry(1000);
  for(auto file:inFiles){
    TFile *fin = new TFile(file.c_str(), "READ");
    TTree *t1 = (TTree*) fin->Get("t1");
    Int_t nentries = t1->GetEntries()/TestParam::linhas_evento;

    for(int ev=0; ev<nentries; ev++){
      Signal s(t1, ev);
      std::vector<Double_t> sig=s.GetVector();
      SpheSearcher Sear(0, searSigma, searPerc);
      Int_t npeaks=Sear.Search(sig, firstEntry, lastEntry);
      if(npeaks<2){
        Double_t charge=s.Integrate(610, 900);
        hcharge->Fill(charge);
      }
    }
  }

  // hcharge->Scale(hcharge->Integral());
  // hcharge->Draw();

  fout->WriteObject(hcharge, "ChargeHist_noFit", "TObject::kOverwrite" );
  cal.FitHist(hcharge);
  fout->WriteObject(hcharge, hcharge->GetName(), "TObject::kOverwrite" );

}

void fitCh0(){
  Calibration cal;

  cal.npeaks=4;

  cal.peak0=0.012;
  cal.mean0=-100.0;
  cal.sigma0=200;

  cal.peak1=0.0035;
  cal.mean1=5500;
  cal.sigma1=500;

  cal.nextpeak=0.005;

  cal.xmin=-1000;
  cal.xmax=30000;
  cal.nextfactor=3;

  getTailPeaks(0, cal);

}

void fitCh1(){
  Calibration cal;

  cal.npeaks=4;

  cal.peak0=0.012;
  cal.mean0=-100.0;
  cal.sigma0=200;

  cal.peak1=0.0035;
  cal.mean1=5500;
  cal.sigma1=500;

  cal.nextpeak=0.005;

  cal.xmin=-1000;
  cal.xmax=30000;
  cal.nextfactor=3;
  cal.rebinNum=10;
  getTailPeaks(1, cal);

}

void fitCh2(){
  Calibration cal;

  cal.npeaks=4;

  cal.peak0=0.012;
  cal.mean0=-100.0;
  cal.sigma0=200;

  cal.peak1=0.0035;
  cal.mean1=5500;
  cal.sigma1=500;

  cal.nextpeak=0.005;

  cal.xmin=-1000;
  cal.xmax=30000;
  cal.nextfactor=3;

  getTailPeaks(2, cal, 3, 0.2);

}

void fitCh8(){
  Calibration cal;

  cal.npeaks=4;

  cal.peak0=0.012;
  cal.mean0=0.0;
  cal.sigma0=200;

  cal.peak1=0.0035;
  cal.mean1=5500;
  cal.sigma1=500;

  cal.nextpeak=0.005;

  cal.xmin=-1000;
  cal.xmax=30000;
  cal.nextfactor=2;

  getTailPeaks(8, cal, 3, 0.16);

}

void fitCh9(){
  Calibration cal;

  cal.npeaks=4;

  cal.peak0=0.045;
  cal.mean0=0.0;
  cal.sigma0=200;

  cal.peak1=0.008;
  cal.mean1=5500;
  cal.sigma1=500;

  cal.nextpeak=0.005;

  cal.xmin=-1000;
  cal.xmax=30000;
  cal.nextfactor=2;
  cal.rebinNum=10;

  getTailPeaks(9, cal, 3, 0.9);

}
void calFunctions(){
  //Main Function

  setLXe();
  //fitCh1();
  fitCh9();

}
