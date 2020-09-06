#pragma once
#define DCORE_RELEASE 0
/*! @brief The key or mouse button was pressed.
 *
 *  The key or mouse button was pressed.
 *
 *  @ingroup input
 */
#define DCORE_PRESS 1
/*! @brief The key was held down until it repeated.
 *
 *  The key was held down until it repeated.
 *
 *  @ingroup input
 */
#define DCORE_REPEAT 2
/*! @} */

/*! @defgroup hat_state Joystick hat states
 *  @brief Joystick hat states.
 *
 *  See [joystick hat input](@ref joystick_hat) for how these are used.
 *
 *  @ingroup input
 *  @{ */
#define DCORE_HAT_CENTERED 0
#define DCORE_HAT_UP 1
#define DCORE_HAT_RIGHT 2
#define DCORE_HAT_DOWN 4
#define DCORE_HAT_LEFT 8
#define DCORE_HAT_RIGHT_UP (DCORE_HAT_RIGHT | DCORE_HAT_UP)
#define DCORE_HAT_RIGHT_DOWN (DCORE_HAT_RIGHT | DCORE_HAT_DOWN)
#define DCORE_HAT_LEFT_UP (DCORE_HAT_LEFT | DCORE_HAT_UP)
#define DCORE_HAT_LEFT_DOWN (DCORE_HAT_LEFT | DCORE_HAT_DOWN)
/*! @} */

/*! @defgroup keys Keyboard keys
 *  @brief Keyboard key IDs.
 *
 *  See [key input](@ref input_key) for how these are used.
 *
 *  These key codes are inspired by the _USB HID Usage Tables v1.12_ (p. 53-60),
 *  but re-arranged to map to 7-bit ASCII for printable keys (function keys are
 *  put in the 256+ range).
 *
 *  The naming of the key codes follow these rules:
 *   - The US keyboard layout is used
 *   - Names of printable alpha-numeric characters are used (e.g. "A", "R",
 *     "3", etc.)
 *   - For non-alphanumeric characters, Unicode:ish names are used (e.g.
 *     "COMMA", "LEFT_SQUARE_BRACKET", etc.). Note that some names do not
 *     correspond to the Unicode standard (usually for brevity)
 *   - Keys that lack a clear US mapping are named "WORLD_x"
 *   - For non-printable keys, custom names are used (e.g. "F4",
 *     "BACKSPACE", etc.)
 *
 *  @ingroup input
 *  @{
 */

/* The unknown key */
#define DCORE_KEY_UNKNOWN -1

/* Printable keys */
#define DCORE_KEY_SPACE 32
#define DCORE_KEY_APOSTROPHE 39 /* ' */
#define DCORE_KEY_COMMA 44      /* , */
#define DCORE_KEY_MINUS 45      /* - */
#define DCORE_KEY_PERIOD 46     /* . */
#define DCORE_KEY_SLASH 47      /* / */
#define DCORE_KEY_0 48
#define DCORE_KEY_1 49
#define DCORE_KEY_2 50
#define DCORE_KEY_3 51
#define DCORE_KEY_4 52
#define DCORE_KEY_5 53
#define DCORE_KEY_6 54
#define DCORE_KEY_7 55
#define DCORE_KEY_8 56
#define DCORE_KEY_9 57
#define DCORE_KEY_SEMICOLON 59 /* ; */
#define DCORE_KEY_EQUAL 61     /* = */
#define DCORE_KEY_A 65
#define DCORE_KEY_B 66
#define DCORE_KEY_C 67
#define DCORE_KEY_D 68
#define DCORE_KEY_E 69
#define DCORE_KEY_F 70
#define DCORE_KEY_G 71
#define DCORE_KEY_H 72
#define DCORE_KEY_I 73
#define DCORE_KEY_J 74
#define DCORE_KEY_K 75
#define DCORE_KEY_L 76
#define DCORE_KEY_M 77
#define DCORE_KEY_N 78
#define DCORE_KEY_O 79
#define DCORE_KEY_P 80
#define DCORE_KEY_Q 81
#define DCORE_KEY_R 82
#define DCORE_KEY_S 83
#define DCORE_KEY_T 84
#define DCORE_KEY_U 85
#define DCORE_KEY_V 86
#define DCORE_KEY_W 87
#define DCORE_KEY_X 88
#define DCORE_KEY_Y 89
#define DCORE_KEY_Z 90
#define DCORE_KEY_LEFT_BRACKET 91  /* [ */
#define DCORE_KEY_BACKSLASH 92     /* \ */
#define DCORE_KEY_RIGHT_BRACKET 93 /* ] */
#define DCORE_KEY_GRAVE_ACCENT 96  /* ` */
#define DCORE_KEY_WORLD_1 161      /* non-US #1 */
#define DCORE_KEY_WORLD_2 162      /* non-US #2 */

