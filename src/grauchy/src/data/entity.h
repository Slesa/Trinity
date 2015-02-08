#ifndef ENTITY_H
#define ENTITY_H

class Entity
{
public:
    Entity();

    int getId() { return m_Id; }
    void setId(int id) { m_Id = id; }

private:
    int m_Id;
};

#endif // ENTITY_H
