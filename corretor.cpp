#include <iostream>
#include <fstream>
#include <string>
#include <filesystem>
#include <set>
#include <vector>

namespace fs = std::filesystem;

bool compareFiles(const std::string& file1, const std::string& file2) {
    std::ifstream inputFile1(file1);
    std::ifstream inputFile2(file2);

    if (!inputFile1.is_open() || !inputFile2.is_open()) {
        std::cerr << "Erro ao abrir os arquivos: " << file1 << " ou " << file2 << std::endl;
        return false;
    }

    // Lê todas as linhas do primeiro arquivo em um conjunto
    std::set<std::string> linesFile1;
    std::string line;
    while (std::getline(inputFile1, line)) {
        linesFile1.insert(line);
    }

    // Lê todas as linhas do segundo arquivo em um conjunto
    std::set<std::string> linesFile2;
    while (std::getline(inputFile2, line)) {
        linesFile2.insert(line);
    }

    // Fecha os arquivos
    inputFile1.close();
    inputFile2.close();

    // Compara os conjuntos
    return linesFile1 == linesFile2;
}

int main() {
    std::string outputFolder = "./output";
    std::string gabaritoFolder = "./gabarito";

    // Verifica se as pastas existem
    if (!fs::exists(outputFolder) || !fs::exists(gabaritoFolder)) {
        std::cerr << "Pastas 'output' ou 'gabarito' não existem!" << std::endl;
        return 1;
    }

    // Percorre todos os arquivos da pasta output
    for (const auto& outputFile : fs::directory_iterator(outputFolder)) {
        if (outputFile.is_regular_file() && outputFile.path().extension() == ".txt") {
            std::string fileName = outputFile.path().filename().string();
            std::string gabaritoFilePath = gabaritoFolder + "/" + fileName;

            if (!fs::exists(gabaritoFilePath)) {
                std::cout << "Arquivo " << fileName << " não encontrado na pasta 'gabarito'." << std::endl;
                continue;
            }

            // Compara os arquivos
            if (compareFiles(outputFile.path().string(), gabaritoFilePath)) {
                std::cout << "Os arquivos " << fileName << " são equivalentes." << std::endl;
            } else {
                std::cout << "Os arquivos " << fileName << " NÃO são equivalentes." << std::endl;
            }
        }
    }

    return 0;
}
