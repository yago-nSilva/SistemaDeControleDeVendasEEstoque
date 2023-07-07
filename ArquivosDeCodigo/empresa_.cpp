// Implementação das funções contidas nas classes e arquivo empresa.hpp

// Função para exibir as senhas armazenadas no objeto Cadastro
void Cadastro::showPasswords(){
  for (unsigned int i = 0; i < Password.size(); i++){
    std::cout << Password.at(i) << std::endl;
  } 
}

// Função para exibir os nomes de usuário armazenados no objeto Cadastro
void Cadastro::showUsernames(){
  for (unsigned int i = 0; i < Username.size(); i++){
    std::cout << Username.at(i) << std::endl;
  }  
}

// Função para inserir um nome de usuário no objeto Cadastro
void Cadastro::insertUsername(std::string username){
    Username.push_back(username);
}

// Função para inserir uma senha no objeto Cadastro
void Cadastro::insertPassword(std::string password){
    Password.push_back(password);
}

// Função para confirmar uma senha no objeto Cadastro
bool Cadastro::confirmPassword(std::string confirmation_password){
  if (confirmation_password == Password.back()) return true;
  return false;
}

// Função para excluir o último nome de usuário cadastrado no objeto Cadastro
void Cadastro::deleteUsername(){
  Username.erase(Username.end() - 1);
}

// Função para excluir a última senha cadastrada no objeto Cadastro
void Cadastro::deletePassword(){
  Password.erase(Password.end() - 1);
}

// Função para transformar o nome em um nome de arquivo com extensão .txt
void FileAux::turnintoNamefile(std::string* pointerto_namefile, std::string name){
  std::string namefile = name + ".txt";
  *pointerto_namefile = name + ".txt";
}

// Função para verificar se um arquivo está aberto
bool LoginFile::isfileOpen(std::string const namefile){
  std::fstream file(namefile);
  return file.is_open();
}

// Função para verificar se o arquivo de usuário existe
bool UserFile::doesuserfileExists(std::string const namefile){
  std::fstream file(namefile);
  return file.is_open();
}
