/*!
 * \file src/UI.cpp
 * \brief UI interface manager
 *
 * \author xythobuz
 */

#include <algorithm>
#include <cstring>

#include "imgui/imgui.h"
#include "stb/stb_image.h"

#include "global.h"
#include "Camera.h"
#include "Console.h"
#include "Game.h"
#include "Log.h"
#include "Menu.h"
#include "Render.h"
#include "RunTime.h"
#include "SoundManager.h"
#include "TextureManager.h"
#include "World.h"
#include "commands/Command.h"
#include "system/Sound.h"
#include "system/Window.h"
#include "utils/time.h"
#include "UI.h"

Shader UI::imguiShader;
bool UI::visible = false;
unsigned int UI::fontTex;
std::string UI::iniFilename;
std::string UI::logFilename;
bool UI::metaKeyIsActive = false;

std::list<std::tuple<KeyboardButton, bool>> UI::keyboardEvents;
std::list<std::tuple<unsigned int, unsigned int, KeyboardButton, bool>> UI::clickEvents;
std::list<std::tuple<int, int, int, int>> UI::motionEvents;
std::list<std::tuple<int, int>> UI::scrollEvents;

void UI::setSize(glm::i32vec2 s) {
    ImGuiIO& io = ImGui::GetIO();
    io.DisplaySize = ImVec2(s.x, s.y);
}

int UI::initialize() {
    if (imguiShader.compile(imguiShaderVertex, imguiShaderFragment) < 0)
        return -1;
    if (imguiShader.addUniform("screen") < 0)
        return -2;
    if (imguiShader.addUniform("textureSampler") < 0)
        return -3;

    iniFilename = RunTime::getBaseDir() + "/imgui.ini";
    logFilename = RunTime::getBaseDir() + "/imgui_log.txt";

    ImGuiIO& io = ImGui::GetIO();
    io.DisplaySize = ImVec2(Window::getSize().x, Window::getSize().y);
    io.DeltaTime = 1.0f / 60.0f;

    io.IniFilename = iniFilename.c_str();
    io.LogFilename = logFilename.c_str();

    io.KeyMap[ImGuiKey_Tab] = tabKey;
    io.KeyMap[ImGuiKey_LeftArrow] = leftKey;
    io.KeyMap[ImGuiKey_RightArrow] = rightKey;
    io.KeyMap[ImGuiKey_UpArrow] = upKey;
    io.KeyMap[ImGuiKey_DownArrow] = downKey;
    io.KeyMap[ImGuiKey_Home] = homeKey;
    io.KeyMap[ImGuiKey_End] = endKey;
    io.KeyMap[ImGuiKey_Delete] = delKey;
    io.KeyMap[ImGuiKey_Backspace] = backspaceKey;
    io.KeyMap[ImGuiKey_Enter] = enterKey;
    io.KeyMap[ImGuiKey_Escape] = escapeKey;
    io.KeyMap[ImGuiKey_A] = aKey;
    io.KeyMap[ImGuiKey_C] = cKey;
    io.KeyMap[ImGuiKey_V] = vKey;
    io.KeyMap[ImGuiKey_X] = xKey;
    io.KeyMap[ImGuiKey_Y] = yKey;
    io.KeyMap[ImGuiKey_Z] = zKey;

    io.RenderDrawListsFn = UI::renderImGui;

    // Load font texture
    //! \todo Use our own font subsystem instead of this?
    const void* png_data;
    unsigned int png_size;
    ImGui::GetDefaultFontData(nullptr, nullptr, &png_data, &png_size);
    int tex_x, tex_y, tex_comp;
    void* tex_data = stbi_load_from_memory((const unsigned char*)png_data,
                                           (int)png_size, &tex_x, &tex_y, &tex_comp, 0);

    fontTex = TextureManager::loadBufferSlot((unsigned char*)tex_data,
                                             tex_x, tex_y, ColorMode::RGBA, 32,
                                             TextureStorage::SYSTEM, -1, false);

    stbi_image_free(tex_data);

    return 0;
}

