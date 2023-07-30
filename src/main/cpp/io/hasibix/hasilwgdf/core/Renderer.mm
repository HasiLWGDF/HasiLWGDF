#include <HasiLWGDF_Core.h>
#import "Renderer.h"

namespace Hasibix::HasiLWGDF::Core
{
    namespace Render
    {
        pair<SDL_Window *, unique_ptr<MetalRenderer>> initMetal(Game::Game *instance)
        {
            SDL_SetHint(SDL_HINT_RENDER_DRIVER, "metal");
            SDL_Window *window = SDL_CreateWindow(instance->getWindow().title, SDL_WINDOWPOS_CENTERED, SDL_WINDOWPOS_CENTERED, instance->getWindow().width, instance->getWindow().height,
                                          SDL_WINDOW_RESIZABLE |
                                              SDL_WINDOW_SHOWN |
                                              SDL_WINDOW_ALLOW_HIGHDPI);
            SDL_Renderer *renderer = SDL_CreateRenderer(window, -1, SDL_RENDERER_PRESENTVSYNC);
            const CAMetalLayer *ctx = (__bridge CAMetalLayer *)SDL_RenderGetMetalLayer(renderer);
            return pair<SDL_Window *, unique_ptr<MetalRenderer>>{window, make_unique<MetalRenderer>(MetalRenderer{ctx, renderer})};
        }
        void renderMetal(double alpha, SDL_Window *window, Game::Game *instance, unique_ptr<MetalRenderer> &renderer)
        {
            @autoreleasepool {
                renderMetalCpp(alpha, window, instance, renderer);
            }
        }
    }
}
