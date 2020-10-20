#ifndef PCB_H
#define PCB_H

#include <Windows.h>
#include <stdlib.h>
#include <stdio.h>

// Constantes que ditam o estado do processo
#define READY 0
#define EXECUTING 1
#define TERMINATED 2

// Estrutura para PCB 
typedef struct pcb {
    int pid;
    int state;
    int execTime;
    int creationTime;
}PCB;

/*
* Cira um ponteiro para um PCB padrao e retorna;
* Entrada: nenhuma;
* Retorno: ponteiro para um PCB padrao;
* Pre-condicao: nenhuma;
* Pos-condicao: um ponteiro para um PCB com valores padrao eh criado e retornado.
*/
PCB* createPCB();

/*
* Executa o processo pelo tempo recebido como parametro e imprime no console informacoes de sua execucao;
* Entrada: pcb do processo a ser executado e o tempo que ira consumir;
* Retorno: tempo que o processo executou;
* Pre-condicao: pcb nao pode ser nulo;
* Pos-condicao: o sistema dorme (sleep) pelo tempo de execucao do processo (simulando sua execucao) e imprime no console informacoes de sua execucao.
*/
int executeProcess(PCB* pcb, int time);

#endif // PCB_H