void UI::eventsFinished() {
    ImGuiIO& io = ImGui::GetIO();
    io.DisplaySize = ImVec2(Window::getSize().x, Window::getSize().y);

    static unsigned long lastTime = 0;
    io.DeltaTime = ((float)(systemTimerGet() - lastTime)) / 1000.0f;
    lastTime = systemTimerGet();
    if (io.DeltaTime <= 0.0f)
        io.DeltaTime = 1.0f / 60.0f;

    ImGui::NewFrame();

    if (!(visible || Console::isVisible())) {
        while (!clickEvents.empty()) {
            auto i = clickEvents.front();
            if (getMenu().isVisible()) {
                getMenu().handleMouseClick(std::get<0>(i), std::get<1>(i),
                                           std::get<2>(i), std::get<3>(i));
            }
            clickEvents.pop_front();
        }

        while (!motionEvents.empty()) {
            auto i = motionEvents.front();
            if (!getMenu().isVisible()) {
                getGame().handleMouseMotion(std::get<0>(i), std::get<1>(i),
                                            std::get<2>(i), std::get<3>(i));
            }
            motionEvents.pop_front();
        }

        while (!scrollEvents.empty()) {
            auto i = scrollEvents.front();
            if (getMenu().isVisible()) {
                getMenu().handleMouseScroll(std::get<0>(i), std::get<1>(i));
            }
            scrollEvents.pop_front();
        }
    }

    while (!keyboardEvents.empty()) {
        auto i = keyboardEvents.front();

        if (!(visible || Console::isVisible())) {
            if (getMenu().isVisible()) {
                getMenu().handleKeyboard(std::get<0>(i), std::get<1>(i));
            } else {
                for (int n = forwardAction; n < ActionEventCount; n++) {
                    if (RunTime::getKeyBinding((ActionEvents)n) == std::get<0>(i))
                        getGame().handleAction((ActionEvents)n, !std::get<1>(i));
                }
            }
        }

        if (std::get<1>(i)) {
            if (!(visible || Console::isVisible())) {
                if (RunTime::getKeyBinding(menuAction) == std::get<0>(i)) {
                    getMenu().setVisible(!getMenu().isVisible());
                }
            }

            if ((!io.WantCaptureKeyboard) || (!(visible || Console::isVisible()))) {
                if (!metaKeyIsActive) {
                    if (RunTime::getKeyBinding(debugAction) == std::get<0>(i)) {
                        visible = !visible;
                    }

                    if (RunTime::getKeyBinding(consoleAction) == std::get<0>(i)) {
                        Console::setVisible(!Console::isVisible());
                    }
                }
            }
        }

        keyboardEvents.pop_front();
    }

    bool clicked = !clickEvents.empty();
    clickEvents.clear();
    motionEvents.clear();
    scrollEvents.clear();

    if ((visible || Console::isVisible()) && (
            ((!io.WantCaptureKeyboard) && io.KeysDown[escapeKey])
            || ((!io.WantCaptureMouse) && clicked)
        )) {
        visible = false;
        Console::setVisible(false);
    }

    if (Window::getTextInput() != (visible || Console::isVisible()))
        Window::setTextInput(visible || Console::isVisible());

    bool input = !(visible || Console::isVisible() || getMenu().isVisible());
    if (Window::getMousegrab() != input)
        Window::setMousegrab(input);

    io.MouseWheel = 0;
}

