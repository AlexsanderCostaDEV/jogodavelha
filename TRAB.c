#include <stdio.h>
#include <string.h>
#include <time.h>
#include <stdlib.h>

/*
 * Prototipos
 */
void imprimir_tabuleiro(int []);
void menu_carregar_arquivo();
void menu_jogar();
void menu_principal();
int ler_opcao();
int terminou_jogo(int []);
void versus_computador(FILE* f);
void versus_jogador(FILE*);
void versus_computador_hard(FILE* f);

/*
 * Prototipos manipulacao de arquivos
 */
void exibir_resultado(FILE* f);
void exibir_duracao(FILE* f);
void exibir_jogada(FILE* f, int n);
FILE* carregar (char *);
FILE* inicializar_arquivo();
void salvar_resultado (FILE*, int);
void salvar_duracao (FILE*, int);
void salvar_jogada (FILE*, int[]);

void gen_random(char *, const int);

/* -----------------------------------------------------------------------------
 * -----------------------------------------------------------------------------
 * MAIN
 * /////////////////////////////////////////////////////////////////////////////
 */
int main(int argc, char **argv) {

	menu_principal();

	return 0;
}

/* -----------------------------------------------------------------------------
 * MENU PRINCIPAL
 * Imprime o menu principal
 * ~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~
 */
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
			system("cls");
			menu_jogar();
			break;

		case 2:
			system("cls");
			menu_carregar_arquivo();
			break;

		case 9:
			printf("Programa finalizado!");
			return;
			break;
		default:
			system("cls");
			printf("Opcao invalida!\n");
			system("pause");
		}
	} while (opcao != 9);
}

/* -----------------------------------------------------------------------------
 * LER
 * Ler opcao
 * ~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~
 */
int ler_opcao () {
	int op;

	printf("Opcao: ");
	scanf(" %d", &op);

	return op;
}

/* -----------------------------------------------------------------------------
 * MENU JOGAR
 * Imprime o menu para jogar
 * ~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~
 */
void menu_jogar() {
	int opcao, op;
	FILE *f;

	printf("~~~~~~~~~~~~~ JOGAR ~~~~~~~~~~~~~~~~~\n"
				"[1] - Versus outro jogador\n"
			    "[2] - Versus computador\n"
			    "[3] - Retornar ao menu anterior\n"
			    "---------\n");
	opcao = ler_opcao();

	switch(opcao) {
	case 1:
		system("cls");
		f = inicializar_arquivo();
		versus_jogador(f);
		fclose(f);
		break;

	case 2:
		system("cls");
		printf("[1] - Easy\n");
		printf("[2] - Hard\n");
		op = ler_opcao();
		if(op == 1){
			f = inicializar_arquivo();
			versus_computador(f);
			fclose(f);
			break;
		}else{
			f = inicializar_arquivo();
			versus_computador_hard(f);
			fclose(f);
			break;
		}		

	case 3:
		return;
		break;
	default:
		system("cls");
		printf("Opcao invalida!\n");
		system("pause");
	}
}

/* -----------------------------------------------------------------------------
 * INICIALIZAR ARQUIVO
 * Abre o arquivo e inicializa o arquivo com valores padroes
 * ~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~
 */
FILE* inicializar_arquivo() {
	int stringTam;
	srand((unsigned)time(NULL));
	stringTam = rand() % 11;	
	char *stringAleat = malloc(stringTam + 1);
    gen_random(stringAleat, stringTam);
	fopen(stringAleat, "wb");
}

/* -----------------------------------------------------------------------------
 * VERSUS JOGADOR
 * Jogar Versus Jogador
 * ~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~
 */
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
		printf("\n 1 | 2 | 3\n 4 | 5 | 6\n 7 | 8 | 9\n");
		do{
			printf("Entre com uma posicao entre 1 e 9 conforme o exemplo acima: ");
			a = ler_opcao();
			if(tab[a-1] == 0 || tab[a-1] == 1){a=10; printf("jogada invalida!\n\n");}
		}while(a < 1 || a > 9);
		tab[a-1] = 0;
		jogadas ++;
		salvar_jogada (f, tab);
		system("cls");
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
		printf("\n 1 | 2 | 3\n 4 | 5 | 6\n 7 | 8 | 9\n");
		do{
			printf("Entre com uma posicao entre 1 e 9 conforme o exemplo acima: ");
			a = ler_opcao();
			if(tab[a-1] == 0 || tab[a-1] == 1){a=10; printf("jogada invalida!\n\n");}
		}while(a < 1 || a > 9);
		tab[a-1] = 1;
		jogadas ++;
		salvar_jogada (f, tab);
		system("cls");
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

