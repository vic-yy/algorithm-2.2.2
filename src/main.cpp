#include <cstdio>
#include <iostream>
#include "../include/algoritmo.hpp"

int main(){
    int numPontos;
    int numFios;

    Grafo redeEletrica; 
    Grafo grafoResidual;

    int** capacidades;
    capacidades = new int*[TAMANHO];
    for(int i = 0; i < TAMANHO; i++){
        capacidades[i] = new int[TAMANHO];
        for(int j = 0; j < TAMANHO; j++){
            capacidades[i][j] = -1;
        }
    }

    scanf("%d %d", &numPontos, &numFios);

    int demanda_total = 0;
    for(int i = 0; i < numPontos; i++){
        int identificador;
        char tipo;
        int demanda;

        scanf("%d %d", &identificador, &demanda);
        demanda_total += demanda;
        if(demanda == 0){
            tipo = 'g';
        }
        else{
            tipo = 'c';
        }
        Ponto ponto(identificador, tipo, demanda);

        redeEletrica.addPonto(ponto);
        grafoResidual.addPonto(ponto);
    }

    for(int i = 0; i < numFios; i++){
        int origem;
        int destino;
        int capacidade;

        scanf("%d %d %d", &origem, &destino, &capacidade);

        redeEletrica.setConexao(origem, destino, capacidade);
        grafoResidual.setConexao(origem, destino, capacidade);
        capacidades[origem][destino] = capacidade;
    }
    
    int fluxoMax = fordFulkerson(&grafoResidual, redeEletrica.getOrigem(), redeEletrica.getDestino());

    std::cout << fluxoMax << std::endl;

    std::cout << (demanda_total - fluxoMax) << std::endl;

    std::cout << (grafoResidual.getGeracaoTotal() - fluxoMax) << std::endl;

    std::vector<std::pair<int, int>> saturadas = grafoResidual.getSaturadas();
    std::cout << saturadas.size() << std::endl;

    while (!saturadas.empty()) {
        int capacidadeMaior = 0;
        int imaior = -1;
        int jmaior = -1;
        size_t indiceMaior = 0;

        //encontrar a aresta com maior capacidade
        for (size_t indice = 0; indice < saturadas.size(); ++indice) {
            int i = saturadas[indice].first;
            int j = saturadas[indice].second;
            if (capacidades[i][j] > capacidadeMaior) {
                capacidadeMaior = capacidades[i][j];
                imaior = i;
                jmaior = j;
                indiceMaior = indice;
            }
        }

        if (imaior != -1 && jmaior != -1) {
            std::cout << imaior << " " << jmaior << " " << capacidadeMaior << std::endl;
        }

        // remover o elemento já printado
        for (size_t indice = indiceMaior; indice < saturadas.size() - 1; ++indice) {
            saturadas[indice] = saturadas[indice + 1];
        }
        saturadas.pop_back();
    }


    //limpar a memória
    for(int i = 0; i < TAMANHO; i++){
        delete[] capacidades[i];
    }
    delete[] capacidades;

    return 0;
}