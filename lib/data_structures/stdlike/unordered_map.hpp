#include <iostream>

#include <vector>
#include <forward_list>

namespace lib {

    template <typename Key, typename Value, typename Hash, typename Equal>
    class unordered_map
    {
    public:
        struct node
        {
            std::pair<const Key, Value> kv;
            uint64_t hash;
        };


    private:
        std::vector<Node*> m_arr;
        std::forward_list<Node> m_fl;

    };

}