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

  void turnintoNamefile(std::string *pointerto_namefile, std::string namefile);

  virtual bool createFile(std::string const namefile) = 0;
  virtual bool writeonFile(std::string username, std::string password) = 0;
  virtual void verifyFile(std::string* search_username_ptr, std::string &search_username) = 0;
  virtual bool searchonFile(std::string username, std::string password) = 0;

protected:
  std::string marker_ = "-------------------";

};


class LoginFile : public FileAux
{

public: 

  bool isfileOpen(std::string const namefile);

  virtual bool createFile (std::string const namefile) override{
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

  virtual void verifyFile(std::string* search_username_ptr, std::string &search_username) override{
    
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

        _file.seekg(0, std::ios::beg);
      }
    }

    _file.close();
  }
      
  virtual bool searchonFile(std::string username, std::string password) override{
        
    std::string line;
    std::string file_username = "User: " + username + " // ";
    
    _file.open("login.txt", std::ios::in);
    _file.seekg(0, std::ios::beg);

    while(getline(_file, line)){
        if (file_username == line){

          _file.seekg(0, std::ios::beg);
          _file.close();

            return true;
        }
    }

    _file.seekg(0, std::ios::beg);
    _file.close();

    std::cout << "-- Nome de usuario nao encontrado --" 
            << std::endl;

    return false;
        
  }

protected:
  std::fstream _file;
};


class UserFile : public LoginFile
{

public:

  bool doesuserfileExists(std::string const namefile);

  virtual bool createFile (std::string const namefile) override{

    std::string username = namefile;
    username.erase(username.length() - 4 );

    _userfile.open(namefile, std::ios::app);

    _userfile << "User: " << username;
    _userfile << std::endl;

    _userfile.close();

    return true;
  }


  virtual bool searchonFile(std::string username, std::string password) override{
    
    std::string user_on_file = "User: " + username + " // ";
    std::string password_on_file = "Senha: " + password;
    
    std::string line;
    _file.open("login.txt", std::ios::in);

    while(getline(_file, line)){

      if (line == user_on_file){
        if (getline(_file, line)){
          if (line == password_on_file){
            std::cout << "Senha Correta!"
                << std::endl;
            std::cout << "-- Logando --"
                << std::endl;

            _file.seekg(0, std::ios::beg);
            _file.close();

            return true;
          }
        }
      }
    }

    std::cout << "Senha incorreta!"
            << std::endl;

    _file.seekg(0, std::ios::beg);
    _file.close();
    
    return false;

  }

private:
  std::fstream _userfile;
};

#include "empresa_.cpp"

#endif
