#include "loja.h"
using namespace std;

Loja::Loja(std::string nome, Morada morada) {
  this->nome = nome;
  this->morada = morada;
}

string Loja::getNome() const {
  return nome;
}

Morada Loja::getMorada() const {
  return morada;
}

void Loja::setNome(std::string nome) {
  this->nome = nome;
}

void Loja::setMorada(Morada morada) {
  this->morada = morada;
}

