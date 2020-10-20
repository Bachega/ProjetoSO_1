#include "filehandler.h"

/*
* Carrega do arquivo de saida os processos para a criacao da fila de processos prontos e nao criados;
* Entrada: nome do arquivo, filas q1 e q2 (fcfs e rr), filas t1 e t2 (fcfs e rr), quantum (rr);
* Retorno: vazio;
* Pre-condicao: arquivo de entrada deve existir;
* Pos-condicao: os processos prontos e nao criados sao carregados para as filas Q e T, respectivamente.
*/
void load(char* filename, Queue* q1, Queue* t1, Queue* q2, Queue* t2, int* quantum) {
    int i, num, pid, execTime, creationTime, state;
    PCB* pcb1;
    PCB* pcb2;

    FILE* file = fopen(filename, "r");

    if(file == NULL) {
        printf("ERROR: couldnt load from input file\n");
        return;
    }

    fscanf(file, "%d", &num); fgetc(file);
    fscanf(file, "%d", quantum); fgetc(file);
    
    for(i = 0; i < num; i++) {
        pcb1 = createPCB();
        pcb2 = createPCB();

        fscanf(file, "%d", &pid); fgetc(file);
        fscanf(file, "%d", &execTime); fgetc(file);
        fscanf(file, "%d", &creationTime); fgetc(file);

        pcb1->pid = pcb2->pid = pid;
        pcb1->execTime = pcb2->execTime = execTime;
        pcb1->creationTime = pcb2->creationTime = creationTime;

        if (creationTime == 0) {
            pcb1->state = pcb2->state = 0;
            insert(q1, pcb1);
            insert(q2, pcb2);
        } else {
            insertPendingQueue(t1, pcb1);
            insertPendingQueue(t2, pcb2);
        }
    }
    
    fclose(file);

}

/*
* Cria o arquivo de saida vazio;
* Entrada: inteiro que determina qual arquivo sera criado (0 para fcfs e 1 para rr);
* Retorno: vazio;
* Pre-condicao: nenhuma;
* Pos-condicao: o arquivo de saida vazio eh criado.
*/
void createOutputFile(int alg) {
    FILE* file;

    if(alg == 0)
        file = fopen(FCFS_OUTPUT, "w");
    else
        file = fopen(RR_OUTPUT, "w");

    if(file == NULL) {
        printf("ERROR: couldnt create output file\n");
        return;
    }

    fseek(file, 0, SEEK_SET);
    fclose(file);
}

/*
* Escreve no arquivo de saida o quantum para o algoritmo round robin;
* Entrada: quantum do algoritmo;
* Retorno: vazio;
* Pre-condicao: nenhuma;
* Pos-condicao: o quantum do algoritmo round robin eh escrito no arquivo de saida.
*/
void writeQuantumMessage(int quantum) {
    FILE* file;

    file = fopen(RR_OUTPUT, "a");

    if(file == NULL) {
        printf("ERROR: couldnt write to output file\n");
        return;
    }

    fprintf(file, "\nQuantum: %d milliseconds", quantum);

    fclose(file);
}

/*
* Escreve no arquivo de saida informacoes sobre a execucao do processo;
* Entrada: pid do processo, tempo de execucao restante em ms, inteiro que determina em qual arquivo sera escrito (0 para fcfs e 1 para rr);
* Retorno: vazio;
* Pre-condicao: nenhuma;
* Pos-condicao: informacoes da execucao de um processo sao escritas no arquivo de saida.
*/
void writeExecutionMessage(int pid, int execTime, int alg) {
    FILE* file;

    if(alg == 0)
        file = fopen(FCFS_OUTPUT, "a");
    else
        file = fopen(RR_OUTPUT, "a");

    if(file == NULL) {
        printf("ERROR: couldnt write to output file\n");
        return;
    }

    fprintf(file, "PID [%d] EXECUTING\tTime remaining: %d milliseconds [%.1f seconds]\n", pid, execTime, ((float)execTime)/1000);

    fclose(file);

}

/*
* Escreve no arquivo de saida informacoes de encerramento do processo e seu tempo de resposta;
* Entrada: pid do processo, tempo de resposta em ms, inteiro que determina em qual arquivo sera escrito (0 para fcfs e 1 para rr);
* Retorno: vazio;
* Pre-condicao: nenhuma;
* Pos-condicao: informacoes de termino do processo sao escritas no arquivo de saida.
*/
void writeOneFinishedMessage(int pid, int responseTime, int alg) {
    FILE* file;

    if(alg == 0)
        file = fopen(FCFS_OUTPUT, "a");
    else
        file = fopen(RR_OUTPUT, "a");

    if(file == NULL) {
        printf("ERROR: couldnt write to output file\n");
        return;
    }

    fprintf(file, "PID [%d] FINISHED\tResponse time: %d milliseconds [%.1f seconds]\n", pid, responseTime, ((float)responseTime)/1000);

    fclose(file);
}

/*
* Escreve no arquivo de saida que todos os processos terminaram, o tempo de resposta medio e o numero de trocas de contexto;
* Entrada: tempo medio de resposta, numero de trocas de contexto e inteiro que determina em qual arquivo sera escrito (0 para fcfs e 1 para rr);
* Retorno: vazio;
* Pre-condicao: nenhuma;
* Pos-condicao: a mensagem que todos os processos terminaram, o tempo de resposta medio e a quantidade de trocas de contexto sao escritos no arquivo de saida.
*/
void writeAllFinishedMessage(int averageResponseTime, int contextSwitch, int alg) {
    FILE* file;

    if(alg == 0)
        file = fopen(FCFS_OUTPUT, "a");
    else
        file = fopen(RR_OUTPUT, "a");

    if(file == NULL) {
        printf("ERROR: couldnt write to output file\n");
        return;
    }
    
    fprintf(file, "\nAll processes finished\nAverage response time: %d milliseconds [%.1f seconds]\nNumber of context switches: %d", averageResponseTime, ((float)averageResponseTime)/1000, contextSwitch);

    fclose(file);
}