#include "MenuNext.h"

MenuNext::MenuNext()
{}

MenuNext::~MenuNext()
{}

void MenuNext::init(SDL_Renderer* renderer, std::vector<TTF_Font*> &mainFonts)
{
    SDL_Color whiteTextColor{255,255,255};
    SDL_Color selectTextColor{245,227,66};

    _prenderer = renderer;

    for(int i = 0; i < static_cast<int>(NextMenuItem::ITEM_TOTAL); i++){
        _textTextureHash.insert(std::make_pair(static_cast<NextMenuItem>(i), CTexture()) );
    }
    _textTextureHash[NextMenuItem::TITLE].loadFromRenderedText(_prenderer, mainFonts[static_cast<int>(FontType::TITLE2)], "LEVLE COMPLETE", whiteTextColor);
    _textTextureHash[NextMenuItem::PRESS_BUTTON].loadFromRenderedText(_prenderer, mainFonts[static_cast<int>(FontType::MENU)], "Press Enter...", whiteTextColor);
   
    Point titlePos{ static_cast<double>((AsteroidConstants::SCREEN_WIDTH - _textTextureHash[NextMenuItem::TITLE].getWidth())/2),
                    static_cast<double>((AsteroidConstants::SCREEN_HEIGHT - _textTextureHash[NextMenuItem::TITLE].getHeight())/3)};
    _textObjectHash[NextMenuItem::TITLE] = GameObject::Create(ObjectType::STATIC, titlePos, &_textTextureHash[NextMenuItem::TITLE]); 
    
    Point playPos{  static_cast<double>((AsteroidConstants::SCREEN_WIDTH - _textTextureHash[NextMenuItem::PRESS_BUTTON].getWidth())/2),
                    static_cast<double>((AsteroidConstants::SCREEN_HEIGHT - _textTextureHash[NextMenuItem::PRESS_BUTTON].getHeight())/2)};
    _textObjectHash[NextMenuItem::PRESS_BUTTON] = GameObject::Create(ObjectType::STATIC, playPos, &_textTextureHash[NextMenuItem::PRESS_BUTTON]); 

}

GameState MenuNext::run()
{
    SDL_Event event;

    while(true){

        while( SDL_PollEvent( &event ) != 0 ) {            
            if( event.type == SDL_QUIT ){
                return GameState::QUIT;
            }
            else if(event.type == SDL_KEYUP){
                switch(event.key.keysym.sym)
                {
                    case SDLK_RETURN:
                        return GameState::RUNNING;
                        break;
                    default:
                        break;
                }
            }
        }

        renderItems();
        
    }
}
        
void MenuNext::renderItems()
{
    SDL_SetRenderDrawColor(_prenderer, 0x00, 0x00, 0x00, 0xFF );
    SDL_RenderClear(_prenderer);

    _textObjectHash[NextMenuItem::TITLE]->render(_prenderer);
    _textObjectHash[NextMenuItem::PRESS_BUTTON]->render(_prenderer);
    
    SDL_RenderPresent(_prenderer);

}