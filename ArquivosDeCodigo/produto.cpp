#include "produto.hpp"
#include "Verificador.hpp"
#include <fstream>
#include <iostream>
#include <vector>

Produto::Produto(const std::string& nome, const std::string& codigo, const std::string& categoria, double preco, const std::string& unidade, int quantidade) : _nome(nome), _codigo(codigo), _categoria(categoria), _preco(preco), _unidade(unidade), _quantidade(quantidade) {
      
      if (quantidade <= 0) {
        throw std::invalid_argument ("A quantidade do produto deve ser um número inteiro positivo");
      }
      if (unidade != "un" && unidade != "cx") {
        throw std::invalid_argument("A unidade do produto deve ser 'un' ou 'cx'.");
      }
      if (preco <= 0) {
        throw std::invalid_argument("O preço do produto deve ser um número positivo.");
      }
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
  
    arquivo << "Código" << "  " << "Nome" << "  " << "Categoria" << "  " << "Preço" << std::endl;
    arquivo << "================================" << std::endl;

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

        std::cout << "Código do produto: ";
        std::cin >> codigo;
        std::cin.ignore(); 

        std::cout << "Nome do produto: ";
        std::getline(std::cin, nome);

        std::cout << "Categoria do produto: ";
        std::getline(std::cin, categoria);

        std::cout << "Preço do produto: ";
        std::cin >> preco;

        std::cout << "Unidade (cx ou un): ";
        std::cin.ignore(); 
        std::getline(std::cin, unidade);
  
        std::cout << "Quantidade: ";
        std::cin >> quantidade;

        Verificador verificador(nomeArquivo);
        while (verificador.verificar(nome) || verificador.verificar(codigo)){
          if (verificador.verificar(codigo)) {
            std::cout << "Código já cadastrado, escreva um novo código: ";
            std::cin >> codigo;
          } else if (verificador.verificar(nome)) {
              std::cout << "Nome já cadastrado, escreva um novo nome.";
              std::cin >> nome;
          } 
        }
      
        produtos.emplace_back(nome, codigo, categoria, preco, unidade, quantidade);
      
        std::cout << "Deseja cadastrar outro produto? (S/N): " << std::endl;
        std::cin >> continuar;

    } while (continuar == 'S' || continuar == 's');

    for (const Produto& produto : produtos) {
        arquivo << produto.getCodigo() << "  " << produto.getNome() << "  " << produto.getCategoria()
                << "  " << "R$" << produto.getPreco() << std::endl;

        arquivo << produto.getUnidade() << "  " << produto.getQuantidade() << std::endl;
        arquivo << "================================" << std::endl;
    }

    arquivo.close();

    std::cout << "Cadastro de produtos concluído." << std::endl;
}
