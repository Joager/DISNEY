#include <chrono>
#include <thread>
#include <vector>
#include <iostream>
#include "engine.h"
#include "colors.h"

struct entidade {
	char representacao; // representacao visual da entidade
	char valor;
	int cor;
};

namespace CampoMinado {
	static int quantidadeDeBombas;
	static int quantidadeDeBandeiras;
//	std::vector< std::vector <entidade> > terreno;
}

int main(int argc, char *argv[]) {
	// iniciar o curses e setar cores
	initscr();
	start_color();
	cbreak();
	noecho();
	nodelay(stdscr, TRUE);
	keypad(stdscr, TRUE);
	init_pair(BACKGROUND_FLASH, COLOR_WHITE, COLOR_BLACK);
	init_pair(TEXT_FLASH, COLOR_GREEN, COLOR_BLACK);
	// iniciar o timer
	int timer = 0;
	Menu::atual = 0;
	std::string linhaTimer; // o timer do jogo e definido aqui
	printw("=== CAMPO MINADO ===");
	if (argc > 1) {
		Menu::carregar_jogo(argv[1]);
	}
	else {
		Menu::trocar(PRINCIPAL);
	}
	// loop principal
	while (1) {
		int movenum;
		std::this_thread::sleep_for(std::chrono::milliseconds(100));
		if (Engine::gameCounter >= 10) { Engine::gameCounter = 0; }
		if (Engine::gameStates == STATE_MENU) {
			movenum = 7;
		}
		else {
			movenum = Engine::sizeY;
		}
		move(movenum, 0);
		timer++;
		// resetando a linha e imprimindo ela de novo com o timer do programa
		linhaTimer = "TIMER -> ";
		linhaTimer += std::to_string((timer / 10));
		linhaTimer += "s ";//			CampoMinado::terreno[i] = std::vector<entidade>(y);
		linhaTimer += std::to_string(Engine::gameCounter);
		linhaTimer += "ms";
		printw(linhaTimer.c_str());
		move(0, 0);
		attron(A_BOLD);
		printw("=== CAMPO MINADO ===");
		attroff(A_BOLD);
		Engine::handleKeyPresses();
		if (Engine::gameStates == STATE_MENU) {
			Menu::animar();
		}
		else {
			if (Engine::gameStates == STATE_GAME) {
				Engine::readScreen();
			}
		}
				Engine::gameCounter++;
			}
			endwin();
			return 0;
		}

void Engine::handleKeyPresses() {
	int tecla;
	tecla = wgetch(stdscr);
	// mudar linha abaixo pra funcionar no linux e no windows eu to com preguica demais
	switch(tecla) {
		case KEY_UP:
			if (Engine::gameStates == STATE_MENU) {
				if (Menu::opcao > 1) {
					Menu::opcao--;
				}
			}
			break;
		case KEY_DOWN:
			if (Engine::gameStates == STATE_MENU) {
				if (Menu::opcao < 5) {
					Menu::opcao++;
				}
			}
			break;
		case KEY_RIGHT:
			if (Engine::gameStates == STATE_GAME) {
			}
			break;
		case KEY_LEFT:
			if (Engine::gameStates == STATE_GAME) {
			}
			break;
		case 10: // tecla enter do centro do teclado, KEY_ENTER e a do numpad
		case KEY_ENTER:
			if (Engine::gameStates == STATE_MENU) {
				switch(Menu::atual) {
					case PRINCIPAL:
						switch(Menu::opcao) {
							case JOGAR:
								Menu::trocar(JOGAR);
								break;
							case SALVAR:
								Menu::salvar();
								break;
							case CARREGAR:
								Menu::trocar(CARREGAR);
								Menu::carregar();
								break;
							case OPCOES:
								Menu::trocar(OPCOES);
								break;
							case SAIR:
								Menu::sair();
								break;
						}
						break;
					case JOGAR:
						int tamX;
						int tamY;
						int dificuldade;
						if (Menu::opcao == 5) { // caso seja o botao de MENU PRINCIPAL
							Menu::trocar(PRINCIPAL);
						}
						switch(Menu::opcao) {
							case 1:
								tamX = 7;
								tamY = 7;
								dificuldade = 4;
								break;
							case 2:
								tamX = 10;
								tamY = 10;
								dificuldade = 6;
								break;
							case 3:
								tamX = 17;
								tamY = 17;
								dificuldade = 10;
								break;
						}
						if (Menu::opcao > 0 && Menu::opcao <= 3) {
						  Menu::jogar(tamX, tamY, dificuldade);
							Engine::sizeX = tamX;
							Engine::sizeY = tamY;
						}
						break;
					case OPCOES:
						if (Menu::opcao == 4) { // caso seja o botao de MENU PRINCIPAL
							Menu::trocar(PRINCIPAL);
						}
						break;
				}
			}
			break;
	}
}

