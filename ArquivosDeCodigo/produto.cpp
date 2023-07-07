Produto::Produto(const std::string& nome, const std::string& codigo, const std::string& categoria, double preco, const std::string& unidade, int quantidade) : _nome(nome), _codigo(codigo), _categoria(categoria), _preco(preco), _unidade(unidade), _quantidade(quantidade) {
      
    //   if (quantidade <= 0) {
    //     throw std::invalid_argument ("A quantidade do produto deve ser um número inteiro                                                   positivo");
    //   }
    //   if (unidade != "un" && unidade != "cx") {
    //     throw std::invalid_argument("A unidade do produto deve ser 'un' ou 'cx'.");
    //   }
    //   if (preco <= 0) {
    //     throw std::invalid_argument("O preco do produto deve ser um número positivo.");
    //   }
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

void cadastrarProduto(const std::string& nomeArquivo) {
    std::fstream arquivo(nomeArquivo, std::ios::app);
  
    arquivo << "Codigo" << "  " << "Nome" << "  " << "Categoria" << "  " << "Preco" << "  " << "Unidade" 
        << "  " << "Quantidade" 
            << std::endl;
    arquivo << "----------------------------------" << std::endl;

    if (!arquivo.is_open()) {
        std::cout << "Erro ao abrir o arquivo." << std::endl;
        return;
    }

    std::vector<Produto> produtos;
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
        while (verificador.verificar(nome) || verificador.verificar(codigo)){
          if (verificador.verificar(codigo)) {
            std::cout << "Codigo ja cadastrado, escreva um novo codigo: ";
            std::cin >> codigo;
          } else if (verificador.verificar(nome)) {
              std::cout << "Nome ja cadastrado, escreva um novo nome.";
              std::cin >> nome;
          } 
        }
      
        produtos.emplace_back(nome, codigo, categoria, preco, unidade, quantidade);
      
        std::cout << "Deseja cadastrar outro produto? (S/N): " << std::endl;
        std::cin >> continuar;

    } while (continuar == 'S' || continuar == 's');

    for (const Produto& produto : produtos) {
        arquivo << produto.getCodigo() << "   |" << produto.getNome() << "   |" << produto.getCategoria()
                << "   |" << "R$" << produto.getPreco() << "   |" << produto.getUnidade() << "   |" << produto.getQuantidade()
                    << std::endl;
        arquivo << "----------------------------------" << std::endl;
    }

    arquivo.close();

    std::cout << "Cadastro de produtos concluído." << std::endl;
}

void productRegister(const std::string& nomeArquivo){
    while (true) {
        std::cout << MARKER
                << std::endl;
        std::cout << "Selecione uma opcao:" 
                << std::endl;
        std::cout << "1. Cadastrar produto"
                    << std::endl;
        std::cout << "2. Verificar produto em estoque" 
                << std::endl;
        std::cout << "3. Mostrar estoque" 
                << std::endl;
        std::cout << "4. Voltar para pagina inicial" 
                << std::endl;
        std::cout << MARKER
                << std::endl;
        
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
        } else {
                std::cout << "Produto nao encontrado." << std::endl;
        }
        } else if (opcao == 3) {
                std::string linha;
                std::ifstream arquivo(nomeArquivo);
        while(std::getline(arquivo, linha)){
                std::cout << linha << std::endl;
        }
        } else if (opcao == 4) {
                break; 
        } else {
                std::cout << "Opcao invalida. Tente novamente." << std::endl;
        }
}
}
