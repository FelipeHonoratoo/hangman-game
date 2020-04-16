#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#include <time.h>
#include "forca.h"

//variáveis globais
char palavrasereta[TAMANHO_PALAVRA];
char chutes[26];
int chutesdados = 0;

void abertura() {
	printf("\n\n");
	printf("       ._______.                                   \n");
	printf("       | \\   / |                                  \n");
	printf("    .--|.O.|.O.|______.                Bem vindo   \n");
	printf("  __).-| = | = |/   \\ |                   ao       \n");
	printf("  >__) \\.'---`./Q.|.Q.|--.           Jogo De Forca \n");
	printf("        \\\\___// = | = |-.\\__                    \n");
	printf("         `---'\\ .---. / \\__<                    \n");
	printf("               \\\\.-.//                           \n");
	printf("                `---'                              \n");
	printf("\n\n");
} 

void chuta() {
	char chute;
	scanf(" %c", &chute);

	chutes[chutesdados] = chute;
	chutesdados++;
}

void desenhaforca() {

	int erros = chuteserrados();

	printf("  _______      \n");     
    printf(" |/      |     \n");     
    printf(" |      %c%c%c \n", (erros >= 1 ? '(' : ' '), 
    	(erros >= 1 ? '_' : ' '), (erros >= 1 ? ')' : ' '));     
    printf(" |      %c%c%c \n", (erros >= 3 ? '\\' : ' '), 
    	(erros >= 2 ? '|' : ' '), (erros >= 3 ? '/' : ' '));     
    printf(" |       %c    \n", (erros >= 2 ? '|' : ' '));     
    printf(" |      %c %c  \n", (erros >= 4 ? '/' : ' '), 
    	(erros >= 4 ? '\\' : ' '));     
    printf(" |             \n");     
    printf("_|___          \n");     
    printf("\n\n");

	for (int i = 0; i < strlen(palavrasereta); i++) {

		int achou = jachutou(palavrasereta[i]);

		if (achou) {
			printf("%c ", palavrasereta[i]);
		} else {
			printf("_ ");
		}
	}
	printf("\n");
}

void adicionapalavra() {

	char quer;

	printf("Voc%c deseja adicionar uma nova palavra no jogo? (S/N) ", 136);
	scanf(" %c", &quer);

	if(quer == 'S') {

		char novapalavra[TAMANHO_PALAVRA];
		printf("Qual a nova palavra? \n");
		scanf("%s", novapalavra);

		FILE* f;

		f = fopen("palavras.txt", "r+");
		if(f == 0) {
		printf("Desculpe, banco de dados indisponivel\n\n");
		exit(1);
		}

		int qtd;
		fscanf(f, "%d", &qtd);
		qtd++;

		fseek(f, 0, SEEK_SET);
		fprintf(f, "%d", qtd);

		fseek(f, 0, SEEK_END);
		fprintf(f, "\n%s", novapalavra);

		fclose(f);
	}
}

void escolhepalavra() {
	FILE* f;

	f = fopen("palavras.txt", "r");
	if(f == 0) {
		printf("Desculpe, banco de dados indisponivel\n\n");
		exit(1);
	}

	int qtddepalavras;
	fscanf(f, "%d", &qtddepalavras);

	srand(time(0));
	int randomico = rand() % qtddepalavras;

	for (int i = 0; i <= randomico; i++) {
		fscanf(f, "%s", palavrasereta);
	}

	fclose(f);
}

int acertou() {
	for (int i = 0; i < strlen(palavrasereta); i++) {
		if(!jachutou(palavrasereta[i])){
			return 0;
		}		
	}

	return 1;
}

int chuteserrados() {
	int erros = 0;

	for (int i = 0; i < chutesdados; i++) {
		int existe = 0;

		for (int j = 0; j < strlen(palavrasereta); j++) {
			if(chutes[i] == palavrasereta[j]) {

				existe = 1;
				break;
			}	
		}

		if(!existe) erros++;
	}

	return erros;
}

int enforcou() {
	
	return chuteserrados() >= 5;
}

int jachutou(char letra) {
	int achou = 0;

	for (int j = 0; j < chutesdados; j++) {
		if (chutes[j] == letra) {
			achou = 1;
			break;
		}
	}
	return achou;
}

void ganhou() {
	printf("\nParab%cns, voc%c ganhou!\n\n", 130, 136); 
	 
	printf("       ___________      \n");     
	printf("      '._==_==_=_.'     \n");     
	printf("      .-\\:      /-.    \n");     
	printf("     | (|:.     |) |    \n");     
	printf("      '-|:.     |-'     \n");     
	printf("        \\::.    /      \n");     
	printf("         '::. .'        \n");     
	printf("           ) (          \n");     
	printf("         _.' '._        \n");     
	printf("        '-------'       \n\n");
}

void perdeu() {
	printf("\nPuxa, voc%c foi enforcado!\n", 136);     
	printf("A palavra era **%s**\n\n", palavrasereta); 
	 
	printf("    _______________         \n");     
	printf("   /               \\       \n");      
    printf("  /                 \\      \n");     
    printf("//                   \\/\\  \n");     
    printf("\\|   XXXX     XXXX   | /   \n");     
    printf(" |   XXXX     XXXX   |/     \n");     
    printf(" |   XXX       XXX   |      \n");     
    printf(" |                   |      \n");     
    printf(" \\__      XXX      __/     \n");     
    printf("   |\\     XXX     /|       \n");     
    printf("   | |           | |        \n");     
    printf("   | I I I I I I I |        \n");     
    printf("   |  I I I I I I  |        \n");     
    printf("   \\_             _/       \n");     
    printf("     \\_         _/         \n");     
    printf("       \\_______/           \n\n");
}

int main() {

	escolhepalavra();
	abertura();

	do {
		desenhaforca();
		chuta();
	} while (!acertou() && !enforcou());

	if(acertou()) {
		ganhou();	
	} else {
		perdeu();	
	}

	adicionapalavra();

	system("pause");
}