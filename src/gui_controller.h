#pragma once

#include <SDL2/SDL.h>
#include <SDL2/SDL_image.h>
#include "controller.h"
#include "gui_view.h"

class GUIController : public Controller {
public:
    GUIController(Game &game, std::shared_ptr<View> view);

    void update() override;
    bool closed() override;
private:
    GUIView &view();
};