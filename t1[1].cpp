#include <algorithm>
#include <iomanip>
#include <iostream>
#include <fstream>
#include <string>
#include <sstream>
#include <math.h>
#include <list>
#include <unordered_map>
#include <queue>

using namespace std;

class processo {
    public:
    string pid;
    char estado;
    int creditos;
    int surto;
    int tempoes;
    int tempocpu;
    int ordem;
    processo(string n, char e, int c, int s, int ts, int tcpu, int o, int p);
};

processo::processo(string pid, char e, int c, int s, int ts, int tcpu, int o, int p){
    pid = pid;
    estado = e;
    creditos = c;
    surto = s;
    tempoes = ts;
    tempocpu = tcpu;
    ordem = o;
}

int main () {
    unordered_map<int, priority_queue<processo>> processos; //mapa que armazena processos
    
    /*
    implementar algoritmo que aloca os processos dentro do mapa
    */
    
    unordered_map<int, priority_queue<processo>>::iterator it; //nao lembro como a gente acessa os objetos de um mapa, algum de vcs vai ter que arrumar

    //calcula tempo de execução (soma de tempo de cpu dos processos)
    int tempo = 0;
    for (it = processos.begin(); it != processos.end(); ++it){
        tempo = it->first->tempocpu;
    }

    //onde o escalonamento acontece
    for (int i = 0; i < tempo; i++) {
        /*
        implementar algoritmo de escolha de processo
        (escolher qual processo vai ser executado nessa medida de tempo)
        aqui vai ir algoritmo round robbin tbm eu acho
        enunciado diz que maior numero de creditos = maior prioridade
        inicialmente creditos = prioridade do processo
        */
        
        //confere se todos os processos tem creditos = 0
        int counter;
        for (it = processos.begin(); it != processos.end(); ++it) {
            if (it->first->creditos /= 0) {
                counter++;
            }
        }
        if (counter == 0) { //se creditos = 0, usa a formula do enunciado
                it->first->creditos = it->first->creditos/2+it->first->prioridade;
            }
        
        it = /*processo atual definido em cima*/;
        if (it->first->tempocpu == 0) { //se processo nao tem mais tempo de cpu, coloca ele no estado d (done)
            it->first->estado = 'd';
            //vai para o proximo processo
        } else if (it->first->surto == 0) { //se processo esgotou tempo de surto, manda pro estado b (block) e muda de processo 
            //ideia: alguns processos não tem surto, então podemos atribuir -1 ao invés de 0 pra esses
            it->first->estado = 'b';
            //vai para o proximo processo
        } else if (it->first->creditos == 0) { //se processo não tem creditos, muda de processo
            //vai para o proximo processo
        } else {
            it->first->creditos--; //decrementa creditos do processo atual
            it->first->tempocpu--; //decrementa tempo de cpu do processo atual
            it->first->surto--; //decrementa tempo de surto (basicamente, isso é um countdown até o surto acontecer se tiver; quando bate em zero, programa trava)
                                //unico problema é que nesse caso eu to decrementando diretamente do objeto mas esse valor tem que ser fixo
                                //e tem que decrementar uma variavel auxiliar
        }

        /*
        implementar algoritmo de impressão
        */
    }
}