#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <time.h>

typedef enum{MUITOFACIL, FACIL, MEDIO, DIFICIL, MUITODIFICIL}Nivel;

typedef enum{CHAPEU = 1, FEIJOEZINHOS, PROFESSORA}Dica;


typedef struct {
    char enunciado[100];
    char alternativaA[100];
    char alternativaB[100];
    char alternativaC[100];
    char alternativaD[100];
    char correta;
    Nivel nivel;
}Pergunta;

void chapeu(Pergunta alternativas){

}

void feijozinhos(Pergunta alternativas){
    srand(time(NULL)); // Inicializa a semente com base no tempo atual

    int minimo = 0;
    int maximo = 3;

    int numero = (rand() % (maximo - minimo + 1)) + minimo;

    if(numero == 0){
        printf("Esse feijão tinha sabor de vomito!(removeu nenhuma alternativa)\n");
    } else if(numero == 1){
        printf("Esse feijão tinha sabor de grama!(removeu 1 alternativa)\n");

    }else if(numero == 2){
        printf("Esse feijão tinha sabor de marshmallow!(removeu 2 alternativa)\n");

    }else if(numero == 3){
        printf("Esse feijão tinha sabor de tutti-frutti!(removeu 3 alternativa)\n");

    }
    return;
}

int exibeQuestao(Pergunta dificuldade[], int indice){
    char resposta;
    int ponto = 0;
    printf("%s", dificuldade[indice].questao);
    printf("%s", dificuldade[indice].alternativaA);
    printf("%s", dificuldade[indice].alternativaB);
    printf("%s", dificuldade[indice].alternativaC);
    printf("%s", dificuldade[indice].alternativaD);
        
    printf("Dicas: Chapeu seletor, Feijõezinhos de todos os sabores, Professora Trelawney(digite 'e' se quiser dica)");
    scanf(" %c", &resposta);
    if(resposta == 'e'){
        int dica;
        printf("Digite 1 para o chapeu seletor, digite 2 para o Feijõezinhos de todos os sabores, digite 3 para a professora Trelawney");
        scanf(" %d", &dica);

        if(dica == 1){

        } else if(dica == 2){
            feijozinhos(dificuldade);
        }
    }else if(resposta == dificuldade[indice].correta){
        printf("Parabens Bruxo, você acertou!");
        ponto++;
    }else {
        print("Seu lugar não é aqui trouxa, você errou!");
    }
    return ponto;
    
}

int chamaQuestao(Pergunta q[], int tamanho, int quantidadeQuestoes){
    srand(time(NULL)); // Inicializa a semente com base no tempo atual

    for (int i = 0; i < quantidadeQuestoes; i++){
        int minimo = 0;
        int maximo = tamanho - 1;
    
        int numero = (rand() % (maximo - minimo + 1)) + minimo;
        
        int verifica = exibeQuestao(q, numero);
        if (verifica == 0){
            exit(1);
        }

        numero = NULL;
    }
    
        
    
}

void classificarQ(Pergunta todas[], int total, Pergunta muitofacil[], Pergunta facil[], Pergunta medio[], Pergunta dificil[], Pergunta muitoDificil[]) {
    int contadorMF = 0, contadorF = 0, contadorM = 0, contadorD = 0, contadorMD = 0;

    for (int i = 0; i < total; i++) {
        switch (todas[i].nivel) {
            case 1:
                if (contadorMF < 20)
                    muitoFacil[contadorMF++] = todas[i];
                break;
            case 2:
                if (contadorF < 20)
                    facil[contadorF++] = todas[i];
                break;
            case 3:
                if (contadorM < 15)
                    medio[contadorM++] = todas[i];
                break;
            case 4:
                if (contadorD < 15)
                    dificil[contadorD++] = todas[i];
                break;
            case 5:
                if (contadorMD < 10)
                    muitoDificil[contadorMD++] = todas[i];
                break;
            default:
                printf("exibeQuestao com nivel invalido: %d\n", todas[i].nivel);
                break;
        }
    }
}

int main() {
    Pergunta muitoFacil[20];
    Pergunta facil[20];
    Pergunta medio[15];
    Pergunta dificil[15];
    Pergunta muitoDificil[10];

    Dica dica;

    FILE *arquivo = fopen("perguntas.csv", "r");
    if (arquivo == NULL) {
        perror("Erro ao abrir o arquivo");
        return 1;
    }

    Pergunta questoes[80];
    char linha[1024];
    int quantidade = 0;

    // Pular a primeira linha (cabeçalho)
    fgets(linha, sizeof(linha), arquivo);

    while (fgets(linha, sizeof(linha), arquivo) != NULL && quantidade < 80) {
        linha[strcspn(linha, "\n")] = '\0';  // Remove o '\n'

        char *token = strtok(linha, ";");
        if (token) strcpy(questoes[quantidade].enunciado, token);

        token = strtok(NULL, ";");
        if (token) strcpy(questoes[quantidade].alternativaA, token);

        token = strtok(NULL, ";");
        if (token) strcpy(questoes[quantidade].alternativaB, token);

        token = strtok(NULL, ";");
        if (token) strcpy(questoes[quantidade].alternativaC, token);

        token = strtok(NULL, ";");
        if (token) strcpy(questoes[quantidade].alternativaD, token);

        token = strtok(NULL, ";");
        if (token) questoes[quantidade].correta = token[0];

        token = strtok(NULL, ";");
        if (token) questoes[quantidade].nivel = atoi(token);

        quantidade++;
    }

    fclose(arquivo);

    classificarQ(questoes, quantidade, muitoFacil, facil, medio, dificil, muitoDificil);

    
    exibeQuestao(muitoFacil, 20, 2);
    exibeQuestao(facil, 20, 2);
    exibeQuestao(medio, 15, 4);
    exibeQuestao(dificil, 15, 4);
    exibeQuestao(muitoDificil, 10, 3);
    
   
    return 0;
}
