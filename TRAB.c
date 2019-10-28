#include <stdio.h>
#include <string.h>
#include <time.h>
#include <stdlib.h>

void menu_principal();
int ler_opcao();
void menu_jogar();
FILE* inicializar_arquivo();
void versus_jogador(FILE*);
void imprimir_tabuleiro(int []);
void salvar_resultado (FILE*, int);
int terminou_jogo(int []);
void versus_computador(FILE* f);

int main(int argc, char **argv) {

	menu_principal();

	return 0;
}

void menu_principal() {
	int opcao;

	do {
		printf("~~~~~~~~~~~~~ JOGO DA VELHA ~~~~~~~~~~~~~~~~~\n"
						"[1] - Jogar\n"
						"[2] - Carregar de um arquivo\n"
						"[9] - Sair\n"
						"---------\n");
		opcao = ler_opcao();

		switch(opcao) {
		case 1:
			menu_jogar();
			break;

		case 2:
			//menu_carregar_arquivo();
			break;

		case 9:
			printf("Programa finalizado!");
			return;
			break;
		}
	} while (opcao != 9);
}

int ler_opcao () {
	int op;

	printf("Opcao: ");
	scanf(" %d", &op);

	return op;
}

void menu_jogar() {
	int opcao;
	FILE *f;

	printf("~~~~~~~~~~~~~ JOGAR ~~~~~~~~~~~~~~~~~\n"
				"[1] - Versus outro jogador\n"
			    "[2] - Versus computador\n"
			    "[3] - Retornar ao menu anterior\n"
			    "---------\n");
	opcao = ler_opcao();

	switch(opcao) {
	case 1:
		f = inicializar_arquivo();
		versus_jogador(f);
		fclose(f);
		break;

	case 2:
		f = inicializar_arquivo();
		versus_computador(f);
		fclose(f);
		break;

	case 3:
		return;
		break;
	}
}

FILE* inicializar_arquivo() {
	fopen("inicio.bin", "wb");
}

void versus_jogador(FILE* f) {
	int a;
	int b;
	int jogadas = 0;
	
	int tab[9] = {2, 2, 2, 2, 2, 2, 2, 2, 2};
	
	if(f == NULL){
		printf("Nao foi possivel abrir o arquivo.\n");
		system("pause");
		exit(1);
	}
	//fseek(f, 2*sizeof(int), SEEK_SET);
	printf("'O' e 'X', respectivamente\n");
	do{
		printf("0 | 1 | 2\n3 | 4 | 5\n6 | 7 | 8\n");
		do{
			printf("Entre com uma posicao entre 0 e 8 conforme o exemplo acima: ");
			scanf("%d", &a);	
		}while(a < 0 || a > 8);
		tab[a] = 0;
		jogadas ++;
		imprimir_tabuleiro(tab);
		b = terminou_jogo(tab);
		if(b == 1){
			printf("Jogador X venceu\n");
			break;
		}if(b == 0){
			printf("Jogador O venceu\n");
			break;
		}if(jogadas == 9){
			printf("Empate\n");
		}
		printf("0 | 1 | 2\n3 | 4 | 5\n6 | 7 | 8\n");
		do{
			printf("Entre com uma posicao entre 0 e 8 conforme o exemplo acima: ");
			scanf("%d", &a);	
		}while(a < 0 || a > 8);
		tab[a] = 1;
		jogadas ++;
		imprimir_tabuleiro(tab);
		b = terminou_jogo(tab);
		if(b == 1){
			printf("Jogador X venceu\n");
			break;
		}if(b == 0){
			printf("Jogador O venceu\n");
			break;
		}if(jogadas == 9){
			printf("Empate\n");
		}
	}while(b != 0 || b != 1);
	
}

void versus_computador(FILE* f){
	int a, b, c, d, e, g;
	
	int tab[9] = {2, 2, 2, 2, 2, 2, 2, 2, 2};
	
	if(f == NULL){
		printf("Nao foi possivel abrir o arquivo.\n");
		system("pause");
		exit(1);
	}
	//fseek(f, 2*sizeof(int), SEEK_SET);
	printf("Escolha 1-(X) ou 2-(O) para jogar: ");
	scanf("%d", &c);
	if(c == 1){
		e = 1;
		g = 0;
	}
	if(c == 2){
		e = 0;
		g = 1;
	}
	do{
		printf("0 | 1 | 2\n3 | 4 | 5\n6 | 7 | 8\n");
		do{
			printf("Entre com uma posicao entre 0 e 8 conforme o exemplo acima: ");
			scanf("%d", &a);	
		}while(a < 0 || a > 8);
		tab[a] = e;
		imprimir_tabuleiro(tab);
		printf("\n");
		b = terminou_jogo(tab);
		if(b == e){
			printf("Voce venceu\n");
			break;
		}if(b == g){
			printf("Voce perdeu\n");
			break;
		}
		
		srand(time(NULL));
		do{
			d = rand() % 9;
		}while(tab[d] == e);
		tab[d] = g;
		imprimir_tabuleiro(tab);
		printf("\n");
		b = terminou_jogo(tab);
		if(b == e){
			printf("Voce venceu\n");
			break;
		}if(b == g){
			printf("Voce perdeu\n");
			break;
		}
	}while(b != 0 || b != 1);
}

void imprimir_tabuleiro(int tab[]) {
	int i, j;

	for (i = 0; i < 3; i++) {

		for (j = 0; j < 3; j++) {
			int k = j + 3*i;

			if (tab[k] == 0)
				printf(" O ");
			else if (tab[k] == 1)
				printf(" X ");
			else
				printf("   ");

			if (j != 2)
				printf("|");
			else
				printf("\n");
		}
	}
}

int terminou_jogo(int tab[]) {
	int i;

	// verificando linhas
	for (i = 0; i < 3; i++) {
		if (tab[i*3] == tab[i*3 + 1] && tab[i*3 + 1] == tab[i*3 + 2]) {
			return tab[i*3];
		}
	}

	// verificando colunas
	for (i = 0; i < 3; i++) {
		if (tab[i] == tab[i+3] && tab[i+3] == tab[i+6]) {
				return tab[i];
		}
	}

	// verificando diagonal
	if (tab[0] == tab[4] && tab[4] == tab[8]) {
		return tab[0];
	}

	// verificando diagonal
	if (tab[2] == tab[4] && tab[4] == tab[6]) {
		return tab[0];
	}

	return -1;
}

void salvar_resultado (FILE *f, int res) {
	/*file = inicializar_arquivo();
	if(f == NULL){
		printf("Nao foi possivel abrir o arquivo.\n");
		system("pause");
		exit(1);
	}*/

}
