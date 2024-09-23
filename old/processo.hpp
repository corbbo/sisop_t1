class Processo {
    private:
        int pid, surto, surto_restante, tempo_es, tempo_cpu, ordem, creditos, prioridade;
        char estado;
    public:
        Processo(int n, char e, int c, int s, int ts, int tcpu, int o, int p);
        int getPid();
        char getEstado();
        int getCreditos();
        int getSurto();
        int getTempoEs();
        int getTempoCpu();
        int getOrdem();
        void setEstado(char e);
        void setCreditos();
        void decSurto();
        void decCreditos();
        void resetSurtoRestante();
};      