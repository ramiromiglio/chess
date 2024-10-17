#pragma once

#include <SDL2/SDL.h>
#include <SDL2/SDL_image.h>
#include <vector>
#include "utils.h"
#include "view.h"
#include "piece.h"
#include "board_point.h"
#include "move.h"
#include <memory>
#include "texture.h"

class GUIView : public View {
public:
    struct PieceTexture {
        PieceTexture(PieceType type, bool white, std::shared_ptr<Texture> ptr) :
            type(type),
            white(white),
            ptr(ptr) {}
        PieceType type = PieceType::NONE;
        bool white = false;
        std::shared_ptr<Texture> ptr;
    };

    struct Event {
        enum Type { CHESS_MOVE, CLOSE_WINDOW, FORCE_REDRAW, KEYDOWN, NONE };
        Event() { m_type = Type::NONE; }
        Event(Type type) { m_type = type; }
        Event(Move move) {
            m_type = Type::CHESS_MOVE;
            m_move = move;
        }
        Event(SDL_Keycode keycode) {
            m_type = Type::KEYDOWN;
            m_keycode = keycode;
        }
        Type type() { return m_type; }
        Move move() { return m_move; }
        SDL_Keycode keycode() { return m_keycode; }
        operator bool() {
            return m_type != Type::NONE;
        }
    private:
        Type m_type = Type::NONE;
        Move m_move;
        SDL_Keycode m_keycode;
    };

    GUIView();
    ~GUIView();
    bool show() override;
    void update(const GameState &st) override;
    GUIView::Event get_event();
    bool closed();
private:
    std::optional<Move> process_click(SDL_Event &e);
    void draw_board();
    int window_size();
    SDL_Surface *window_surface();
    void fill_sq(int r, int c, SDL_Color color);
    void fill_rect(SDL_Rect r, SDL_Color c);
    void draw_board_pieces();
    void draw_piece(int r, int c, PieceType type, bool white);    
    SDL_Window *m_window = nullptr;
    std::vector<PieceTexture> m_pieces;
    std::vector<std::shared_ptr<Texture>> m_numbers;
    std::vector<std::shared_ptr<Texture>> m_letters;
    std::optional<BoardPoint> m_selected_sq;
    const SDL_Color m_color_light = {0xFF, 0xCF, 0x9F, 0xFF};
    const SDL_Color m_color_dark = {0xD2, 0x8C, 0x45, 0xFF};
    const SDL_Color m_color_selected = {0xFF, 0x00, 0x00, 0xFF};
    const int m_sz = 512;
    bool m_closed = false;
    GameState m_game_state;
};