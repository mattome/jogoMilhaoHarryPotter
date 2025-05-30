#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <time.h>
#include <ctype.h>


typedef enum{MUITOFACIL = 1, FACIL, MEDIO, DIFICIL, MUITODIFICIL}Nivel;

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

void chapeu(Pergunta alternativas[], int indice){
    printf("\n");
    if (alternativas[indice].correta != 'A') alternativas[indice].alternativaA[0] = '\0';
    if (alternativas[indice].correta != 'B') alternativas[indice].alternativaB[0] = '\0';
    if (alternativas[indice].correta != 'C') alternativas[indice].alternativaC[0] = '\0';
    if (alternativas[indice].correta != 'D') alternativas[indice].alternativaD[0] = '\0';
}

void feijozinhos(Pergunta alternativas[], int indice){
    int contador = 0;

    int minimo = 0;
    int maximo = 3;

    int numero = (rand() % (maximo - minimo + 1)) + minimo;

    if(numero == 0){
        printf("Esse feijão tinha sabor de vomito!(removeu nenhuma alternativa)\n");
    } else if(numero == 1){
        printf("Esse feijão tinha sabor de grama!(removeu 1 alternativa)\n");
        if(alternativas[indice].correta != 'A'){
            alternativas[indice].alternativaA[0] = '\0';
            contador++;
        }
        if(alternativas[indice].correta != 'B'){
            alternativas[indice].alternativaB[0] = '\0';
            contador++;
        }

    }else if(numero == 2){
        printf("Esse feijão tinha sabor de marshmallow!(removeu 2 alternativa)\n");
        if(alternativas[indice].correta != 'A'){
            alternativas[indice].alternativaA[0] = '\0';  // Correto
            contador++;
        }
        if(alternativas[indice].correta != 'B' && contador != 2){
            alternativas[indice].alternativaB[0] = '\0';
            contador++;
        }
        if(alternativas[indice].correta != 'C' && contador != 2){
            alternativas[indice].alternativaC[0] = '\0';
            contador++;
        }
    }else if(numero == 3){
        printf("Esse feijão tinha sabor de tutti-frutti!(removeu 3 alternativa)\n");
        if (alternativas[indice].correta != 'A') alternativas[indice].alternativaA[0] = '\0';
        if (alternativas[indice].correta != 'B') alternativas[indice].alternativaB[0] = '\0';
        if (alternativas[indice].correta != 'C') alternativas[indice].alternativaC[0] = '\0';
        if (alternativas[indice].correta != 'D') alternativas[indice].alternativaD[0] = '\0';
    }
    return;
}

void professora(Pergunta alternativas[], int indice){
    int contador = 0;
    if(alternativas[indice].correta != 'A'){
            alternativas[indice].alternativaA[0] = '\0';  // Correto
            contador++;
        }
        if(alternativas[indice].correta != 'B' && contador != 2){
            alternativas[indice].alternativaB[0] = '\0';
            contador++;
        }
        if(alternativas[indice].correta != 'C' && contador != 2){
            alternativas[indice].alternativaC[0] = '\0';
            contador++;
        }
}

int exibeQuestao(Pergunta dificuldade[], int indice){
    char resposta;
    int ponto = 0;
    printf("%s\n", dificuldade[indice].enunciado);
    printf("A) %s\n", dificuldade[indice].alternativaA);
    printf("B) %s\n", dificuldade[indice].alternativaB);
    printf("C) %s\n", dificuldade[indice].alternativaC);
    printf("D) %s\n", dificuldade[indice].alternativaD);

    
    printf("Dicas: Chapeu seletor, Feijõezinhos de todos os sabores, Professora Trelawney");
    printf("Digite sua resposta (ou 'e' para pedir dica): ");
    scanf(" %c", &resposta);
    resposta = toupper(resposta); // para aceitar minúsculas
    if(resposta == 'E'){
        int dica;
        
        do{
            printf("Digite 1 para o chapeu seletor, digite 2 para o Feijõezinhos de todos os sabores, digite 3 para a professora Trelawney");
            scanf(" %d", &dica);
        } while (dica != 1 && dica != 2 && dica != 3);
        

        if(dica == 1){
            chapeu(dificuldade, indice);
        } else if(dica == 2){
            feijozinhos(dificuldade, indice);
        } else if(dica == 3){
            professora(dificuldade, indice);
        }

        char respostaDepoisdaDica;

        printf("%s\n", dificuldade[indice].enunciado);
        printf("A) %s\n", dificuldade[indice].alternativaA);
        printf("B) %s\n", dificuldade[indice].alternativaB);
        printf("C) %s\n", dificuldade[indice].alternativaC);
        printf("D) %s\n", dificuldade[indice].alternativaD);

        printf("Digite sua resposta: ");
        scanf(" %c", &respostaDepoisdaDica);

        if(respostaDepoisdaDica == dificuldade[indice].correta){
            printf("Parabens Bruxo, você acertou!");
            ponto++;
        }

    }else if(resposta == dificuldade[indice].correta){
        printf("Parabens Bruxo, você acertou!");
        ponto++;
    }else {
        printf("Seu lugar não é aqui trouxa, você errou!");
    }
    return ponto;
    
}

