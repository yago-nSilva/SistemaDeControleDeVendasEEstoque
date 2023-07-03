#include<iostream>
#include<vector>

#ifndef VENDAS_HPP
#define VENDAS_HPP

struct Product {
  std::string name;
  std::string category;
  int quantity;
  int code;
  float price;
};

bool sellProduct(std::vector<Product>&stock);

#endif