#pragma once
#ifndef ENTITY_H
#define ENTITY_H
#include "Vector.hpp"
#include "Weapon.hpp"
#include <SDL2/SDL_image.h>
#include <string>
#include <vector>

const int MAX_AMMO = 20;

class Weapon;

class Entity
{
protected:
    Vector m_position;
    Vector m_velocity;
    Vector m_acceleration;

    int size_x;
    int size_y;
    int m_mass;

    int m_max_speed;
    float m_friction;
    float m_max_force;

    float m_radius;
    float m_last_angle;

    int m_life;

    bool m_hit;
    bool m_can_fire;

    int m_ammo;

    Vector m_target;

    bool m_await_input;
    bool m_dead;

    std::string m_texture;
    std::string m_tag;

    Weapon *m_weapon_1;
    Weapon *m_weapon_2;
public:
    Entity() : m_position(0,0),
               m_velocity(0,0),
               m_acceleration(0,0),
               size_x(0),
               size_y(0),
               m_mass(0),
               m_max_speed(0),
               m_friction(0),
               m_max_force(.2),
               m_radius(0),
               m_last_angle(0),
               m_life(100),
               m_hit(false),
               m_can_fire(true),
               m_ammo(80),
               m_target(),
               m_await_input(false),
               m_dead(false),
               m_texture(""),
               m_tag("Entity"),
               m_weapon_1(0),
               m_weapon_2(0)
    {}

    Entity(std::string texture) : m_position(0,0),
                                  m_velocity(0,0),
                                  m_acceleration(0,0),
                                  size_x(0),
                                  size_y(0),
                                  m_mass(0),
                                  m_max_speed(0),
                                  m_friction(0),
                                  m_max_force(.2),
                                  m_radius(0),
                                  m_last_angle(0),
                                  m_life(100),
                                  m_hit(false),
                                  m_can_fire(true),
                                  m_ammo(80),
                                  m_target(),
                                  m_await_input(false),
                                  m_dead(false),
                                  m_texture(texture),
                                  m_tag("Entity"),
                                  m_weapon_1(0),
                                  m_weapon_2(0)
    {}

    virtual ~Entity()
    {}

    void SetTexture(std::string texture) { m_texture = texture; }
    void SetSize(int x, int y) { size_x = x; size_y = y; }

    virtual void Draw();
    virtual void Update();
    void ApplyForce(Vector force);
    virtual void Move();
    virtual void Seek(Vector target);
    virtual void Separate(std::vector<Entity *> ships);
    virtual void Align(std::vector<Entity *> ships);
    virtual void Cohesion(std::vector<Entity *> ships);

    void SetPosition(Vector position) { m_position = position; }
    void SetVelocity(Vector velocity) { m_velocity = velocity; }
    void SetRadius(float radius) { m_radius = radius; }
    void SetMaxSpeed(int max_speed) { m_max_speed = max_speed; }
    void SetCoefficentFriction(float coefficent) { m_friction = coefficent; }
    void SetMass(int mass) { m_mass = mass; }
    void SetTag(std::string tag) { m_tag = tag; }
    void SetAngle(float angle) { m_last_angle = angle; }
    void SetMaxForce(float force) { m_max_force = force; }

    void SetWeapon1(Weapon *weapon_1) { m_weapon_1 = weapon_1; }
    void SetWeapon2(Weapon *weapon_2) { m_weapon_2 = weapon_2; }

    void SetLife(int life) { m_life = life; }
    int GetLife() const { return m_life; }
    bool IsLive() { return m_life <= 0; }
    
    void SetHit(bool hit) { m_hit = hit; }
    bool IsHit() const { return m_hit; }
    void Damage(int dmg) { m_life -= dmg; }

    void SetFire(bool value) { m_can_fire = value; }
    bool CanFire() const { return m_can_fire; }

    void SetDead(bool value) { m_dead = value; }
    bool IsDead() const { return m_dead; }

    void SetAmmo(int ammo) { m_ammo = ammo; }
    int GetAmmo() const { return m_ammo; }

    Vector *GetPosition() { return &m_position; }
    Vector *GetVelocity() { return &m_velocity; }
    int GetSizeX() { return size_x; }
    int GetSizeY() { return size_y; }
    float GetRadius() { return m_radius; }
    int GetMaxSpeed() { return m_max_speed; }
    float GetCoefficentFriction() { return m_friction; }
    int GetMass() { return m_mass; }
    float GetAngle() const { return m_last_angle; }
    float GetMaxForce() const { return m_max_force; }
    std::string GetTag() { return m_tag; }
};

#endif // !ENTITY_H