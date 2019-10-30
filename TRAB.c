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
void salvar_duracao (FILE*, int);
void salvar_jogada (FILE*, int[]);
FILE* carregar (char *);
void menu_carregar_arquivo();
void exibir_resultado(FILE* f);
void exibir_duracao(FILE* f);
void exibir_jogada(FILE* f, int n);

void gen_random(char *s, const int len);

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
			menu_carregar_arquivo();
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

	int stringTam;

	printf("Entre com o tamanho da string: ");
	scanf("%d", &stringTam);

	char *stringAleat = malloc(stringTam + 1);

    gen_random(stringAleat, stringTam);

	fopen(stringAleat, "wb");

}

void versus_jogador(FILE* f) {
	int a, b, jogadas = 0;

	int tab[9] = {2, 2, 2, 2, 2, 2, 2, 2, 2};

	if(f == NULL){
		printf("Nao foi possivel abrir o arquivo.\n");
		system("pause");
		exit(1);
	}
	printf("'O' e 'X', respectivamente\n");
	do{
		printf("0 | 1 | 2\n3 | 4 | 5\n6 | 7 | 8\n");
		do{
			printf("Entre com uma posicao entre 0 e 8 conforme o exemplo acima: ");
			scanf("%d", &a);
			if(tab[a] == 0 || tab[a] == 1){a=9; printf("jogada invalida!\n\n");}
		}while(a < 0 || a > 8);
		tab[a] = 0;
		jogadas ++;
		if(jogadas == 1){
			salvar_jogada (f, tab);
		}
		imprimir_tabuleiro(tab);
		b = terminou_jogo(tab);
		if(b == 1){
			printf("Jogador X venceu\n");
			salvar_resultado (f, b);
			salvar_duracao (f, jogadas);
			break;
		}if(b == 0){
			printf("Jogador O venceu\n");
			salvar_resultado (f, b);
			salvar_duracao (f, jogadas);
			break;
		}if(jogadas == 9){
			printf("Empate\n");
			salvar_resultado (f, b);
			salvar_duracao (f, jogadas);
			break;
		}
		printf("0 | 1 | 2\n3 | 4 | 5\n6 | 7 | 8\n");
		do{
			printf("Entre com uma posicao entre 0 e 8 conforme o exemplo acima: ");
			scanf("%d", &a);
			if(tab[a] == 0 || tab[a] == 1){a=9; printf("jogada invalida!\n\n");}
		}while(a < 0 || a > 8);
		tab[a] = 1;
		jogadas ++;
		imprimir_tabuleiro(tab);
		b = terminou_jogo(tab);
		if(b == 1){
			printf("Jogador X venceu\n");
			salvar_resultado (f, b);
			salvar_duracao (f, jogadas);
			break;
		}if(b == 0){
			printf("Jogador O venceu\n");
			salvar_resultado (f, b);
			salvar_duracao (f, jogadas);
			break;
		}if(jogadas == 9){
			printf("Empate\n");
			salvar_resultado (f, b);
			salvar_duracao (f, jogadas);
			break;
		}
	}while(b != 0 || b != 1);

}

void versus_computador(FILE* f){
	int a, b, d, e, g;
	int jogadas = 0;

	//TABULEIRO EM BRANCO
	int tab[9] = {2, 2, 2, 2, 2, 2, 2, 2, 2};

	if(f == NULL){
		printf("Nao foi possivel abrir o arquivo.\n");
		system("pause");
		exit(1);
	}

	printf("'O' Jogador e 'X' Computador, respectivamente\n");
	do{
		printf("0 | 1 | 2\n3 | 4 | 5\n6 | 7 | 8\n");
		do{
			printf("Entre com uma posicao entre 0 e 8 conforme o exemplo acima: ");
			scanf("%d", &a);
			if(tab[a] == 0 || tab[a] == 1){a=9; printf("jogada invalida!\n\n");}
		}while(a < 0 || a > 8);
		tab[a] = 0;
		jogadas++;
		if(jogadas == 1){
			salvar_jogada (f, tab);
		}
		imprimir_tabuleiro(tab);
		printf("\n");
		b = terminou_jogo(tab);
		if(b == 0){
			printf("Voce venceu\n");
			salvar_resultado (f, b);
			salvar_duracao (f, jogadas);
			break;
		}if(jogadas == 9){
			printf("Empate\n");
			salvar_resultado (f, b);
			salvar_duracao (f, jogadas);
			break;
		}

		srand(time(NULL));
		do{
			d = rand() % 9;
		}while(tab[d] != 2);
		tab[d] = 1;
		jogadas++;
		imprimir_tabuleiro(tab);
		printf("\n");
		b = terminou_jogo(tab);
		if(b == 1){
			printf("Voce perdeu\n");
			salvar_resultado (f, b);
			salvar_duracao (f, jogadas);
			break;
		}if(jogadas == 9){
			printf("Empate\n");
			salvar_resultado (f, b);
			salvar_duracao (f, jogadas);
			break;
		}
	}while(b != 0 || b != 1);
}

