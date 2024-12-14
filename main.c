#include <stdio.h>
#include <stdlib.h>
#include <time.h>

#include <SDL.h>
#include <SDL_image.h>
#include <SDL_mixer.h>
#include <SDL2_gfxPrimitives.h>

#include "header.h"

//les fonctions utilisées dans main.c

Mix_Music* play(const char* s, int pause);
SDL_Texture* initialize_texture_from_file(const char* file_name, SDL_Renderer* renderer);
void jouer(SDL_Renderer* renderer, GAME* game);
void Multiplayer(SDL_Renderer* renderer, GAME* game);
void Singleplayer(SDL_Renderer* renderer, GAME* game);
void game_over_condition(GAME* game, SDL_Renderer* renderer);
void afficher_resultat(SDL_Renderer* renderer, const char* image_path, const char* sound_effect, GAME* game);

void x_gagne(SDL_Renderer* renderer, GAME* game);
void o_gagne(SDL_Renderer* renderer, GAME* game);
void tie(SDL_Renderer* renderer, GAME* game);




Mix_Music* play(const char* s, int pause) {
    if (strcmp(s, "start") == 0) {
        s = "assets/music/start.mp3";
    }
    else if (strcmp(s, "draw") == 0) {
        s = "assets/music/draw.mp3";
    }
    else if (strcmp(s, "effect") == 0) {
        s = "assets/music/click_effect.mp3";
    }
    else if (strcmp(s, "rematch") == 0) {
        s = "assets/music/rematch.mp3";
    }
    else if (strcmp(s, "win") == 0) {
        s = "assets/music/win.mp3";
    }
    else if (strcmp(s, "beep") == 0) {
        s = "assets/music/beep.mp3";
    }
    else if (strcmp(s, "click") == 0) {
        s = "assets/music/click.mp3";
    }

    int result = 0;
    int flags = MIX_INIT_MP3;

    if (SDL_Init(SDL_INIT_AUDIO) < 0) {
        printf("Failed to init SDL\n");
        exit(1);
    }

    if (flags != (result = Mix_Init(flags))) {
        printf("Could not initialize mixer (result: %d).\n", result);
        printf("Mix_Init: %s\n", Mix_GetError());
        exit(1);
    }

    Mix_OpenAudio(22050, AUDIO_S16SYS, 2, 600);
    Mix_Music* music = Mix_LoadMUS(s);

    if (!music) {
        printf("Failed to load music: %s\n", Mix_GetError());
      
    }
    else {
        if (Mix_PlayMusic(music, 1) == -1) {
            printf("Failed to play music: %s\n", Mix_GetError());
            
        }

        SDL_Delay(pause);
        Mix_FreeMusic(music);
    }

    return music;
}


SDL_Texture* initialize_texture_from_file(const char* file_name, SDL_Renderer* renderer) {
    SDL_Surface* image = IMG_Load(file_name);
    SDL_Texture* image_texture = SDL_CreateTextureFromSurface(renderer, image);
    SDL_FreeSurface(image);
    return image_texture;
}



int main(int argc, char* argv[]) {
    SDL_Init(SDL_INIT_VIDEO);

    SDL_Window* window = SDL_CreateWindow("Morpion", SDL_WINDOWPOS_CENTERED, SDL_WINDOWPOS_CENTERED, width, height, SDL_WINDOW_OPENGL);
    SDL_Surface* iconSurface = IMG_Load("assets/images/icon.png");
    SDL_SetWindowIcon(window, iconSurface);
    SDL_Renderer* renderer = SDL_CreateRenderer(window, -1, SDL_RENDERER_ACCELERATED | SDL_RENDERER_PRESENTVSYNC);
    SDL_SetRenderDrawColor(renderer, 0, 0, 0, 255);

    GAME game = {.tableau = {EMPTY, EMPTY, EMPTY,
                              EMPTY, EMPTY, EMPTY,
                              EMPTY, EMPTY, EMPTY },
                .joueur = JOUEUR_X,
                .etat = ETAT_LANCEMENT,
                .type = EMPTY
                };



    jouer(renderer, &game);


    SDL_FreeSurface(iconSurface);
    SDL_DestroyRenderer(renderer);
    SDL_DestroyWindow(window);
    SDL_Quit();

    return 0;
}



