#include <assert.h>
#include <SDL2/SDL.h>

int main (int argc, char* args[])
{
    /* INICIALIZACAO */
    SDL_Init(SDL_INIT_EVERYTHING);
    SDL_Window* win = SDL_CreateWindow("Colisão entre Objetos",
                         SDL_WINDOWPOS_UNDEFINED,
                         SDL_WINDOWPOS_UNDEFINED,
                         200, 100, SDL_WINDOW_SHOWN
                      );
    SDL_Renderer* ren = SDL_CreateRenderer(win, -1, 0);

    /* EXECUÇÃO */
    SDL_Rect r1 = { 40, 30, 10,10 };
    SDL_Rect r2 = { 140,30, 10,10 };
    int go1 = 1;
    int go2 = 1;
    int espera = 500;
    while (1) {
        SDL_SetRenderDrawColor(ren, 0xFF,0xFF,0xFF,0x00);
        SDL_RenderClear(ren);
        SDL_SetRenderDrawColor(ren, 0x00,0x00,0xFF,0x00);
        SDL_RenderFillRect(ren, &r1);
        SDL_RenderFillRect(ren, &r2);
        SDL_RenderPresent(ren);

        SDL_Event evt;
        Uint32 antes = SDL_GetTicks();
        int isevt = SDL_WaitEventTimeout(&evt, espera);
        if (isevt) {
            espera -= (SDL_GetTicks() - antes);
            if (espera < 0) {
                espera = 0;
            }
            if (evt.type == SDL_MOUSEBUTTONDOWN) {
                SDL_Point m = { evt.button.x, evt.button.y };
                if (SDL_PointInRect(&m, &r1)) {
                    go1 = !go1;
                }
                if (SDL_PointInRect(&m, &r2)) {
                    go2 = !go2;
                }
            }
        } else {
            espera = 500;
            if (go1) {
                r1.x += 2;
            }
            if (go2) {
                r2.x -= 2;
            }
            if (SDL_HasIntersection(&r1, &r2)) {
                go1 = go2 = 0;
            }
        }
    }

    /* FINALIZACAO */
    SDL_DestroyRenderer(ren);
    SDL_DestroyWindow(win);
    SDL_Quit();
}

