#pragma once
#include <glfw/glfw3.h>
/*! @name Key and button actions
 *  @{ */
/*! @brief The key or mouse button was released.
 *
 *  The key or mouse button was released.
 *
 *  @ingroup input
 */
#define DCORE_RELEASE GLFW_RELEASE
/*! @brief The key or mouse button was pressed.
 *
 *  The key or mouse button was pressed.
 *
 *  @ingroup input
 */
#define DCORE_PRESS GLFW_PRESS
/*! @brief The key was held down until it repeated.
 *
 *  The key was held down until it repeated.
 *
 *  @ingroup input
 */
#define DCORE_REPEAT GLFW_REPEAT
/*! @defgroup hat_state Joystick hat states
 *  @brief Joystick hat states.
 *
 *  See [joystick hat input](@ref joystick_hat) for how these are used.
 *
 *  @ingroup input
 *  @{ */
#define DCORE_HAT_CENTERED GLFW_HAT_CENTERED
#define DCORE_HAT_UP GLFW_HAT_UP
#define DCORE_HAT_RIGHT GLFW_HAT_RIGHT
#define DCORE_HAT_DOWN GLFW_HAT_DOWN
#define DCORE_HAT_LEFT GLFW_HAT_LEFT
#define DCORE_HAT_RIGHT_UP GLFW_HAT_RIGHT_UP
#define DCORE_HAT_RIGHT_DOWN GLFW_HAT_RIGHT_DOWN
#define DCORE_HAT_LEFT_UP GLFW_HAT_LEFT_UP
#define DCORE_HAT_LEFT_DOWN GLFW_HAT_LEFT_DOWN
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
#define DCORE_KEY_UNKNOWN GLFW_KEY_UNKNOWN

/* Printable keys */
#define DCORE_KEY_SPACE GLFW_KEY_SPACE
#define DCORE_KEY_APOSTROPHE GLFW_KEY_APOSTROPHE
#define DCORE_KEY_COMMA GLFW_KEY_COMMA
#define DCORE_KEY_MINUS GLFW_KEY_MINUS
#define DCORE_KEY_PERIOD GLFW_KEY_PERIOD
#define DCORE_KEY_SLASH GLFW_KEY_SLASH
#define DCORE_KEY_0 GLFW_KEY_0
#define DCORE_KEY_1 GLFW_KEY_1
#define DCORE_KEY_2 GLFW_KEY_2
#define DCORE_KEY_3 GLFW_KEY_3
#define DCORE_KEY_4 GLFW_KEY_4
#define DCORE_KEY_5 GLFW_KEY_5
#define DCORE_KEY_6 GLFW_KEY_6
#define DCORE_KEY_7 GLFW_KEY_7
#define DCORE_KEY_8 GLFW_KEY_8
#define DCORE_KEY_9 GLFW_KEY_9
#define DCORE_KEY_SEMICOLON GLFW_KEY_SEMICOLON
#define DCORE_KEY_EQUAL GLFW_KEY_EQUAL
#define DCORE_KEY_A GLFW_KEY_A
#define DCORE_KEY_B GLFW_KEY_B
#define DCORE_KEY_C GLFW_KEY_C
#define DCORE_KEY_D GLFW_KEY_D
#define DCORE_KEY_E GLFW_KEY_E
#define DCORE_KEY_F GLFW_KEY_F
#define DCORE_KEY_G GLFW_KEY_G
#define DCORE_KEY_H GLFW_KEY_H
#define DCORE_KEY_I GLFW_KEY_I
#define DCORE_KEY_J GLFW_KEY_J
#define DCORE_KEY_K GLFW_KEY_K
#define DCORE_KEY_L GLFW_KEY_L
#define DCORE_KEY_M GLFW_KEY_M
#define DCORE_KEY_N GLFW_KEY_N
#define DCORE_KEY_O GLFW_KEY_O
#define DCORE_KEY_P GLFW_KEY_P
#define DCORE_KEY_Q GLFW_KEY_Q
#define DCORE_KEY_R GLFW_KEY_R
#define DCORE_KEY_S GLFW_KEY_S
#define DCORE_KEY_T GLFW_KEY_T
#define DCORE_KEY_U GLFW_KEY_U
#define DCORE_KEY_V GLFW_KEY_V
#define DCORE_KEY_W GLFW_KEY_W
#define DCORE_KEY_X GLFW_KEY_X
#define DCORE_KEY_Y GLFW_KEY_Y
#define DCORE_KEY_Z GLFW_KEY_Z
#define DCORE_KEY_LEFT_BRACKET GLFW_KEY_LEFT_BRACKET
#define DCORE_KEY_BACKSLASH GLFW_KEY_BACKSLASH
#define DCORE_KEY_RIGHT_BRACKET GLFW_KEY_RIGHT_BRACKET
#define DCORE_KEY_GRAVE_ACCENT GLFW_KEY_GRAVE_ACCENT
#define DCORE_KEY_WORLD_1 GLFW_KEY_WORLD_1
#define DCORE_KEY_WORLD_2 GLFW_KEY_WORLD_2