void jouer(SDL_Renderer* renderer, GAME* game) {

    SDL_Texture* image_texture = initialize_texture_from_file("assets/images/menu.jpg", renderer);
     
    SDL_Rect texture_destination;
    
    SDL_QueryTexture(image_texture, NULL, NULL, &texture_destination.w, &texture_destination.h);

    
    

    texture_destination.x = 0;
    texture_destination.y = 0;
    

    
    SDL_RenderClear(renderer);

    
    SDL_RenderCopy(renderer, image_texture, NULL, &texture_destination);



    SDL_RenderPresent(renderer);
    int static first = 1;
    if (first) {
        first = 0;
        play("start", 2400);
    }
    
    SDL_Event event;
    while (game->etat != ETAT_FERMETURE) {
        while (SDL_PollEvent(&event)) {
            switch (event.type) {
            case SDL_QUIT:
                game->etat = ETAT_FERMETURE;
                break;                                                                

            case SDL_MOUSEBUTTONDOWN:
            
                    //printf("x = %d\n", event.button.x);
                    //printf("y = %d\n", event.button.y);

                    if (event.button.x >= 243 && event.button.x <= 559 && event.button.y >= 262 && event.button.y <= 289) {
                        play("effect", 500);
                        play("click", 1000);
                        game->type = MULTIPLAYER;
                        Multiplayer(renderer, game);
                    }
                              
                    else if (event.button.x >= 182 && event.button.x <= 615 && event.button.y >= 355 && event.button.y <= 379) {
                        play("effect", 500);
                        play("click", 1000);
                        game->type = SINGLEPLAYER;
                        Singleplayer(renderer, game);

                    }

                    else if (event.button.x >= 304 && event.button.x <= 495 && event.button.y >= 445 && event.button.y <= 468) {
                        play("effect", 1000);
                        game->etat = ETAT_FERMETURE;
                    }

                    break;
            }


     
        }

    }
     IMG_Quit();

}



void Multiplayer(SDL_Renderer* renderer, GAME* game) {

    SDL_Texture* image_texture = initialize_texture_from_file("assets/images/board.jpg", renderer);
  

    SDL_Rect texture_destination;

    SDL_QueryTexture(image_texture, NULL, NULL, &texture_destination.w, &texture_destination.h);

    

    texture_destination.x = 0;
    texture_destination.y = 0;


    SDL_RenderClear(renderer);

    SDL_RenderCopy(renderer, image_texture, NULL, &texture_destination);

    SDL_RenderPresent(renderer);

    SDL_Event e;
    while (game->etat != ETAT_FERMETURE) {
        while (SDL_PollEvent(&e)) {
            switch (e.type) {
            case SDL_QUIT:
                game->etat = ETAT_FERMETURE;
                break;
            case SDL_MOUSEBUTTONDOWN:
                for (int i = 0; i < 3; ++i) {
                    for (int j = 0; j < 3; ++j) {
                        if (e.button.x >= j * CELL_WIDTH && e.button.x <= (j + 1) * CELL_WIDTH && e.button.y >= i * CELL_HEIGHT && e.button.y <= (i + 1) * CELL_HEIGHT) {
                            creer_tableau(renderer, i, j, game);
                        }
                    }
                }

                game_over_condition(game, renderer);
                break;
            case SDL_KEYDOWN:
                switch (e.key.keysym.sym) {
                case SDLK_ESCAPE:
                    compteurx = 1;
                    compteuro = 1;
                    system("cls");
                    reset_game(game);
                    jouer(renderer, game);
                    break;
                }

                break;

            default:
                break;
            }
        }

    }
    IMG_Quit();
}




