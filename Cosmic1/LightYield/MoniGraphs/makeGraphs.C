#include "moniData.C"

void graphMaker(std::vector<Double_t> T,
                std::vector<Double_t> glass,
                std::vector<Double_t> noGlass,
                double endTime,
                std::string title="No Title"){


  TGraph *gNo = new TGraph(T.size(), &T[0], &noGlass[0]);
  gNo->SetMarkerStyle(22);
  gNo->SetMarkerColor(kBlack);
  gNo->SetMarkerSize(1);

  gNo->SetLineColor(kBlue);
  gNo->SetLineWidth(2);

  TGraph *gGlass= new TGraph(T.size(), &T[0], &glass[0]);
  gGlass->SetMarkerStyle(23);
  gGlass->SetMarkerColor(kBlack);
  gGlass->SetMarkerSize(1);

  gGlass->SetLineColor(kOrange-5);
  gGlass->SetLineWidth(2);

  gNo->GetYaxis()->SetRangeUser(std::min(gNo->GetYaxis()->GetXmin(),
                                   gGlass->GetYaxis()->GetXmin())-100,
                          std::max(gNo->GetYaxis()->GetXmax(),
                                   gGlass->GetYaxis()->GetXmax())+100);


  gNo->SetTitle(title.c_str());
  gNo->GetXaxis()->SetTitle("T (min)");
  gNo->GetYaxis()->SetTitle("Average #gamma/Ev");

  gNo->Draw("ALP");

  gGlass->Draw("same LP");

  TGraph *gEnd = new TGraph();
  gEnd->SetPoint(0, 0, 0);
  gEnd->SetPoint(1, 0, 2000);
  gEnd->SetPoint(2, endTime, 2000);
  gEnd->SetPoint(3, endTime, 0);
  gEnd->SetLineColor(kRed);
  gEnd->SetLineWidth(1);
  gEnd->Draw("same L");

  TLegend *lgd = new TLegend(0.6,0.7,0.9,0.9);
  lgd->SetHeader("Legend", "C");
  lgd->AddEntry(gNo, "No Glass", "l");
  lgd->AddEntry(gGlass, "Glass", "l");
  lgd->AddEntry(gEnd, "Started/Stopped Dopping", "l");

  lgd->Draw();

}


void makeGraphs(){

  using namespace N2;

  graphMaker(RelTime, LYGlass, LYNoGlass,endTime,
             "N2 Dopping Monitoring Light Yield");



  // using namespace Xe10ppm;
  // graphMaker(RelTime, LYGlass, LYNoGlass,endTime,
  //            "Xe Dopping from 0 to 10ppm Monitoring");

  // using namespace Xe20ppm;
  // graphMaker(RelTime, LYGlass, LYNoGlass, 100,
  //            "Xe Dopping from 10 to 20ppm Monitoring");


}
