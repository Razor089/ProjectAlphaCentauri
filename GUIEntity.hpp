#pragma once
#ifndef GUIENTITY_H
#define GUIENTITY_H
#include "Vector.hpp"
#include <string>

class GUIEntity
{
protected:
    Vector m_position;

    std::string m_texture;

    float m_size_x;
    float m_size_y;

    float m_src_x;
    float m_src_y;

    int m_num_frames;

    bool m_animated;
public:
    GUIEntity() : m_position(0,0),
                  m_num_frames(1),
                  m_animated(false),
                  m_src_x(0),
                  m_src_y(0),
                  m_texture("")
    {}

    GUIEntity(std::string texture) : m_position(0,0),
                                     m_num_frames(1),
                                     m_animated(false),
                                     m_src_x(0),
                                     m_src_y(0),
                                     m_texture(texture)
    {}

    void SetTexture(std::string texture) { m_texture = texture; }
    virtual void SetSize(int size_x, int size_y) { m_size_x = size_x; m_size_y = size_y; }
    virtual void SetOriginSize(int size_x, int size_y) { m_src_x = size_x; m_src_y = size_y; }
    void SetPosition(Vector position) { m_position = position; }
    void SetNumFrames(int num_frames) { m_num_frames = num_frames; }
    void SetAnimated(bool value) { m_animated = value; }

    std::string GetTexture() { return m_texture; }
    Vector GetPosition() { return m_position; }

    virtual void Update();
    virtual void Draw();
};

#endif