#pragma ince


namespace notes
{
    
template <typename Key, typename Value>
struct ISet
{
public:
    using key_type = Key;
    using value_type = Value;

    struct pair
    {
        key_type key;
        value_type value;
    }

public:
    // Container 
    void build(...); // given an iterable X, build sequence from items in X
    int len(); // return the number of stored items

    // Static
    find(key_type k) // return the stored item with key k

    // Dynamic
    void insert(pair x); // add x to set (replace item with key x.key if one already exists)
    value_type delete(k) // remove and return the stored item with key k

    struct iterator {};
    // Order
    iterator iter_ord()  // return the stored items one-by-one in key order
    pair find_min()      // return the stored item with smallest key
    pair find_max()      // return the stored item with largest key
    pair find_next(key_type k)    // return the stored item with smallest key larger than k
    pair find_prev(key_type k)    // return the stored item with largest key smaller than k

    /*
    • Special case interfaces:
        dictionary := set without the Order operations
    • In recitation, you will be asked to implement a Set, given a Sequence data structure. 
    */
};

} // namespace notes