/* Function keys */
#define DCORE_KEY_ESCAPE 256
#define DCORE_KEY_ENTER 257
#define DCORE_KEY_TAB 258
#define DCORE_KEY_BACKSPACE 259
#define DCORE_KEY_INSERT 260
#define DCORE_KEY_DELETE 261
#define DCORE_KEY_RIGHT 262
#define DCORE_KEY_LEFT 263
#define DCORE_KEY_DOWN 264
#define DCORE_KEY_UP 265
#define DCORE_KEY_PAGE_UP 266
#define DCORE_KEY_PAGE_DOWN 267
#define DCORE_KEY_HOME 268
#define DCORE_KEY_END 269
#define DCORE_KEY_CAPS_LOCK 280
#define DCORE_KEY_SCROLL_LOCK 281
#define DCORE_KEY_NUM_LOCK 282
#define DCORE_KEY_PRINT_SCREEN 283
#define DCORE_KEY_PAUSE 284
#define DCORE_KEY_F1 290
#define DCORE_KEY_F2 291
#define DCORE_KEY_F3 292
#define DCORE_KEY_F4 293
#define DCORE_KEY_F5 294
#define DCORE_KEY_F6 295
#define DCORE_KEY_F7 296
#define DCORE_KEY_F8 297
#define DCORE_KEY_F9 298
#define DCORE_KEY_F10 299
#define DCORE_KEY_F11 300
#define DCORE_KEY_F12 301
#define DCORE_KEY_F13 302
#define DCORE_KEY_F14 303
#define DCORE_KEY_F15 304
#define DCORE_KEY_F16 305
#define DCORE_KEY_F17 306
#define DCORE_KEY_F18 307
#define DCORE_KEY_F19 308
#define DCORE_KEY_F20 309
#define DCORE_KEY_F21 310
#define DCORE_KEY_F22 311
#define DCORE_KEY_F23 312
#define DCORE_KEY_F24 313
#define DCORE_KEY_F25 314
#define DCORE_KEY_KP_0 320
#define DCORE_KEY_KP_1 321
#define DCORE_KEY_KP_2 322
#define DCORE_KEY_KP_3 323
#define DCORE_KEY_KP_4 324
#define DCORE_KEY_KP_5 325
#define DCORE_KEY_KP_6 326
#define DCORE_KEY_KP_7 327
#define DCORE_KEY_KP_8 328
#define DCORE_KEY_KP_9 329
#define DCORE_KEY_KP_DECIMAL 330
#define DCORE_KEY_KP_DIVIDE 331
#define DCORE_KEY_KP_MULTIPLY 332
#define DCORE_KEY_KP_SUBTRACT 333
#define DCORE_KEY_KP_ADD 334
#define DCORE_KEY_KP_ENTER 335
#define DCORE_KEY_KP_EQUAL 336
#define DCORE_KEY_LEFT_SHIFT 340
#define DCORE_KEY_LEFT_CONTROL 341
#define DCORE_KEY_LEFT_ALT 342
#define DCORE_KEY_LEFT_SUPER 343
#define DCORE_KEY_RIGHT_SHIFT 344
#define DCORE_KEY_RIGHT_CONTROL 345
#define DCORE_KEY_RIGHT_ALT 346
#define DCORE_KEY_RIGHT_SUPER 347
#define DCORE_KEY_MENU 348

#define DCORE_KEY_LAST DCORE_KEY_MENU

/*! @} */

/*! @defgroup mods Modifier key flags
 *  @brief Modifier key flags.
 *
 *  See [key input](@ref input_key) for how these are used.
 *
 *  @ingroup input
 *  @{ */

/*! @brief If this bit is set one or more Shift keys were held down.
 *
 *  If this bit is set one or more Shift keys were held down.
 */
#define DCORE_MOD_SHIFT 0x0001
/*! @brief If this bit is set one or more Control keys were held down.
 *
 *  If this bit is set one or more Control keys were held down.
 */
#define DCORE_MOD_CONTROL 0x0002
/*! @brief If this bit is set one or more Alt keys were held down.
 *
 *  If this bit is set one or more Alt keys were held down.
 */
#define DCORE_MOD_ALT 0x0004
/*! @brief If this bit is set one or more Super keys were held down.
 *
 *  If this bit is set one or more Super keys were held down.
 */
#define DCORE_MOD_SUPER 0x0008
/*! @brief If this bit is set the Caps Lock key is enabled.
 *
 *  If this bit is set the Caps Lock key is enabled and the @ref
 *  DCORE_LOCK_KEY_MODS input mode is set.
 */
#define DCORE_MOD_CAPS_LOCK 0x0010
/*! @brief If this bit is set the Num Lock key is enabled.
 *
 *  If this bit is set the Num Lock key is enabled and the @ref
 *  DCORE_LOCK_KEY_MODS input mode is set.
 */
#define DCORE_MOD_NUM_LOCK 0x0020

/*! @} */

