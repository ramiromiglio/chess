#include <assert.h>
#include "console_view.h"
#include "ncurses_utils.h"

ConsoleView::ConsoleView() {}
ConsoleView::~ConsoleView() {}

    static AttrManager attr_manager;
static ScopedAttr scoped_attr(int color_fg, int color_bg) {
    return attr_manager.get_scoped_attr(color_fg, color_bg);
}

bool ConsoleView::show() {
    m_window = initscr();
    raw();
    noecho();
    keypad(stdscr, TRUE);
    start_color();
    curs_set(0);
    cbreak();
    addstr(">> CHESS GAME <<\n\n");
    m_row_offset = getcury((WINDOW*)m_window);
    return true;
}

void ConsoleView::update(const GameState &st) {
    move(m_row_offset, 0);

    for (int i = 0; i < 8; i++) {
        print_row();
        print_col();
    }
    print_row();
    m_last_row = getcury((WINDOW*)m_window);

    static int pch[6] = {0};
    pch[PieceType::R] = 'R';
    pch[PieceType::D] = 'D';
    pch[PieceType::T] = 'T';
    pch[PieceType::A] = 'A';
    pch[PieceType::C] = 'C';
    pch[PieceType::P] = 'P';

    for (const Iterator &it : st.board()) {
        if (it.sq_state.occupied) {
            int ch = pch[(int)it.sq_state.piece_type];            
            print_piece(it.col, it.row, ch, it.sq_state.piece_is_white);
        }
    }    
}

int ConsoleView::getcol(int col) {
    int col_off = 2;
    col = (col * col_off) * 2 + col_off;
}

int ConsoleView::getrow(int row) {
    int row_off = 1;
    row = (row * row_off) * 2 + row_off + m_row_offset;
}

void ConsoleView::print_piece(int col, int row, int ch, bool white) {
    if (white) {
        ScopedAttr _ = scoped_attr(COLOR_BLACK, COLOR_WHITE);
        move(getrow(row), getcol(col));
        addch(ch);
    }
    else {
        move(getrow(row), getcol(col));
        addch(ch);
    }
}

void ConsoleView::print_row() {
    for (int i = 0; i < 8; i++) {
        addstr("+---");
    }
    addch('+');
    addch('\n');
}

void ConsoleView::print_col() {
    for (int i = 0; i < 8; i++) {
        addstr("|   ");
    }
    addch('|');
    addch('\n');
}

void ConsoleView::focus_on_piece(int col, int row) {
    int ch = mvinch(getrow(row), getcol(col)) & A_CHARTEXT;
    ScopedAttr _ = scoped_attr(COLOR_BLACK, COLOR_GREEN);
    addch(ch);
    const char *piece = nullptr;
    switch (ch)
    {
        case 'R': piece = "[REY]"; break;
        case 'D': piece = "[DAMA]"; break;
        case 'T': piece = "[TORRE]"; break;
        case 'A': piece = "[ALFIL]"; break;
        case 'C': piece = "[CABALLO]"; break;
        case 'P': piece = "[PEON]"; break;
        default:  piece = ""; /* casillero vacio */
    }

    mvaddstr(m_last_row + 1, 0, piece);
    clrtoeol();
}

void ConsoleView::reset_board_colors(const GameState &st) {
    ScopedAttr _ = scoped_attr(COLOR_WHITE, COLOR_BLACK);
    update(st);
}

void ConsoleView::mark(int col, int row) {
    int ch = mvinch(getrow(row), getcol(col)) & A_CHARTEXT;
    ScopedAttr _ = scoped_attr(COLOR_GREEN, COLOR_GREEN);
    addch(ch);    
}

void ConsoleView::mark_bg(int col, int row) {
    int ch = mvinch(getrow(row), getcol(col)) & A_CHARTEXT;
    ScopedAttr _ = scoped_attr(COLOR_WHITE, COLOR_GREEN);
    addch(ch);    
}

void ConsoleView::debug(const char *str) {
    mvaddstr(m_last_row + 3, 0, str);
}