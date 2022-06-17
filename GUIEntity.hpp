#pragma once
#ifndef GUIENTITY_H
#define GUIENTITY_H
#include "Vector.hpp"
#include <string>

class GUIEntity
{
private:
    Vector m_position;

    std::string m_texture;

    int m_size_x;
    int m_size_y;

    int m_src_x;
    int m_src_y;

    int m_num_frames;

    // action
public:
    GUIEntity() : m_position(0,0),
                  m_texture("")
    {}

    GUIEntity(std::string texture) : m_position(0,0),
                                     m_texture(texture)
    {}

    void SetTexture(std::string texture) { m_texture = texture; }
    void SetSize(int size_x, int size_y) { m_size_x = size_x; m_size_y = size_y; }
    void SetOriginSize(int size_x, int size_y) { m_src_x = size_x; m_src_y = size_y; }
    void SetPosition(Vector position) { m_position = position; }
    void SetNumFrames(int num_frames) { m_num_frames = num_frames; }

    std::string GetTexture() { return m_texture; }
    Vector GetPosition() { return m_position; }

    void Draw();
};

#endif