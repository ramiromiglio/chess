#pragma once

#include <SDL2/SDL.h>
#include <SDL2/SDL_image.h>
#include "controller.h"
#include "console_view.h"
#include "board_square.h"

class ConsoleController : public Controller {
public:
    ConsoleController(Game &game, std::shared_ptr<View> view);

    void update() override;
    bool closed() override;
private:
    ConsoleView &view();
    bool m_closed;
    int m_flicker_col = 0;
    int m_flicker_row = 7;
    int m_selected_col = -1;
    int m_selected_row = -1;
    bool m_has_mark = false;
    const BoardSquare &get_board_sq(int col, int row);
};