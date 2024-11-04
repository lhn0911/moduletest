#include <SDL2/SDL.h>
#include <iostream>

int main(int argc, char *argv[])
{
    if (SDL_Init(SDL_INIT_VIDEO) != 0)
    {
        std::cout << "SDL_Init Error: " << SDL_GetError() << std::endl;
        return 1;
    }

    SDL_Window *window = SDL_CreateWindow("Move Cursor with Arrow Keys",
                                          SDL_WINDOWPOS_CENTERED, SDL_WINDOWPOS_CENTERED,
                                          800, 600, SDL_WINDOW_SHOWN);
    if (window == nullptr)
    {
        std::cout << "SDL_CreateWindow Error: " << SDL_GetError() << std::endl;
        SDL_Quit();
        return 1;
    }

    SDL_Renderer *renderer = SDL_CreateRenderer(window, -1, SDL_RENDERER_ACCELERATED | SDL_RENDERER_PRESENTVSYNC);
    if (renderer == nullptr)
    {
        SDL_DestroyWindow(window);
        std::cout << "SDL_CreateRenderer Error: " << SDL_GetError() << std::endl;
        SDL_Quit();
        return 1;
    }

    int cursorX = 400, cursorY = 300; // Vị trí ban đầu của con trỏ
    int cursorSize = 10;              // Kích thước của con trỏ
    bool running = true;

    while (running)
    {
        SDL_Event event;
        while (SDL_PollEvent(&event))
        {
            if (event.type == SDL_QUIT)
            {
                running = false;
            }
            else if (event.type == SDL_KEYDOWN)
            {
                // Xử lý các phím điều hướng
                switch (event.key.keysym.sym)
                {
                case SDLK_UP:
                    cursorY -= 50;
                    break;
                case SDLK_DOWN:
                    cursorY += 50;
                    break;
                case SDLK_LEFT:
                    cursorX -= 50;
                    break;
                case SDLK_RIGHT:
                    cursorX += 50;
                    break;
                }
            }
        }

        // Giới hạn vị trí của con trỏ trong cửa sổ
        if (cursorX < 0)
            cursorX = 0;
        if (cursorY < 0)
            cursorY = 0;
        if (cursorX > 800 - cursorSize)
            cursorX = 800 - cursorSize;
        if (cursorY > 600 - cursorSize)
            cursorY = 600 - cursorSize;

        // Xóa màn hình
        SDL_SetRenderDrawColor(renderer, 0, 0, 0, 255); // Màu nền đen
        SDL_RenderClear(renderer);

        // Vẽ con trỏ
        SDL_Rect cursorRect = {cursorX, cursorY, cursorSize, cursorSize};
        SDL_SetRenderDrawColor(renderer, 255, 0, 0, 255); // Màu đỏ cho con trỏ
        SDL_RenderFillRect(renderer, &cursorRect);

        // Hiển thị kết quả lên màn hình
        SDL_RenderPresent(renderer);

        SDL_Delay(16);
    }

    SDL_DestroyRenderer(renderer);
    SDL_DestroyWindow(window);
    SDL_Quit();

    return 0;
}
