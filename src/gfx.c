#include "gfx.h"

SDL_Window* createWindow(int width, int height)
{
    if (SDL_Init(SDL_INIT_VIDEO) != 0)
    {
        printf("unabled to set video mode\n");
        exit(1);
    }

    SDL_GL_SetAttribute(SDL_GL_CONTEXT_PROFILE_MASK, SDL_GL_CONTEXT_PROFILE_CORE);
    SDL_GL_SetAttribute(SDL_GL_CONTEXT_MAJOR_VERSION, 4);
    SDL_GL_SetAttribute(SDL_GL_CONTEXT_MINOR_VERSION, 3);
    SDL_GL_SetAttribute(SDL_GL_STENCIL_SIZE, 8);

    SDL_Window *window = SDL_CreateWindow(
            "orbitsgl",
            SDL_WINDOWPOS_UNDEFINED,
            SDL_WINDOWPOS_UNDEFINED,
            width,
            height,
            SDL_WINDOW_OPENGL);

    // this returns something but we don't need it, so omitted capturing the value to avoid
    // compiler warning
    SDL_GL_CreateContext(window);

    glewExperimental = GL_TRUE;
    glewInit();

    printf("%s\n", glGetString(GL_RENDERER));

    return window;
}

GLuint compileShader(const char* path, GLenum type)
{
    // read file into a buffer
    char* buffer;
    buffer = calloc(1, getFileSize(path)+1);
    readFile(path, buffer);

    // try to compile shader
    const char* src = buffer;
    GLuint shader = glCreateShader(type);
    glShaderSource(shader, 1, &src, NULL);
    glCompileShader(shader);

    // free memory allocated for buffer
    free(buffer);

    // check results of compilation
    GLint result = GL_FALSE;
    int logLength;
    glGetShaderiv(shader, GL_COMPILE_STATUS, &result);
    glGetShaderiv(shader, GL_INFO_LOG_LENGTH, &logLength);
    if (logLength > 1)
    {
        // something is in the log so we failed to compile
        char err[logLength];
        glGetShaderInfoLog(shader, logLength, NULL, err);

        fputs("error compiling shader ", stderr);
        fputs(path, stderr);
        fputs("\n", stderr);
        fputs(err, stderr);

        exit(1);
    }

    return shader;
}

GLuint compileShaderProgram(const char* vsPath, const char* fsPath)
{
    GLuint vs = compileShader(vsPath, GL_VERTEX_SHADER);
    GLuint fs = compileShader(fsPath, GL_FRAGMENT_SHADER);

    GLuint shaderProgram = glCreateProgram();
    glAttachShader(shaderProgram, vs);
    glAttachShader(shaderProgram, fs);

    glDeleteShader(vs);
    glDeleteShader(fs);

    glLinkProgram(shaderProgram);

    GLint result = GL_FALSE;
    glGetProgramiv(shaderProgram, GL_LINK_STATUS, &result);
    if (result == GL_FALSE)
    {
        GLint logLength = 0;
        glGetProgramiv(shaderProgram, GL_INFO_LOG_LENGTH, &logLength);
        char err[logLength];
        glGetProgramInfoLog(shaderProgram, logLength, NULL, err);

        fputs("error linking shader program\n", stderr);
        fputs(err, stderr);

        exit(1);
    }

    return shaderProgram;
}
