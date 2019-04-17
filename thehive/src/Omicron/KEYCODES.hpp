#ifndef _KEYCODES_H
#define _KEYCODES_H

#include <GL/glew.h>
#include <GLFW/glfw3.h>


namespace gg{
    enum KEYCODE{
        F1 = GLFW_KEY_F1,

        A = GLFW_KEY_A,
        B = GLFW_KEY_B,
        D = GLFW_KEY_D,
        C = GLFW_KEY_C,
        E = GLFW_KEY_E,
        F = GLFW_KEY_F,
        G = GLFW_KEY_G,
        H = GLFW_KEY_H,
        I = GLFW_KEY_I,
        J = GLFW_KEY_J,
        K = GLFW_KEY_K,
        L = GLFW_KEY_L,
        M = GLFW_KEY_M,
        N = GLFW_KEY_N,
        O = GLFW_KEY_O,
        P = GLFW_KEY_P,
        Q = GLFW_KEY_Q,
        R = GLFW_KEY_R,
        S = GLFW_KEY_S,
        T = GLFW_KEY_T,
        U = GLFW_KEY_U,
        V = GLFW_KEY_V,
        W = GLFW_KEY_W,
        X = GLFW_KEY_X,
        Y = GLFW_KEY_Y,
        Z = GLFW_KEY_Z,

        LCONTROL = GLFW_KEY_LEFT_CONTROL,
        LSHIFT = GLFW_KEY_LEFT_SHIFT,
        ALT = GLFW_KEY_LEFT_ALT,
        SPACEBAR = GLFW_KEY_SPACE,

        ENTER = GLFW_KEY_ENTER,
        ESC = GLFW_KEY_ESCAPE,

        _0 = GLFW_KEY_0,
        _1 = GLFW_KEY_1,
        _2 = GLFW_KEY_2,
        _3 = GLFW_KEY_3,
        _4 = GLFW_KEY_4,
        _5 = GLFW_KEY_5,
        _6 = GLFW_KEY_6,
        _7 = GLFW_KEY_7,
        _8 = GLFW_KEY_8,
        _9 = GLFW_KEY_9,

        KEYCOUNT
    };
}

#endif