/* Function keys */
#define DCORE_KEY_ESCAPE GLFW_KEY_ESCAPE
#define DCORE_KEY_ENTER GLFW_KEY_ENTER
#define DCORE_KEY_TAB GLFW_KEY_TAB
#define DCORE_KEY_BACKSPACE GLFW_KEY_BACKSPACE
#define DCORE_KEY_INSERT GLFW_KEY_INSERT
#define DCORE_KEY_DELETE GLFW_KEY_DELETE
#define DCORE_KEY_RIGHT GLFW_KEY_RIGHT
#define DCORE_KEY_LEFT GLFW_KEY_LEFT
#define DCORE_KEY_DOWN GLFW_KEY_DOWN
#define DCORE_KEY_UP GLFW_KEY_UP
#define DCORE_KEY_PAGE_UP GLFW_KEY_PAGE_UP
#define DCORE_KEY_PAGE_DOWN GLFW_KEY_PAGE_DOWN
#define DCORE_KEY_HOME GLFW_KEY_HOME
#define DCORE_KEY_END GLFW_KEY_END
#define DCORE_KEY_CAPS_LOCK GLFW_KEY_CAPS_LOCK
#define DCORE_KEY_SCROLL_LOCK GLFW_KEY_SCROLL_LOCK
#define DCORE_KEY_NUM_LOCK GLFW_KEY_NUM_LOCK
#define DCORE_KEY_PRINT_SCREEN GLFW_KEY_PRINT_SCREEN
#define DCORE_KEY_PAUSE GLFW_KEY_PAUSE
#define DCORE_KEY_F1 GLFW_KEY_F1
#define DCORE_KEY_F2 GLFW_KEY_F2
#define DCORE_KEY_F3 GLFW_KEY_F3
#define DCORE_KEY_F4 GLFW_KEY_F4
#define DCORE_KEY_F5 GLFW_KEY_F5
#define DCORE_KEY_F6 GLFW_KEY_F6
#define DCORE_KEY_F7 GLFW_KEY_F7
#define DCORE_KEY_F8 GLFW_KEY_F8
#define DCORE_KEY_F9 GLFW_KEY_F9
#define DCORE_KEY_F10 GLFW_KEY_F10
#define DCORE_KEY_F11 GLFW_KEY_F11
#define DCORE_KEY_F12 GLFW_KEY_F12
#define DCORE_KEY_F13 GLFW_KEY_F13
#define DCORE_KEY_F14 GLFW_KEY_F14
#define DCORE_KEY_F15 GLFW_KEY_F15
#define DCORE_KEY_F16 GLFW_KEY_F16
#define DCORE_KEY_F17 GLFW_KEY_F17
#define DCORE_KEY_F18 GLFW_KEY_F18
#define DCORE_KEY_F19 GLFW_KEY_F19
#define DCORE_KEY_F20 GLFW_KEY_F20
#define DCORE_KEY_F21 GLFW_KEY_F21
#define DCORE_KEY_F22 GLFW_KEY_F22
#define DCORE_KEY_F23 GLFW_KEY_F23
#define DCORE_KEY_F24 GLFW_KEY_F24
#define DCORE_KEY_F25 GLFW_KEY_F25
#define DCORE_KEY_KP_0 GLFW_KEY_KP_0
#define DCORE_KEY_KP_1 GLFW_KEY_KP_1
#define DCORE_KEY_KP_2 GLFW_KEY_KP_2
#define DCORE_KEY_KP_3 GLFW_KEY_KP_3
#define DCORE_KEY_KP_4 GLFW_KEY_KP_4
#define DCORE_KEY_KP_5 GLFW_KEY_KP_5
#define DCORE_KEY_KP_6 GLFW_KEY_KP_6
#define DCORE_KEY_KP_7 GLFW_KEY_KP_7
#define DCORE_KEY_KP_8 GLFW_KEY_KP_8
#define DCORE_KEY_KP_9 GLFW_KEY_KP_9
#define DCORE_KEY_KP_DECIMAL GLFW_KEY_KP_DECIMAL
#define DCORE_KEY_KP_DIVIDE GLFW_KEY_KP_DIVIDE
#define DCORE_KEY_KP_MULTIPLY GLFW_KEY_KP_MULTIPLY
#define DCORE_KEY_KP_SUBTRACT GLFW_KEY_KP_SUBTRACT
#define DCORE_KEY_KP_ADD GLFW_KEY_KP_ADD
#define DCORE_KEY_KP_ENTER GLFW_KEY_KP_ENTER
#define DCORE_KEY_KP_EQUAL GLFW_KEY_KP_EQUAL
#define DCORE_KEY_LEFT_SHIFT GLFW_KEY_LEFT_SHIFT
#define DCORE_KEY_LEFT_CONTROL GLFW_KEY_LEFT_CONTROL
#define DCORE_KEY_LEFT_ALT GLFW_KEY_LEFT_ALT
#define DCORE_KEY_LEFT_SUPER GLFW_KEY_LEFT_SUPER
#define DCORE_KEY_RIGHT_SHIFT GLFW_KEY_RIGHT_SHIFT
#define DCORE_KEY_RIGHT_CONTROL GLFW_KEY_RIGHT_CONTROL
#define DCORE_KEY_RIGHT_ALT GLFW_KEY_RIGHT_ALT
#define DCORE_KEY_RIGHT_SUPER GLFW_KEY_RIGHT_SUPER
#define DCORE_KEY_MENU GLFW_KEY_MENU

