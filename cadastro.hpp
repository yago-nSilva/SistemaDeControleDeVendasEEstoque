#ifndef CADASTRO_H
#define CADASTRO_H

#include <iostream>
#include <vector>
#include <string>

class Cadastro{
    public:

      void showPasswords();
      void showUsernames();
      void insertUsername(std::string username);
      void forcedinsertUsername(std::string username);  // utilizar outra classe
      void insertPassword(std::string password);
      bool confirmPassword(std::string password);   //
      bool verifyUsername(std::string username);    // utilizar outra classe

    private:
      std::vector<std::string> Username;
      std::vector<std::string> Password;
};

#include "cadastro_.cpp"

#endif
