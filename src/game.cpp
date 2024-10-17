#include <SDL2/SDL.h>
#include <SDL2/SDL_net.h>
#include <memory>
#include "game.h"
#include "game_state.h"
//#include "gui_view.h"
//#include "gui_controller.h"
#include "console_view.h"
#include "console_controller.h"
#include <iostream>

Game::Game() {}

void Game::run() {
    m_view = std::shared_ptr<View>(new GUIView());
    m_controller = std::shared_ptr<Controller>(new GUIController(*this /* `Game` acts like the model */, m_view));

    //m_view = std::shared_ptr<View>(new ConsoleView());
    //m_controller = std::shared_ptr<Controller>(
    //    new ConsoleController(*this /* `Game` acts like the model */, m_view));

    if (m_view->show()) {
        update_view();
        while (! m_controller->closed()) {
            m_controller->update();
        }
    }
}

void Game::update_view() {
    m_view->update(m_engine.get_state());
}

void Game::save() {
    m_engine.get_state().save_to_file("board.json");
}

void Game::load() {
    GameState state; state.load_from_file("board.json");
    m_engine.set_state(state);
    update_view();
}

void Game::close() {
    
}