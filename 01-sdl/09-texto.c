#include <assert.h>
#include <SDL2/SDL.h>
#include <SDL2/SDL_ttf.h>

int main (int argc, char* args[])
{
    /* INICIALIZACAO */
    SDL_Init(SDL_INIT_EVERYTHING);
    TTF_Init();
    SDL_Window* win = SDL_CreateWindow("Texto",
                         SDL_WINDOWPOS_UNDEFINED,
                         SDL_WINDOWPOS_UNDEFINED,
                         400, 200, SDL_WINDOW_SHOWN
                      );
    SDL_Renderer* ren = SDL_CreateRenderer(win, -1, 0);

    TTF_Font* fnt = TTF_OpenFont("tiny.ttf", 20);
    assert(fnt != NULL);
    SDL_Color clr = {0xFF,0x00,0x00,0xFF};
    SDL_Surface* sfc = TTF_RenderText_Blended(fnt, "ola mundo", clr);
    assert(sfc != NULL);
    SDL_Texture* txt = SDL_CreateTextureFromSurface(ren, sfc);
    assert(txt != NULL);
    SDL_FreeSurface(sfc);

    /* EXECUÇÃO */
    SDL_SetRenderDrawColor(ren, 0xFF,0xFF,0xFF,0x00);
    SDL_RenderClear(ren);
    SDL_Rect r = { 50,50, 200,80 };
    SDL_RenderCopy(ren, txt, NULL, &r);
    SDL_RenderPresent(ren);
    SDL_Delay(5000);

    /* FINALIZACAO */
    SDL_DestroyTexture(txt);
    TTF_CloseFont(fnt);
    SDL_DestroyRenderer(ren);
    SDL_DestroyWindow(win);
    TTF_Quit();
    SDL_Quit();
}
