/*!
 * \file include/system/Shader.h
 * \brief OpenGL Shader implementation
 *
 * \author xythobuz
 */

#ifndef _SHADER_H_
#define _SHADER_H_

#include <vector>

#include "TextureManager.h"

class ShaderBuffer {
  public:
    ShaderBuffer() : created(false), buffer(0), boundSize(0) { }
    ~ShaderBuffer();

    void bufferData(int elem, int size, void* data);

    template<typename T>
    void bufferData(std::vector<T> v)
        { bufferData(v.size(), sizeof(T), &v[0]); }

    void bindBuffer();
    void bindBuffer(int location, int size);
    void unbind(int location);

    int getSize() { return boundSize; }

  private:
    bool created;
    unsigned int buffer;
    int boundSize;
};

class Shader {
  public:
    Shader() : programID(-1) { }
    ~Shader();

    int compile(const char* vertex, const char* fragment);
    void use();

    int addUniform(const char* name);
    unsigned int getUniform(int n);

    void loadUniform(int uni, glm::vec2 vec);
    void loadUniform(int uni, glm::vec4 vec);
    void loadUniform(int uni, glm::mat4 mat);
    void loadUniform(int uni, int texture, TextureStorage store);

    static int initialize();
    static void shutdown();

    static void drawGL(ShaderBuffer& vertices, ShaderBuffer& uvs, glm::vec4 color, unsigned int texture,
                       TextureStorage store = TextureStorage::SYSTEM);

    static void drawGL(ShaderBuffer& vertices, ShaderBuffer& uvs, unsigned int texture, glm::mat4 MVP,
                       TextureStorage store = TextureStorage::GAME);
    static void drawGL(ShaderBuffer& vertices, ShaderBuffer& uvs, ShaderBuffer& indices,
                       unsigned int texture, glm::mat4 MVP,
                       TextureStorage store = TextureStorage::GAME);

    static void drawGL(ShaderBuffer& vertices, ShaderBuffer& colors, glm::mat4 MVP,
                       unsigned int mode = GL_TRIANGLES);
    static void drawGL(ShaderBuffer& vertices, ShaderBuffer& colors, ShaderBuffer& indices,
                       glm::mat4 MVP, unsigned int mode = GL_TRIANGLES);

  private:
    int programID;
    std::vector<unsigned int> uniforms;

    static Shader textShader;
    static const char* textShaderVertex;
    static const char* textShaderFragment;

    static Shader textureShader;
    static const char* textureShaderVertex;
    static const char* textureShaderFragment;

    static Shader colorShader;
    static const char* colorShaderVertex;
    static const char* colorShaderFragment;

    static unsigned int vertexArrayID;
};

#endif
