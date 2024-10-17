#include <ncurses/ncurses.h>
#include <unordered_map>

struct ColorPair {
    ColorPair(int color_fg, int color_bg);
    bool operator== (const ColorPair &rhs) const;
    int color_fg;
    int color_bg;
};

namespace std {
    template<>
    struct hash<ColorPair> {
        size_t operator() (const ColorPair &cp) const {
            hash<int>()(cp.color_fg) + hash<int>()(cp.color_bg);
        }
    };
}

struct ScopedAttr {
    friend class AttrManager;
    ~ScopedAttr();
private:
    ScopedAttr(NCURSES_COLOR_T attr, NCURSES_COLOR_T prev_attr);
    const NCURSES_COLOR_T m_active_attr;
    const NCURSES_COLOR_T m_prev_attr;
};

struct AttrManager {
    ScopedAttr get_scoped_attr(int color_fg, int color_bg);

    int m_attr_total = 0;
    NCURSES_COLOR_T m_prev_attr = -1;
    std::unordered_map<ColorPair, NCURSES_COLOR_T> m_attr_map;
};