void Singleplayer(SDL_Renderer* renderer, GAME* game) {
    

    SDL_Texture* image_texture = initialize_texture_from_file("assets/images/board.jpg", renderer);

    
    SDL_Rect texture_destination;

    SDL_QueryTexture(image_texture, NULL, NULL, &texture_destination.w, &texture_destination.h);



    texture_destination.x = 0;
    texture_destination.y = 0;


    
    SDL_RenderClear(renderer);

    SDL_RenderCopy(renderer, image_texture, NULL, &texture_destination);

    SDL_RenderPresent(renderer);


    SDL_Event e;
    while (game->etat != ETAT_FERMETURE) {
        while (SDL_PollEvent(&e)) {
            switch (e.type) {
            case SDL_QUIT:
                game->etat = ETAT_FERMETURE;
                break;


            case SDL_MOUSEBUTTONDOWN:
                for (int i = 0; i < 3; ++i) {
                    for (int j = 0; j < 3; ++j) {
                        if (e.button.x >= j * CELL_WIDTH && e.button.x <= (j + 1) * CELL_WIDTH &&
                            e.button.y >= i * CELL_HEIGHT && e.button.y <= (i + 1) * CELL_HEIGHT) {
                            if (game->tableau[i * 3 + j] == EMPTY) {
                                creer_tableau(renderer, i, j, game);
                                game_over_condition(game, renderer);      // Check for game-over conditions after the player's move
                                if (game->etat != ETAT_FERMETURE) {
                                    makeComputerMove(renderer, game);
                                    game_over_condition(game, renderer);  // Check for game-over conditions after the computer's move
                                }
                             game_over_condition(game, renderer);
                            }
                            else { printf("cette cellule est pleine. \n"); }
                        }
                    }

                }
                break;
            case SDL_KEYDOWN:
                switch (e.key.keysym.sym) {
                case SDLK_ESCAPE:  
                    compteurx = 1;
                    compteuro = 1;
                    system("cls");
                    reset_game(game);
                    jouer(renderer, game);
                    break;
                }
                break;

            default:
                break;
            }
            

        }
    }
    IMG_Quit();
}



void game_over_condition(GAME* game, SDL_Renderer* renderer)
{
    if (verifier_joueur_gagnant(game, JOUEUR_X)) {
        game->etat = JOUEUR_X_GAGNE;
        reset_game(game);
        x_gagne(renderer, game);
    }
    else if (verifier_joueur_gagnant(game, JOUEUR_O)) {
        game->etat = JOUEUR_O_GAGNE;
        reset_game(game);
        o_gagne(renderer, game);
    }
    else if (count_cellule(game->tableau, EMPTY) == 0) {
        game->etat = ETAT_EGALITE;
        reset_game(game);
        tie(renderer, game);
    }
}



void afficher_resultat(SDL_Renderer* renderer, const char* image_path, const char* sound_effect, GAME* game) {

    SDL_Texture* image_texture = initialize_texture_from_file(image_path, renderer);
    
    SDL_Rect texture_destination;

    SDL_QueryTexture(image_texture, NULL, NULL, &texture_destination.w, &texture_destination.h);



    texture_destination.x = 0;
    texture_destination.y = 0;


    SDL_RenderClear(renderer);

    SDL_RenderCopy(renderer, image_texture, NULL, &texture_destination);

    SDL_RenderPresent(renderer);

    play(sound_effect, 1000);

    SDL_Event event;
    while (game->etat != ETAT_FERMETURE) {
        while (SDL_PollEvent(&event)) {
            switch (event.type) {
            case SDL_QUIT:
                game->etat = ETAT_FERMETURE;
                break;
            case SDL_MOUSEBUTTONDOWN:
                //printf("x = %d\n", event.button.x);
                //printf("y = %d\n", event.button.y);

                if (event.button.x >= 99 && event.button.x <= 326  && event.button.y >= 469 && event.button.y <= 518 && game->type == MULTIPLAYER) {
                    system("cls");
                    play("rematch", 1000);
                    Multiplayer(renderer, game);
                    
                }
                else if (event.button.x >= 99 && event.button.x <=  326  && event.button.y >= 469  && event.button.y <= 518 && game->type == SINGLEPLAYER) {
                    system("cls");
                    play("rematch", 1000);
                    Singleplayer(renderer, game);
                    
                }
                break;
            case SDL_KEYDOWN:
                switch (event.key.keysym.sym) {
                case SDLK_ESCAPE:
                    compteurx = 1;
                    compteuro = 1;
                    system("cls");
                    reset_game(game);
                    jouer(renderer, game); 
                    break;
                }

                break;
            }
        }

    }
    IMG_Quit();
}



void x_gagne(SDL_Renderer* renderer, GAME* game) {

    printf("x wins:%d fois \n ", compteurx++);

    afficher_resultat(renderer, "assets/images/x_gagnant.jpg", "win", game);
}



void o_gagne(SDL_Renderer* renderer, GAME* game) {

    printf("O wins:%d fois \n", compteuro++);

    afficher_resultat(renderer, "assets/images/o_gagnant.jpg", "win", game);
}



void tie(SDL_Renderer* renderer, GAME* game) {
    afficher_resultat(renderer, "assets/images/tie.jpg", "draw", game);

}




