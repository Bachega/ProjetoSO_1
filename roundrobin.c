#include "roundrobin.h"

/*
* Executa o algoritmo Round Robin para as filas de processos prontos e nao criados, imprime as informacoes de sua execucao no console e no arquivo de saida;
* Entrada: Fila Q de processos prontos, Fila T de processos nao criados e quantum para o algoritmo;
* Retorno: vazio;
* Pre-condicao: nenhuma;
* Pos-condicao: o resultado da execucao eh impresso no console e no arquivo de saida.
*/
void roundRobin(Queue* q, Queue* t, int quantum) {
    PCB* pcb;
    int responseTime = 0;
    int averageResponseTime = 0;
    int contextSwitch = 0;
    int num = q->lenght;

    createOutputFile(1);

    printf("\nROUND ROBIN\n\n");
    while(q->lenght) {
        contextSwitch++;
        pcb = q->head->pcb;
        
        writeExecutionMessage(pcb->pid, pcb->execTime, 1);
        responseTime += executeProcess(pcb, quantum);

        if(q->lenght > 1)
            sendFirstToEnd(q);
            
        if((t->creationTime > 0) && (responseTime >= t->creationTime)) {
            sendPendingToReady(q, t);
            num++;
        }
        
        if(pcb->state == TERMINATED) {
            averageResponseTime += responseTime;
            writeOneFinishedMessage(pcb->pid, responseTime, 1);
            printf("PID [%d] FINISHED\tResponse time: %d milliseconds [%.1f seconds]\n", pcb->pid, responseTime, ((float)responseTime)/1000);
            removeElement(q, pcb->pid);
        }
    }

    averageResponseTime /= num;
    writeQuantumMessage(quantum);
    writeAllFinishedMessage(averageResponseTime, contextSwitch, 1);
    printf("\nQuantum: %d milliseconds", quantum);
    printf("\nAll processes finished\nAverage response time: %d milliseconds [%.1f seconds]\nNumber of context switches: %d", averageResponseTime, ((float)averageResponseTime)/1000, contextSwitch);
}