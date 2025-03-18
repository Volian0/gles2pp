#version 100

attribute vec4 a_position;
attribute vec2 a_uv;
attribute vec4 a_tint;

varying vec2 v_uv;
varying vec4 v_tint;

void main()
{
    v_uv = a_uv;
    v_tint = a_tint;
    gl_Position = a_position;
} 