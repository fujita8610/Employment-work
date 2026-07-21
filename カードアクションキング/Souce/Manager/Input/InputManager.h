#pragma once

class InputManager
{
public:

    static InputManager& GetInstance();

    void Update();

    bool IsKeyPressed(int key) const;
    bool IsKeyDown(int key) const;
    bool IsKeyUp(int key) const;

    int GetMouseX() const;
    int GetMouseY() const;

    bool IsMousePressed(int button) const;
    bool IsMouseDown(int button) const;
    bool IsMouseUp(int button) const;

private:

    InputManager() = default;
    ~InputManager() = default;

    InputManager(const InputManager&) = delete;
    InputManager& operator=(const InputManager&) = delete;

private:

    char m_nowKey[256]{};
    char m_oldKey[256]{};

    int m_mouseX = 0;
    int m_mouseY = 0;

    int m_nowMouse = 0;
    int m_oldMouse = 0;
};