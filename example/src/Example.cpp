#define STB_IMAGE_IMPLEMENTATION

#include <gles2pp/gles2pp.hpp>

#include <SDL3/SDL.h>
#include <SDL3/SDL_events.h>
#include <SDL3/SDL_init.h>
#include <SDL3/SDL_main.h>
#include <SDL3/SDL_timer.h>
#include <SDL3/SDL_video.h>
#include <stb/stb_image.h>

#ifdef __EMSCRIPTEN__
#include <emscripten.h>
#include <emscripten/html5.h>
#endif

#include <cmath>
#include <cstddef>
#include <cstdint>
#include <cstdlib>
#include <exception>
#include <iostream>
#include <span>
#include <stdexcept>
#include <string>
#include <thread>

class Context;

class SDL
{
public:
    SDL(SDL_InitFlags t_flags)
    {
        if (!SDL_Init(t_flags))
        {
            throw std::runtime_error("Failed to initialize SDL");
        }
    }

    ~SDL()
    {
        SDL_Quit();
    }

    SDL(const SDL&) = delete;
    auto operator=(const SDL&) -> SDL& = delete;
    SDL(SDL&&) = delete;
    auto operator=(SDL&&) -> SDL& = delete;
};

class Window
{
    friend Context;

public:
    Window(const std::string& t_title, unsigned t_width, unsigned t_height, SDL_WindowFlags t_flags)
        : m_handle{SDL_CreateWindow(t_title.data(), static_cast<int>(t_width), static_cast<int>(t_height), t_flags)}
    {
        if (m_handle == nullptr)
        {
            throw std::runtime_error("Failed to create window");
        }
    }

    ~Window()
    {
        SDL_DestroyWindow(m_handle);
    }

    void swap()
    {
        SDL_GL_SwapWindow(m_handle);
    }

    Window(const Window&) = delete;
    auto operator=(const Window&) -> Window& = delete;
    Window(Window&&) = delete;
    auto operator=(Window&&) -> Window& = delete;

private:
    SDL_Window* m_handle;
};

class Context
{
public:
    Context(Window& t_window) : m_handle{SDL_GL_CreateContext(t_window.m_handle)}
    {
        if (m_handle == nullptr)
        {
            throw std::runtime_error("Failed to create GL context");
        }
    }

    ~Context()
    {
        SDL_GL_DestroyContext(m_handle);
    }

    Context(const Context&) = delete;
    auto operator=(const Context&) -> Context& = delete;
    Context(Context&&) = delete;
    auto operator=(Context&&) -> Context& = delete;

private:
    SDL_GLContext m_handle;
};

class Image
{
public:
    Image(const std::string& t_path, unsigned t_channels = 4)
        : m_handle{stbi_load(t_path.data(), &m_width, &m_height, &m_channels, static_cast<int>(t_channels))}
    {
        if (m_handle == nullptr)
        {
            throw std::runtime_error("Failed to load image");
        }
    }

    ~Image()
    {
        stbi_image_free(m_handle);
    }

    [[nodiscard]] auto create_texture(gles2pp::easy::Texture2D::ScaleMode t_scale_mode) const
        -> gles2pp::easy::Texture2D
    {
        return gles2pp::easy::Texture2D{static_cast<GLuint>(m_width), static_cast<GLuint>(m_height), data(),
                                        t_scale_mode};
    }

    [[nodiscard]] auto data() const -> std::span<const std::byte>
    {
        return std::span<const std::byte>{reinterpret_cast<const std::byte*>(m_handle),
                                          static_cast<std::size_t>(m_width) * static_cast<std::size_t>(m_height) *
                                              static_cast<std::size_t>(m_channels)};
    }

    Image(const Image&) = delete;
    auto operator=(const Image&) -> Image& = delete;
    Image(Image&&) = delete;
    auto operator=(Image&&) -> Image& = delete;

private:
    int m_width{0};
    int m_height{0};
    int m_channels{0};
    stbi_uc* m_handle;
};

class Game
{
public:
    constexpr static unsigned WINDOW_WIDTH{640};
    constexpr static unsigned WINDOW_HEIGHT{360};
    constexpr static std::size_t BUFFER_SIZE{50};

