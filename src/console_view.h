#pragma once

#include <SDL2/SDL.h>
#include <SDL2/SDL_image.h>
#include "view.h"

class ConsoleView : public View {
public:
    friend class ConsoleController;
    struct Event {};
    ConsoleView();
    ~ConsoleView();
    bool show() override;
    void update(const GameState &st) override;
    bool closed();
    ConsoleView::Event get_event();
private:
    int getcol(int col);
    int getrow(int row);
    void print_row();
    void print_col();
    void print_piece(int col, int row, int ch, bool white);
    void reset_board_colors(const GameState &st);
    void focus_on_piece(int col, int row);
    void mark(int col, int row);
    void mark_bg(int col, int row);
    void debug(const char *str);
    void *m_window = nullptr;
    int m_row_offset = 0;
    int m_last_row = 0;
};
