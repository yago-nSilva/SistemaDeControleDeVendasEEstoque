#include "produto.hpp"

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

// Função para cadastrar um produto no arquivo
void cadastrarProduto(const std::string& nomeArquivo) {
    // Abre o arquivo no modo de append (acrescentar ao final)
    std::fstream arquivo(nomeArquivo, std::ios::app);

    // Escreve a linha de cabeçalho no arquivo
    arquivo << "Codigo" << "  " << "Nome" << "  " << "Categoria" << "  " << "Preco" << "  " << "Unidade"
        << "  " << "Quantidade"
        << std::endl;
    arquivo << "----------------------------------" << std::endl;

    // Verifica se o arquivo foi aberto corretamente
    if (!arquivo.is_open()) {
        std::cout << "Erro ao abrir o arquivo." << std::endl;
        return;
    }

    // Vetor para armazenar os produtos
    std::vector<Produto> produtos;
    char continuar;

    // Loop para cadastrar produtos
    do {
        // Variáveis para armazenar os dados do produto
        std::string nome, codigo, categoria, unidade;
        double preco;
        int quantidade;

        // Solicita os dados do produto ao usuário
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

        // Verifica se o nome ou código do produto já estão cadastrados
        Verificador verificador(nomeArquivo);
        while (verificador.verificar(nome) || verificador.verificar(codigo)) {
            if (verificador.verificar(codigo)) {
                std::cout << "Codigo ja cadastrado, escreva um novo codigo: ";
                std::cin >> codigo;
            } else if (verificador.verificar(nome)) {
                std::cout << "Nome ja cadastrado, escreva um novo nome.";
                std::cin >> nome;
            }
        }

        // Cria um objeto Produto com os dados fornecidos
        produtos.emplace_back(nome, codigo, categoria, preco, unidade, quantidade);

        // Pergunta se deseja cadastrar outro produto
        std::cout << "Deseja cadastrar outro produto? (S/N): " << std::endl;
        std::cin >> continuar;

    } while (continuar == 'S' || continuar == 's');

    // Escreve os produtos no arquivo
    for (const Produto& produto : produtos) {
        arquivo << produto.getCodigo() << "   |" << produto.getNome() << "   |" << produto.getCategoria()
            << "   |" << "R$" << produto.getPreco() << "   |" << produto.getUnidade() << "   |" << produto.getQuantidade()
            << std::endl;
        arquivo << "----------------------------------" << std::endl;
    }

    // Fecha o arquivo
    arquivo.close();

    std::cout << "Cadastro de produtos concluído." << std::endl;
}

// Função para remover um produto do arquivo
void removerProduto(const std::string& nomeArquivo, const std::string& nomeProduto) {
    // Abre o arquivo para leitura
    std::ifstream arquivo(nomeArquivo);
    if (!arquivo.is_open()) {
        std::cout << "Erro ao abrir o arquivo." << std::endl;
        return;
    }

    // Vetor para armazenar as linhas do arquivo
    std::vector<std::string> linhas;
    std::string linha;

    // Lê cada linha do arquivo
    while (std::getline(arquivo, linha)) {
        // Verifica se a linha contém o nome do produto
        if (linha.find(nomeProduto) == std::string::npos) {
            // Se não contém, adiciona a linha ao arquivo
            linhas.push_back(linha);
        }
    }

    // Fecha o arquivo
    arquivo.close();

    // Abre o arquivo novamente para escrita
    std::ofstream arquivoAtualizado(nomeArquivo);
    if (!arquivoAtualizado.is_open()) {
        std::cout << "Erro ao abrir o arquivo." << std::endl;
        return;
    }

    // Escreve as linhas atualizadas no arquivo
    for (const std::string& linhaAtualizada : linhas) {
        arquivoAtualizado << linhaAtualizada << std::endl;
    }

    // Fecha o arquivo novamente
    arquivoAtualizado.close();

    std::cout << "Produto removido com sucesso." << std::endl;
}

// Função para registrar produtos
void productRegister(const std::string& nomeArquivo) {
    // Loop principal do registro de produtos
    while (true) {{
        std::cout << MARKER << std::endl;
        std::cout << "Selecione uma opcao:" << std::endl;
        std::cout << "1. Cadastrar produto" << std::endl;
        std::cout << "2. Verificar produto em estoque" << std::endl;
        std::cout << "3. Mostrar estoque" << std::endl;
        std::cout << "4. Remover produto" << std::endl;
        std::cout << "5. Voltar para pagina inicial" << std::endl;
        std::cout << MARKER << std::endl;

        // Variável para armazenar a opção selecionada
        int opcao;
        std::cin >> opcao;

        // Realiza a ação correspondente à opção selecionada
        if (opcao == 1) {
            cadastrarProduto(nomeArquivo);
        } else if (opcao == 2) {
            // Verifica o estoque de um produto
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
            break;
        } else {
            std::cout << "Opcao invalida. Tente novamente." << std::endl;
        }
    }
}}