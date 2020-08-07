#include "/home/greg/myARPC/Codes/Reader.C"
#include "/home/greg/myARPC/Codes/RunGlobals.h"
#include "/home/greg/myARPC/Codes/utilities.h"


void copyToRoot(){
  //Turn .dats into .root, putting their info in a tree, with baseline calculated
  
  setLXe();
  
  std::string ext=".dat";
  std::vector<std::string> Files=GetFiles(ext);

  Reader R(20000, 600, 10);
  
  for(int i=0; i<Files.size(); i++){
    Files[i] = Files[i].substr(0, Files[i].find(ext));
    R.CopyTxt(Files[i], ext);
  }
}
