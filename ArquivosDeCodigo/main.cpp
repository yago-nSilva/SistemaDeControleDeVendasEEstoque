#include "empresa.hpp"

#include <iostream>
#include <vector>
#include <string>
#include <cstdlib> // Limpar o terminal


int main() {

Cadastro cadastro;
std::string username;
std::string password;
std::string confirmation_password;

unsigned escolha;
unsigned escolha_;

unsigned loop = 0;
    while(loop == 0){       // O uso de uma variável como parâmetro do while se deve à sintaxe do switch case
        
        //std::system("cls");

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
                cadastro.insertUsername(username);
                // while(!cadastro.verifyUsername(username)){
                //     std::cout << "----- Nome de usuario invalido -----"
                //             << std::endl;
                //     std::cout << "Digite o nome de usuario novamente: ";
                //     std::cin >> username;
                //     if (cadastro.verifyUsername(username)) break;  //////////////////////
                // }

                //cadastro.forcedinsertUsername(username);

                std::cout << "Digite a senha: ";
                std::cin >> password;
                cadastro.insertPassword(password);

                std::cout << "Confirme a senha: ";
                std::cin >> confirmation_password;
                if (cadastro.confirmPassword(confirmation_password) == false){
                    std::cout << "-- SENHA ERRADA --" << std::endl;
                    std::cout << "Realize o cadastro novamente" << std::endl;
                    loop = 1;
                }   else std::cout << "-- Cadastro Finalizado --" 
                                << std::endl;
                

                cadastro.showUsernames();
                cadastro.showPasswords();

                std::cout << "Digite 0 para continuar: ";
                std::cin >> escolha_;
                if (escolha_ == 0) continue;
                
                loop = 1;
                std::cout << "saindo" << std::endl;

            // return 0;
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
