#include "empresa.hpp"

#include <iostream>
#include <vector>
#include <string>
#include <cstdlib> // Limpar o terminal
#include <fstream>


int main() {

Cadastro cadastro;
LoginFile login_file;

std::string const login_filename = "login.txt";

if (!login_file.isfileOpen(login_filename)){
        std::cout << "arquivo existe" << std::endl;
        login_file.createFile(login_filename);
}

std::string* username_ptr;
std::string username;

std::string password;
std::string confirmation_password;

std::string teste;

unsigned int escolha;
unsigned int escolha_;

unsigned loop = 0;
while(loop == 0){     

    std::cout << "------------------------"
            << std::endl;
    std::cout << "Escolha uma das opcoes" 
            << std::endl;
    std::cout << "1 - Login" 
            << std::endl;
    std::cout << "2 - Cadastro" 
            << std::endl;
    std::cout << "3 - Sair"
            << std::endl;
    std::cout << "------------------------"
            << std::endl;
    
    std::cin >> escolha;

    switch(escolha){
        case 1:
            std::cout << "-- Fazendo login --"
                << std::endl;                
break;

        case 2:
            
                std::cout << "-- Fazendo cadastro --"
                        << std::endl;

                std::cout << "Digite o nome de usuario: ";
                std::cin >> username;
                username_ptr = &username;
                login_file.searchonFile(username_ptr, username); // nesse caso nao esta salvando, verificar o motivo

                cadastro.insertUsername(username);

                std::cout << "Digite a senha: ";
                std::cin >> password;
                cadastro.insertPassword(password);

                std::cout << "Confirme a senha: ";
                std::cin >> confirmation_password;

        for (unsigned int i = 0; i < 1; i++){    
                if (confirmation_password != password){

                        std::cout << "-- SENHA ERRADA --" 
                            << std::endl;
                        std::cout << "-- CONFIRME A SENHA NOVAMENTE --" 
                            << std::endl;
                        std::cin >> confirmation_password;

                        if (confirmation_password != password){
                                std::cout << "-- SENHA ERRADA --"
                                        << std::endl;
                                std::cout << "-- REALIZE O CADASTRO NOVAMENTE --"
                                        << std::endl;
                        
                                 cadastro.deleteUsername();
                                 cadastro.deletePassword();

                                i = 3;
                        }   
                        else {
                                std::cout << "-- Cadastro Finalizado --" 
                                        << std::endl;
                                login_file.writeonFile(username, password);
                                i = 3;
                        }
                }

                else  {
                        std::cout << "-- Cadastro Finalizado --" 
                                << std::endl;
                        login_file.writeonFile(username, password);
                        i = 3;
                }

        }      

        cadastro.showUsernames();
        cadastro.showPasswords();

        std::cout << "Digite 0 para continuar: ";
        std::cin >> escolha_;
        if (escolha_ != 0) loop =  1; //////// fazer caso de exceção para quando não é letra

            
        std::cout << "saindo" << std::endl;

        break;

        case 3:
            std::cout << "saindo" << std::endl;
            loop = 1;
        break;

        default: 
                std::cout << "Numero de escolha invalido"
                        << std::endl;

        }

    }

}