void UI::display() {
    Console::display();

    if (!visible) {
        ImGui::Render();
        return;
    }

    static bool showTestWindow = false;
    if (ImGui::Begin("Engine", &visible, ImVec2(400, 400))) {
        Render::displayUI();
        RunTime::display();
        SoundManager::display();

        /*
        static bool visibleTex = false;
        static bool visibleTile = false;
        static bool visibleAnim = false;
        static bool visibleSprite = false;
        if (ImGui::CollapsingHeader("Texture Viewer")) {
            static bool game = getGame().isLoaded();
            static int index = 0;
            ImGui::PushItemWidth(ImGui::GetWindowWidth() * 0.5f);
            ImGui::SliderInt("##texslide", &index, 0, TextureManager::.numTextures(
                                 game ? TextureStorage::GAME : TextureStorage::SYSTEM) - 1);
            ImGui::PopItemWidth();
            ImGui::SameLine();
            if (ImGui::Button("+##texplus", ImVec2(0, 0), true)) {
                if (index < (TextureManager::numTextures(
                                 game ? TextureStorage::GAME : TextureStorage::SYSTEM) - 1))
                    index++;
                else
                    index = 0;
            }
            ImGui::SameLine();
            if (ImGui::Button("-##texminus", ImVec2(0, 0), true)) {
                if (index > 0)
                    index--;
                else
                    index = TextureManager::numTextures(
                                game ? TextureStorage::GAME : TextureStorage::SYSTEM) - 1;
            }
            ImGui::SameLine();
            if ((TextureManager::numTextures() > 0)) {
                ImGui::Checkbox("Game##texgame", &game);
            } else {
                game = false;
            }
            ImGui::SameLine();
            if (ImGui::Button("Show##texshow")) {
                visibleTex = true;
                visibleTile = false;
                visibleAnim = false;
                visibleSprite = false;
            }
            ImGui::SameLine();
            if (ImGui::Button("Clear##texclear")) {
                getRender().debugDisplayTexture();
                visibleTex = false;
            }
            if (visibleTex) {
                getRender().debugDisplayTexture(index,
                                                game ? TextureStorage::GAME : TextureStorage::SYSTEM,
                                                ImGui::GetWindowPos().x - ImGui::GetWindowWidth(),
                                                ImGui::GetWindowPos().y,
                                                ImGui::GetWindowWidth(), ImGui::GetWindowWidth());
            }
        }

        if (ImGui::CollapsingHeader("Textile Viewer")) {
            if (TextureManager::numTiles() > 0) {
                static int index = 0;
                ImGui::PushItemWidth(ImGui::GetWindowWidth() * 0.5f);
                ImGui::SliderInt("##tileslide", &index, 0, TextureManager::numTiles() - 1);
                ImGui::PopItemWidth();
                ImGui::SameLine();
                if (ImGui::Button("+##tileplus", ImVec2(0, 0), true)) {
                    if (index < (TextureManager::numTiles() - 1))
                        index++;
                    else
                        index = 0;
                }
                ImGui::SameLine();
                if (ImGui::Button("-##tileminus", ImVec2(0, 0), true)) {
                    if (index > 0)
                        index--;
                    else
                        index = TextureManager::numTiles() - 1;
                }
                ImGui::SameLine();
                if (ImGui::Button("Show##tileshow")) {
                    visibleTile = true;
                    visibleTex = false;
                    visibleAnim = false;
                    visibleSprite = false;
                }
                ImGui::SameLine();
                if (ImGui::Button("Clear##tileclear")) {
                    getRender().debugDisplayTextile();
                    visibleTile = false;
                }
                if (visibleTile && (index < TextureManager::numTiles())) {
                    ImGui::Text(TextureManager::.getTile(index).isTriangle() ? "Triangle" : "Rectangle");
                }
                if (visibleTile) {
                    getRender().debugDisplayTextile(index,
                                                    ImGui::GetWindowPos().x - (ImGui::GetWindowWidth() / 2),
                                                    ImGui::GetWindowPos().y,
                                                    (ImGui::GetWindowWidth() / 2), (ImGui::GetWindowWidth() / 2));
                }
            } else {
                ImGui::Text("Please load a level using the new loader!");
            }
        }

        if (ImGui::CollapsingHeader("Animated Textile Viewer")) {
            if (TextureManager::.numAnimatedTiles() > 0) {
                static int index = 0;
                static int tile = TextureManager::.getFirstTileAnimation(index);
                ImGui::PushItemWidth(ImGui::GetWindowWidth() * 0.5f);
                if (ImGui::SliderInt("##animslide", &index, 0, TextureManager::.numAnimatedTiles() - 1)) {
                    tile = TextureManager::.getFirstTileAnimation(index);
                }
                ImGui::PopItemWidth();
                ImGui::SameLine();
                if (ImGui::Button("+##animplus", ImVec2(0, 0), true)) {
                    if (index < (TextureManager::.numAnimatedTiles() - 1))
                        index++;
                    else
                        index = 0;
                    tile = TextureManager::.getFirstTileAnimation(index);
                }
                ImGui::SameLine();
                if (ImGui::Button("-##animminus", ImVec2(0, 0), true)) {
                    if (index > 0)
                        index--;
                    else
                        index = TextureManager::.numAnimatedTiles() - 1;
                    tile = TextureManager::.getFirstTileAnimation(index);
                }
                ImGui::SameLine();
                if (ImGui::Button("Show##animshow")) {
                    visibleAnim = true;
                    visibleTex = false;
                    visibleTile = false;
                    visibleSprite = false;
                }
                ImGui::SameLine();
                if (ImGui::Button("Clear##animclear")) {
                    getRender().debugDisplayTextile();
                    visibleAnim = false;
                }
                if (visibleAnim) {
                    static int fr = 0;
                    if (fr > 0) {
                        fr--;
                    } else {
                        getRender().debugDisplayTextile(tile,
                                                        ImGui::GetWindowPos().x - (ImGui::GetWindowWidth() / 2),
                                                        ImGui::GetWindowPos().y,
                                                        (ImGui::GetWindowWidth() / 2), (ImGui::GetWindowWidth() / 2));
                        fr = RunTime::getFPS() / 2;
                        tile = TextureManager::.getNextTileAnimation(tile);
                    }
                    ImGui::Text("Current Tile: %d", tile);
                }
            } else {
                ImGui::Text("Please load a level with animated textures!");
            }
        }

        if (ImGui::CollapsingHeader("Sprite Sequence Viewer")) {
            if (getWorld().sizeSprite() <= 0) {
                ImGui::Text("Please load a level containing sprites!");
            } else {
                static int index = 0;
                static int sprite = 0;
                ImGui::PushItemWidth(ImGui::GetWindowWidth() * 0.5f);
                if (ImGui::SliderInt("##spriteslide", &index, 0, getWorld().sizeSprite() - 1))
                    sprite = 0;
                ImGui::PopItemWidth();
                ImGui::SameLine();
                if (ImGui::Button("+##spriteplus", ImVec2(0, 0), true)) {
                    if (index < (getWorld().sizeSprite() - 1))
                        index++;
                    else
                        index = 0;
                    sprite = 0;
                }
                ImGui::SameLine();
                if (ImGui::Button("-##spriteminus", ImVec2(0, 0), true)) {
                    if (index > 0)
                        index--;
                    else
                        index = getWorld().sizeSprite() - 1;
                    sprite = 0;
                }
                ImGui::SameLine();
                if (ImGui::Button("Show##spriteshow")) {
                    visibleSprite = true;
                    visibleTex = false;
                    visibleTile = false;
                    visibleAnim = false;
                    sprite = 0;
                }
                ImGui::SameLine();
                if (ImGui::Button("Clear##spriteclear")) {
                    getRender().debugDisplaySprite();
                    visibleSprite = false;
                }
                if (visibleSprite) {
                    static int fr = 0;
                    if (fr > 0) {
                        fr--;
                    } else {
                        getRender().debugDisplaySprite(index, sprite,
                                                       ImGui::GetWindowPos().x - (ImGui::GetWindowWidth() / 2),
                                                       ImGui::GetWindowPos().y,
                                                       (ImGui::GetWindowWidth() / 2), (ImGui::GetWindowWidth() / 2));
                        fr = RunTime::getFPS() / 10;
                        if (sprite < (getWorld().getSprite(index).size() - 1))
                            sprite++;
                        else
                            sprite = 0;
                    }

                    ImGui::Text("Sprite %d/%d", sprite + 1, getWorld().getSprite(index).size());
                }
            }
        }
        */

        if (ImGui::CollapsingHeader("ImGui/Debug UI Help")) {
            //ImGui::TextWrapped("DebugViewer Textures/Textiles/Sprites will be drawn on"
            //                   " the left side and scale with the size of this window!");
            //ImGui::Separator();
            ImGui::ShowUserGuide();
            ImGui::Separator();
            if (ImGui::Button("Show/Hide Test Window")) {
                showTestWindow = !showTestWindow;
            }
        }
    }
    ImGui::End();

    if (showTestWindow)
        ImGui::ShowTestWindow();

    ImGui::Render();
}

