#include <stdio.h>
#include <stdlib.h>
#include <string.h>

typedef enum{MUITOFACIL, FACIL, MEDIO, DIFICIL, MUITODIFICIL}Nivel;


typedef struct {
    char questao[100];
    char alternativa[4][100];
    char correta;
    Nivel nivel;
}Pergunta;




void Questao(Pergunta dificuldade){
    printf("%s", dificuldade.questao);
    for (int i = 0; i < 4; i++){
        printf("%s", dificuldade.alternativa[i]);
        
    }
    
}

int main() {
    Pergunta muitoFacil[20];
    Pergunta facil[20];
    Pergunta medio[15];
    Pergunta dificil[15];
    Pergunta muitoDificil[10];

    
   
    return 0;
}
