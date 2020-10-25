#ifndef LOJA_H
#define LOJA_H

#include <iostream>

struct Morada{
  std::string rua;
  std::string localidade;
};

class Loja {
private:
  std::string nome;
  Morada morada;
public:
  Loja(std::string nome, Morada morada);
  std::string getNome() const;
  Morada getMorada() const;
  void setNome(std::string nome);
  void setMorada(Morada morada);
};


#endif //LOJA_H
