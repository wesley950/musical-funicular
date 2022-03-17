#pragma once

#include <string>
#include <vector>
#include <unordered_map>

#include <cstdint>

class Input
{
public:
    struct Action
    {
        std::vector<int32_t> key_codes;
    };

    enum KeyCode
    {
        KEY_UNKNOWN = 0,
        KEY_ESCAPE,
        KEY_F1,
        KEY_F2,
        KEY_F3,
        KEY_F4,
        KEY_F5,
        KEY_F6,
        KEY_F7,
        KEY_F8,
        KEY_F9,
        KEY_F10,
        KEY_F11,
        KEY_F12,
        KEY_1, KEY_2, KEY_3, KEY_4, KEY_5, KEY_6, KEY_7, KEY_8, KEY_9, KEY_0,
        KEY_SHIFT, KEY_CONTROL, KEY_SUPER, KEY_ALT, 
        KEY_ENTER, KEY_BACKSPACE, KEY_DELETE, KEY_INSERT, 
        KEY_PAGE_UP, KEY_PAGE_DOWN, KEY_HOME, KEY_END, 
        KEY_UP, KEY_DOWN, KEY_LEFT, KEY_RIGHT, 
        KEY_A, KEY_B, KEY_C, KEY_D, KEY_E, KEY_F, KEY_G, 
        KEY_H, KEY_I, KEY_J, KEY_K, KEY_L, KEY_M, KEY_N, 
        KEY_O, KEY_P, KEY_Q, KEY_R, KEY_S, KEY_T, KEY_U, 
        KEY_V, KEY_W, KEY_X, KEY_Y, KEY_Z, KEY_SPACE
    };

    static void init();
    static void update();

    static void add_action(const std::string& name);
    static void action_add_key(const std::string& name, int32_t key_code);
    static bool is_action_pressed(const std::string& name);
    static bool is_action_just_pressed(const std::string& name);

    static int32_t get_key_code(const std::string& name);

    static void set_key_pressed(int32_t key_code, bool pressed = true);

private:
    static std::unordered_map<std::string, Action> s_Actions;
    static std::unordered_map<std::string, int32_t> s_KeyMap;

    static bool s_Keys[512];
    static bool s_KeysJustPressed[512];
};
