#include "/home/greg/myARPC/Codes/Signals.C"
#include "/home/greg/myARPC/Codes/finder.C"
#include "/home/greg/myARPC/Codes/PeakSearcher.h"

#include "/home/greg/myARPC/Codes/utilities.h"
#include "/home/greg/myARPC/Codes/LXe/LXeAnalysis.h"



void makeAtree(Int_t ch, Double_t charge, Double_t var){

  //Create Outfile names based on channel
  std::string CH = "Ch" + std::to_string(ch);
  std::string outFile = CH+"sphes.root";
  std::string st = "Ch" + std::to_string(ch) +
    "-";

  //Creates out file and out tree
  TFile *fout= new TFile(outFile.c_str(), "RECREATE");
  TTree *t1 = new TTree("t1", "t1");
  Double_t peak, time;
  Int_t entry(0);
  t1->Branch("peak", &peak, "peak/D");
  t1->Branch("time", &time, "time/D");
  t1->Branch("entry", &entry, "entry/I");

  //Files to be used in the code
  std::vector<std::string> inFiles=GetFiles(st);

  //Defines Sigma and height for the peaks to be searched
  SpheSearcher sear;
  sear.searchSigma=5;
  sear.hPercent=0.2;

  Double_t sigma(1), tres(28);
  //Defines a finder to select the charges
  ChargeFinder f(charge, var, sigma, tres);

  //Sample Hist and SpheSize for future use
  Int_t spheSize(2000), xsize= TMath::Power(2, TestParam::digitizerBits)/100;
  TH2D* sample = new TH2D("sample", "Sphes Selected",
			  spheSize, 0,
			  spheSize,
			  xsize, -20,
			  xsize-20);
  TH1D* hcharge = new TH1D("charges", "Sampled Charge Hists", 500,
			   0, 20000);

  //Average signal
  std::vector<Double_t> avg(spheSize);

  std::fill(avg.begin(), avg.end(), 0);

  //Runs through files
  for(int i=0; i<inFiles.size(); i++){

    TFile *fin = new TFile(inFiles[i].c_str(), "READ");
    TTree *tin = (TTree*) fin->Get("t1");

    Double_t inPeak, inTime;

    Int_t nentries = tin->GetEntries()/TestParam::linhas_evento;
    for(int ev=0; ev<nentries; ev++){

      Signal s(tin, ev);
      std::vector<Double_t> sig=s.GetVector();

      //Find peaks in the last 1000 entries of the signal vector
      sear.Search(sig, 1000);

      std::vector<Double_t> xp=sear.GetXpeaks();
      std::vector<Double_t> yp=sear.GetYpeaks();

      Int_t pStart(0), pEnd(0);
      //For each found peak
      for(int i=0; i<xp.size(); i++){
        //evaluetes charges for Sphe
        bool isSphe = f.isPeak(sig, xp[i], pStart, pEnd);

        //if is, se the start point at 0 and fill up to SpheSize events
        if(isSphe){
          for(int j=pStart; j<spheSize+pStart; j++){

            time=(j-pStart)/0.15;
            if(j<pEnd)
              peak=sig[j];

            else
              peak=0;

            //Set samples and add peak to average
            avg[j-pStart]+=peak;
            sample->Fill(j-pStart, peak);
            t1->Fill();

          }
          entry++;
          //	  std::cout << entry << "\n";
          hcharge->Fill(f.lastCharge);
        }

        pStart=0; pEnd=0;
      }
    }

    tin->Delete();
    fin->Close();
  }

  //Save stuff in the file
  fout->cd();
  std::string tTitle = "tCh"+std::to_string(ch);
  TTree *tavg = new TTree(tTitle.c_str(), tTitle.c_str());
  Double_t avgpeak, avgtime;
  tavg->Branch("peak", &avgpeak, "peak/D");
  tavg->Branch("time", &avgtime, "time/D");

  std::vector<Double_t> I;
  for(int i=0; i<avg.size(); i++){
    avg[i]/=entry;
    I.push_back(i);

    avgpeak=avg[i];
    avgtime=i/0.15;

    tavg->Fill();

  }

  tavg->Write();

  TGraph *gr = new TGraph(I.size(), &I[0], &avg[0]);
  gr->SetTitle("Average Sphe");
  gr->SetLineWidth(2);
  gr->SetLineColor(kBlue);
  gr->Draw();
  gr->Write();


  //saving avg sphe



  TCanvas *c1 = new TCanvas("c1", "Events Sample");
  c1->SetGrid();
  c1->SetTicks();
  sample->Draw("COLZ");
  fout -> WriteObject(c1, "persistence", "TObject::kOverwrite");
  hcharge->Write();
  t1->Write();
}


void collapse(){

  std::vector<std::string> spheFiles=GetFiles("sphes.root");

  TFile *fout = new TFile("Sphes.root", "RECREATE");

  for(int i=0; i<spheFiles.size(); i++){

    std::string tName = "t" + spheFiles[i].substr(0, spheFiles[i].find("sphes"));

    std::vector<Double_t> peaks=GetBranch(spheFiles[i], tName, "peak");
    std::vector<Double_t> times=GetBranch(spheFiles[i], tName, "time");

    TTree *tin = new TTree(tName.c_str(), tName.c_str());
    Double_t peak, time;
    tin->Branch("peak", &peak, "peak/D");
    tin->Branch("time", &time, "time/D");

    for(int j=0; j<peaks.size(); j++){
      peak=peaks[j];
      time=times[j];
      tin->Fill();
    }

    fout->WriteObject(tin, tName.c_str(), "TObject::kOverwrite");

    tin->Delete();
  }

}

void makeTree(){
  //  Int_t i=1;

  setLXe();
  gROOT->SetBatch(true);

  for(int i=0; i<LXeutils::Channels.size(); i++){

    makeAtree(LXeutils::Channels[i],
  	      CosmicRun1::charges[i],
  	      CosmicRun1::vars[i]);
  }

  collapse();

  gROOT->SetBatch(false);
}
