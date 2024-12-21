#ifndef PONTO
#define PONTO

class Ponto{
    private:
        int identificador;
        char tipo; //g de gerador, c de consumidor
        int demanda;
        
    public:
        Ponto();
        Ponto(int identificador, char tipo, int demanda);
        int getIdentificador(); 
        char getTipo();
        void setTipo(char tipo);
        void setIdentificador(int identificador);
        void setDemanda(int demanda);
        int getDemanda();
};


#endif