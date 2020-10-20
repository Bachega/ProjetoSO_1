#ifndef FCFS_H
#define FCFS_H

#include "queue.h"
#include "filehandler.h"

/*
* Executa o algoritmo First Come First Served para as filas de processos prontos e nao criados, imprime as informacoes de sua execucao no console e no arquivo de saida;
* Entrada: Fila Q de processos prontos e Fila T de processos nao criados;
* Retorno: vazio;
* Pre-condicao: nenhuma;
* Pos-condicao: o resultado da execucao eh impresso no console e no arquivo de saida.
*/
void fcfs(Queue* q, Queue* t);

#endif // FCFS_H