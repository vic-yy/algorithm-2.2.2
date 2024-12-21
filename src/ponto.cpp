#include "../include/ponto.hpp" 

Ponto::Ponto(){
    identificador = -1;
    tipo = ' ';
    demanda = -1;
}

Ponto::Ponto(int identificador, char tipo, int demanda){
    this->identificador = identificador;
    this->tipo = tipo;
    this->demanda = demanda;
}

void Ponto::setIdentificador(int identificador){
    this->identificador = identificador;
}

int Ponto::getIdentificador(){
    return identificador;
}

void Ponto::setTipo(char tipo){
    this->tipo = tipo;
}

char Ponto::getTipo(){
    return tipo;
}

void Ponto::setDemanda(int demanda){
    this->demanda = demanda;
}

int Ponto::getDemanda(){
    return demanda;
}