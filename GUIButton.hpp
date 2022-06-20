#pragma once
#ifndef GUIBUTTON_H
#define GUIBUTTON_H
#include "GUIEntity.hpp"
#include "Action.hpp"
#include <string>

class GUIButton : public GUIEntity
{
private:
    std::string m_text;

    bool m_clicked;

    Action *m_action;
public:
    GUIButton() : m_text(""), m_clicked(false), m_action(0) {}
    GUIButton(std::string texture, std::string text) : GUIEntity(texture), m_text(text), m_clicked(false), m_action(0) {}

    void SetText(std::string text) { m_text = text; }
    void SetAction(Action *action) { m_action = action; }

    bool MouseOver();

    virtual void Update();
    virtual void Draw();
};


#endif