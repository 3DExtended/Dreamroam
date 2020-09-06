#pragma once
#include <glfw/glfw3.h>

#include <ComponentBased/Entity.hh>
#include <entt/entt.hpp>
#include <lava/features/GlfwWindow.hh>

#include "InputSystemDefines.hh"

namespace DCore {
namespace ComponentSystem {
/// <summary>
/// This system is used to handle user inputs.
/// Check here, if the mouse was moved, the user hit some mouse button or
/// entered something on the keyboard.
/// </summary>
class InputSystem {
public:
    /// <summary>
    /// This constructor should only get called from the scene handler class.
    /// The input system in each scene gets also set there.
    /// </summary>
    /// <param name="window"></param>
    InputSystem(lava::features::SharedGlfwWindow window) : mWindow(window){};

    /// <summary>
    /// Returns true, if the keyboard key stored in an key code (see e.g.
    /// "DCORE_KEY_A" define) is pressed.
    /// </summary>
    /// <param name="keyCode">The key code</param>
    /// <returns>True if key is pressed</returns>
    bool IsKeyDown(int keyCode) {
        return glfwGetKey(mWindow->window(), keyCode) == DCORE_PRESS;
    }

    /// <summary>
    /// Returns true, if the keyboard key stored in an key code (see e.g.
    /// "DCORE_KEY_A" define) is NOT pressed (i.e. release).
    /// </summary>
    /// <param name="keyCode">The key code</param>
    /// <returns>True if key is release</returns>
    bool IsKeyUp(int keyCode) {
        return glfwGetKey(mWindow->window(), keyCode) == DCORE_RELEASE;
    }

    /// <summary>
    /// Returns true, if the mouse button stored in an button code (e.g. see
    /// "DCORE_MOUSE_BUTTON_1" define) is pressed.
    /// </summary>
    /// <param name="mouseButtonCode">The button code</param>
    /// <returns>True if button is pressed</returns>
    bool IsMouseButtonDown(int mouseButtonCode) {
        return glfwGetMouseButton(mWindow->window(), mouseButtonCode) ==
               DCORE_PRESS;
    }

    /// <summary>
    /// Returns true, if the mouse button stored in an button code (e.g. see
    /// "DCORE_MOUSE_BUTTON_1" define) is NOT pressed (i.e. released).
    /// </summary>
    /// <param name="mouseButtonCode">The button code</param>
    /// <returns>True if button is released</returns>
    bool IsMouseButtonUp(int mouseButtonCode) {
        return glfwGetMouseButton(mWindow->window(), mouseButtonCode) ==
               DCORE_RELEASE;
    }

    /// <summary>
    /// Returns the current mouse position relative to the top left corner of
    /// the window.
    /// </summary>
    /// <returns>Vec2 storing the mouse position in pixels</returns>
    glm::vec2 GetMousePosition() {
        double x, y;
        glfwGetCursorPos(mWindow->window(), &x, &y);
        return glm::vec2(x, y);
    }

    /// <summary>
    /// Returns the current mouse position relative to the top left corner of
    /// the window. This is a value relative to the window dimensions.
    /// </summary>
    /// <returns>Vec2 storing the mouse position relative to the windows
    /// dimensions</returns>
    glm::vec2 GetMousePositionRelative() {
        auto pos = GetMousePosition();
        return pos * glm::vec2(1.0 / mWindow->width(), 1.0 / mWindow->height());
    }

protected:
    lava::features::SharedGlfwWindow mWindow;
};
}  // namespace ComponentSystem
}  // namespace DCore