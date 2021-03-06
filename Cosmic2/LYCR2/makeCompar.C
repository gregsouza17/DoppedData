

void makePlot(std::vector<std::string> runName,
              std::string type,
              std::vector<std::string> legends,
              std::string Title="Title", Int_t rebin=1){

  std::vector<std::string> fileNames;
  for(auto s:runName) fileNames.push_back(s+"_lightYield.root");

  std::vector<std::string> histName;
  for(int i=0; i<fileNames.size(); i++){
    std::string s="phHist_"+type;
    histName.push_back(runName[i]+s);
  }

  std::vector<TH1I*> hists(fileNames.size());

  for(int i=0; i<fileNames.size(); i++){
    TFile* fin = new TFile(fileNames[i].c_str(), "READ");
    hists[i] = (TH1I*) fin->Get(histName[i].c_str());
    hists[i]->Scale(1/hists[i]->Integral());
    //hists[i]->Print();
    //fin->Close();
  }

  hists[0]->Rebin(rebin);
  hists[0]->SetTitle(Title.c_str());
  hists[0]->Draw("HIST");
  hists[0]->SetStats(0);

  hists[0]->GetXaxis()->SetTitle("N# Photons");
  hists[0]->GetYaxis()->SetTitle("Frequency");

  hists[0]->SetLineWidth(2);
  hists[0]->SetLineColor(kBlue);

  for(int i=1; i<hists.size(); i++){
    hists[i]->Rebin(rebin);
    hists[i]->Draw("same HIST");
    hists[i]->SetStats(0);

    hists[i]->SetLineWidth(2);
    hists[i]->SetLineColor(kBlue+i*4);
  }

  TLegend *legend = new TLegend(0.48,0.7,0.68,0.9);
  legend->SetHeader("Light Yield","C");
  for(int i=0; i<hists.size(); i++){
    legend->AddEntry(hists[i], legends[i].c_str(), "l");
  }
  legend->Draw("same");



}

void GlassEvoCompar(){
  std::vector<std::string> runName={"PreN2", "PostN2", "10ppm", "20ppm",
                                    "30ppm"};
  std::vector<std::string> legends={"Pre N2 w glass", "Post N2 w glass",
                                    "10ppm Xe w glass", "20ppm Xe w glass",
                                    "30ppm Xe w glass"};

  std::string type="glass";

  makePlot(runName, type, legends ,"Light Yield With Glass Comparison", 6);
}


void NoEvoCompar(){
  std::vector<std::string> runName={"PreN2", "PostN2", "10ppm", "20ppm",
                                    "30ppm"};
  std::vector<std::string> legends={"Pre N2", "Post N2",
                                    "10ppm Xe", "20ppm Xe",
                                    "30ppm Xe"};

  std::string type="Noglass";

  makePlot(runName, type, legends ,"Light Yield No Glass Comparison", 20);

}

void noGlassN2(){

    std::vector<std::string> runName={"PreN2", "PostN2"};

    std::vector<std::string> legends={"Pre N2 no glass", "Post N2 no glass"};

    std::string type="Noglass";

    makePlot(runName, type, legends ,"No Glass Comparison to N2", 20);



}

void makeCompar(){

  noGlassN2();

}
