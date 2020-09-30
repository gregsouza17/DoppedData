

void tst(){

  system("pwd >> readFolder.txt");

  std::string folderName;
  std::ifstream file;
  file.open("readFolder.txt");
  file>>folderName;

  std::cout << folderName.substr(folderName.find("_N_")+3) <<" \n";

  system("rm readFolder.txt");

}
