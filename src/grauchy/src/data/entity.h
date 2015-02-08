#ifndef ENTITY_H
#define ENTITY_H

class Entity
{
public:
    Entity();

    int getId() { return _Id; }
    void setId(int id) { _Id = id; }

private:
    int _Id;
};

#endif // ENTITY_H
