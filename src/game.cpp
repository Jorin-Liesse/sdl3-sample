#pragma region Includes / Defines

#include "game.h"

// using namespace sge::gameObjects;
using namespace std;
using namespace sge;

#pragma endregion

#pragma region Constructor / Destructor

Game::~Game()
{
    Cleanup();
}

#pragma endregion

#pragma region Init / Cleanup

bool Game::Init()
{
    m_event = nullptr;
    m_window = nullptr;
    m_renderer = nullptr;

    m_running = true;

    LoadLibraries();

    // AssetsHandler::GetInstance().Init();

    // m_infoDataId = AssetsHandler::GetInstance().UsedJson("assets/data/info.json");

    CreateWindow();
    CreateRenderer();

    return true;
}

void Game::Cleanup()
{
    if (m_renderer)
        SDL_DestroyRenderer(m_renderer);
    if (m_window)
        SDL_DestroyWindow(m_window);

    MIX_Quit();
    TTF_Quit();
    SDL_Quit();

    delete m_renderer;
    delete m_window;
    delete m_event;
}

#pragma endregion

#pragma region Engine Methods

void Game::Run()
{
    m_event = new SDL_Event();

#ifdef __EMSCRIPTEN__
    emscripten_set_main_loop_arg(
        [](void *arg)
        {
            Game *game = static_cast<Game *>(arg);
            if (game->m_running)
            {
                game->Update();
                game->Render();
            }
            else
            {
                game->Cleanup();
                emscripten_cancel_main_loop();
            }
        },
        this,
        0,
        1);
#else
    while (m_running)
    {
        Update();
        Render();
    }

    Cleanup();
#endif
}

void Game::Update()
{
    while (SDL_PollEvent(m_event))
    {
        if (m_event->type == SDL_EVENT_QUIT)
            m_running = false;
    }
}

void Game::Render()
{
    SDL_SetRenderDrawColor(m_renderer, 0, 0, 0, 255);
    SDL_RenderClear(m_renderer);
    SDL_RenderPresent(m_renderer);
}

#pragma endregion

#pragma region Private Methods

bool Game::LoadLibraries()
{
    if (not SDL_Init(SDL_INIT_VIDEO | SDL_INIT_AUDIO))
    {
        ShowError("SDL_Init Error");
        return false;
    }

    if (not TTF_Init())
    {
        ShowError("TTF_Init Error");
        SDL_Quit();
        return false;
    }

    if (not MIX_Init())
    {
        ShowError("MIX_Init Error");
        TTF_Quit();
        SDL_Quit();
        return false;
    }

    return true;
}

void Game::CreateWindow()
{
    // cJSON *infoJson = AssetsHandler::GetInstance().GetJson(m_infoDataId);
    // string title = cJSON_GetStringValue(cJSON_GetObjectItem(infoJson, "title"));

    m_window = SDL_CreateWindow("SDL Minimal Sample", 500, 500, SDL_WINDOW_HIGH_PIXEL_DENSITY);
    if (not m_window)
        ShowError("SDL_CreateWindow Error");

    SDL_Surface *icon = IMG_Load("assets/icons/icon.png");
    if (not icon)
        ShowError("Icon Load Error");

    SDL_SetWindowIcon(m_window, icon);
    SDL_DestroySurface(icon);
}

void Game::CreateRenderer()
{
    m_renderer = SDL_CreateRenderer(m_window, NULL);
    if (not m_renderer)
        ShowError("SDL_CreateRenderer Error");
}

#pragma endregion

#pragma region Public Methods

void Game::ShowError(const string &title, const string &message)
{
    if (not message.empty())
        SDL_ShowSimpleMessageBox(SDL_MESSAGEBOX_ERROR, title.c_str(), message.c_str(), nullptr);
    else
        SDL_ShowSimpleMessageBox(SDL_MESSAGEBOX_ERROR, title.c_str(), SDL_GetError(), nullptr);
}

#pragma endregion

#pragma region Getters / Setters

SDL_Window *Game::GetWindow()
{
    return m_window;
}
SDL_Renderer *Game::GetRenderer()
{
    return m_renderer;
}

#pragma endregion
