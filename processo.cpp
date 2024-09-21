#include "processo.hpp"

Processo::Processo(int n, char e, int c, int s, int ts, int tcpu, int o, int p){
    pid = n;
    estado = e;
    creditos = c;
    surto = s;
    surto_restante = s;
    tempo_es = ts;
    tempo_cpu = tcpu;
    ordem = o;
    prioridade = p;
}

int Processo::getPid()      {return pid;}
char Processo::getEstado()  {return estado;}
int Processo::getCreditos() {return creditos;}
int Processo::getSurto()    {return surto;}
int Processo::getTempoEs()  {return tempo_es;}
int Processo::getTempoCpu() {return tempo_cpu;}
int Processo::getOrdem()    {return ordem;}

void Processo::setEstado(char e) {estado = e;}
void Processo::decSurto() {surto_restante--;}
void Processo::decCreditos() {creditos--;}
void Processo::resetSurtoRestante() {surto_restante = surto;}

void Processo::setCreditos() {
    creditos = creditos/2 + prioridade;
}
