#pragma once
#ifndef QUADTREE_H
#define QUADTREE_H
#include "Entity.hpp"
#include "Geometry2D.hpp"
#include <vector>

struct QuadTreeData 
{
    Entity *object;
    Rectangle2D bounds;
    bool flag;
    inline QuadTreeData(Entity *obj, const Rectangle2D &b) : object(obj), bounds(b), flag(false) {}
};

class QuadTreeNode
{
protected:
    std::vector<QuadTreeNode> children;
    std::vector<QuadTreeData *> contents;
    static int max_depth;
    static int max_object_node;
    Rectangle2D node_bounds;
    int current_depth;
public:
    inline QuadTreeNode(const Rectangle2D &bounds) : node_bounds(bounds), current_depth(0) {}
    bool IsLeaf();
    int NumObjects();
    void Insert(QuadTreeData &data);
    void Remove(QuadTreeData &data);
    void Update(QuadTreeData &data);
    void Shake();
    void Split();
    void Reset();
    std::vector<QuadTreeData *> Query(const Rectangle2D &area);
};

typedef QuadTreeNode QuadTree;

#endif