void Menu::jogar(int x, int y, int dificuldade) {
	Engine::gameStates = STATE_GAME;
	printw("Carregando...");
	int minas = dificuldade;
	entidade **terreno;
	terreno = (entidade**)malloc(x * sizeof(entidade*));
	for (int i = 0; i < x; i++) {
		terreno[i] = (entidade*)malloc(y * sizeof(entidade));
	}
	srand(time(NULL));
	clear();
	for (int k = 0; k < x; k++) {
		for (int l = 0; l < y; l++) {
			terreno[k][l].valor = VALOR_NADA;
		}
	}
	while (minas > 0) {
		for (int i = 0; i < x; i++) {
 			for (int j = 0; j < y; j++) {
	   			int random = std::rand(); // rand() retorna entre 0 e MAX
	   			if (minas > 0 && random % dificuldade == 0 && terreno[i][j].valor != VALOR_BOMBA) { // chance de <dificuldade>
				      terreno[i][j].valor = VALOR_BOMBA;
							minas--;
					}
					else {
							terreno[i][j].valor = VALOR_NADA;
					}
					terreno[i][j].representacao = '-';
			}
		}
	}
	Engine::tela = (char**)malloc(x * sizeof(char*));
	for (int i = 0; i < x; i++) {
		Engine::tela[i] = (char*)malloc(y * sizeof(char));
	}
	for (int i = 0; i < x; i++) {
		for (int j = 0; j < y; j++) {
			Engine::tela[i][j] = terreno[i][j].representacao;
		}
	}
	Engine::gameIsReady = 1;
}

void Engine::drawTerrain(char** terreno) {
	for (int x = 0; x < Engine::sizeX; x++) {
		for (int y = 0; y < Engine::sizeY; y++) {
			move(x, y);
			printw(&terreno[x][y]);
		}
	}
}

void Engine::readScreen() {
	if (Engine::gameIsReady) {
		Engine::drawTerrain(tela);
	}
}

void Menu::salvar() {
	conteudo[SALVAR] = "-> Salve o jogo quando ele estiver sendo executado!";
	move(SALVAR + 1, 7);
	printw(conteudo[SALVAR].c_str());
}

void Menu::trocar(int tipo) {
	beep();
	Menu::atual = tipo;
	clear();
}

void Menu::sair() {
	beep();
	endwin();
	exit(0);
}

int Menu::carregar() {
	return 0;
}

int Menu::carregar_jogo(std::string filename) {
	std::ifstream file;
	char data[26];
	std::string s;
	file.open(filename, std::ios::in);
	if (!file) {
		return 1;
	}
//	file >> data;
//	Menu::jogar(data[0], data[2]);
	while(file.eof()==0) {
        file >> s;
        std::cout<<s;
	}
	std::cout<<"\n";
	return 0;
}

void Menu::animar() {
	switch(Menu::atual) {
		case PRINCIPAL:
			conteudo[0] = "MENU PRINCIPAL";
			conteudo[1] = "Novo Jogo";
			conteudo[2] = "Salvar";
			conteudo[3] = "Carregar";
			conteudo[4] = "Opcoes";
			conteudo[5] = "Sair";
			break;
		case JOGAR:
			conteudo[0] = "NOVO JOGO";
			conteudo[1] = "Facil           (6x6)";
			conteudo[2] = "Medio           (9x9)";
			conteudo[3] = "Dificil         (16x16)";
			conteudo[4] = "Super Aleatorio (?x?)";
			conteudo[5] = "MENU PRINCIPAL";
			break;
		case SALVAR:
			conteudo[0] = "SALVAR JOGO";
			conteudo[1] = "Digite o nome do arquivo para que o jogo seja salvo... (terminado em .txt)";
			conteudo[2] = "-> ";
			conteudo[3] = "Arquivo do jogo...";
			conteudo[4] = "MENU PRINCIPAL";
			conteudo[5] = "Volte ao menu principal acima...";
			break;
		case CARREGAR:
			conteudo[0] = "CARREGAR JOGO";
			conteudo[1] = "Digite o nome do arquivo para que o jogo seja carregado... (terminado em .txt)";
			conteudo[2] = "-> ";
			conteudo[3] = "Arquivo do jogo...";
			conteudo[4] = "MENU PRINCIPAL";
			conteudo[5] = "Volte ao menu principal acima...";
			break;
		case OPCOES:
			conteudo[0] = "OPCOES";
			conteudo[1] = "Aqui ficariam as opcoes do jogo como audio e etc.";
			conteudo[2] = "Eu queria utilizar OpenAL para fazer audio, mas parece ser uma ma ideia";
			conteudo[3] = "usar libraries externas. Deixo aqui o recado!";
			conteudo[4] = "MENU PRINCIPAL";
			conteudo[5] = "Volte ao menu principal acima...";
			break;
		// ...
	}
	int attr;
	for (int x = 0; x <= 5; x++) {
		if (conteudo[x] == "") { break; }
		move(x + 1, 0);
		if (Menu::opcao == x) {
			if (Engine::gameCounter % 2 == 0) {
				attron(COLOR_PAIR(TEXT_FLASH));
				attron(A_BOLD);
				attr = TEXT_FLASH;
			}
		}
		printw((conteudo[x].c_str()));
		attroff(COLOR_PAIR(attr)); // desliga o attr se nao for hora de animar
		attroff(A_BOLD);
	}
	move(Menu::opcao + 1, 0);
	refresh();
}
