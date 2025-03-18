#define STB_IMAGE_IMPLEMENTATION

#include <gles2pp/gles2pp.hpp>

#include <SDL3/SDL.h>
#include <SDL3/SDL_events.h>
#include <SDL3/SDL_init.h>
#include <SDL3/SDL_main.h>
#include <SDL3/SDL_timer.h>
#include <SDL3/SDL_video.h>
#include <stb/stb_image.h>

#include <cmath>
#include <cstddef>
#include <cstdint>
#include <cstdlib>
#include <exception>
#include <iostream>
#include <span>
#include <stdexcept>
#include <string>

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

auto main(int t_argument_size, char* t_arguments[]) -> int
try
{
    // Initialize everything
    SDL sdl(SDL_INIT_VIDEO);
    SDL_GL_SetAttribute(SDL_GL_CONTEXT_PROFILE_MASK, SDL_GL_CONTEXT_PROFILE_ES);
    SDL_GL_SetAttribute(SDL_GL_CONTEXT_MAJOR_VERSION, 2);
    SDL_GL_SetAttribute(SDL_GL_CONTEXT_MINOR_VERSION, 0);
    constexpr unsigned WINDOW_WIDTH{640};
    constexpr unsigned WINDOW_HEIGHT{360};
    Window window{"Example", WINDOW_WIDTH, WINDOW_HEIGHT, SDL_WINDOW_OPENGL};
    Context context{window};
    constexpr std::size_t BUFFER_SIZE{50};

    // Create buffers
    gles2pp::easy::ArrayBuffer array_buffer{BUFFER_SIZE};
    gles2pp::easy::ArrayElementBuffer array_element_buffer{BUFFER_SIZE};

    // Specify Generic Vertex Attributes
    gles2pp::easy::VertexAttributes vertex_attributes{std::array{
        gles2pp::easy::VertexAttribute{"a_position", gles2pp::ComponentSize::FOUR, gles2pp::ComponentType::FLOAT},
        gles2pp::easy::VertexAttribute{"a_uv", gles2pp::ComponentSize::TWO, gles2pp::ComponentType::FLOAT},
        gles2pp::easy::VertexAttribute{"a_tint", gles2pp::ComponentSize::FOUR, gles2pp::ComponentType::FLOAT}}};

    // Specify Uniforms
    gles2pp::easy::Uniforms uniforms{gles2pp::easy::Uniform{"u_sampler"}};

    // Get Vertex Attribute and Uniform locations
    gles2pp::easy::Program program{"res/vertex_shader.vert", "res/fragment_shader.frag", vertex_attributes, uniforms};

    // Set sampler to texture unit 0
    gles2pp::uniform(uniforms[0].get_location(), 0);

    // Enable vertex attribute arrays
    vertex_attributes.enable();

    // Call glVertexAttribPointer for all attributes
    vertex_attributes.pointer();

    // Load textures
    stbi_set_flip_vertically_on_load(1);
    auto texture_background =
        Image{"res/texture_background.png"}.create_texture(gles2pp::easy::Texture2D::ScaleMode::LINEAR);
    auto texture_sprite = Image{"res/texture_sprite.png"}.create_texture(gles2pp::easy::Texture2D::ScaleMode::NEAREST);

    // Enable face culling
    gles2pp::enable(gles2pp::Capability::CULL_FACE);

    // Enable blending
    gles2pp::enable(gles2pp::Capability::BLEND);
    blend_function(gles2pp::SourceBlendFactor::SOURCE_ALPHA, gles2pp::DestinationBlendFactor::ONE_MINUS_SOURCE_ALPHA);

    // Main loop
    while ([&]() {
        for (SDL_Event event; SDL_PollEvent(&event);)
        {
            if (event.type == SDL_EVENT_QUIT)
            {
                return false;
            }
        }

        // Clear screen and buffers
        gles2pp::clear();
        array_buffer.clear();
        array_element_buffer.clear();

        constexpr auto aspect_ratio =
            static_cast<gles2pp::Float>(WINDOW_WIDTH) / static_cast<gles2pp::Float>(WINDOW_HEIGHT);

        { // Render background
            texture_background.bind();
            const std::array<gles2pp::Float, 40> background_vertices{-1, -1, 0, 1, 0,
                                                                     0,  1,  1, 1, 1,
                                                                     -1, 1,  0, 1, 0,
                                                                     1,  1,  1, 1, 1,
                                                                     1,  1,  0, 1, 1.0 / aspect_ratio,
                                                                     1,  1,  1, 1, 1,
                                                                     1,  -1, 0, 1, 1.0 / aspect_ratio,
                                                                     0,  1,  1, 1, 1};
            const std::array<gles2pp::UShort, 6> background_indices{2, 1, 0, 0, 3, 2};
            array_buffer.insert(background_vertices);
            array_element_buffer.insert(background_indices);
            array_buffer.subdata();
            array_element_buffer.subdata();
            array_element_buffer.draw();
        }

        // Clear buffers
        array_buffer.clear();
        array_element_buffer.clear();

        { // Render sprite
            texture_sprite.bind();
            const std::array<gles2pp::Float, 40> sprite_vertices{
                -1 * 0.5 / aspect_ratio, -1 * 0.5, 0, 1, 0, 0, 1, 1, 1, 0,
                -1 * 0.5 / aspect_ratio, 1 * 0.5,  0, 1, 0, 1, 1, 1, 1, 1,
                1 * 0.5 / aspect_ratio,  1 * 0.5,  0, 1, 1, 1, 1, 1, 1, 1,
                1 * 0.5 / aspect_ratio,  -1 * 0.5, 0, 1, 1, 0, 1, 1, 1, 0};
            const std::array<gles2pp::UShort, 6> sprite_indices{2, 1, 0, 0, 3, 2};
            array_buffer.insert(sprite_vertices);
            array_element_buffer.insert(sprite_indices);
            array_buffer.subdata();
            array_element_buffer.subdata();
            array_element_buffer.draw();
        }

        window.swap();
        return true;
    }())
    {
    }
    return EXIT_SUCCESS;
}
catch (const std::exception& exception)
{
    std::cerr << exception.what() << '\n';
    return EXIT_FAILURE;
}