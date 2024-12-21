#include "../include/grafo.hpp"
#include <queue>
#include <climits>
#include <algorithm>

// Função auxiliar para atualizar as capacidades no grafo residual
void atualizarCapacidades(Grafo* residual, int* antecessores, bool* reversed, int fluxoCaminho, int origemID, int destinoID) {
    for (int i = destinoID; i != origemID; i = antecessores[i]) {
        int j = antecessores[i];
        if (reversed[i]) {
            residual->setConexaoReversa(j, i, residual->getCapacidadeReversa(j, i) - fluxoCaminho);
            residual->setConexao(i, j, residual->getCapacidade(i, j) + fluxoCaminho);
        } else {
            residual->setConexao(j, i, residual->getCapacidade(j, i) - fluxoCaminho);
            residual->setConexaoReversa(i, j, residual->getCapacidadeReversa(i, j) + fluxoCaminho);
        }
    }
}

// Função auxiliar para calcular o fluxo do caminho encontrado
int calcularFluxoCaminho(Grafo* residual, int* antecessores, bool* reversed, int origemID, int destinoID) {
    int fluxoCaminho = INT_MAX;
    for (int i = destinoID; i != origemID; i = antecessores[i]) {
        int j = antecessores[i];
        if (reversed[i]) {
            fluxoCaminho = std::min(fluxoCaminho, residual->getCapacidadeReversa(j, i));
        } else {
            fluxoCaminho = std::min(fluxoCaminho, residual->getCapacidade(j, i));
        }
    }
    return fluxoCaminho;
}

// BFS para encontrar caminhos no grafo residual
bool BFS(Grafo* residual, int* antecessores, bool* reversed, int origemID, int destinoID) {
    std::vector<bool> visitados(TAMANHO, false);
    std::queue<int> fila;
    fila.push(origemID);

    while (!fila.empty()) {
        int atual = fila.front();
        fila.pop();
        visitados[atual] = true;

        for (int i = 0; i < TAMANHO; i++) {
            if (atual != i) {
                int capacidade = residual->getCapacidade(atual, i);
                if (capacidade > 0 && !visitados[i]) {
                    fila.push(i);
                    antecessores[i] = atual;
                    reversed[i] = false;
                    if (i == destinoID) return true;
                } else {
                    capacidade = residual->getCapacidadeReversa(atual, i);
                    if (capacidade > 0 && !visitados[i]) {
                        fila.push(i);
                        antecessores[i] = atual;
                        reversed[i] = true;
                        if (i == destinoID) return true;
                    }
                }
            }
        }
    }
    return false;
}

// Algoritmo principal de Ford-Fulkerson
int fordFulkerson(Grafo* grafoResidual, Ponto origem, Ponto destino) {
    int fluxoMax = 0;
    int antecessores[TAMANHO];
    bool reversed[TAMANHO];

    while (true) {
        std::fill(antecessores, antecessores + TAMANHO, -1);
        std::fill(reversed, reversed + TAMANHO, false);

        if (!BFS(grafoResidual, antecessores, reversed, origem.getIdentificador(), destino.getIdentificador())) {
            break; // Não há mais caminhos aumentantes
        }

        // Calcula o fluxo mínimo no caminho encontrado
        int fluxoCaminho = calcularFluxoCaminho(grafoResidual, antecessores, reversed, origem.getIdentificador(), destino.getIdentificador());

        // Atualiza as capacidades no grafo residual
        atualizarCapacidades(grafoResidual, antecessores, reversed, fluxoCaminho, origem.getIdentificador(), destino.getIdentificador());

        fluxoMax += fluxoCaminho;
    }

    return fluxoMax;
}
