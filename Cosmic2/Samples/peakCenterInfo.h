#include <string>


void peakCenter(std::string inRun, double &pCenter, double &pVar){

  if(inRun=="Bias47V_Day15_samples.root"){
    pCenter=383; pVar=5;
  }
  else if(inRun=="preDop_Day16_samples.root"){
    pCenter=383; pVar=5;
  }
  else if(inRun=="10ppmCR2_samples.root"){
        pCenter=432; pVar=6;
    }
  else if (inRun=="30ppmCR2_NDoping_samples.root"){
    pCenter=449; pVar=8;
  }
  else if(inRun=="AlphaFrom0_samples.root"){
    pCenter=400; pVar=9;
  }
  else if(inRun=="PreXe30ppm_samples.root"){
    pCenter=410; pVar=7;
  }
  else if(inRun=="XeFrom0_Day20_12-20-36_samples.root"){
    pCenter=448; pVar=5;
  }
  else if(inRun=="XeFrom0_Day20_16-00-36_samples.root"){
    pCenter=448; pVar=5;
  }
  else if(inRun=="XePreDopping_Day17_samples.root"){
    pCenter=414; pVar=6;
  }
  else if(inRun=="XeVMuon_Day17_samples.root"){
    pCenter=415; pVar=5;
  }
  else if(inRun=="XeVMuon_Day18_samples.root"){
    pCenter=410; pVar=4;
  }
  else{
    pCenter=430; pVar=50;
  }


}
