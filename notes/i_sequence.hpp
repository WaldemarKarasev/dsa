#pragma once

namespace notes
{
    
template <typename T>
struct ISequence
{
public:
    using value_type = T;

public:
    // Conteiner
    void build(); // building values from ...
    int len() const; // return length of stored values

    // Static
    struct iterator{}; // functionality to be able to iterate through all values
    value_type get_at(iterator it); // return value stored at "it" position
    void set_at(iterator it, value_type x); // set "x" value at "it" position

    // Dynamic
    void insert_at(int i, value_type x); // add "x" as a "i"th item
    value_type delete_at(iterator i); // remove and return the "i"th item
    void insert_first(value_type x); // add "x" as the first element
    value_type delete_first(); // remove and return first element
    void insert_last(value_type x); // add "x" as the last element
    value_type delete_last(); // remove and return last element

    /*
    Special case interfaces:
    stack: insert_last(x) and delete_last()
    queue: insert_last(x) and delete_first()
    Every other Dynamic interface functions are "deleted"
    */
};

} // namespace notes
