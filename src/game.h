#pragma once

#include <string>
#include <memory>
#include "engine.h"
#include "game_state.h"
#include "gui_controller.h"
#include "console_controller.h"

class Game {
public:
    friend class GUIController;
    friend class ConsoleController;
    Game();
    void run();
    void save();
    void load();
private:
    void update_view();
    void close();
    std::shared_ptr<View> m_view;
    std::shared_ptr<Controller> m_controller;
    Engine m_engine;
};