//esta gravando sempre 0 independente de quem ganha
void salvar_resultado (FILE *f, int res) {
	rewind(f);
	fwrite(&res, sizeof(res), 1, f);
}

void salvar_duracao (FILE *f, int dur) {
	fseek(f, sizeof(int), SEEK_SET);
	fwrite(&dur, sizeof(dur), 1, f);
}

void salvar_jogada (FILE *f, int tab[]) {
	fseek(f, 2*sizeof(int), SEEK_SET);
	fwrite(tab, 9*sizeof(int), 1, f);
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
		return tab[2];
	}

	return -1;
}

void menu_carregar_arquivo() {
	FILE *f;
	int opcao, n;
	char filename[15];

	f = NULL;

	do {
		printf("~~~~~~~~~~~~~ CARREGAR ARQUIVO ~~~~~~~~~~~~~~~~~\n"
					"[1] - Carregar Arquivo\n"
					"[2] - Exibir resultado\n"
					"[3] - Exibir numero de jogadas\n"
					"[4] - Exibir jogada\n"
					"[5] - Retornar ao menu anterior\n"
					"---------\n");
		opcao = ler_opcao();

		switch(opcao) {

		case 1:
			printf("Entre com o nome do arquivo: ");
			scanf("%s", filename);

			f = carregar(filename);
			break;

		case 2:
			if (f == NULL) {
				printf("É preciso primeiramente carregar um arquivo!");
			}
			else {
				exibir_resultado(f);
			}
			break;

		case 3:
			if (f == NULL) {
						printf("É preciso primeiramente carregar um arquivo!");
			}
			else {
				exibir_duracao(f);
			}
			break;

		case 4:
			if (f == NULL) {
						printf("É preciso primeiramente carregar um arquivo!");
			}
			else {
				printf("Entre com a jogada a ser exibida: ");
				scanf("%d", &n);

				exibir_jogada(f, n);
			}
			break;

		case 5:
			return;
			break;
		}
	} while (opcao != 5);
}

FILE *carregar(char* filename) {
	FILE *f = fopen(filename, "rb");
}

void exibir_resultado(FILE* f) {
	int a;
	rewind(f);
	fread(&a, sizeof(a), 1, f);
	printf("%d\n", a);
}

void exibir_duracao(FILE* f) {
	int a;
	fseek(f, sizeof(int), SEEK_SET);
	fread(&a, sizeof(a), 1, f);
	printf("%d\n", a);
}

void exibir_jogada(FILE* f, int n) {
	int a;
	int i;

	if(n == 1){
		fseek(f, 2*sizeof(int), SEEK_SET);
		for(i=0; i<9; i++){
			fread(&a, sizeof(a), 1, f);
			//printf("%d\n", a);
			if(a == 0){
				printf(" O ");
			}if(a == 1){
				printf(" X ");
			}if(a == 2){
				printf("   ");
			}
			if(i == 2 || i == 5 || i == 8){
				printf("\n");
			}else{
				printf("|");
			}
		}
	}
}



void gen_random(char *s, const int len) {
	srand(time(NULL));
    static const char alphanum[] =
        "0123456789"
        "ABCDEFGHIJKLMNOPQRSTUVWXYZ"
        "abcdefghijklmnopqrstuvwxyz";
	int i;
    for (i = 0; i < len; ++i) {
        s[i] = alphanum[rand() % (sizeof(alphanum) - 1)];
    }

    s[len] = 0;

}