void UI::shutdown() {
    ImGui::Shutdown();
}

void UI::handleKeyboard(KeyboardButton key, bool pressed) {
    ImGuiIO& io = ImGui::GetIO();
    io.KeysDown[key] = pressed;
    io.KeyCtrl = io.KeysDown[leftctrlKey] | io.KeysDown[rightctrlKey];
    io.KeyShift = io.KeysDown[leftshiftKey] | io.KeysDown[rightshiftKey];

    keyboardEvents.push_back(std::make_tuple(key, pressed));

    if ((key == leftguiKey) || (key == rightguiKey))
        metaKeyIsActive = pressed;
}

void UI::handleText(char* text, bool notFinished) {
    if (notFinished)
        return;

    ImGuiIO& io = ImGui::GetIO();
    while (*text != '\0') {
        io.AddInputCharacter(*text);
        text++;
    }
}

void UI::handleMouseClick(unsigned int x, unsigned int y, KeyboardButton button, bool released) {
    ImGuiIO& io = ImGui::GetIO();
    io.MousePos = ImVec2((float)x, (float)y);
    if (button == leftmouseKey) {
        io.MouseDown[0] = !released;
    } else if (button == rightmouseKey) {
        io.MouseDown[1] = !released;
    } else if (button == middlemouseKey) {
        io.MouseDown[2] = !released;
    } else if (button == fourthmouseKey) {
        io.MouseDown[3] = !released;
    } else if (button == fifthmouseKey) {
        io.MouseDown[4] = !released;
    }

    clickEvents.push_back(std::make_tuple(x, y, button, released));
}

