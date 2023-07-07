#ifndef EMPRESA_H
#define EMPRESA_H

#include <iostream>
#include <vector>
#include <string>
#include <fstream>

class Cadastro
{
public:

  void showPasswords();
  void showUsernames();

  void insertUsername(std::string username);
  void insertPassword(std::string password);

  void deleteUsername(); // Deleta o último nome de usuário cadastrado
  void deletePassword(); // Deleta a última senha cadastrada

  bool confirmPassword(std::string confirmation_password);    

private:

  std::vector<std::string> Username;
  std::vector<std::string> Password;
};

class FileAux
{
public:

  std::string turnintoNamefile(std::string namefile);

  virtual bool createFile(std::string const namefile) = 0;
  virtual bool writeonFile(std::string username, std::string password) = 0;
  virtual void searchonFile(std::string* search_username_ptr, std::string &search_username) = 0;

protected:
  std::string marker_ = "-------------------";

};

class LoginFile : public FileAux
{

public: 

  bool isfileOpen(std::string const namefile);

  bool createFile (std::string const namefile) override{
  _file.open(namefile, std::ios::out);

  _file << "-- Dados de login --"
      << std::endl;

  _file << marker_;

  if(!_file.is_open()){
    std::cout << "Erro ao abrir o arquivo" //
            << std::endl;

    return false;
  }

  std::cout << "Arquivo Aberto" //
          << std::endl;

  _file.close();
  return true;
  }
  
  virtual bool writeonFile(std::string username, std::string password) override{

    _file.open("login.txt", std::ios::in);

    std::string search_word;
    std::string line;
    
    do {
      
      if (_file.eof()){
        _file.close();

        _file.open("login.txt", std::ios::app);

        _file << std::endl;
        _file << "User: " << username 
              << " // " << std::endl
              <<"Senha: " << password 
              << std::endl << marker_;
      }
    } while (getline(_file, line));
    

    _file.close();

    return true;
  }

  virtual void searchonFile(std::string* search_username_ptr, std::string &search_username) override{
    
    _file.open("login.txt", std::ios::in);

    std::string line;
    std::string username_string = "User: " + *search_username_ptr + " // ";
    
    while (getline(_file, line)){

      if (line == username_string){
        while (line == username_string){
          *search_username_ptr = "";   // Ressetar o search_username;
          std::cout << "-- Nome de usuario ja cadastrado --"
                  << std::endl;
          std::cout << "Digite outro nome de usuario: ";
          
          std::cin >> search_username;

          username_string = "User: " + *search_username_ptr + " // ";

        }

        break;
      }
    }

    _file.close();
  }

private:
  std::fstream _file;
};


#include "empresa_.cpp"

#endif
