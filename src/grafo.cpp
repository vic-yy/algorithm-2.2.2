#include "../include/grafo.hpp"
#include <iostream>

Grafo::Grafo(){
    capacidades = new int*[TAMANHO];
    for(int i = 0; i < TAMANHO; i++){
        capacidades[i] = new int[TAMANHO];
        for(int j = 0; j < TAMANHO; j++){
            capacidades[i][j] = -1;
        }
    }

    fluxos = new int*[TAMANHO];
    for(int i = 0; i < TAMANHO; i++){
        fluxos[i] = new int[TAMANHO];
        for(int j = 0; j < TAMANHO; j++){
            fluxos[i][j] = 0;
        }
    }

    this->origemGlobal.setIdentificador(0);
    this->origemGlobal.setTipo('g');
    this->origemGlobal.setDemanda(0);
    this->destinoGlobal.setIdentificador(TAMANHO - 1);
    this->destinoGlobal.setTipo('c');
    this->destinoGlobal.setDemanda(2000);

    capacidades[0][TAMANHO - 1] = -1;
    capacidades[TAMANHO - 1][0] = -1;
    fluxos[0][TAMANHO - 1] = 0;
    fluxos[TAMANHO - 1][0] = 0;

    for(int i = 1; i < TAMANHO - 1; i++){
        ativos[i] = 0;
    }

    ativos[0] = 1;
    ativos[TAMANHO - 1] = 1;

}

Grafo::~Grafo(){
    for(int i = 0; i < TAMANHO; i++){
        delete[] capacidades[i];
    }
    delete[] capacidades;
    for(int i = 0; i < TAMANHO; i++){
        delete[] fluxos[i];
    }
    delete[] fluxos;
}

void Grafo::setConexao(int origem, int destino, int capacidade){
    bool primeira = false;
    if(capacidades[origem][destino] == -1){
        primeira = true;
    }
    capacidades[origem][destino] = capacidade;
    if(capacidades[0][origem] != -1 && origem != 0 && primeira){
        this->geracaoTotal += capacidade;
    }
    return;
}

void Grafo::setConexaoReversa(int origem, int destino, int capacidade){
    fluxos[origem][destino] = capacidade;
    return;
}

void Grafo::addPonto(Ponto ponto){
    if(ponto.getTipo() == 'g'){
        setConexao(origemGlobal.getIdentificador(), ponto.getIdentificador(), 20000);
        ativos[ponto.getIdentificador()] = 1;
        return;
    }
    else if(ponto.getTipo() == 'c'){
        setConexao(ponto.getIdentificador(), destinoGlobal.getIdentificador(), ponto.getDemanda());
        ativos[ponto.getIdentificador()] = 1;
        return;
    }

    return;
}

void Grafo::print(){
    for(int i = 0; i < TAMANHO; i++){
        for(int j = 0; j < TAMANHO; j++){
            if(capacidades[i][j] > -1 && i != j && ativos[i] == 1 && ativos[j] == 1){
                std::cout << "Conexao de " << i << " para " << j << " de capacidade " << capacidades[i][j] << std::endl;
            }
            if(capacidades[i][j] == -1){
                continue;
            }
        }
    }
    return;
}

void Grafo::printMatriz(){
    for(int i = 0; i < TAMANHO; i++){
        for(int j = 0; j < TAMANHO; j++){
            std::cout << capacidades[i][j] << " ";
        }
        std::cout << std::endl;
    }
    return;
}

void Grafo::criarGrafoResidual(Grafo* grafo,Grafo* grafoResidual){
    for(int i = 0; i < TAMANHO; i++){
       for(int j = 0; j < TAMANHO; j++){
            if(grafo->capacidades[i][j] > (-1)){

                ativos[i] = 1;
                ativos[j] = 1;

                int capacidade = grafo->capacidades[i][j];
                
                grafoResidual->setConexao(i, j, capacidade);
            }
        }
    }
}

int Grafo::getCapacidade(int origem, int destino){
    return capacidades[origem][destino];
}

int Grafo::getCapacidadeReversa(int origem, int destino){
    return fluxos[origem][destino];
}

Ponto Grafo::getDestino(){
    return destinoGlobal;
}

Ponto Grafo::getOrigem(){
    return origemGlobal;
}

bool Grafo::getAtivo(int i){
    return ativos[i];
}

std::vector<std::pair<int, int>> Grafo::getSaturadas() {
    std::vector<std::pair<int, int>> saturadas;
    for(int i = 1; i < TAMANHO-1; i++){
        for(int j = TAMANHO - 2; j >= 1; j--){
            if(capacidades[i][j] == 0) {
                saturadas.push_back({i, j});
            }
        }
    }
    return saturadas;
}

Ponto Grafo::getPonto(int i){
    return vertices[i];
}

int Grafo::getGeracaoTotal(){
    return this->geracaoTotal;
}