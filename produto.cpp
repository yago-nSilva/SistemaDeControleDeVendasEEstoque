#include "produto.hpp"
#include <sstream>


Produto::Produto(const std::string& nome, const std::string& codigo, const std::string& categoria, double preco, const std::string& unidade, int quantidade)
    : _nome(nome), _codigo(codigo), _categoria(categoria), _preco(preco), _unidade(unidade), _quantidade(quantidade) {
    // ...
}

std::string Produto::getNome() const {
    return _nome;
}

std::string Produto::getCodigo() const {
    return _codigo;
}

std::string Produto::getCategoria() const {
    return _categoria;
}

double Produto::getPreco() const {
    return _preco;
}

std::string Produto::getUnidade() const {
    return _unidade;
}

int Produto::getQuantidade() const {
    return _quantidade;
}

// Função responsável por cadastrar um produto no arquivo
void cadastrarProduto(const std::string& nomeArquivo) {
    std::fstream arquivo(nomeArquivo, std::ios::app);
    // Abre o arquivo em modo de append

    arquivo << "Codigo" << "  " << "Nome" << "  " << "Categoria" << "  " << "Preco" << "  " << "Unidade"
        << "  " << "Quantidade"
        << std::endl;
    arquivo << "----------------------------------" << std::endl;
    // Escreve os cabeçalhos das colunas no arquivo

    if (!arquivo.is_open()) {
        // Se não foi possível abrir o arquivo, exibe uma mensagem de erro e retorna
        std::cout << "Erro ao abrir o arquivo." << std::endl;
        return;
    }

    std::vector<Produto> produtos;
    // Vetor para armazenar os produtos cadastrados
    char continuar;

    do {
        std::string nome, codigo, categoria, unidade;
        double preco;
        int quantidade;

        std::cout << "Codigo do produto: ";
        std::cin >> codigo;
        std::cin.ignore();

        std::cout << "Nome do produto: ";
        std::getline(std::cin, nome);

        std::cout << "Categoria do produto: ";
        std::getline(std::cin, categoria);

        std::cout << "Preco do produto: ";
        std::cin >> preco;

        std::cout << "Unidade (cx ou un): ";
        std::cin.ignore();
        std::getline(std::cin, unidade);

        std::cout << "Quantidade: ";
        std::cin >> quantidade;

        Verificador verificador(nomeArquivo);
        // Cria um objeto Verificador para verificar se o nome ou código já estão cadastrados

        while (verificador.verificar(nome) || verificador.verificar(codigo)) {
            // Enquanto o nome ou código já estiverem cadastrados, solicita um novo nome ou código
            if (verificador.verificar(codigo)) {
                std::cout << "Codigo ja cadastrado, escreva um novo codigo: ";
                std::cin >> codigo;
            } else if (verificador.verificar(nome)) {
                std::cout << "Nome ja cadastrado, escreva um novo nome.";
                std::cin >> nome;
            }
        }

        produtos.emplace_back(nome, codigo, categoria, preco, unidade, quantidade);
        // Adiciona o produto ao vetor de produtos cadastrados

        std::cout << "Deseja cadastrar outro produto? (S/N): " << std::endl;
        std::cin >> continuar;

    } while (continuar == 'S' || continuar == 's');
    // Repete o processo enquanto o usuário desejar cadastrar mais produtos

    for (const Produto& produto : produtos) {
        // Escreve as informações dos produtos cadastrados no arquivo
        arquivo << produto.getCodigo() << "   |" << produto.getNome() << "   |" << produto.getCategoria()
            << "   |" << "R$" << produto.getPreco() << "   |" << produto.getUnidade() << "   |" << produto.getQuantidade()
            << std::endl;
        arquivo << "----------------------------------" << std::endl;
    }

    arquivo.close();
    // Fecha o arquivo

    std::cout << "Cadastro de produtos concluído." << std::endl;
    // Exibe uma mensagem informando que o cadastro foi concluído
}


// Função responsável por remover um produto do arquivo
void removerProduto(const std::string& nomeArquivo, const std::string& nomeProduto) {
    std::ifstream arquivo(nomeArquivo);
    // Abre o arquivo em modo de leitura

    if (!arquivo.is_open()) {
        // Se não foi possível abrir o arquivo, exibe uma mensagem de erro e retorna
        std::cout << "Erro ao abrir o arquivo." << std::endl;
        return;
    }

    std::vector<std::string> linhas;
    // Vetor para armazenar as linhas do arquivo
    std::string linha;

    while (std::getline(arquivo, linha)) {
        // Lê cada linha do arquivo
        if (linha.find(nomeProduto) == std::string::npos) {
            // Se a linha não contém o nome do produto a ser removido, adiciona a linha ao vetor
            linhas.push_back(linha);
        }
    }

    arquivo.close();
    // Fecha o arquivo de leitura

    std::ofstream arquivoAtualizado(nomeArquivo);
    // Abre o arquivo em modo de escrita, sobrescrevendo seu conteúdo

    if (!arquivoAtualizado.is_open()) {
        // Se não foi possível abrir o arquivo, exibe uma mensagem de erro e retorna
        std::cout << "Erro ao abrir o arquivo." << std::endl;
        return;
    }

    for (const std::string& linhaAtualizada : linhas) {
        // Escreve as linhas atualizadas no arquivo
        arquivoAtualizado << linhaAtualizada << std::endl;
    }

    arquivoAtualizado.close();
    // Fecha o arquivo de escrita

    std::cout << "Produto removido com sucesso." << std::endl;
    // Exibe uma mensagem informando que o produto foi removido com sucesso
}


