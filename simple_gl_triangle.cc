// -*- mode: c++; coding: utf-8-unix; tab-width: 4; -*-
/**
 * @file
 * @brief
 *
 * create    : <2015-02-14 16:30:20 it_lives_vainly>
 * $Id$
 */
#include "simple_gl_triangle.h"
#include <cmath>
#include <stdlib.h>


namespace gl_sample{

GLint CreateShader(GLenum type, const char* vsh_source)
{
    GLint object_id = glCreateShader(type);
    //DBG_ASSERT(glGetError() == GL_NO_ERROR, "GL_VERTEX_SHADER が失敗");
    glShaderSource(object_id, 1, &vsh_source, NULL);
    glCompileShader(object_id);

    GLint compile_state = 0;
    glGetShaderiv(object_id, GL_COMPILE_STATUS, &compile_state);
    if (compile_state == GL_FALSE) {
        GLint info_len = 0;
        glGetShaderiv(object_id, GL_INFO_LOG_LENGTH, &info_len);

        if (info_len > 0) {
            char* info_log = (char*)malloc(sizeof(char) * info_len);

            glGetShaderInfoLog(object_id, info_len, NULL, info_log);
            //DBG_ASSERT(false, info_log);
        }
        return 0;
    }

    return object_id;
}

GLint CreateProgram(GLint vs, GLint fs)
{
    GLuint program = glCreateProgram();

    if (program == 0) {
        return 0;
    }

    glAttachShader(program, vs);
    glAttachShader(program, fs);

    // リンク
    glLinkProgram(program);
    //DBG_ASSERT(glGetError() == GL_NO_ERROR, "プログラムのリンクに失敗");

    // リンク結果のチェック
    GLint linked = 0;
    glGetProgramiv(program, GL_LINK_STATUS, &linked);
    if (!linked) {
        GLint info_len = 0;
        glGetShaderiv(program, GL_INFO_LOG_LENGTH, &info_len);

        if (info_len > 0) {
            char* info_log = (char*)malloc(sizeof(char) * info_len);

            glGetProgramInfoLog(program, info_len, NULL, info_log);

            //DBG_ASSERT(glGetError() == GL_NO_ERROR, info_log);

            free(info_log);
        }else{
            //DBG_ASSERT(false, "プログラムのリンクに失敗");
        }

        return 0;
    }
    return program;
}

GLint InitShaderProgram()
{
#if (PS_PLATFORM == PS_OSX)
    const char* vsh_source = ("#version 410\n"
                              "in vec4 a_Position;\n"
                              "in vec4 a_Color;\n"
                              "\n"
                              "uniform mat4 WorldViewProjection;\n"
                              "\n"
                              "out vec4 v_Color;\n"
                              "\n"
                              "void main()\n"
                              "{\n"
                              "     gl_Position = WorldViewProjection * a_Position;\n"
                              "     v_Color = a_Color;\n"
                              "}\n");

    const char* fsh_source = ("#version 410\n"
                              "#define PRECISION\n"
                              "PRECISION\n"
                              "in vec4 v_Color;\n"
                              "out vec4 out_Color;\n"
                              "\n"
                              "void main()\n"
                              "{\n"
                              "    out_Color = v_Color;\n"
                              "}\n");
#else
    const char* vsh_source = ("#version 300 es\n"
                              "in vec4 a_Position;\n"
                              "in vec4 a_Color;\n"
                              "\n"
                              "uniform mat4 WorldViewProjection;\n"
                              "\n"
                              "out vec4 v_Color;\n"
                              "\n"
                              "void main()\n"
                              "{\n"
                              "     gl_Position = WorldViewProjection * a_Position;\n"
                              "     v_Color = a_Color;\n"
                              "}\n");

    const char* fsh_source = ("#version 300 es\n"
                              "#define PRECISION precision mediump float;\n"
                              "PRECISION\n"
                              "in vec4 v_Color;\n"
                              "out vec4 out_Color;\n"
                              "\n"
                              "void main()\n"
                              "{\n"
                              "    out_Color = v_Color;\n"
                              "}\n");

#endif

    GLint vertex_object_id = CreateShader(GL_VERTEX_SHADER, vsh_source);
    GLint fragment_object_id = CreateShader(GL_FRAGMENT_SHADER, fsh_source);

    GLuint program = CreateProgram(vertex_object_id, fragment_object_id);

    // attrib
    glBindAttribLocation(program, 0, "a_Position");
    glBindAttribLocation(program, 1, "a_Color");

    return program;

}

//void TestDraw(GLContext* gc)
void TestDraw()
{
    static GLint program = 0;
    if (program == 0) {
        program = InitShaderProgram();
    }

    glUseProgram(program);

    static float y = 0.0f;
    y += 0.01f;

    float s = std::sin(y);
    float c = std::cos(y);

    // uniform
    GLuint location = glGetUniformLocation(program, "WorldViewProjection");
    GLfloat m[16] = {    c, 0.0f,    s, 0.0f,
                      0.0f, 1.0f, 0.0f, 0.0f,
                        -s, 0.0f,    c, 0.0f,
                      0.0f, 0.0f, 0.0f, 1.0f };
    glUniformMatrix4fv(location, 1, false, m);
    //DBG_ASSERT(glGetError() == GL_NO_ERROR, "glUniformMatrix4fv に失敗");


    //wglMakeCurrent(hdc, g_gl_context);
    {
        glClearColor(0.0f, 0.0f, 0.0f, 1.0f);
        glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);

        struct VertexData{
            float pos[3];
            float color[4];
        };

        VertexData vertices[] = {
            { { 0.0f, 0.5f, 0.0f}, { 1.0f, 0.0f, 0.0f, 1.0f} },
            { { -0.5f, -0.5f, 0.0f}, { 0.0f, 1.0f, 0.0f, 1.0f} },
            { { 0.5f, -0.5f, 0.0f}, { 0.0f, 0.0f, 1.0f, 1.0f} },
        };

        // VBO
        GLuint vbo;
        glGenBuffers(1, &vbo);
        glBindBuffer(GL_ARRAY_BUFFER, vbo);
        glBufferData(GL_ARRAY_BUFFER, sizeof(VertexData) * 3, vertices, GL_STATIC_DRAW);

        // VAO
        GLuint vao;
        glGenVertexArrays(1, &vao);
        glBindVertexArray(vao);

        {
            //glVertexAttribPointer(0, 3, GL_FLOAT, false, sizeof(VertexData), (void*)vertices[0].pos);
            glVertexAttribPointer(0, 3, GL_FLOAT, false, sizeof(VertexData), (void*)0);
            glEnableVertexAttribArray(0);

            //            glVertexAttribPointer(1, 4, GL_FLOAT, false, sizeof(VertexData), (void*)vertices[0].color);
            glVertexAttribPointer(1, 4, GL_FLOAT, false, sizeof(VertexData), (void*)(sizeof(float) * 3));
            glEnableVertexAttribArray(1);

            glDrawArrays(GL_TRIANGLES, 0, 3);
            //DBG_ASSERT(glGetError() == GL_NO_ERROR, "なにかに失敗");
        }

        glDeleteBuffers(1, &vbo);
        glDeleteBuffers(1, &vao);

        glFlush();
    }
    //SwapBuffers(hdc);
    //wglMakeCurrent(0, 0);
}

} // end ns gl_sample

//===
// EOF
//===
