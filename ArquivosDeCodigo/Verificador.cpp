// Construtor da classe Verificador
Verificador::Verificador(const std::string& arquivo) : _nomeArquivo(arquivo) {
  abrirArquivo();
  // Abre o arquivo para leitura
}

// Destrutor da classe Verificador
Verificador::~Verificador() {
  fecharArquivo();
  // Fecha o arquivo
}

// Verifica se uma palavra existe no arquivo
bool Verificador::verificar(const std::string& palavra){
  std::string linha; 
  bool encontrada = false;

  while(std::getline(_arquivo, linha)){
    // Lê cada linha do arquivo
    size_t pos = linha.find(palavra);
    // Procura a posição da palavra na linha
    if (pos != std::string::npos) {
      // Se encontrou a palavra, marca como encontrada e interrompe o loop
      encontrada = true;
      break;
    }
  }

  _arquivo.clear();
  _arquivo.seekg(0);
  // Retorna ao início do arquivo

  return encontrada;
  // Retorna se a palavra foi encontrada ou não
}

// Retorna a linha onde a palavra foi encontrada
std::string Verificador::linhaEncontrada(const std::string& palavra) {
  std::string linha; 
  bool encontrada = false;

  while(std::getline(_arquivo, linha)){
    // Lê cada linha do arquivo
    size_t pos = linha.find(palavra);
    // Procura a posição da palavra na linha
    if (pos != std::string::npos) {
      // Se encontrou a palavra, marca como encontrada e interrompe o loop
      encontrada = true;
      break;
    }
  }
  
  _arquivo.clear();
  _arquivo.seekg(0);
  // Retorna ao início do arquivo

  if (encontrada) {
    // Se a palavra foi encontrada, retorna a linha
    return linha;
  } else {
    // Se a palavra não foi encontrada, retorna uma mensagem de erro
    return "Palavra nao encontrada.";
  }
}

// Retorna a próxima linha após a linha onde a palavra foi encontrada
std::string Verificador::proxLinha(const std::string& palavra) {
  std::string linha;
  bool encontrada = false;
  bool proxLinha = false;

  while(std::getline(_arquivo, linha)){
    // Lê cada linha do arquivo
    size_t pos = linha.find(palavra);
    // Procura a posição da palavra na linha
    if (pos != std::string::npos) {
      // Se encontrou a palavra, marca como encontrada e marca para pegar a próxima linha
      encontrada = true;
      proxLinha = true;
      break;
    }
  }
  
  while(std::getline(_arquivo, linha)){
    // Lê cada linha do arquivo após a linha encontrada
    if(encontrada && proxLinha) {
      // Se já encontrou a linha e está na próxima linha, interrompe o loop
      break;
    }
  }

  _arquivo.clear();
  _arquivo.seekg(0);
  // Retorna ao início do arquivo

  if(encontrada && proxLinha) {
    // Se a linha foi encontrada e a próxima linha foi encontrada, retorna a próxima linha
    return linha; 
  } else {
    // Se a linha não foi encontrada ou a próxima linha não foi encontrada, retorna uma mensagem de erro
    return "Linha nao encontrada.";
  }
}

// Abre o arquivo para leitura
void Verificador::abrirArquivo() {
  _arquivo.open(_nomeArquivo);
  if(!_arquivo.is_open()) {
    // Se não foi possível abrir o arquivo, exibe uma mensagem de erro
    std::cout << "Erro ao abrir o arquivo." << std::endl;
  }
}

// Fecha o arquivo
void Verificador::fecharArquivo() {
  if(_arquivo.is_open()) {
    // Se o arquivo estiver aberto, fecha o arquivo
    _arquivo.close();
  }
}

