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

  return std::to_int(chNum);

}

void makeCosmicSample(){

  gROOT->SetBatch(true);

  std::vector<std::string> inFiles=GetFiles("copy.root");
  int num=monitorNumber();
  std::string foutName="N2Mon"+std::to_string(num)+"_sample.root";
  TFile *fout = new TFile(foutName.c_str(), "RECREATE");

  for(std::string s:inFiles){
    MakeCosmicSample(s, GetCh(s), fout);
  }

  gROOT->SetBatch(false);
}
