#include "removerProduto.hpp"

bool removeProduct(std::vector<Product>&stock){
  std::string productName;
  std::cout << "Digite o nome do produto:" << std::endl;
  std::cin >> productName;
  std::cout << std::endl;
  for (auto&product : stock){
    if (productName == product.name){
      for (auto i = stock.begin(); i != stock.end(); ++i) { 
        if (i->name == productName) {
            stock.erase(i);
            break;
        }
      }
      std::cout << "Produto apagado com sucesso!" << std::endl;
      std::cout << std::endl;
      return true;
    } else {
      std::cout << "Nome de produto inválido." << std::endl;
      std::cout << std::endl;
      return false;
    }
  }
  
  return false;
}