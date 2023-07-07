#ifndef PRODUTO_HPP
#define PRODUTO_HPP

#include <string>

class Produto {
private:
    std::string _nome;
    std::string _codigo;
    std::string _categoria;
    double _preco;
    std::string _unidade;
    int _quantidade;

public:
    Produto(const std::string& nome, const std::string& codigo, const std::string& categoria,
            double preco, const std::string& unidade, int quantidade);

    std::string getNome() const;
    std::string getCodigo() const;
    std::string getCategoria() const;
    double getPreco() const;
    std::string getUnidade() const;
    int getQuantidade() const;
};

void cadastrarProduto(const std::string& nomeArquivo);

#endif