/*! @defgroup buttons Mouse buttons
 *  @brief Mouse button IDs.
 *
 *  See [mouse button input](@ref input_mouse_button) for how these are used.
 *
 *  @ingroup input
 *  @{ */
#define DCORE_MOUSE_BUTTON_1 0
#define DCORE_MOUSE_BUTTON_2 1
#define DCORE_MOUSE_BUTTON_3 2
#define DCORE_MOUSE_BUTTON_4 3
#define DCORE_MOUSE_BUTTON_5 4
#define DCORE_MOUSE_BUTTON_6 5
#define DCORE_MOUSE_BUTTON_7 6
#define DCORE_MOUSE_BUTTON_8 7
#define DCORE_MOUSE_BUTTON_LAST DCORE_MOUSE_BUTTON_8
#define DCORE_MOUSE_BUTTON_LEFT DCORE_MOUSE_BUTTON_1
#define DCORE_MOUSE_BUTTON_RIGHT DCORE_MOUSE_BUTTON_2
#define DCORE_MOUSE_BUTTON_MIDDLE DCORE_MOUSE_BUTTON_3
/*! @} */

/*! @defgroup joysticks Joysticks
 *  @brief Joystick IDs.
 *
 *  See [joystick input](@ref joystick) for how these are used.
 *
 *  @ingroup input
 *  @{ */
#define DCORE_JOYSTICK_1 0
#define DCORE_JOYSTICK_2 1
#define DCORE_JOYSTICK_3 2
#define DCORE_JOYSTICK_4 3
#define DCORE_JOYSTICK_5 4
#define DCORE_JOYSTICK_6 5
#define DCORE_JOYSTICK_7 6
#define DCORE_JOYSTICK_8 7
#define DCORE_JOYSTICK_9 8
#define DCORE_JOYSTICK_10 9
#define DCORE_JOYSTICK_11 10
#define DCORE_JOYSTICK_12 11
#define DCORE_JOYSTICK_13 12
#define DCORE_JOYSTICK_14 13
#define DCORE_JOYSTICK_15 14
#define DCORE_JOYSTICK_16 15
#define DCORE_JOYSTICK_LAST DCORE_JOYSTICK_16
/*! @} */

/*! @defgroup gamepad_buttons Gamepad buttons
 *  @brief Gamepad buttons.
 *
 *  See @ref gamepad for how these are used.
 *
 *  @ingroup input
 *  @{ */
#define DCORE_GAMEPAD_BUTTON_A 0
#define DCORE_GAMEPAD_BUTTON_B 1
#define DCORE_GAMEPAD_BUTTON_X 2
#define DCORE_GAMEPAD_BUTTON_Y 3
#define DCORE_GAMEPAD_BUTTON_LEFT_BUMPER 4
#define DCORE_GAMEPAD_BUTTON_RIGHT_BUMPER 5
#define DCORE_GAMEPAD_BUTTON_BACK 6
#define DCORE_GAMEPAD_BUTTON_START 7
#define DCORE_GAMEPAD_BUTTON_GUIDE 8
#define DCORE_GAMEPAD_BUTTON_LEFT_THUMB 9
#define DCORE_GAMEPAD_BUTTON_RIGHT_THUMB 10
#define DCORE_GAMEPAD_BUTTON_DPAD_UP 11
#define DCORE_GAMEPAD_BUTTON_DPAD_RIGHT 12
#define DCORE_GAMEPAD_BUTTON_DPAD_DOWN 13
#define DCORE_GAMEPAD_BUTTON_DPAD_LEFT 14
#define DCORE_GAMEPAD_BUTTON_LAST DCORE_GAMEPAD_BUTTON_DPAD_LEFT

#define DCORE_GAMEPAD_BUTTON_CROSS DCORE_GAMEPAD_BUTTON_A
#define DCORE_GAMEPAD_BUTTON_CIRCLE DCORE_GAMEPAD_BUTTON_B
#define DCORE_GAMEPAD_BUTTON_SQUARE DCORE_GAMEPAD_BUTTON_X
#define DCORE_GAMEPAD_BUTTON_TRIANGLE DCORE_GAMEPAD_BUTTON_Y
/*! @} */

/*! @defgroup gamepad_axes Gamepad axes
 *  @brief Gamepad axes.
 *
 *  See @ref gamepad for how these are used.
 *
 *  @ingroup input
 *  @{ */
#define DCORE_GAMEPAD_AXIS_LEFT_X 0
#define DCORE_GAMEPAD_AXIS_LEFT_Y 1
#define DCORE_GAMEPAD_AXIS_RIGHT_X 2
#define DCORE_GAMEPAD_AXIS_RIGHT_Y 3
#define DCORE_GAMEPAD_AXIS_LEFT_TRIGGER 4
#define DCORE_GAMEPAD_AXIS_RIGHT_TRIGGER 5
#define DCORE_GAMEPAD_AXIS_LAST DCORE_GAMEPAD_AXIS_RIGHT_TRIGGER