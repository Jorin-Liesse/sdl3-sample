#pragma once
#include "patterns/singleton/singleton.h"
#include <SDL3/SDL.h>
#include <SDL3_ttf/SDL_ttf.h>
#include <SDL3_mixer/SDL_mixer.h>
#include <SDL3_image/SDL_image.h>
#include <string>
#include <vector>
#include <math.h>

namespace sge
{
    class Game : public sge::patterns::singleton::Singleton<Game>
    {
        friend class sge::patterns::singleton::Singleton<Game>;

    public:
        Game() = default;
        ~Game();

        bool Init();
        void Run();

        SDL_Window *GetWindow();
        SDL_Renderer *GetRenderer();

        void ShowError(const std::string &title, const std::string &message);

    private:
        bool LoadLibraries();
        void CreateWindow();
        void CreateRenderer();

        void Render();
        void Update();
        void Cleanup();

        SDL_Event *m_event;
        SDL_Window *m_window;
        SDL_Renderer *m_renderer;

        bool m_running;

        int m_infoDataId;
    };
}
