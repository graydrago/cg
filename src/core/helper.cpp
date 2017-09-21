#pragma once

#include <string>
#include <random>
#include <GL/gl.h>

static std::mt19937 gen(time(0)); 
static std::uniform_real_distribution<> urd(0, 1); 

enum class color_map : int{
  black = 0x000000,
  red = 0xff0000,
  green = 0x00ff00,
  blue = 0x0000ff,
  yellow = 0xffff00,
  magenta = 0xff00ff,
  cyan = 0x00ffff,
  white = 0xffffff
};

struct Color {
  float r;
  float g;
  float b;
  Color(int hex) {
    r = static_cast<float>((hex >> 16) & 255)/255.f;
    g = static_cast<float>((hex >> 8) & 255)/255.f;
    b = static_cast<float>(hex & 255)/255.f;
  };
  Color(float _r, float _g, float _b) : r(_r), g(_g), b(_b) {};
  Color(color_map c) : Color(static_cast<int>(c)) {};
};


void color(Color c) { glColor3f(c.r, c.g, c.b); }
void color(int hex) { Color c(hex); glColor3f(c.r, c.g, c.b); }
void color(color_map c) { color(static_cast<int>(c)); }
void random_color() { glColor3f(urd(gen), urd(gen), urd(gen)); }
Color get_random_color() { return Color(urd(gen), urd(gen), urd(gen)); }
