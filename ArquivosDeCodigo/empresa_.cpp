//Implementação das funções contidas nas classes e arquivo empresa.hpp

void Cadastro::showPasswords(){
  for (unsigned int i = 0; i < Password.size(); i++){
    std::cout << Password.at(i) << std::endl;
  } 
}

void Cadastro::showUsernames(){
  for (unsigned int i = 0; i < Username.size(); i++){
    std::cout << Username.at(i) << std::endl;
  }  
}

void Cadastro::insertUsername(std::string username){
    Username.push_back(username);
}

void Cadastro::insertPassword(std::string password){
    Password.push_back(password);
}

bool Cadastro::confirmPassword(std::string confirmation_password){

  if (confirmation_password == Password.back()) return true;

  return false;
}

void Cadastro::deleteUsername(){
  Username.erase(Username.end() - 1);
}

void Cadastro::deletePassword(){
  Password.erase(Password.end() - 1);
}

void FileAux::turnintoNamefile(std::string* pointerto_namefile, std::string name){
  
  std::string namefile = name + ".txt";

  *pointerto_namefile = name + ".txt";

}

bool LoginFile::isfileOpen(std::string const namefile){
  
  std::fstream file(namefile);

  return file.is_open();
}

bool UserFile::doesuserfileExists(std::string const namefile){

  std::fstream file(namefile);

  return file.is_open();
}



