#version 100

precision mediump float;

uniform sampler2D u_sampler;

varying vec2 v_uv;
varying vec4 v_tint;

void main()
{
    //get color from texture
    vec4 color = texture2D(u_sampler, v_uv);

    //apply tint
    color *= v_tint;

    gl_FragColor = color;
} 