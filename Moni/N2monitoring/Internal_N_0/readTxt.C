#include "../Codes/Reader.C"

#include "../Codes/CalibrationCode.C"


void readOne(std::string inF="27Nov2019_Vbias=47_LED_A_test_Ch0-2019-11-27_17-00-04",
	     Int_t maxEv=10000){

  setLXe();

  // std::cout << TestParam::adc_step << "\n" << TestParam::linhas_evento
  // 	    << "\n";


  //Reading up to 10000 events with a pretrigger count of 400
  Reader R(maxEv, 400);

  std::string ext(".dat");

  //Reades inF with extension ext, creates a file name inF + "_copy.root"
  std::string outFile=R.CopyTxt(inF, ext);


  //Extra graphs if you need
  // TFile *f1 = new TFile(std::string(inF+"_samples.root").c_str(), "RECREATE");
  // Calibration Cal(10000);

  // Cal.SetIntegrationTime(400, 1500);
  
  // Cal.MeanSignal(outFile, f1);
  //  Cal.SampleGraphs(outFile, f1);
  
  
}


void readTxt(Int_t maxEv=10000){
  setLXe();
  gROOT->SetBatch(true);
  system("rm dats.txt");
  system("rm *.root");
  system("ls | grep .dat >> dats.txt");

  std::ifstream file;
  std::string txtfile="dats.txt";
  file.open(txtfile.c_str());

  //  std::vector<std::string> datFiles;
  std::string data;
  while(!file.fail()){
    file>>data;
    std::string fname= data.substr(0, data.find(".dat",0));
    //    std::cout << fname <<"\n";
    readOne(fname, maxEv);
  }

  system("rm dats.txt");
  // system("mkdir dats");
  // system("mv *.dat* dats/");
    
  gROOT->SetBatch(false);
}


