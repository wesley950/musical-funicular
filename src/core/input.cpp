#include "input.hpp"

std::unordered_map<std::string, Input::Action> Input::s_Actions;
std::unordered_map<std::string, int32_t> Input::s_KeyMap;

bool Input::s_Keys[512];
bool Input::s_KeysJustPressed[512];

void Input::init()
{
    s_KeyMap = {
        {"Escape", KEY_ESCAPE},
        {"F1", KEY_F1},
        {"F2", KEY_F2},
        {"F3", KEY_F3},
        {"F4", KEY_F4},
        {"F5", KEY_F5},
        {"F6", KEY_F6},
        {"F7", KEY_F7},
        {"F8", KEY_F8},
        {"F9", KEY_F9},
        {"F10", KEY_F10},
        {"F11", KEY_F11},
        {"F12", KEY_F12},
        {"1", KEY_1},
        {"2", KEY_2},
        {"3", KEY_3},
        {"4", KEY_4},
        {"5", KEY_5},
        {"6", KEY_6},
        {"7", KEY_7},
        {"8", KEY_8},
        {"9", KEY_9},
        {"0", KEY_0},
        {"Shift", KEY_SHIFT},
        {"Control", KEY_CONTROL},
        {"Super", KEY_SUPER},
        {"Alt", KEY_ALT},
        {"Enter", KEY_ENTER},
        {"Backspace", KEY_BACKSPACE},
        {"Delete", KEY_DELETE},
        {"Insert", KEY_INSERT},
        {"PageUp", KEY_PAGE_UP},
        {"PageDown", KEY_PAGE_DOWN},
        {"Home", KEY_HOME},
        {"End", KEY_END},
        {"Up", KEY_UP},
        {"Down", KEY_DOWN},
        {"Left", KEY_LEFT},
        {"Right", KEY_RIGHT},
        {"A", KEY_A},
        {"B", KEY_B},
        {"C", KEY_C},
        {"D", KEY_D},
        {"E", KEY_E},
        {"F", KEY_F},
        {"G", KEY_G},
        {"H", KEY_H},
        {"I", KEY_I},
        {"J", KEY_J},
        {"K", KEY_K},
        {"L", KEY_L},
        {"M", KEY_M},
        {"N", KEY_N},
        {"O", KEY_O},
        {"P", KEY_P},
        {"Q", KEY_Q},
        {"R", KEY_R},
        {"S", KEY_S},
        {"T", KEY_T},
        {"U", KEY_U},
        {"V", KEY_V},
        {"W", KEY_W},
        {"X", KEY_X},
        {"Y", KEY_Y},
        {"Z", KEY_Z}};

    for (int i = 0; i < 512; i++)
    {
        s_Keys[i] = false;
        s_KeysJustPressed[i] = false;
    }
}

void Input::update()
{
    for (int i = 0; i < 512; i++)
    {
        s_KeysJustPressed[i] = false;
    }
}

void Input::add_action(const std::string &name)
{
    s_Actions[name] = {};
}

void Input::action_add_key(const std::string &name, int32_t key_code)
{
    s_Actions.at(name).key_codes.push_back(key_code);
}

bool Input::is_action_pressed(const std::string &name)
{
    Input::Action &action = s_Actions.at(name);
    for (int32_t key_code : action.key_codes)
    {
        if (s_Keys[key_code])
            return true;
    }
    return false;
}

bool Input::is_action_just_pressed(const std::string &name)
{
    Input::Action &action = s_Actions.at(name);
    for (int32_t key_code : action.key_codes)
    {
        if (s_KeysJustPressed[key_code])
            return true;
    }
    return false;
}

int32_t Input::get_key_code(const std::string &name)
{
    return s_KeyMap[name];
}

void Input::set_key_pressed(int32_t key_code, bool pressed)
{
    s_Keys[key_code] = pressed;
    s_KeysJustPressed[key_code] = pressed;
}