#define DCORE_KEY_LAST GLFW_KEY_LAST

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
#define DCORE_MOD_SHIFT GLFW_MOD_SHIFT
/*! @brief If this bit is set one or more Control keys were held down.
 *
 *  If this bit is set one or more Control keys were held down.
 */
#define DCORE_MOD_CONTROL GLFW_MOD_CONTROL
/*! @brief If this bit is set one or more Alt keys were held down.
 *
 *  If this bit is set one or more Alt keys were held down.
 */
#define DCORE_MOD_ALT GLFW_MOD_ALT
/*! @brief If this bit is set one or more Super keys were held down.
 *
 *  If this bit is set one or more Super keys were held down.
 */
#define DCORE_MOD_SUPER GLFW_MOD_SUPER
/*! @brief If this bit is set the Caps Lock key is enabled.
 *
 *  If this bit is set the Caps Lock key is enabled and the @ref
 *  DCORE_LOCK_KEY_MODS GLFW_LOCK_KEY_MODS
 */
#define DCORE_MOD_CAPS_LOCK GLFW_MOD_CAPS_LOCK
/*! @brief If this bit is set the Num Lock key is enabled.
 *
 *  If this bit is set the Num Lock key is enabled and the @ref
 *  DCORE_LOCK_KEY_MODS GLFW_LOCK_KEY_MODS
 */
#define DCORE_MOD_NUM_LOCK GLFW_MOD_NUM_LOCK

/*! @} */

/*! @defgroup buttons Mouse buttons
 *  @brief Mouse button IDs.
 *
 *  See [mouse button input](@ref input_mouse_button) for how these are used.
 *
 *  @ingroup input
 *  @{ */
#define DCORE_MOUSE_BUTTON_1 GLFW_MOUSE_BUTTON_1
#define DCORE_MOUSE_BUTTON_2 GLFW_MOUSE_BUTTON_2
#define DCORE_MOUSE_BUTTON_3 GLFW_MOUSE_BUTTON_3
#define DCORE_MOUSE_BUTTON_4 GLFW_MOUSE_BUTTON_4
#define DCORE_MOUSE_BUTTON_5 GLFW_MOUSE_BUTTON_5
#define DCORE_MOUSE_BUTTON_6 GLFW_MOUSE_BUTTON_6
#define DCORE_MOUSE_BUTTON_7 GLFW_MOUSE_BUTTON_7
#define DCORE_MOUSE_BUTTON_8 GLFW_MOUSE_BUTTON_8
#define DCORE_MOUSE_BUTTON_LAST GLFW_MOUSE_BUTTON_8
#define DCORE_MOUSE_BUTTON_LEFT GLFW_MOUSE_BUTTON_1
#define DCORE_MOUSE_BUTTON_RIGHT GLFW_MOUSE_BUTTON_2
#define DCORE_MOUSE_BUTTON_MIDDLE GLFW_MOUSE_BUTTON_3
/*! @} */

/*! @defgroup joysticks Joysticks
 *  @brief Joystick IDs.
 *
 *  See [joystick input](@ref joystick) for how these are used.
 *
 *  @ingroup input
 *  @{ */
