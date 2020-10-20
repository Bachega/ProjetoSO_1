#include <stdlib.h>
#include <stdio.h>

#include "queue.h"
#include "pcb.h"
#include "fcfs.h"
#include "roundrobin.h"
#include "filehandler.h"

/*
* Cria filas de processos prontos e de processos nao criados para cada
* algoritmo (fcfs e rr), carrega os dados do arquivo de entrada e executa
* os algoritmos First Come First Served e Round Robin.
*/
int main(int argc, char * argv[]) {
    int quantum = -1;
    Queue* q1 = createQueue();
    Queue* t1 = createQueue();
    Queue* q2 = createQueue();
    Queue* t2 = createQueue();

    load(argv[1], q1, t1, q2, t2, &quantum);
    fcfs(q1, t1);
    printf("\n\n");
    roundRobin(q2, t2, quantum);
    return 0;
}