void venda(const std::string& palavraDesejada, const std::string& nomeArquivo, int numeroSubtrair) {
    std::ifstream arquivoIn(nomeArquivo); // Abrir o arquivo de entrada
    
    if (!arquivoIn.is_open()) {
        std::cout << "Erro ao abrir o arquivo de entrada." << std::endl;
        return;
    }
    
    std::ofstream arquivoOut("temp.txt"); // Abrir um arquivo temporario para escrever
    
    if (!arquivoOut.is_open()) {
        std::cout << "Erro ao abrir o arquivo temporario." << std::endl;
        return;
    }
    
    std::string linha;
    
    while (std::getline(arquivoIn, linha)) {
        std::istringstream iss(linha);
        std::string palavra;
        int ultimoNumero = 0;
        
        // Procura pela palavra desejada na linha
        size_t pos = linha.find(palavraDesejada);
        
        if (pos != std::string::npos) {
            // Le o ultimo numero da linha
            while (iss >> palavra) {
                std::istringstream issNumero(palavra);
                int numero;
                
                if (issNumero >> numero) {
                    ultimoNumero = numero;
                    std::cout << numero << std::endl;
                }
            }
            
            if (ultimoNumero >= numeroSubtrair){
            // Subtrai o numero fornecido do ultimo numero
            ultimoNumero -= numeroSubtrair;
            
            // Substitui o ultimo numero na linha
            std::string novoUltimoNumero = std::to_string(ultimoNumero);
            linha.replace(pos, palavraDesejada.length(), novoUltimoNumero);
            }else {
                std::cout << "Quantidade em estoque insuficiente." << std::endl;
                return;
            }
        }
        
        // Escreve a linha no arquivo temporario
        arquivoOut << linha << std::endl;
    }
    
    arquivoIn.close(); // Fechar o arquivo de entrada
    arquivoOut.close(); // Fechar o arquivo temporari
    
    // Substitui o arquivo original pelo arquivo temporario
    std::remove(nomeArquivo.c_str());
    std::rename("temp.txt", nomeArquivo.c_str());
    
    std::cout << "Venda de " << numeroSubtrair << " " << palavraDesejada << " realizada com sucesso" << std::endl;
}

void productRegister(const std::string& nomeArquivo) {
    while (true) {{
        std::cout << MARKER << std::endl;
        std::cout << "Selecione uma opcao:" << std::endl;
        std::cout << "1. Cadastrar produto" << std::endl;
        std::cout << "2. Verificar produto em estoque" << std::endl;
        std::cout << "3. Mostrar estoque" << std::endl;
        std::cout << "4. Remover produto" << std::endl;
        std::cout << "5. Vender produto" << std::endl;
        std::cout << "6. Voltar para pagina inicial" << std::endl;
        std::cout << MARKER << std::endl;

        int opcao;
        std::cin >> opcao;

        if (opcao == 1) {
            cadastrarProduto(nomeArquivo);
        } else if (opcao == 2) {
        std::cout << "Digite o codigo do produto a ser verificado: ";
        std::string nome;
        std::cin >> nome;

        Verificador verificador(nomeArquivo);
        std::string linha = verificador.linhaEncontrada(nome);

        if (linha != "Palavra não encontrada.") {
                std::cout << "Produto encontrado!" 
                        << std::endl;
                std::cout << "--------------------------------" 
                        << std::endl;
                std::cout << "Codigo" << "  " << "Nome" << "  " 
                        << "Categoria" << "  " << "Preco" 
                                                << std::endl;
                std::cout << linha 
                        << std::endl;
                std::cout << "--------------------------------" 
                        << std::endl;
                std::string proxLinha = verificador.proxLinha(nome);
                std::cout << "--------------------------------" 
                        << std::endl;

                if (proxLinha != "Linha nao encontrada.") {
                        std::cout << "Estoque: " << proxLinha << std::endl;
                } else {
                        std::cout << "Nao ha registro de estoque do produto informado." << std::endl;
                }
        }
            
        } else if (opcao == 3) {
            std::string linha;
            std::ifstream arquivo(nomeArquivo);
                while(std::getline(arquivo, linha)){
            std::cout << linha << std::endl;
        }     
        } else if (opcao == 4) {
            std::cout << "Digite o nome do produto a ser removido: ";
            std::string nomeProduto;
            std::cin.ignore();
            std::getline(std::cin, nomeProduto);
            removerProduto(nomeArquivo, nomeProduto);
        } else if (opcao == 5) {
            std::cout << "Digite a o produto a ser vendido: ";
            std::string nomeProduto;
            std::cin.ignore();
            std::getline(std::cin, nomeProduto);
            std::cout << std::endl;
            std::cout << "Digite a quantidade a ser vendida: ";
            int quantidade;
            std::cin >> quantidade;
            std::cout << std::endl;
            venda(nomeProduto, nomeArquivo, quantidade);
    
        }else if (opcao == 6) {
            break;
        } else {
            std::cout << "Opcao invalida. Tente novamente." << std::endl;
        }
    }
}}
