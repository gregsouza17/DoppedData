#include <iostream>
#include <string>
#include <vector>

#include "/home/greg/myARPC/Codes/utilities.h"
#include "/home/greg/myARPC/Codes/LXe/LXeAnalysis.h"


void makePlot(std::vector<std::string> runName,
              std::vector<Int_t> ch ,
              std::vector<std::string> legends,
              std::string Title="Title", std::string opt=""){

  std::vector<std::string> fileNames;
  for(auto s:runName) fileNames.push_back(s+"_deconved.root");

  std::vector<std::string> graphName;
  std::vector<std::string> treeName;
  for(int i=0; i<fileNames.size(); i++){
    std::string s="_"+std::to_string(ch[i]);
    treeName.push_back("tCh"+std::to_string(ch[i]));
    graphName.push_back(runName[i]+s);

  }

  std::vector<TGraph*> graphs(fileNames.size());

  Double_t yshift(0);
  if(opt=="LOG")
    yshift=0;

  for(int i=0; i<fileNames.size(); i++){


    TFile* fin = new TFile(fileNames[i].c_str(), "READ");
    if(opt=="SHAPE" || opt=="LOG"){
      graphs[i] = new TGraph();
      TTree *t1 = (TTree*) fin->Get(treeName[i].c_str());
      Signal sig(t1,0);
      Double_t maximum = sig.GetHighestValue();
      std::vector<Double_t> sigVec=sig.GetVector();

      for(int k=0; k<sigVec.size(); k++){
        graphs[i]->SetPoint(k, (double) k/0.15, (sigVec[k]/maximum) + yshift);
      }
    }

    else
      graphs[i] = (TGraph*) fin->Get(graphName[i].c_str());

  }

  graphs[0]->SetTitle(Title.c_str());
  graphs[0]->Draw("AL");


  if(opt=="SHAPE"){
    graphs[0]->GetYaxis()->SetRangeUser(-0.05, 1.1);
    graphs[0]->GetYaxis()->SetTitle("a.u.");
  }
  else if(opt=="LOG"){
    graphs[0]->GetYaxis()->SetRangeUser(yshift-0.1, 1.1+yshift);
    graphs[0]->GetYaxis()->SetTitle("log a.u.");
    gPad->SetLogy();
  }
  else{
    graphs[0]->GetYaxis()->SetRangeUser(-250, 12000);
    graphs[0]->GetYaxis()->SetTitle("adcs");
  }
  //graphs[0]->SetStats(0);

  graphs[0]->GetXaxis()->SetTitle("t (ns)");
  Int_t lineWidth=2;
  graphs[0]->SetLineWidth(lineWidth);
  graphs[0]->SetLineColor(kBlue);

  for(int i=1; i<graphs.size(); i++){
    graphs[i]->Draw("same L");
    //graphs[i]->SetStats(0);

    graphs[i]->SetLineWidth(lineWidth);
    graphs[i]->SetLineColor(kBlue+i*2);
  }

  TLegend *legend = new TLegend(0.48,0.7,0.68,0.9);
  legend->SetHeader("Light Yield","C");
  for(int i=0; i<graphs.size(); i++){
    legend->AddEntry(graphs[i], legends[i].c_str(), "l");
  }
  legend->Draw("same");
}

void XeCompar30(std::string opt="LOG"){

  std::vector<std::string> runName={"30ppm",
                                    "30ppm"};
  std::vector<Int_t> ch={1,8,1,8};

  std::vector<std::string> legends={"30ppm wG", "30ppm nG"};

  std::string Title="Effects of 30ppmXe/N2 in LAr (Shape Comparison)";

  makePlot(runName, ch, legends, Title, opt);

}


void XeCompar10(std::string opt="LOG"){

  std::vector<std::string> runName={"10ppm", "10ppm"};
  std::vector<Int_t> ch={1,8};

  std::vector<std::string> legends={"10ppm wG", "10ppm nG"};

  std::string Title="Effects of 10ppmXe/N2 in LAr (Shape Comparison)";

  makePlot(runName, ch, legends, Title,opt);

}



void N2Compar(std::string opt="LOG"){

  std::vector<std::string> runName={"PreN2", "PreN2",
                                    "PostN2", "PostN2"};
  std::vector<Int_t> ch={0,8,0,8};
  std::vector<std::string> legends={"PreN2 wG", "PreN2 nG",
                                    "PostN2 wG", "PostN2 nG"};

  std::string Title="Effects of N2 in LAr (Shape Comparison)";

  makePlot(runName, ch, legends, Title,opt);

}

void All5ComparWG(std::string opt="LOG"){

  std::vector<std::string> runName={"PreN2", "PostN2",
                                    "10ppm", "20ppm", "30ppm"};
  std::vector<Int_t> ch={0,0,0,0,0};
  std::vector<std::string> legends={"PreN2", "PostN2",
                                    "10ppm", "20ppm", "30ppm"};

  std::string Title="From 0 to 30Xe ppm with quartz glass Deconv";

  makePlot(runName, ch, legends, Title, opt);

}

void All5ComparNG(std::string opt="LOG"){

  std::vector<std::string> runName={"PreN2", "PostN2",
                                    "10ppm", "20ppm", "30ppm"};
  std::vector<Int_t> ch={8,8,8,8,8};
  std::vector<std::string> legends={"PreN2", "PostN2",
                                    "10ppm", "20ppm", "30ppm"};

  std::string Title="From 0 to 30Xe ppm no quartz glass Deconv";

  makePlot(runName, ch, legends, Title, opt);

}


void makeCompar(){
  setLXe();

  XeCompar30();

  //N2Compar();

  //All5ComparWG();


  //All5ComparNG();
}
