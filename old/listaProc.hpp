#include "processo.hpp"
#include <queue>
#include <vector>

struct Comp {
    bool operator()(const Processo& p1, const Processo& p2) {
        return p1.getOrdem() < p2.getOrdem();
    }
};

class ListaProc {
    private:
        std::priority_queue<Processo, std::vector<Processo>, Comp> processos;
        int prioridade;
    public:
        ListaProc(int p);
        void insereProc(Processo p);
        void roundRobin(); //algoritmo de escalonamento
        Processo getProc(); //retorna o processo com maior prioridade
};