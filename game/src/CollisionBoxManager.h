
#include <vector>
#include <map>
#include <string>
#include <memory>
#include "CollisionBox.h"

// class Singleton
// {
// public:
//     Singleton(Singleton const&) = delete;
//     Singleton& operator=(Singleton const&) = delete;

//     static std::shared_ptr<Singleton> instance()
//     {
//         static std::shared_ptr<Singleton> s{new Singleton};
//         return s;
//     }

// private:
//     Singleton() {}
// };
class CollisionBoxManager
{
public:
    CollisionBoxManager(const CollisionBoxManager &) = delete;
    CollisionBoxManager &operator=(const CollisionBoxManager &) = delete;

    static CollisionBoxManager &GetInstance()
    {
        return CollisionBoxManager::s_Instance;
    }

    void AddCollisionBox(std::string key, CollisionBox *box);
    std::vector<CollisionBox *> GetCollisionBoxesFor(std::string);
    // static void AddCollisionBox(std::string key, CollisionBox *box) { return instance()->impl_AddCollisionBox(key, box); }
    // static std::vector<CollisionBox *> GetCollinionBoxesFor(std::string key) { return instance()->impl_GetCollisionBoxesFor(key); }

private:
    static CollisionBoxManager s_Instance;
    CollisionBoxManager(){};
    bool Has(std::string);

    // void impl_AddCollisionBox(std::string key, CollisionBox *box);
    // std::vector<CollisionBox *> impl_GetCollisionBoxesFor(std::string);

    std::map<std::string, std::vector<CollisionBox *>> m_CollisionBoxes;
};