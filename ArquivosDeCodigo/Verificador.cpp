#include "Verificador.hpp"
#include <iostream>

Verificador::Verificador(const std::string& arquivo) : _nomeArquivo(arquivo) {
  abrirArquivo();
}

Verificador::~Verificador() {
  fecharArquivo();
}

bool Verificador::verificar(const std::string& palavra){
  std::string linha; 
  bool encontrada = false;

  while(std::getline(_arquivo, linha)){
    size_t pos = linha.find(palavra);
    if (pos != std::string::npos) {
      encontrada = true;
      break;
    }
  }
  _arquivo.clear();
  _arquivo.seekg(0);
  return encontrada;
}

std::string Verificador::linhaEncontrada(const std::string& palavra) {
  std::string linha; 
  bool encontrada = false;

  while(std::getline(_arquivo, linha)){
    size_t pos = linha.find(palavra);
    if (pos != std::string::npos) {
      encontrada = true;
      break;
    }
  }
  
  _arquivo.clear();
  _arquivo.seekg(0);
  
  if (encontrada) {
    return linha;
  } else {
    return "Palavra não encontrada.";
  }
}

std::string Verificador::proxLinha(const std::string& palavra) {
  std::string linha;
  bool encontrada = false;
  bool proxLinha = false;

  while(std::getline(_arquivo, linha)){
    size_t pos = linha.find(palavra);
    if (pos != std::string::npos) {
      encontrada = true;
      proxLinha = true;
      break;
    }
  }
  
  while(std::getline(_arquivo, linha)){
    if(encontrada && proxLinha) {
      break;
    }
  }

  _arquivo.clear();
  _arquivo.seekg(0);
  
  if(encontrada && proxLinha) {
    return linha; 
  } else {
    return "Linha não encontrada.";
  }
}
  
void Verificador::abrirArquivo() {
  _arquivo.open(_nomeArquivo);
  if(!_arquivo.is_open()) {
    std::cout << "Erro ao abrir o arquivo." << std::endl;
  }
}

void Verificador::fecharArquivo() {
  if(_arquivo.is_open()) {
    _arquivo.close();
  }
}
