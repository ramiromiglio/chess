#include <ncurses/ncurses.h>
#include <cmath>
#include "console_controller.h"
#include "game.h"

ConsoleController::ConsoleController(Game &game, std::shared_ptr<View> view) : Controller::Controller(game, view) {}

void ConsoleController::update() {
    int ch = getch();

    view().reset_board_colors(m_game.m_engine.get_state());

    switch (ch) {
        case 'q':
            m_closed = true;
            break;
        case KEY_LEFT:
            m_flicker_col--;
            break;
        case KEY_RIGHT:
            m_flicker_col++;
            break;
        case KEY_DOWN:
            m_flicker_row++;
            break;
        case KEY_UP:
            m_flicker_row--;
            break;
        case KEY_ENTER:
        case '\n': {
            if (m_has_mark) {
                BoardPoint from(m_selected_row, m_selected_col);
                BoardPoint to(m_flicker_row, m_flicker_col);

                if (m_game.m_engine.is_valid_move(from, to)) {
                    m_game.m_engine.move(from, to);
                    m_has_mark = false;
                    m_game.update_view();
                    break;
                }
            }

            if (get_board_sq(m_flicker_col, m_flicker_row).piece_is_white == m_game.m_engine.is_white_turn()) {
                m_selected_row = m_flicker_row;
                m_selected_col = m_flicker_col;
                m_has_mark = true;
            }        
            break;
        }
    }

    m_flicker_col = std::min(std::max(m_flicker_col, 0), 7);
    m_flicker_row = std::min(std::max(m_flicker_row, 0), 7);

    if (m_has_mark) {
        view().mark(m_selected_col, m_selected_row);

        const BoardPoint from (
            m_selected_row,
            m_selected_col
        );
            
        for (const Iterator &it : m_game.m_engine.board()) {
            Move move(
                from, BoardPoint(it.row, it.col)
            );

            if (m_game.m_engine.is_valid_move (move)) {
                view().mark_bg(it.col, it.row);
            }
        }
    }

    view().focus_on_piece(
        m_flicker_col,
        m_flicker_row);    
}

bool ConsoleController::closed() {
    return m_closed;
}

ConsoleView &ConsoleController::view() {
    return static_cast<ConsoleView&>(*m_view);
}

const BoardSquare &ConsoleController::get_board_sq(int col, int row) {
    return m_game.m_engine.board().get(row, col);
}