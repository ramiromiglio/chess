#include "gui_controller.h"
#include "game.h"
#include <stdio.h>

static const Uint8 *g_kbd;

GUIController::GUIController(Game &game, std::shared_ptr<View> view) : Controller(game, view) {
    
}

void GUIController::update() {

    if (! g_kbd) {
        g_kbd = SDL_GetKeyboardState(nullptr);
    }

    GUIView::Event ev = view().get_event();
    if (! ev) {
        return;
    }

    if (ev.type() == GUIView::Event::KEYDOWN) {
        if (ev.keycode() == SDLK_s) {
            m_game.save();
        }
        else
        if (ev.keycode() == SDLK_l) {
            m_game.load();
        }
    }
    if (ev.type() == GUIView::Event::FORCE_REDRAW) {
        m_game.update_view();
    }
    else
    if (ev.type() == GUIView::Event::CLOSE_WINDOW) {
        m_game.close();
    }
    else
    if (ev.type() == GUIView::Event::CHESS_MOVE) {
        if (m_game.m_engine.is_valid_move(ev.move())) {
            m_game.m_engine.move(ev.move());
            m_game.update_view();
        }
    }
}

bool GUIController::closed() {
    return view().closed();
}

GUIView &GUIController::view() {
    return static_cast<GUIView&>(*m_view);
}
