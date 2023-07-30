#import <Renderer.h>

namespace Hasibix::HasiLWGDF::Core
{
    namespace Render
    {
        unique_ptr<MetalRenderer> initMetal(SDL_Window *window, Game::Game *instance)
        {
            SDL_SetHint(SDL_HINT_RENDER_DRIVER, "metal");
            SDL_Renderer *renderer = SDL_CreateRenderer(window, -1, SDL_RENDERER_PRESENTVSYNC);
            const CAMetalLayer *ctx = (__bridge CAMetalLayer *)SDL_RenderGetMetalLayer(renderer);
            return make_unique<MetalRenderer>(MetalRenderer{ctx, renderer});
        }
        void renderMetal(double alpha, SDL_Window *window, Game::Game *instance, unique_ptr<MetalRenderer> renderer)
        {
            @autoreleasepool {
                renderMetalCpp(alpha, window, instance, renderer);
            }
        }
    }
}
