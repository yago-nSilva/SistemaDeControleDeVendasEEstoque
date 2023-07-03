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

void Cadastro::forcedinsertUsername(std::string username){
    Username.back() = username;
}

// bool Cadastro::verifyUsername(std::string username){
//     if (Username.empty()) return true;

//     unsigned test_key = 0;
//     for (unsigned i = 0; i < Username.size() - 1; i++){
        
//         if (username == Username.at(i)) test_key++;
//         if (test_key > 1) {
//             return false;
//         }
//     }

//     return true;
// }

void Cadastro::insertPassword(std::string password){
    Password.push_back(password);
}

bool Cadastro::confirmPassword(std::string password){
  //  if (Password.empty()) return false;

    for (unsigned i = 0; i < Password.size(); i++){
        if (password == Password.at(i)) return true;
    }

      Username.erase(Username.end() - 1);
      Password.erase(Password.end() - 1);

    return false;
}