void chamaQuestao(Pergunta q[], int tamanho, int quantidadeQuestoes){
    srand(time(NULL)); // Inicializa a semente com base no tempo atual

    for (int i = 0; i < quantidadeQuestoes; i++){
        int minimo = 0;
        int maximo = tamanho - 1;
    
        int numero = (rand() % (maximo - minimo + 1)) + minimo;
        
        int verifica = exibeQuestao(q, numero);
        if (verifica == 0){
            exit(1);
        }

    }
}

void classificarQ(Pergunta todas[], int total, Pergunta muitoFacil[], Pergunta facil[], Pergunta medio[], Pergunta dificil[], Pergunta muitoDificil[]) {
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

void sistemaBusca(Pergunta questoes[], int total) {
    int nivelEscolhido;
    int encontrados[80]; // guarda os índices das perguntas com o nível escolhido
    int contador = 0;

    do{
    printf("\n--- BUSCA POR NÍVEL ---\n");
    printf("Escolha o nível de dificuldade:\n");
    printf("1 - Muito Fácil\n");
    printf("2 - Fácil\n");
    printf("3 - Médio\n");
    printf("4 - Difícil\n");
    printf("5 - Muito Difícil\n");
    printf("Digite o número correspondente: ");
    scanf(" %d", &nivelEscolhido);
    }while(nivelEscolhido != 1 && nivelEscolhido != 2 && nivelEscolhido != 3 && nivelEscolhido != 4 && nivelEscolhido != 5);

    // Coleta índices das perguntas com o nível escolhido
    for (int i = 0; i < total; i++) {
        if (questoes[i].nivel == nivelEscolhido) {
            encontrados[contador++] = i;
        }
    }

    if (contador == 0) {
        printf("Nenhuma pergunta encontrada para esse nível.\n");
        return;
    }

    int pos = 0;
    char opcao;
    do {
        int idx = encontrados[pos];
        printf("\nPergunta %d de %d\n", pos + 1, contador);
        printf("%s\n", questoes[idx].enunciado);
        printf("A) %s\n", questoes[idx].alternativaA);
        printf("B) %s\n", questoes[idx].alternativaB);
        printf("C) %s\n", questoes[idx].alternativaC);
        printf("D) %s\n", questoes[idx].alternativaD);
        printf("Resposta correta: %c\n", questoes[idx].correta);

        printf("\nDigite 'n' para próxima, 'a' para anterior, 's' para sair: ");
        scanf(" %c", &opcao);

        if (opcao == 'n' && pos < contador - 1) {
            pos++;
        } else if (opcao == 'a' && pos > 0) {
            pos--;
        }

    } while (opcao != 's');
}


int main() {
    Pergunta muitoFacil[20];
    Pergunta facil[20];
    Pergunta medio[15];
    Pergunta dificil[15];
    Pergunta muitoDificil[10];

    //Dica dica;

    FILE *arquivo = fopen("QuestoesHarryPotter.csv", "r");
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

    srand(time(NULL)); // Inicializa a semente com base no tempo atual


    printf("Jogo do milhão do Harry Potter\n\n");
    printf("MENU:\n");
    printf("--------------------------\n");
    printf("1-Jogar\n");
    printf("2-Busca\n");
    printf("3-Sair\n");
    
    int menu = 0;
    scanf(" %d", &menu);

    if(menu == 1){
        chamaQuestao(muitoFacil, 20, 2);
        chamaQuestao(facil, 20, 2);
        chamaQuestao(medio, 15, 4);
        chamaQuestao(dificil, 15, 4);
        chamaQuestao(muitoDificil, 10, 3);
        printf("Você realmente é um bruxo de puro-sangue - Você venceu\n");
    } else if(menu == 2){
        sistemaBusca(questoes, quantidade);
    } else if(menu == 3){
        exit(1);
    }
   
    return 0;
}
