#include "QuadTree.hpp"
#include <queue>

int QuadTreeNode::max_depth = 5;
int QuadTreeNode::max_object_node = 15;

bool QuadTreeNode::IsLeaf()
{
    return children.size() == 0;
}

int QuadTreeNode::NumObjects()
{
    Reset();
    int objectCount = contents.size();
    for(int i = 0, size = contents.size(); i < size; ++i)
    {
        contents[i]->flag = true;
    }

    std::queue<QuadTreeNode *> process;
    process.push(this);

    while(process.size() > 0)
    {
        QuadTreeNode *processing = process.back();
        if(!processing->IsLeaf())
        {
            for(int i = 0, size = processing->children.size(); i < size; ++i)
            {
                process.push(&processing->children[i]);
            }
        }
        else
        {
            for(int i = 0, size = processing->contents.size(); i < size; ++i)
            {
                if(!processing->contents[i]->flag)
                {
                    objectCount += 1;
                    processing->contents[i]->flag = true;
                }
            }
        }
        process.pop();
    }
    Reset();
    return objectCount;
}

void QuadTreeNode::Insert(QuadTreeData &data)
{
    if(!RectangleRectangle(data.bounds, node_bounds))
    {
        return;
    }

    if(IsLeaf() && contents.size()+1 > max_object_node)
    {
        Split();
    }

    if(IsLeaf())
    {
        contents.push_back(&data);
    }
    else
    {
        for(int i = 0, size = children.size(); i < size; ++i)
        {
            children[i].Insert(data);
        }
    }
}

void QuadTreeNode::Remove(QuadTreeData &data)
{
    if(IsLeaf())
    {
        int remove_index = -1;
        for(int i = 0, size = contents.size(); i < size; ++i)
        {
            if(contents[i]->object == data.object)
            {
                remove_index = i;
                break;
            }
        }

        if(remove_index != -1)
        {
            contents.erase(contents.begin() + 1);
        }
    }
    else
    {
        for(int i = 0, size = children.size(); i < size; ++i)
        {
            children[i].Remove(data);
        }
    }
    Shake();
}

void QuadTreeNode::Update(QuadTreeData &data)
{
    Remove(data);
    Insert(data);
}

void QuadTreeNode::Reset()
{
    if(IsLeaf())
    {
        for(int i = 0, size = contents.size(); i < size; ++i)
        {
            contents[i]->flag = false;
        }
    }
    else
    {
        for(int i = 0, size = children.size(); i < size; ++i)
        {
            children[i].Reset();
        }
    }
}

void QuadTreeNode::Shake()
{
    if(!IsLeaf())
    {
        int num_obj = NumObjects();
        if(num_obj == 0)
        {
            children.clear();
        }
    }
    else if(NumObjects() < max_object_node)
    {
        std::queue<QuadTreeNode *> process;
        process.push(this);
        while (process.size() > 0)
        {
            QuadTreeNode * processing = process.back();
            if(!processing->IsLeaf())
            {
                for (int i = 0, size = processing->children.size(); i < size; ++i)
                {
                    process.push(&processing->children[i]);
                }
            }
            else
            {
    //            contents.insert(contents.end(), processing->contents.begin(), processing->contents.end());
            }
            process.pop();
        }
        children.clear();
    }
}

void QuadTreeNode::Split()
{
    if(current_depth + 1 >= max_depth)
    {
        return;
    }

    Vector min = GetMin(node_bounds);
    Vector max = GetMax(node_bounds);
    Vector diff = Vector::Sub(max, min);
    diff.Mult(.5f);
    Vector center = Vector::Add(min,diff);

    Rectangle2D childAreas[] = {
        Rectangle2D
        (
            FromMinMax
            (
                Vector(min.x, min.y),
                Vector(center.x, center.y)
            )
        ),
        Rectangle2D
        (
            FromMinMax
            (
                Vector(center.x, min.y),
                Vector(max.x, center.y)
            )
        ),
        Rectangle2D
        (
            FromMinMax
            (
                Vector(center.x, center.y),
                Vector(max.x, max.y)
            )
        ),
        Rectangle2D
        (
            FromMinMax
            (
                Vector(min.x, center.y),
                Vector(center.x, max.y)
            )
        )
    };

    for(int i = 0; i < 4; ++i)
    {
        children.push_back(QuadTreeNode(childAreas[i]));
        children[i].current_depth = current_depth + 1;
    }

    for(int i = 0, size = contents.size(); i < size; ++i)
    {
        children[i].Insert(*contents[i]);
    }
    contents.clear();
}

std::vector<QuadTreeData *> QuadTreeNode::Query(const Rectangle2D &area)
{
    std::vector<QuadTreeData *> result;
    if(!RectangleRectangle(area, node_bounds))
    {
        return result;
    }

    if(IsLeaf())
    {
        for(int i = 0, size = contents.size(); i < size; ++i)
        {
            if(RectangleRectangle(contents[i]->bounds, area))
            {
                result.push_back(contents[i]);
            }
        }
    }
    else
    {
        for(int i = 0, size = children.size(); i < size; ++i)
        {
            std::vector<QuadTreeData *> recurse = children[i].Query(area);
            if(recurse.size() > 0)
            {
   //             result.insert(result.end(), recurse.begin(), recurse.end());
            }
        }
    }
    return result;
}