#include "Menu.h"

Menu::Menu(SDL_Renderer& renderer, GameObjectStatic& backgroundObject, std::vector<TTF_Font*> &mainFonts)
    : _renderer(renderer), _backgroundObject(backgroundObject), _mainFonts(mainFonts)
{
    initMenuItems();
}

GameState Menu::run()
{
    SDL_Event event;

    while(true){

        while(SDL_PollEvent(&event) != 0){
            if(event.type == SDL_QUIT){
                return GameState::QUIT;
            }
            else if(event.type == SDL_KEYUP){
                switch(event.key.keysym.sym)
                {
                    case SDLK_RETURN:   return GameState::RUNNING;  break;
                    default:                                        break;
                }
            }
        }

        render();
    }
}

void Menu::render()
{
    SDL_SetRenderDrawColor(&_renderer, 0x00, 0x00, 0x00, 0xFF );
    SDL_RenderClear(&_renderer);

    SDL_Rect backgroundRect{0,0,AsteroidConstants::SCREEN_WIDTH, AsteroidConstants::SCREEN_HEIGHT};
    _backgroundObject.render(_renderer, backgroundRect);

    renderMenuItems();
    
    SDL_RenderPresent(&_renderer);
}

void Menu::renderMenuItems()
{
    for(auto &textObject: _textObjectHash){
        textObject.second->render(_renderer);
    }
}

std::unique_ptr<GameObjectStatic> Menu::createStaticTextObject(Point pos, CTexture& tex)
{
    std::unique_ptr<GameObject> pGO = GameObject::Create(ObjectType::STATIC, pos, tex); 
    return static_unique_ptr_cast<GameObjectStatic, GameObject>(std::move(pGO));
}


