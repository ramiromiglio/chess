#include "ncurses_utils.h"

ColorPair::ColorPair(int color_fg, int color_bg) :
    color_fg(color_fg), color_bg(color_bg) {}

bool ColorPair::operator== (const ColorPair &rhs) const {
    return color_fg == rhs.color_fg && color_bg == rhs.color_bg;
}

ScopedAttr::ScopedAttr(NCURSES_COLOR_T attr, NCURSES_COLOR_T prev_attr) : m_active_attr(attr), m_prev_attr(prev_attr)
{
    attron(COLOR_PAIR(m_active_attr));
}
ScopedAttr::~ScopedAttr() {
    attroff(COLOR_PAIR(m_active_attr));
    if (m_prev_attr != -1) {
        attron(COLOR_PAIR(m_prev_attr));
    }
}

ScopedAttr AttrManager::get_scoped_attr(int color_fg, int color_bg) {
    ColorPair cp(color_fg, color_bg);
    if (m_attr_map.find(cp) == m_attr_map.end()) {
        NCURSES_COLOR_T attr = ++m_attr_total;
        init_pair(attr, color_fg, color_bg);
        m_attr_map[cp] = attr;
    }

    NCURSES_COLOR_T prev = m_prev_attr;
    m_prev_attr = m_attr_map[cp];
    return ScopedAttr(m_attr_map[cp], prev);
}