void UI::handleMouseMotion(int xrel, int yrel, int xabs, int yabs) {
    ImGuiIO& io = ImGui::GetIO();
    io.MousePos = ImVec2((float)xabs, (float)yabs);

    motionEvents.push_back(std::make_tuple(xrel, yrel, xabs, yabs));
}

void UI::handleMouseScroll(int xrel, int yrel) {
    ImGuiIO& io = ImGui::GetIO();
    io.MouseWheel += yrel;

    scrollEvents.push_back(std::make_tuple(xrel, yrel));
}

void UI::handleControllerAxis(float value, KeyboardButton axis) {
    getGame().handleControllerAxis(value, axis);
}

void UI::handleControllerButton(KeyboardButton button, bool released) {
    getGame().handleControllerButton(button, released);
}

void UI::renderImGui(ImDrawList** const cmd_lists, int cmd_lists_count) {
    if (cmd_lists_count == 0)
        return;

    static ShaderBuffer vert, uv, col;

    glEnable(GL_SCISSOR_TEST);
    glDisable(GL_DEPTH_TEST);

    imguiShader.use();
    imguiShader.loadUniform(0, Window::getSize());
    imguiShader.loadUniform(1, fontTex, TextureStorage::SYSTEM);
    vert.bindBuffer(0, 2);
    uv.bindBuffer(1, 2);
    col.bindBuffer(2, 4);

    /*! \fixme Don't copy data
     * The GL calls and the shaders can probably be slightly altered
     * to avoid copying all the vertices, uvs and colors again here.
     */

    for (int i = 0; i < cmd_lists_count; i++) {
        auto& commands = cmd_lists[i]->commands;
        auto& buffer = cmd_lists[i]->vtx_buffer;

        int offset = 0;
        for (int n = 0; n < commands.size(); n++) {
            std::vector<glm::vec2> vertices;
            std::vector<glm::vec2> uvs;
            std::vector<glm::vec4> colors;

            for (int v = 0; v < commands[n].vtx_count; v++) {
                vertices.push_back(glm::vec2(buffer[offset + v].pos.x, buffer[offset + v].pos.y));
                uvs.push_back(glm::vec2(buffer[offset + v].uv.x, buffer[offset + v].uv.y));

                float r, g, b, a;
                a = ((buffer[offset + v].col & 0xFF000000) >> 24) / 255.0f;
                b = ((buffer[offset + v].col & 0x00FF0000) >> 16) / 255.0f;
                g = ((buffer[offset + v].col & 0x0000FF00) >> 8) / 255.0f;
                r = (buffer[offset + v].col & 0x000000FF) / 255.0f;
                colors.push_back(glm::vec4(r, g, b, a));
            }

            offset += commands[n].vtx_count;

            vert.bufferData(vertices);
            uv.bufferData(uvs);
            col.bufferData(colors);

            glScissor(commands[n].clip_rect.x,
                      Window::getSize().y - commands[n].clip_rect.w,
                      commands[n].clip_rect.z - commands[n].clip_rect.x,
                      commands[n].clip_rect.w - commands[n].clip_rect.y);

            glDrawArrays(GL_TRIANGLES, 0, vertices.size());
        }
    }

    vert.unbind(0);
    uv.unbind(1);
    col.unbind(2);

    glEnable(GL_DEPTH_TEST);
    glDisable(GL_SCISSOR_TEST);
}

// --------------------------------------
// *INDENT-OFF*

const char* UI::imguiShaderVertex = R"!?!(
#version 330 core

layout(location = 0) in vec2 vertexPosition_screen;
layout(location = 1) in vec2 vertexUV;
layout(location = 2) in vec4 vertexColor;

out vec2 UV;
out vec4 FragColor;

uniform vec2 screen;

void main() {
    vec2 halfScreen = screen / 2;
    vec2 vertexPosition_homogenous = (vertexPosition_screen - halfScreen) / halfScreen;

    gl_Position = vec4(vertexPosition_homogenous.x, -vertexPosition_homogenous.y, 0, 1);
    UV = vertexUV;
    FragColor = vertexColor;
}
)!?!";

const char* UI::imguiShaderFragment = R"!?!(
#version 330 core

in vec2 UV;
in vec4 FragColor;

out vec4 color;

uniform sampler2D textureSampler;

void main() {
    color = texture(textureSampler, UV) * FragColor;
}
)!?!";

// --------------------------------------
// *INDENT-ON*

