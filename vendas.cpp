#include "vendas.hpp"

bool sellProduct(std::vector<Product>&stock){
  int quantity;
  std::string productName;
  std::cout << "Digite o nome do produto:" << std::endl;
  std::cin >> productName;
  std::cout << "Digite a quantidade:" << std::endl;
  std::cin >> quantity;

  
  if (quantity <= 0){
    std::cout << "Quantidade inválida" << std::endl;
    std::cout << std::endl;
    return false;
  }
  
  for (auto&product : stock){
    if (productName == product.name){
      if (product.quantity >= quantity){
        product.quantity -= quantity;
        std::cout << "Venda de " << quantity << " " << product.name << " realizada com sucesso!" << std::endl 
        << "Valor da venda: R$" << product.price * quantity << std::endl;
        std::cout << std::endl;
        return true;
      } else {
      std::cout << "Estoque insuficiente. Quantidade disponível:" << product.quantity << std::endl;
        std::cout << std::endl;
        return false;
      }
    }
  }
  std::cout<< "Produto não encontrado." << std::endl;
  std::cout << std::endl;
  return false;
}