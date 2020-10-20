#ifndef ROUNDROBIN_H
#define ROUNDROBIN_H

#include "queue.h"
#include "filehandler.h"

/*
* Executa o algoritmo Round Robin para as filas de processos prontos e nao criados, imprime as informacoes de sua execucao no console e no arquivo de saida;
* Entrada: Fila Q de processos prontos, Fila T de processos nao criados e quantum para o algoritmo;
* Retorno: vazio;
* Pre-condicao: nenhuma;
* Pos-condicao: o resultado da execucao eh impresso no console e no arquivo de saida.
*/
void roundRobin(Queue* q, Queue* t, int quantum);

#endif // ROUNDROBIN_H