#define DCORE_JOYSTICK_1 GLFW_JOYSTICK_1
#define DCORE_JOYSTICK_2 GLFW_JOYSTICK_2
#define DCORE_JOYSTICK_3 GLFW_JOYSTICK_3
#define DCORE_JOYSTICK_4 GLFW_JOYSTICK_4
#define DCORE_JOYSTICK_5 GLFW_JOYSTICK_5
#define DCORE_JOYSTICK_6 GLFW_JOYSTICK_6
#define DCORE_JOYSTICK_7 GLFW_JOYSTICK_7
#define DCORE_JOYSTICK_8 GLFW_JOYSTICK_8
#define DCORE_JOYSTICK_9 GLFW_JOYSTICK_9
#define DCORE_JOYSTICK_10 GLFW_JOYSTICK_10
#define DCORE_JOYSTICK_11 GLFW_JOYSTICK_11
#define DCORE_JOYSTICK_12 GLFW_JOYSTICK_12
#define DCORE_JOYSTICK_13 GLFW_JOYSTICK_13
#define DCORE_JOYSTICK_14 GLFW_JOYSTICK_14
#define DCORE_JOYSTICK_15 GLFW_JOYSTICK_15
#define DCORE_JOYSTICK_16 GLFW_JOYSTICK_16
#define DCORE_JOYSTICK_LAST GLFW_JOYSTICK_16
/*! @} */

/*! @defgroup gamepad_buttons Gamepad buttons
 *  @brief Gamepad buttons.
 *
 *  See @ref gamepad for how these are used.
 *
 *  @ingroup input
 *  @{ */
#define DCORE_GAMEPAD_BUTTON_A GLFW_GAMEPAD_BUTTON_A
#define DCORE_GAMEPAD_BUTTON_B GLFW_GAMEPAD_BUTTON_B
#define DCORE_GAMEPAD_BUTTON_X GLFW_GAMEPAD_BUTTON_X
#define DCORE_GAMEPAD_BUTTON_Y GLFW_GAMEPAD_BUTTON_Y
#define DCORE_GAMEPAD_BUTTON_LEFT_BUMPER GLFW_GAMEPAD_BUTTON_LEFT_BUMPER
#define DCORE_GAMEPAD_BUTTON_RIGHT_BUMPER GLFW_GAMEPAD_BUTTON_RIGHT_BUMPER
#define DCORE_GAMEPAD_BUTTON_BACK GLFW_GAMEPAD_BUTTON_BACK
#define DCORE_GAMEPAD_BUTTON_START GLFW_GAMEPAD_BUTTON_START
#define DCORE_GAMEPAD_BUTTON_GUIDE GLFW_GAMEPAD_BUTTON_GUIDE
#define DCORE_GAMEPAD_BUTTON_LEFT_THUMB GLFW_GAMEPAD_BUTTON_LEFT_THUMB
#define DCORE_GAMEPAD_BUTTON_RIGHT_THUMB GLFW_GAMEPAD_BUTTON_RIGHT_THUMB
#define DCORE_GAMEPAD_BUTTON_DPAD_UP GLFW_GAMEPAD_BUTTON_DPAD_UP
#define DCORE_GAMEPAD_BUTTON_DPAD_RIGHT GLFW_GAMEPAD_BUTTON_DPAD_RIGHT
#define DCORE_GAMEPAD_BUTTON_DPAD_DOWN GLFW_GAMEPAD_BUTTON_DPAD_DOWN
#define DCORE_GAMEPAD_BUTTON_DPAD_LEFT GLFW_GAMEPAD_BUTTON_DPAD_LEFT
#define DCORE_GAMEPAD_BUTTON_LAST GLFW_GAMEPAD_BUTTON_DPAD_LEFT

#define DCORE_GAMEPAD_BUTTON_CROSS GLFW_GAMEPAD_BUTTON_A
#define DCORE_GAMEPAD_BUTTON_CIRCLE GLFW_GAMEPAD_BUTTON_B
#define DCORE_GAMEPAD_BUTTON_SQUARE GLFW_GAMEPAD_BUTTON_X
#define DCORE_GAMEPAD_BUTTON_TRIANGLE GLFW_GAMEPAD_BUTTON_Y
/*! @} */

/*! @defgroup gamepad_axes Gamepad axes
 *  @brief Gamepad axes.
 *
 *  See @ref gamepad for how these are used.
 *
 *  @ingroup input
 *  @{ */
#define DCORE_GAMEPAD_AXIS_LEFT_XGLFW_GAMEPAD_AXIS_LEFT_X
#define DCORE_GAMEPAD_AXIS_LEFT_YGLFW_GAMEPAD_AXIS_LEFT_Y
#define DCORE_GAMEPAD_AXIS_RIGHT_XGLFW_GAMEPAD_AXIS_RIGHT_X
#define DCORE_GAMEPAD_AXIS_RIGHT_YGLFW_GAMEPAD_AXIS_RIGHT_Y
#define DCORE_GAMEPAD_AXIS_LEFT_TRIGGERGLFW_GAMEPAD_AXIS_LEFT_TRIGGER
#define DCORE_GAMEPAD_AXIS_RIGHT_TRIGGERGLFW_GAMEPAD_AXIS_RIGHT_TRIGGER
#define DCORE_GAMEPAD_AXIS_LAST GLFW_GAMEPAD_AXIS_RIGHT_TRIGGER