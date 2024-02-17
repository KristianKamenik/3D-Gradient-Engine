#pragma once

struct Color {
	float R;
	float G;
	float B;
	float A;
};
struct VERTEX {
	float x, y, z;
	Color color;
};

#define PLANE_COUNT 6
constexpr VERTEX PLANE[] = //Without back culling
{
    {-1.0f, 0.5f,   0.5f, Color{1.0f, 1.0f, 1.0f, 1.0f}},
    {1.0f,  -0.5,   0.5f, Color{1.0f, 1.0f, 1.0f, 1.0f}},
    {-1.0f, -0.5f,  0.5f, Color{1.0f, 1.0f, 1.0f, 1.0f}},
    {-1.0f, 0.5f,   0.5f, Color{1.0f, 1.0f, 1.0f, 1.0f}},
    {1.0f,  0.5f,   0.5f, Color{1.0f, 1.0f, 1.0f, 1.0f}},
    {1.0f,  -0.5f,  0.5f, Color{1.0f, 1.0f, 1.0f, 1.0f}},
};

#define CUBE_COUNT 36
constexpr VERTEX CUBE[] = //Without back culling
{
    {0.75f, 0.0f,  -0.5f, Color{0.9f, 0.9f, 0.9f, 1.0f}},
    {1.0f,  -0.25f,   -0.5f, Color{0.9f, 0.9f, 0.9f, 1.0f}},
    {0.75f, -0.25f,   -0.5f, Color{0.9f, 0.9f, 0.9f, 1.0f}},
    {0.75f, 0.0f,  -0.5f, Color{0.9f, 0.9f, 0.9f, 1.0f}},
    {1.0f,  0.0f,  -0.5f, Color{0.9f, 0.9f, 0.9f, 1.0f}},
    {1.0f,  -0.25f,   -0.5f, Color{0.9f, 0.9f, 0.9f, 1.0f}},

    {1.0f, 0.0f,  -0.5f, Color{0.7f, 0.7f, 0.7f, 1.0f}},
    {1.0f,  -0.25f,   -0.25f, Color{0.7f, 0.7f, 0.7f, 1.0f}},
    {1.0f, -0.25f,   -0.5f, Color{0.7f, 0.7f, 0.7f, 1.0f}},
    {1.0f, 0.0f,  -0.5f, Color{0.7f, 0.7f, 0.7f, 1.0f}},
    {1.0f,  0.0f,  -0.25f, Color{0.7f, 0.7f, 0.7f, 1.0f}},
    {1.0f,  -0.25f,   -0.25f, Color{0.7f, 0.7f, 0.7f, 1.0f}},

    {0.75f, 0.0f,  -0.25f, Color{0.9f, 0.9f, 0.9f, 1.0f}},
    {0.75f, -0.25f,   -0.25f, Color{0.9f, 0.9f, 0.9f, 1.0f}},
    {1.0f,  -0.25f,   -0.25f, Color{0.9f, 0.9f, 0.9f, 1.0f}},
    {0.75f, 0.0f,  -0.25f, Color{0.9f, 0.9f, 0.9f, 1.0f}},
    {1.0f,  -0.25f,   -0.25f, Color{0.9f, 0.9f, 0.9f, 1.0f}},
    {1.0f,  0.0f,  -0.25f, Color{0.9f, 0.9f, 0.9f, 1.0f}},

    {0.75f, 0.0f,  -0.5f, Color{0.7f, 0.7f, 0.7f, 1.0f}},
    {0.75f, -0.25f,   -0.5f, Color{0.7f, 0.7f, 0.7f, 1.0f}},
    {0.75f,  -0.25f,   -0.25f, Color{0.7f, 0.7f, 0.7f, 1.0f}},
    {0.75f, 0.0f,  -0.5f, Color{0.7f, 0.7f, 0.7f, 1.0f}},
    {0.75f,  -0.25f,   -0.25f, Color{0.7f, 0.7f, 0.7f, 1.0f}},
    {0.75f,  0.0f,  -0.25f, Color{0.7f, 0.7f, 0.7f, 1.0f}},

    {0.75f, 0.0f,  -0.5f, Color{1.0f, 1.0f, 1.0f, 1.0f}},
    {0.75f,  0.0f,   -0.25f, Color{1.0f, 1.0f, 1.0f, 1.0f}},
    {1.0f, 0.0f,   -0.25f, Color{1.0f, 1.0f, 1.0f, 1.0f}},
    {0.75f, 0.0f,  -0.5f, Color{1.0f, 1.0f, 1.0f, 1.0f}},
    {1.0f,  0.0f,   -0.25f, Color{1.0f, 1.0f, 1.0f, 1.0f}},
    {1.0f,  0.0f,  -0.5f, Color{1.0f, 1.0f, 1.0f, 1.0f}},

    {0.75f, -0.25f,  -0.5f, Color{0.5f, 0.5f, 0.5f, 1.0f}},
    {1.0f, -0.25f,   -0.25f, Color{0.5f, 0.5f, 0.5f, 1.0f}},
    {0.75f,  -0.25f,   -0.25f, Color{0.5f, 0.5f, 0.5f, 1.0f}},
    {0.75f, -0.25f,  -0.5f, Color{0.5f, 0.5f, 0.5f, 1.0f}},
    {1.0f,  -0.25f,  -0.5f, Color{0.5f, 0.5f, 0.5f, 1.0f}},
    {1.0f,  -0.25f,   -0.25f, Color{0.5f, 0.5f, 0.5f, 1.0f}},
};