#include "pcb.h"

/*
* Cira um ponteiro para um PCB padrao e retorna;
* Entrada: nenhuma;
* Retorno: ponteiro para um PCB padrao;
* Pre-condicao: nenhuma;
* Pos-condicao: um ponteiro para um PCB com valores padrao eh criado e retornado.
*/
PCB* createPCB() {
    PCB* pcb = (PCB*)malloc(sizeof(PCB));
    pcb->pid = -1;
    pcb->state = -1;
    pcb->execTime = 0;
    pcb->creationTime = -1;
    return pcb;
}

/*
* Executa o processo pelo tempo recebido como parametro e imprime no console informacoes de sua execucao;
* Entrada: pcb do processo a ser executado e o tempo que ira consumir;
* Retorno: tempo que o processo executou;
* Pre-condicao: pcb nao pode ser nulo;
* Pos-condicao: o sistema dorme (sleep) pelo tempo de execucao do processo (simulando sua execucao) e imprime no console informacoes de sua execucao.
*/
int executeProcess(PCB* pcb, int time) {
    pcb->state = EXECUTING;
    int consumedQuantum = 0;;

    printf("PID [%d] EXECUTING\tTime remaining: %d milliseconds [%.1f seconds]\n", pcb->pid, pcb->execTime, ((float)pcb->execTime)/1000);

    if(pcb->execTime > time) {
        consumedQuantum = time;
        Sleep(consumedQuantum);
        pcb->state = READY;
    } else {
        consumedQuantum = pcb->execTime;
        Sleep(consumedQuantum);
        pcb->state = TERMINATED;
    }
    pcb->execTime -= time;

    return consumedQuantum;
}