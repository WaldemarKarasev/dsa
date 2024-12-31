#include <iostream>


/*

                fake_node == end()
                  /
                 / 
                /\
               /  \ 
              /    \
             / tree \
            /  impl  \
begin() -> /__________\ < - end() - 1

*/

namespace map {

    template <typename Key, typename Value>
    class map
    {
    public:
        struct base_node
        {
            
            base_node* left;
            base_node* right;
            base_node* parent;
        };

        struct node : base_node
        {
            std::pair<const Key, Value> kv;
            bool red;
        };

    private:
        base_node* m_head;

    };

}