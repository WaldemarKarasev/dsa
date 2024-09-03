#ifndef STRING_H
#define STRING_H

#include <iostream>

//#define MY_DEBUG
#include "../debug.h"

namespace MyTypes
{
    class String final{

    public:

        using size_type = size_t;
        static constexpr size_type npos = -1;

    private:
        char* m_str_ = nullptr;
        size_type m_len_ = 0;
        size_type m_cap_ = 0;
        size_type m_increaseBy_ = 5;
    public:
        String();
        String(const String& other);
        String(String&& other);
        String(const String& other, size_type pos, size_type len = npos);
        String(const char* str);
        String(const char* s, size_type n);
        String(size_type n, char c);

    // Deatructor
        ~String();

    // Equality operator

    String& operator=(const String& other);
    String& operator=(String&& other);
    
    // Length function
    size_type length();
    

    /*
    *   Modifiers
    */
    public:
        String& operator+=(const String& str);
        String& operator+=(const char* ch); 
        String& operator+=(char ch);

        String& append(const String& other); 
        String& append(const String& other, size_type subpos, size_t sublen = npos); 
        String& append(const char* str); 
        String& append(const char* str, size_t n); 
        String& append(size_type n, char ch); 
        
        void push_back(char ch);
        void pop_back();

        std::ostream& operator<<(std::ostream& os);
    
    /*
    *   Operators
    */
    public: 
    char operator[](size_type i);

    private:
        void substr_(char * & buffer, const char * other, size_type pos = 0, size_t len = npos) const;

    private:
        void append_(const char* str);
        void append_(const char* str, size_type n);
        size_type getLength_(const String& str, size_type pos, size_type len = npos) const;

    private:
        void setLength_(const size_type len);
        void setCapacity_(const size_type cap);
        void increaseCapacity_(const size_type n);
        void decreaseCapacity_(const size_type n);
        void alloc_cstring_(char* &buffer,const size_type n) const;
	    void alloc_cstring_(char* &buffer,const size_type n, char c) const;
        void fill_str_(char* other, const size_type len, const size_type pos, char c) const;
        void clear_str_(const size_type pos);

    public:
        int compare(const String& other) const;
        friend std::ostream& operator<<(std::ostream& os, const String& str);
    };

    bool operator==(const String& lhs, const String& rhs);
    bool operator!=(const String& lhs, const String& rhs);
    bool operator< (const String& lhs, const String& rhs);
    bool operator> (const String& lhs, const String& rhs);
    bool operator<=(const String& lhs, const String& rhs);
    bool operator>=(const String& lhs, const String& rhs);

    String& operator+(String& lhs, const String& rhs);
    
    std::ostream& operator<<(std::ostream& os, const String& str);

}

#endif