    Game()
        : m_sdl{SDL_INIT_VIDEO}, m_window{[]() {
              SDL_GL_SetAttribute(SDL_GL_CONTEXT_PROFILE_MASK, SDL_GL_CONTEXT_PROFILE_ES);
              SDL_GL_SetAttribute(SDL_GL_CONTEXT_MAJOR_VERSION, 2);
              SDL_GL_SetAttribute(SDL_GL_CONTEXT_MINOR_VERSION, 0);
              return Window{"Example", WINDOW_WIDTH, WINDOW_HEIGHT, SDL_WINDOW_OPENGL | SDL_WINDOW_RESIZABLE};
          }()},
          m_context{m_window}, m_array_buffer{BUFFER_SIZE}, m_array_element_buffer{BUFFER_SIZE},
          m_vertex_attributes{std::array{
              gles2pp::easy::VertexAttribute{"a_position", gles2pp::ComponentSize::FOUR, gles2pp::ComponentType::FLOAT},
              gles2pp::easy::VertexAttribute{"a_uv", gles2pp::ComponentSize::TWO, gles2pp::ComponentType::FLOAT},
              gles2pp::easy::VertexAttribute{"a_tint", gles2pp::ComponentSize::FOUR, gles2pp::ComponentType::FLOAT}}},
          m_uniforms{gles2pp::easy::Uniform{"u_sampler"}},
          m_texture_background{
              Image{"res/texture_background.png"}.create_texture(gles2pp::easy::Texture2D::ScaleMode::LINEAR)},
          m_texture_sprite{
              Image{"res/texture_sprite.png"}.create_texture(gles2pp::easy::Texture2D::ScaleMode::NEAREST)},
          m_program{gles2pp::easy::VertexShader{"res/vertex_shader.vert"},
                    gles2pp::easy::FragmentShader{"res/fragment_shader.frag"}, m_vertex_attributes, m_uniforms},
          m_aspect_ratio{static_cast<float>(WINDOW_WIDTH) / static_cast<float>(WINDOW_HEIGHT)}
    {
        // Set sampler to texture unit 0
        gles2pp::uniform(m_uniforms[0].get_location(), 0);

        // Enable vertex attribute arrays
        m_vertex_attributes.enable();

        // Call glVertexAttribPointer for all attributes
        m_vertex_attributes.pointer();

        // Enable face culling
        gles2pp::enable(gles2pp::Capability::CULL_FACE);

        // Enable blending
        gles2pp::enable(gles2pp::Capability::BLEND);
        blend_function(gles2pp::SourceBlendFactor::SOURCE_ALPHA,
                       gles2pp::DestinationBlendFactor::ONE_MINUS_SOURCE_ALPHA);
    }

    auto frame() -> bool
    {
        for (SDL_Event event; SDL_PollEvent(&event);)
        {
            if (event.type == SDL_EVENT_QUIT)
            {
                return false;
            }
            if (event.type == SDL_EVENT_WINDOW_PIXEL_SIZE_CHANGED)
            {
                gles2pp::viewport(event.window.data1, event.window.data2);
                m_aspect_ratio = static_cast<float>(event.window.data1) / static_cast<float>(event.window.data2);
            }
        }

        // Clear screen and buffers
        gles2pp::clear();
        m_array_buffer.clear();
        m_array_element_buffer.clear();

        // Render background
        m_texture_background.bind();
        const std::array<gles2pp::Float, 40> background_vertices{-1, -1, 0, 1, 0,
                                                                 0,  1,  1, 0, 1,
                                                                 -1, 1,  0, 1, 0,
                                                                 1,  1,  1, 1, 1,
                                                                 1,  1,  0, 1, 1.0F / m_aspect_ratio,
                                                                 1,  1,  1, 1, 1,
                                                                 1,  -1, 0, 1, 1.0F / m_aspect_ratio,
                                                                 0,  1,  1, 1, 1};
        const std::array<gles2pp::UShort, 6> background_indices{2, 1, 0, 0, 3, 2};
        m_array_buffer.insert(background_vertices);
        m_array_element_buffer.insert(background_indices);
        m_array_buffer.subdata();
        m_array_element_buffer.subdata();
        m_array_element_buffer.draw();

        // Clear buffers
        m_array_buffer.clear();
        m_array_element_buffer.clear();

        // Render sprite
        m_texture_sprite.bind();
        const std::array<gles2pp::Float, 40> sprite_vertices{
            -1.0F * 0.5F / m_aspect_ratio, -1 * 0.5, 0, 1, 0, 0, 1, 1, 1, 0,
            -1.0F * 0.5F / m_aspect_ratio, 1 * 0.5,  0, 1, 0, 1, 1, 1, 1, 1,
            1.0F * 0.5F / m_aspect_ratio,  1 * 0.5,  0, 1, 1, 1, 1, 1, 1, 1,
            1.0F * 0.5F / m_aspect_ratio,  -1 * 0.5, 0, 1, 1, 0, 1, 1, 1, 0};
        const std::array<gles2pp::UShort, 6> sprite_indices{2, 1, 0, 0, 3, 2};
        m_array_buffer.insert(sprite_vertices);
        m_array_element_buffer.insert(sprite_indices);
        m_array_buffer.subdata();
        m_array_element_buffer.subdata();
        m_array_element_buffer.draw();

        m_window.swap();
        return true;
    }

private:
    SDL m_sdl;
    Window m_window;
    Context m_context;
    gles2pp::easy::ArrayBuffer m_array_buffer;
    gles2pp::easy::ArrayElementBuffer m_array_element_buffer;
    gles2pp::easy::VertexAttributes<3> m_vertex_attributes;
    gles2pp::easy::Uniforms<1> m_uniforms;
    gles2pp::easy::Texture2D m_texture_background;
    gles2pp::easy::Texture2D m_texture_sprite;
    gles2pp::easy::Program m_program;
    float m_aspect_ratio;
};

auto main(int t_argument_size, char* t_arguments[]) -> int
try
{
    stbi_set_flip_vertically_on_load(1);
    Game game;

#ifdef __EMSCRIPTEN__
    emscripten_set_main_loop_arg(
        [](void* t_user_data) {
            if (!static_cast<Game*>(t_user_data)->frame())
            {
                emscripten_cancel_main_loop();
            }
        },
        &game, 0, true);
#else
    while (game.frame())
    {
    }
#endif

    return EXIT_SUCCESS;
}
catch (const std::exception& exception)
{
    std::cerr << exception.what() << '\n';
    return EXIT_FAILURE;
}