/* -----------------------------------------------------------------------------
 * VERSUS COMPUTADOR
 * Jogar Versus Computador
 * ~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~
 */
void versus_computador(FILE* f){
	int a, b, d;
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
		printf("\n 1 | 2 | 3\n 4 | 5 | 6\n 7 | 8 | 9\n");
		do{
			printf("Entre com uma posicao entre 1 e 9 conforme o exemplo acima: ");
			a = ler_opcao();
			if(tab[a-1] == 0 || tab[a-1] == 1){a=10; printf("jogada invalida!\n\n");}
		}while(a < 1 || a > 9);
		tab[a-1] = 0;
		jogadas++;
		salvar_jogada (f, tab);
		system("cls");
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

		srand((unsigned)time(NULL));
		do{
			d = rand() % 9;
		}while(tab[d] != 2);
		tab[d] = 1;
		jogadas++;
		salvar_jogada (f, tab);
		system("cls");
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

/* -----------------------------------------------------------------------------
 * VERSUS COMPUTADOR MODO HARD 
 * Jogar Versus Computador - Inteligencia Artificial 
 * ~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~
 */
void versus_computador_hard(FILE* f){
	int a, b, d;
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
		printf("\n 1 | 2 | 3\n 4 | 5 | 6\n 7 | 8 | 9\n");
		do{
			printf("Entre com uma posicao entre 1 e 9 conforme o exemplo acima: ");
			a = ler_opcao();
			if(tab[a-1] == 0 || tab[a-1] == 1){a=10; printf("jogada invalida!\n\n");}
		}while(a < 1 || a > 9);
		tab[a-1] = 0;
		jogadas++;
		salvar_jogada (f, tab);
		system("cls");
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

					//linhas
			 if(tab[0] == 1 && tab[1] == 1 && tab[2] == 2){tab[2] = 1;}
		else if(tab[3] == 1 && tab[4] == 1 && tab[5] == 2){tab[5] = 1;}
		else if(tab[6] == 1 && tab[7] == 1 && tab[8] == 2){tab[8] = 1;}
		else if(tab[0] == 1 && tab[1] == 2 && tab[2] == 1){tab[1] = 1;}
		else if(tab[3] == 1 && tab[4] == 2 && tab[5] == 1){tab[4] = 1;}
		else if(tab[6] == 1 && tab[7] == 2 && tab[8] == 1){tab[7] = 1;}
		else if(tab[0] == 2 && tab[1] == 1 && tab[2] == 1){tab[0] = 1;}
		else if(tab[3] == 2 && tab[4] == 1 && tab[5] == 1){tab[3] = 1;}
		else if(tab[6] == 2 && tab[7] == 1 && tab[8] == 1){tab[6] = 1;}
					//colunas
		else if(tab[0] == 1 && tab[3] == 1 && tab[6] == 2){tab[6] = 1;}
		else if(tab[1] == 1 && tab[4] == 1 && tab[7] == 2){tab[7] = 1;}
		else if(tab[2] == 1 && tab[5] == 1 && tab[8] == 2){tab[8] = 1;}
		else if(tab[0] == 1 && tab[3] == 2 && tab[6] == 1){tab[3] = 1;}
		else if(tab[1] == 1 && tab[4] == 2 && tab[7] == 1){tab[4] = 1;}
		else if(tab[2] == 1 && tab[5] == 2 && tab[8] == 1){tab[5] = 1;}
		else if(tab[0] == 2 && tab[3] == 1 && tab[6] == 1){tab[0] = 1;}
		else if(tab[1] == 2 && tab[4] == 1 && tab[7] == 1){tab[1] = 1;}
		else if(tab[2] == 2 && tab[5] == 1 && tab[8] == 1){tab[2] = 1;}
					//diagonais
		else if(tab[0] == 1 && tab[4] == 1 && tab[8] == 2){tab[8] = 1;}
		else if(tab[0] == 1 && tab[4] == 2 && tab[8] == 1){tab[4] = 1;}
		else if(tab[0] == 2 && tab[4] == 1 && tab[8] == 1){tab[0] = 1;}
		else if(tab[2] == 1 && tab[4] == 1 && tab[6] == 2){tab[6] = 1;}
		else if(tab[2] == 1 && tab[4] == 2 && tab[6] == 1){tab[4] = 1;}
		else if(tab[2] == 2 && tab[4] == 1 && tab[6] == 1){tab[2] = 1;}
					
					//linhas
		else if(tab[0] == 0 && tab[1] == 0 && tab[2] == 2){tab[2] = 1;}
		else if(tab[3] == 0 && tab[4] == 0 && tab[5] == 2){tab[5] = 1;}
		else if(tab[6] == 0 && tab[7] == 0 && tab[8] == 2){tab[8] = 1;}
		else if(tab[0] == 0 && tab[1] == 2 && tab[2] == 0){tab[1] = 1;}
		else if(tab[3] == 0 && tab[4] == 2 && tab[5] == 0){tab[4] = 1;}
		else if(tab[6] == 0 && tab[7] == 2 && tab[8] == 0){tab[7] = 1;}
		else if(tab[0] == 2 && tab[1] == 0 && tab[2] == 0){tab[0] = 1;}
		else if(tab[3] == 2 && tab[4] == 0 && tab[5] == 0){tab[3] = 1;}
		else if(tab[6] == 2 && tab[7] == 0 && tab[8] == 0){tab[6] = 1;}
					//colunas
		else if(tab[0] == 0 && tab[3] == 0 && tab[6] == 2){tab[6] = 1;}
		else if(tab[1] == 0 && tab[4] == 0 && tab[7] == 2){tab[7] = 1;}
		else if(tab[2] == 0 && tab[5] == 0 && tab[8] == 2){tab[8] = 1;}
		else if(tab[0] == 0 && tab[3] == 2 && tab[6] == 0){tab[3] = 1;}
		else if(tab[1] == 0 && tab[4] == 2 && tab[7] == 0){tab[4] = 1;}
		else if(tab[2] == 0 && tab[5] == 2 && tab[8] == 0){tab[5] = 1;}
		else if(tab[0] == 2 && tab[3] == 0 && tab[6] == 0){tab[0] = 1;}
		else if(tab[1] == 2 && tab[4] == 0 && tab[7] == 0){tab[1] = 1;}
		else if(tab[2] == 2 && tab[5] == 0 && tab[8] == 0){tab[2] = 1;}
					//diagonais
		else if(tab[0] == 0 && tab[4] == 0 && tab[8] == 2){tab[8] = 1;}
		else if(tab[0] == 0 && tab[4] == 2 && tab[8] == 0){tab[4] = 1;}
		else if(tab[0] == 2 && tab[4] == 0 && tab[8] == 0){tab[0] = 1;}
		else if(tab[2] == 0 && tab[4] == 0 && tab[6] == 2){tab[6] = 1;}
		else if(tab[2] == 0 && tab[4] == 2 && tab[6] == 0){tab[4] = 1;}
		else if(tab[2] == 2 && tab[4] == 0 && tab[6] == 0){tab[2] = 1;}
					
		else if(tab[4] == 2){tab[4] = 1;}
		else if((tab[0] == 0 && tab[8] == 0) || (tab[2] == 0 && tab[6] == 0)){
				 if(tab[1] == 2){tab[1] = 1;}
			else if(tab[3] == 2){tab[3] = 1;}
			else if(tab[5] == 2){tab[5] = 1;}
			else if(tab[7] == 2){tab[7] = 1;}}
			else if(tab[0] == 2){tab[0] = 1;}
			else if(tab[2] == 2){tab[2] = 1;}
			else if(tab[6] == 2){tab[6] = 1;}
			else if(tab[8] == 2){tab[8] = 1;}
		else{
			do{
				srand((unsigned)time(NULL));
				d = rand() % 9;
			}while(tab[d] != 2);
			tab[d] = 1;
			
		}
		jogadas++;
		salvar_jogada (f, tab);
		system("cls");
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

/* -----------------------------------------------------------------------------
 * SALVAR RESULTADO
 * Salva o resultado do jogo no arquivo
 * ~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~
 */
void salvar_resultado (FILE *f, int res) {
	rewind(f);
	fwrite(&res, sizeof(res), 1, f);
}

/* -----------------------------------------------------------------------------
 * SALVAR DURACAO
 * Salva a duração (numero de jogadas) da partida no arquivo
 * ~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~
 */
void salvar_duracao (FILE *f, int dur) {
	fseek(f, sizeof(int), SEEK_SET);
	fwrite(&dur, sizeof(dur), 1, f);
}

/* -----------------------------------------------------------------------------
 * SALVAR JOGADA
 * Salva a jogada (estado do tabuleiro) no arquivo
 * ~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~
 */
void salvar_jogada (FILE *f, int tab[]) {
	int i, j=0;
	for(i=0;i<9;i++){
		if(tab[i] == 0 || tab[i] == 1){
			j++;
		}
	}
	if(j==1){
		fseek(f, 2*sizeof(int), SEEK_SET);
		fwrite(tab, 9*sizeof(int), 1, f);
	}else{
		fseek(f, 8+((j-1)*36), SEEK_SET);
		fwrite(tab, 9*sizeof(int), 1, f);
	}
	
}

/* -----------------------------------------------------------------------------
 * IMPRIMIR_TABULEIRO
 * Recebe uma matriz e imprime o tabuleiro.
 * ~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~
 */
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

/* -----------------------------------------------------------------------------
 * TERMINOU JOGO
 * Verifica se o jogo terminou
 * ~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~
 */
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

/* -----------------------------------------------------------------------------
 * MENU CARREGAR ARQUIVO
 * Imprime o menu para carregar do arquivo
 * ~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~
 */
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
			system("cls");
			break;

		case 2:
			if (f == NULL) {
				printf("É preciso primeiramente carregar um arquivo!");
			}
			else {
				system("cls");
				exibir_resultado(f);
			}
			break;

		case 3:
			if (f == NULL) {
						printf("É preciso primeiramente carregar um arquivo!");
			}
			else {
				system("cls");
				exibir_duracao(f);
			}
			break;

		case 4:
			if (f == NULL) {
						printf("É preciso primeiramente carregar um arquivo!");
			}
			else {
				system("cls");
				printf("Entre com a jogada a ser exibida: ");
				scanf("%d", &n);
				system("cls");
				exibir_jogada(f, n);
			}
			break;

		case 5:
			system("cls");
			return;
			break;
		default:
			system("cls");
			printf("Opcao invalida!\n");
			system("pause");
		}
	} while (opcao != 5);
}

