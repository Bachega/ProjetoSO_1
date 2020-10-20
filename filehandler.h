#ifndef FILEHANDLER_H
#define FILEHANDLER_H

#define FCFS_OUTPUT "fcfs_output.txt"
#define RR_OUTPUT "roundrobin_output.txt"

#include <stdlib.h>
#include <stdio.h>

#include "queue.h"

/*
* Carrega do arquivo de saida os processos para a criacao da fila de processos prontos e nao criados;
* Entrada: nome do arquivo, filas q1 e q2 (fcfs e rr), filas t1 e t2 (fcfs e rr), quantum (rr);
* Retorno: vazio;
* Pre-condicao: arquivo de entrada deve existir;
* Pos-condicao: os processos prontos e nao criados sao carregados para as filas Q e T, respectivamente.
*/
void load(char* filename, Queue* q1, Queue* t1, Queue* q2, Queue* t2, int* quantum);

/*
* Cria o arquivo de saida vazio;
* Entrada: inteiro que determina qual arquivo sera criado (0 para fcfs e 1 para rr);
* Retorno: vazio;
* Pre-condicao: nenhuma;
* Pos-condicao: o arquivo de saida vazio eh criado.
*/
void createOutputFile(int alg);

/*
* Escreve no arquivo de saida o quantum para o algoritmo round robin;
* Entrada: quantum do algoritmo;
* Retorno: vazio;
* Pre-condicao: nenhuma;
* Pos-condicao: o quantum do algoritmo round robin eh escrito no arquivo de saida.
*/
void writeQuantumMessage(int quantum);

/*
* Escreve no arquivo de saida informacoes sobre a execucao do processo;
* Entrada: pid do processo, tempo de execucao restante em ms, inteiro que determina em qual arquivo sera escrito (0 para fcfs e 1 para rr);
* Retorno: vazio;
* Pre-condicao: nenhuma;
* Pos-condicao: informacoes da execucao de um processo sao escritas no arquivo de saida.
*/
void writeExecutionMessage(int pid, int execTime, int alg);

/*
* Escreve no arquivo de saida informacoes de encerramento do processo e seu tempo de resposta;
* Entrada: pid do processo, tempo de resposta em ms, inteiro que determina em qual arquivo sera escrito (0 para fcfs e 1 para rr);
* Retorno: vazio;
* Pre-condicao: nenhuma;
* Pos-condicao: informacoes de termino do processo sao escritas no arquivo de saida.
*/
void writeOneFinishedMessage(int pid, int responseTime, int alg);

/*
* Escreve no arquivo de saida que todos os processos terminaram, o tempo de resposta medio e o numero de trocas de contexto;
* Entrada: tempo medio de resposta, numero de trocas de contexto e inteiro que determina em qual arquivo sera escrito (0 para fcfs e 1 para rr);
* Retorno: vazio;
* Pre-condicao: nenhuma;
* Pos-condicao: a mensagem que todos os processos terminaram, o tempo de resposta medio e a quantidade de trocas de contexto sao escritos no arquivo de saida.
*/
void writeAllFinishedMessage(int averageResponseTime, int contextSwitch, int alg);

#endif // FILEHANDLER_H