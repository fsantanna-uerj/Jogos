#include <assert.h>
#include <SDL2/SDL.h>
#include <SDL2/SDL_image.h>

int main (int argc, char* args[])
{
    /* INICIALIZACAO */
    SDL_Init(SDL_INIT_EVERYTHING);
    IMG_Init(0);
    SDL_Window* win = SDL_CreateWindow("Recorte",
                         SDL_WINDOWPOS_UNDEFINED,
                         SDL_WINDOWPOS_UNDEFINED,
                         400, 200, SDL_WINDOW_SHOWN
                      );
    SDL_Renderer* ren = SDL_CreateRenderer(win, -1, 0);
    SDL_Texture* img = IMG_LoadTexture(ren, "bird.png");
    assert(img != NULL);

    /* EXECUÇÃO */
    int isup = 1;
    int x = -100;
    while (1) {
        SDL_SetRenderDrawColor(ren, 0xFF,0xFF,0xFF,0x00);
        SDL_RenderClear(ren);
        SDL_Rect r = { x,50, 100,80 };
        SDL_Rect c;
        if (isup) {
            c = (SDL_Rect) {   0,0, 100,80 };
        } else {
            c = (SDL_Rect) { 100,0, 100,80 };
        }
        SDL_RenderCopy(ren, img, &c, &r);
        SDL_RenderPresent(ren);
        SDL_Delay(250);
        x = (x + 10) % 400;
        isup = !isup;
    }

    /* FINALIZACAO */
    SDL_DestroyTexture(img);
    SDL_DestroyRenderer(ren);
    SDL_DestroyWindow(win);
    SDL_Quit();
}
