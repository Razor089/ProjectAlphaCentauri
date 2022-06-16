#include "Entity.hpp"
#include "Engine.hpp"
#include "TextureManager.hpp"
#include <iostream>

void Entity::Draw()
{
    TextureManager::Instance()->DrawFrame(m_texture, (int)m_position.x, (int)m_position.y, 1401, 1449, size_x, size_y, 1, 0, m_last_angle, Engine::Instance()->GetRenderer(), SDL_FLIP_NONE);
}

void Entity::Update()
{   
    Vector drag = Vector::Mult(m_velocity, -1);
    drag.Normalize();
    drag.Mult(m_friction);
    ApplyForce(drag);

    if(m_velocity.Length() != 0)
    {
        m_last_angle = m_velocity.Heading();
    }
    Move();
}

void Entity::Seek(Vector target)
{
    Vector desired = Vector::Sub(target, m_position);
    desired.Normalize();
    desired.Mult(5);
    Vector steer = Vector::Sub(desired, m_velocity);
    steer.Limit(.2);
    ApplyForce(steer);
}

void Entity::Move()
{
    m_velocity.Add(m_acceleration);
    m_velocity.Limit(m_max_speed);
    m_position.Add(m_velocity);
    m_acceleration.Mult(0);
}

void Entity::ApplyForce(Vector force)
{
    Vector update_force = Vector::Div(force, m_mass);
    m_acceleration.Add(force);
}

void Entity::Separate(std::vector<Entity *> ships)
{
    float desired_separataion = 30;
    Vector sum = Vector();
    int count = 0;
    for(std::vector<Entity *>::iterator it = ships.begin(); it != ships.end(); ++it)
    {
        float dist = Vector::Distance(*(*it)->GetPosition(), m_position);

        if(dist > 0 && dist < desired_separataion)
        {
            Vector diff = Vector::Sub(m_position, *(*it)->GetPosition());
            diff.Normalize();
            sum.Add(diff);
            ++count;
        }
    }

    if(count > 0)
    {
        sum.Div(count);
        sum.Normalize();
        sum.Mult(m_max_speed);
        Vector steer = Vector::Sub(sum, m_velocity);
        steer.Limit(.2);
        ApplyForce(steer);
    }
}

void Entity::Align(std::vector<Entity *> ship)
{
    float neigh_dist = 50;
    Vector sum = Vector();
    int count = 0;
    for(std::vector<Entity *>::iterator it = ship.begin(); it != ship.end(); ++it)
    {
        float dist = Vector::Distance(m_position, *(*it)->GetPosition());
        if(dist > 0 && dist < neigh_dist)
        {
            sum.Add(*(*it)->GetVelocity());
            ++count;
        }
    }

    if(count > 0)
    {
        sum.Div(count);
        sum.Normalize();
        sum.Mult(m_max_speed);
        Vector steer = Vector::Sub(sum, m_velocity);
        steer.Limit(.2);
        ApplyForce(steer);
    }
}

void Entity::Cohesion(std::vector<Entity *> ship)
{
    float neigh_dist = 50;
    Vector sum = Vector();
    int count = 0;
    for(std::vector<Entity *>::iterator it = ship.begin(); it != ship.end(); ++it)
    {
        float dist = Vector::Distance(m_position, *(*it)->GetPosition());
        if(dist > 0 && dist < neigh_dist)
        {
            sum.Add(*(*it)->GetPosition());
            ++count;
        }
    }
    if(count > 0)
    {
        sum.Div(count);
        Seek(sum);
    }
}