/* -----------------------------------------------------------------------------
 * CARREGAR ARQUIVO
 * Abre o arquivo com o nome fornecido como parametro
 * ~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~
 */
FILE *carregar(char* filename) {
	FILE *f = fopen(filename, "rb");
}

/* -----------------------------------------------------------------------------
 * EXIBIR RESULTADO
 * Le do arquivo e exibe o resultado da partida
 * ~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~
 */
void exibir_resultado(FILE* f) {
	int a;
	rewind(f);
	fread(&a, sizeof(a), 1, f);
	if(a == 0){
		printf("Vencedor = O\n");
	}else if(a == 1){
		printf("Vencedor = X\n");
	}else{
		printf("Empate!\n");
	}
}

/* -----------------------------------------------------------------------------
 * EXIBIR DURACAO
 * Le do arquivo e exibe a duracao (numero de jogadas)
 * ~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~
 */
void exibir_duracao(FILE* f) {
	int a;
	fseek(f, sizeof(int), SEEK_SET);
	fread(&a, sizeof(a), 1, f);
	printf("%d Jogadas\n", a);
}

/* -----------------------------------------------------------------------------
 * EXIBIR JOGADA
 * Le do arquivo e exibe na tela o estado do tabuleiro na jogada n fornecida
 * ~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~
 */
void exibir_jogada(FILE* f, int n) {
	int a;
	int i;
	
	if(n == 1){
		system("cls");
		fseek(f, 2*sizeof(int), SEEK_SET);
		for(i=0; i<9; i++){
			fread(&a, sizeof(a), 1, f);
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
	}else{
		system("cls");
		fseek(f, 8+((n-1)*36), SEEK_SET);
		for(i=0; i<9; i++){
			fread(&a, sizeof(a), 1, f);
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

/* -----------------------------------------------------------------------------
 * GEN RANDOM
 * Gera uma string aleatoria com o tamanho len passado como parametro
 * ~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~
 */
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
