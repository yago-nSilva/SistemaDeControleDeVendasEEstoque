#ifndef VERIFICADOR_HPP
#define VERIFICADOR_HPP

#include <string>
#include <fstream>

class Verificador {
private: 
  std::ifstream _arquivo;
  std::string _nomeArquivo;
  void abrirArquivo();
  void fecharArquivo();

public: 
  Verificador(const std::string& arquivo);
  ~Verificador();

  bool verificar(const std::string& palavra);
  std::string linhaEncontrada(const std::string& palavra);
  std::string proxLinha(const std::string& palavra);
};

#endif
