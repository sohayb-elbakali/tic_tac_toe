
#define N      3
#define width  800
#define height 600
#define CELL_WIDTH  (width / N)
#define CELL_HEIGHT (height / N)

#define EMPTY    0
#define	JOUEUR_X 1
#define JOUEUR_O 2

#define ETAT_LANCEMENT 3
#define ETAT_FERMETURE 4
#define JOUEUR_X_GAGNE 5
#define JOUEUR_O_GAGNE 6
#define ETAT_EGALITE   7
#define MULTIPLAYER    8
#define SINGLEPLAYER   9



typedef struct GAME {
	int tableau[N * N];
	int joueur;
	int etat;
    int type;
}GAME;

int static compteurx = 1;
int static compteuro = 1;
const SDL_Color COULEUR_X = { .r = 0, .g = 255, .b = 255 };
const SDL_Color COULEUR_O = { .r = 255, .g = 0, .b = 0};

//les fonctions utilisées dans header.h
Mix_Music* play(const char* s, int pause);
void render_x(SDL_Renderer* renderer, int ligne, int colonne, const SDL_Color* couleur);
void render_o(SDL_Renderer* renderer, int ligne, int colonne, const SDL_Color* couleur);
void changer_joueur(GAME* game);
void creer_tableau(SDL_Renderer* renderer, int ligne, int colonne, GAME* game);
void makeComputerMove(SDL_Renderer* renderer, GAME* game);
int verifier_joueur_gagnant(GAME* game, int player);
int  count_cellule(const int* tableau, int cell);
void reset_game(GAME* game);



// Rend une représentation graphique de la croix (symbole du joueur X)
void render_x(SDL_Renderer* renderer, int ligne, int colonne, const SDL_Color* couleur)
{
    const float cote_demi_boite = fmin(CELL_WIDTH, CELL_HEIGHT) * 0.25;
    const float centre_x = CELL_WIDTH * 0.5 + colonne * CELL_WIDTH;
    const float centre_y = CELL_HEIGHT * 0.5 + ligne * CELL_HEIGHT;
    thickLineRGBA(renderer,
        centre_x - cote_demi_boite,
        centre_y - cote_demi_boite,
        centre_x + cote_demi_boite,
        centre_y + cote_demi_boite,
        10,
        couleur->r,
        couleur->g,
        couleur->b,
        255);
    thickLineRGBA(renderer,
        centre_x + cote_demi_boite,
        centre_y - cote_demi_boite,
        centre_x - cote_demi_boite,
        centre_y + cote_demi_boite,
        10,
        couleur->r,
        couleur->g,
        couleur->b,
        255);
    SDL_RenderPresent(renderer);
}


// Rend une représentation graphique du cercle (symbole du joueur O)
void render_o(SDL_Renderer* renderer, int ligne, int colonne, const SDL_Color* couleur)
{
    const float cote_demi_boite = fmin(CELL_WIDTH, CELL_HEIGHT) * 0.25;
    const float centre_x = CELL_WIDTH  * 0.5 + colonne *  CELL_WIDTH;
    const float centre_y = CELL_HEIGHT * 0.5 + ligne   *  CELL_HEIGHT;

    filledCircleRGBA(renderer,
        centre_x, centre_y, cote_demi_boite + 5,
        couleur->r, couleur->g, couleur->b, 255);
    filledCircleRGBA(renderer,
        centre_x, centre_y, cote_demi_boite - 5,
        0, 0, 0, 255);
    SDL_RenderPresent(renderer);
}



void changer_joueur(GAME* game)
{

    if (game->joueur == JOUEUR_X) {
        play("beep", 1200);  
        game->joueur = JOUEUR_O;    
    }
    else if (game->joueur == JOUEUR_O) {
        play("beep", 1200);
        game->joueur = JOUEUR_X;    
    }
}


//  Gère la logique de création du tableau de jeu en fonction de la cellule choisie par le joueur

void creer_tableau(SDL_Renderer* renderer, int ligne, int colonne, GAME* game) {
    switch (game->tableau[ligne * N + colonne]) {
    case EMPTY:
        if (game->joueur == JOUEUR_X) {
            game->tableau[ligne * N + colonne] = JOUEUR_X;
            render_x(renderer, ligne, colonne, &COULEUR_X);
            changer_joueur(game);
            break;
        }
        else if (game->joueur == JOUEUR_O) {
            game->tableau[ligne * N + colonne] = JOUEUR_O;
            render_o(renderer, ligne, colonne, &COULEUR_O);
            changer_joueur(game);
            break;
        }




    case JOUEUR_X:
        printf("cette cellule est pleine.\n");
        break;

    case JOUEUR_O:
        printf("cette cellule est pleine.\n");
        break;
    }
}


// Effectue un mouvement aléatoire pour le joueur O (ordinateur)
void makeComputerMove(SDL_Renderer* renderer, GAME* game) {

    srand(time(NULL));
    int i, j;
    do {
        i = rand() % 3;
        j = rand() % 3;
    } while (game->tableau[i * 3 + j] != EMPTY );

    //creer_tableau(renderer, i, j, game) ; on peut remplacer les 3 ligne ce dessus par cette fonction . mais ça peut elevé la complexité .

    game->tableau[i* N + j] = JOUEUR_O;
    render_o(renderer, i, j, &COULEUR_O);
    changer_joueur(game);

    
}



// Vérifie si le joueur spécifié (X ou O) a gagnée le jeu
int verifier_joueur_gagnant(GAME* game, int player)
{
    int count_ligne = 0  ;
    int count_colonne = 0;
    int diag1_count = 0  ;
    int diag2_count = 0  ;

    for (int i = 0; i < N; ++i) {

        for (int j = 0; j < N; ++j) {

            if (game->tableau[i * N + j] == player) {
                count_ligne++;
            }
            if (game->tableau[j * N + i] == player) {
                count_colonne++;
            }
        }

        if (count_ligne == N || count_colonne == N) {
            return 1;
        }

        count_ligne =   0  ;
        count_colonne = 0;

        if (game->tableau[i * N + i] == player) {
            diag1_count++;
        }

        if (game->tableau[i * N + N - i - 1] == player) {
            diag2_count++;
        }
       
    }

     if (diag1_count == N || diag2_count == N) { return 1; }
     else                                      { return 0; }
}



int count_cellule(const int* tableau, int cell)
{
    int count = 0;

    for (int i = 0; i < N * N; ++i) {
        if (tableau[i] == cell) {
            count++;
        }
    }

    return count;
}



// Réinitialise les valeurs du jeu pour le redémarrage
void reset_game(GAME* game)
{
    game->joueur = JOUEUR_X;
    game->etat = ETAT_LANCEMENT;
    for (int i = 0; i < N * N; ++i) {
        game->tableau[i] = EMPTY;
    }
}

