#ifndef EMPRESA_H
#define EMPRESA_H

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
      bool verifyUsername(std::string username);    // utilizar outra classe // Utilizar método com arquivo para verificar se nome de usuario ja existe

    private:
      std::vector<std::string> Username;
      std::vector<std::string> Password;
};

#include "empresa_.cpp"

#endif
