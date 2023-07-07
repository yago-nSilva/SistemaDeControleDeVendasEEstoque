#include "empresa.hpp"
// #include "produto.hpp"
// #include "verificador.hpp"

#include <iostream>
#include <vector>
#include <string>
#include <cstdlib> // Limpar o terminal
#include <fstream>


int main() {

Cadastro cadastro;
LoginFile login_file;

UserFile user_file;
std::string *user_filename_ptr;
std::string userfile_name;

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

char choice;
char continue_choice;

unsigned loop = 0;

bool userexists_verify;
bool correct_password;

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
    
    std::cin >> choice;

    switch(choice){
        case '1':
                unsigned int second_choice;
                std::cout << "-- Fazendo login --"
                        << std::endl;
                std::cout << "Digite o nome de usuario: ";
                std::cin >> username;

                userexists_verify = login_file.searchonFile(username, password);
                if (!userexists_verify){
                        while (!userexists_verify){
                                std::cout << "------------------------"
                                        << std::endl;
                                std::cout << "Escolha uma das opcoes"
                                        << std::endl;
                                std::cout << "1 - Digitar outro nome de usuario"
                                        << std::endl;
                                std::cout << "2 - Sair"
                                        << std:: endl;
                                std::cout << "------------------------"
                                        << std::endl;
                                std::cin >> second_choice;

                                if (second_choice == 1){
                                        std::cout << "Digite o nome de usuario: ";
                                        std::cin >> username;
                                        userexists_verify = login_file.searchonFile(username, password);
                                }
                                else {
                                        std::cout << "saindo"
                                                << std::endl;
                                        break;
                                }
                        }
                }

                userfile_name = username;
                user_filename_ptr = &userfile_name;
                

                user_file.turnintoNamefile(user_filename_ptr, userfile_name);

                if (userexists_verify == true){
                        if(!user_file.doesuserfileExists(userfile_name)){
                                std::cout << "-- Arquivo nao existe --" 
                                        << std::endl;
                                std::cout << "-- Criando arquivo --"
                                        << std::endl;
                                user_file.createFile(userfile_name);
                        }

                        std::cout << "Digite a senha: ";
                        std::cin >> password;
                        correct_password = user_file.searchonFile(username, password);

                        if (correct_password == true){
                                std::cout << "-- Voce esta logado como: " << username
                                        << std::endl;
                        }

                        if (!correct_password){

                                char incorrect_password_choice;
                                std::cout << "------------------------"
                                        << std::endl;
                                std::cout << "1 - Deseja digitar a senha novamente? "
                                        << std::endl;
                                std::cout << "'S' - Sim // 'N' - Nao"
                                        << std::endl;
                                std::cin >> incorrect_password_choice;

                                std::cout << "------------------------"
                                        << std::endl;

                                while ((incorrect_password_choice == 's') || (incorrect_password_choice == 'S')){

                                        std::cout << "Digite a senha novamente: ";
                                        
                                        std::cin >> password;
                                        correct_password = user_file.searchonFile(username, password);

                                        if (correct_password == true){
                                                std::cout << "-- Voce esta logado como: " << username
                                                        << std::endl;
                                                break;
                                        }

                                        if(!correct_password){
                                                std::cout << "1 - Deseja digitar a senha novamente? "
                                                        << std::endl;
                                                  std::cout << "'S' - Sim // 'N' - Nao"
                                                	<< std::endl;

                                                std::cin >> incorrect_password_choice;
                                                std::cout << "------------------------"
                                                        << std::endl;
                                        }

                                }

                        }

                }

        break;

        case '2':
            
                std::cout << "-- Fazendo cadastro --"
                        << std::endl;

                std::cout << "Digite o nome de usuario: ";
                std::cin >> username;
                username_ptr = &username;
                login_file.verifyFile(username_ptr, username);

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
                                std::cout << "Digite a senha: ";
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

                // cadastro.showUsernames();
                // cadastro.showPasswords();

                std::cout << "Digite 0 para continuar: ";
                std::cin >> continue_choice;
                if (continue_choice == '0'){
                        break;
                }
                
                loop =  1;

            
                std::cout << "Saindo..." << std::endl;

                return 0;
                break;

        case '3':
            std::cout << "Saindo..." << std::endl;
            loop = 1;
        break;

        default: 
                std::cout << "-- Numero de escolha invalido --"
                        << std::endl;
        break;

   }
 }
}
