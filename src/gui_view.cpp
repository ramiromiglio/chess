#include <algorithm>
#include "gui_view.h"
#include "spritesheet.h"
#include "assert.h"

GUIView::GUIView() : View::View() {}

GUIView::~GUIView() {
    if (m_window) {
        SDL_DestroyWindow(m_window);
        m_window = nullptr;
        m_pieces.clear();
    }
}

bool GUIView::show() {
    if (SDL_Init (SDL_INIT_VIDEO) == -1) {
        return false;
    }

    SpriteSheet ss("assets/pieces.png", 6, 2);
    if (! ss.is_open()) {
        return false;
    }

    for (int y = 0; y < 2; y++) {    
        for (int x = 0; x < 6; x++) {
            PieceType type;
            switch (x)
            {
            case 0: type = PieceType::R; break;
            case 1: type = PieceType::D; break;
            case 2: type = PieceType::A; break;
            case 3: type = PieceType::C; break;
            case 4: type = PieceType::T; break;
            case 5: type = PieceType::P; break;
            }

            PieceTexture piece(type, y == 0, ss.cut(x, y));
            m_pieces.push_back(piece);
        }
    }

    assert(m_pieces.size() == 12);

    SpriteSheet abc("assets/abc.png", 8, 2);
    if (! abc.is_open()) {
        return false;
    }

    for (int y = 0; y < 2; y++) {    
        for (int x = 0; x < 8; x++) {
            std::shared_ptr<Texture> ptr = abc.cut(x, y);
            if (y == 0) {
                /* Letters */
                m_letters.push_back(ptr);
            }
            else {
                /* Numbers */
                m_numbers.push_back(ptr);
            }
        }
    }

    assert(m_letters.size() == 8);
    assert(m_numbers.size() == 8);

    SDL_Window *window = SDL_CreateWindow(
        "",
        SDL_WINDOWPOS_UNDEFINED,
        SDL_WINDOWPOS_UNDEFINED,
        m_sz,
        m_sz,
        SDL_WINDOW_SHOWN);

    if (! window) {
        // TODO: Shutdown SDL
        return false;
    }
    m_window = window;
    return true;
}

void GUIView::update(const GameState &st) {
    m_game_state = st;
    draw_board();
    draw_board_pieces();
    SDL_UpdateWindowSurface(m_window);
}

GUIView::Event GUIView::get_event() {
    SDL_Event e;
    while (SDL_PollEvent(&e)) {
        if (e.type == SDL_KEYDOWN) {
            SDL_FlushEvents(SDL_FIRSTEVENT, SDL_LASTEVENT);
            return Event(e.key.keysym.sym);
        }
        else
        if (e.type == SDL_WINDOWEVENT && e.window.event == SDL_WINDOWEVENT_CLOSE) {
            m_closed = true;
        }
        else
        if (e.type == SDL_MOUSEBUTTONDOWN) {
            float norm_y = (window_size() - e.button.y) / (float)window_size();
            float norm_x = e.button.x / (float)window_size();
            int y = (int)(norm_y * 9);
            int x = (int)(norm_x * 9);

            x--;

            if (x > 0 && y < 8) {
                if (m_selected_sq) {
                    if (*m_selected_sq != BoardPoint(y, x)) {
                        Move move = Move(*m_selected_sq, BoardPoint(y, x));
                        m_selected_sq = {};
                        SDL_FlushEvents(SDL_FIRSTEVENT, SDL_LASTEVENT);
                        return Event(move);
                    }
                }
                else {
                    const BoardSquare s = m_game_state.board().get(y, x);
                    if (s.occupied && m_game_state.white_turn() == s.piece_is_white) {
                        m_selected_sq = BoardPoint(y, x);
                    }
                }
                SDL_FlushEvents(SDL_FIRSTEVENT, SDL_LASTEVENT);
                return Event(Event::Type::FORCE_REDRAW);
            }
        }
        return Event(Event::Type::NONE);
    }
}

bool GUIView::closed() {
    return m_closed;
}

void GUIView::draw_board() {
    int sz = window_size();

    for (int x = 0; x < 9; x++) {
        int sz = window_size();
        SDL_Rect rect = {};
        rect.x = x * (sz / 9);
        rect.y = 0;
        rect.w = sz / 9;
        rect.h = rect.w;
        m_letters[0]->draw(window_surface(), rect);
    }

    for (int y = 0; y < 9; y++) {
        int sz = window_size();
        SDL_Rect rect = {};
        rect.x = 0;
        rect.y = y * (sz / 9);
        rect.w = sz / 9;
        rect.h = rect.w;
        m_letters[0]->draw(window_surface(), rect);
    }

    for (int r = 0; r < 8; r++) {
        for (int c = 0; c < 8; c++) {
            bool dark_sq = (r % 2 == (c % 2));
            /* +1 porque me salto los casilleros que indican fila y columna */
            fill_sq(r, c+1, dark_sq ? m_color_light : m_color_dark);
        }
    }

    if (m_selected_sq) {
        fill_sq(m_selected_sq->row()+1, m_selected_sq->col()+1, m_color_selected);
    }
}

int GUIView::window_size() {
    int sz;
    SDL_GetWindowSize(m_window, &sz, NULL);
    return sz;
}

SDL_Surface *GUIView::window_surface() {        
    return SDL_GetWindowSurface(m_window);
}

void GUIView::fill_sq(int r, int c, SDL_Color color) {
    int sz = window_size();
    SDL_Rect rect = {};
    rect.x = c * (sz / 9);
    rect.y = (9-1 - r) * (sz / 9);
    rect.w = sz / 9;
    rect.h = rect.w;
    fill_rect(rect, color);
}

void GUIView::fill_rect(SDL_Rect r, SDL_Color c) {
    SDL_FillRect(window_surface(), &r, SDL_MapRGB(window_surface()->format, c.r, c.g, c.b));
}

void GUIView::draw_board_pieces() {
    for (const Iterator &it : m_game_state.board()) {
        if (it.sq_state.occupied) {
            int r = it.row;
            int c = it.col;
            //if (! white_player) {
            //    r = 8-1 - r;
            //    c = 8-1 - c;
            //}
            draw_piece(r, c, it.sq_state.piece_type, it.sq_state.piece_is_white);
        }
    }
}

void GUIView::draw_piece(int r, int c, PieceType type, bool white) {
    c+=1;
    auto it = std::find_if(m_pieces.begin(), m_pieces.end(), [&] (const PieceTexture &texture) {
        return texture.type == type && texture.white == white;
    });
    assert(it != m_pieces.end());

    int sz = window_size();

    SDL_Rect rect = {};
    rect.x = c * (sz / 9);
    rect.y = (9-1 - r) * (sz / 9);
    rect.w = sz / 9;
    rect.h = rect.w;
    it->ptr->draw(window_surface(), rect);    
}