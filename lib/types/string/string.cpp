#include <lib/types/string/string.hpp>

#include <cstring>


namespace lib
{
	String::String() {
		setCapacity_(0);
		setLength_(0);
	}

	String::String(const String & other)  {
		append_(other.m_str_, other.m_len_);
	}
	String::String(String && other) {
		*this = std::move(other);
	}

	String::String(const String & other, size_type pos, size_type len) {
		append(other.m_str_, pos, len);
	}

	String::String(const char * str) {
		DEBUG_PRINT("String(char*)");
		append_(str);
	}

	String::String(const char * str, size_type n) {
		append(str, 0, n);
	}

	String::String(size_type n, char ch) {
		append(n, ch);
	}

	// Destructor
	String::~String()
	{
		delete[] m_str_;
	}

	/*
	*	Equality operator
	*/
	String& String::operator=(const String& other)
	{
		if(this != &other)
		{
			setLength_(0);
			append_(other.m_str_, other.m_len_);
		}
		return *this;
	}

	String& String::operator=(String&& other)
	{
		if(this != &other)
		{
			if(m_str_ != nullptr) delete[] m_str_;

			m_str_ = other.m_str_;
			m_len_ = other.m_len_;
			m_cap_ = other.m_cap_;
			other.m_str_ = nullptr;
			other.m_len_ = 0;
			other.m_cap_ = 0;
		}

		return *this;
	}

	// Length function
	String::size_type String::length()
	{
		return m_len_;
	}

	/* 
	*	Modifiers
	*/
	String& String::operator+=(const String& other)
	{
		append_(other.m_str_, other.m_len_);
		return *this;
	}
	String& String::operator+=(const char* str)
	{
		append_(str);
		return *this;
	}
	String& String::operator+=(char ch)
	{
		append_(&ch, 1);
		return *this;
	}

	/*
	*	append
	*/
	String& String::append(const String& other)
	{
		append_(other.m_str_, other.m_len_);
		return *this;
	}

	String& String::append(const String& other, size_type subpos, size_type sublen)
	{
		char * buf = nullptr;
		substr_(buf, other.m_str_, subpos, sublen);
		append_(buf, sublen);
		delete buf;
		return *this;
	}

	String& String::append(const char* str)
	{
		append_(str);
		return *this;
	}

	String& String::append(const char* str, size_t n)
	{
		char* buf = nullptr;
		substr_(buf, str, 0, n);
		append_(buf, n);
		delete buf;
		return *this;
	}

	String& String::append(size_type n, char ch)
	{
		char* buf = nullptr;
		alloc_cstring_(buf, n, ch);
		append_(buf, n);
		return *this;
	}
	
	/*
	*	push_back()
	*/
	void String::push_back(char ch)
	{
		append_(&ch, 1);
	}
	
	/*
	*	pop_back()
	*/
	void String::pop_back()
	{
		if (!m_str_ && m_len_ == 0)
			return;

		m_len_ -= 1;
		fill_str_(m_str_, m_len_, m_len_, '\0');
	}

    std::ostream &String::operator<<(std::ostream &os)
    {
        return os << m_str_ << std::endl;
    }

    char String::operator[](size_type i)
    {
        if(i > m_len_ || i < 0)
            throw;

        return *(m_str_ + i);
	}

	void String::substr_(char * & buffer, const char * other, size_type pos, size_t len) const
	{
		if(!other) return;

		alloc_cstring_(buffer, len);
		for (size_type i = 0; i < len; ++i)
		{
			buffer[i] = other[pos + 1];
		}
		
	}

	// private service funtions 
	void String::append_(const char* str)
	{
		DEBUG_PRINT("String::append_(const char*)");
		return append_(str, strlen(str));
	}
    
	void String::append_(const char* other, size_type n)
	{
		DEBUG_PRINT("String::append_(const char*, size_type)");
		if(!other || n == 0)
			return;
		
		increaseCapacity_(m_len_ + n);
		size_type i = 0;
		for(; i < n; ++i)
		{
			m_str_[m_len_ + i] = other[i];
		}
		m_str_[m_len_ + i] = '\0';
		setLength_(m_len_ + n);
	}

	String::size_type String::getLength_(const String& str, size_type pos, size_type len) const
	{
		if (len == npos)
			len = m_len_ - pos;

		if (pos + len > str.m_len_)
		{
			throw;	
		}
		return len;
	}

	void String::setLength_(const size_type len)
	{
		DEBUG_PRINT("String::setLength_(const syze_type)")
		if(m_len_ > len)
			clear_str_(len);
		else if(m_cap_ < len)
			increaseCapacity_(len);
		m_len_ = len;
		
	}

	void String::setCapacity_(const size_type cap)
	{
		DEBUG_PRINT("String::setCapacity(const size_type)");
		if(m_cap_ == cap && m_str_)
			return;
		if(cap < m_len_)
			return;
		m_cap_ = cap;

		char* buf = m_str_;
		m_str_ = nullptr;
		
		alloc_cstring_(m_str_, m_cap_);

		if(buf)
		{
			// if temp_str is not null then strcpy
			for (size_type i = 0; i < m_len_; i++)
			{
				m_str_[i] = buf[i];
			}
			m_str_[m_len_] = '\0';
			
		}
		delete buf;
	}

	void String::increaseCapacity_(const size_type n)
	{
		DEBUG_PRINT("String::increaseCapacity(const syze_type)")
		if(m_cap_ > n && m_str_)
			return;

		// increasing capacity calculation
		size_type cap = m_cap_;
		while(cap <= n)
			cap += m_increaseBy_;
		
		m_increaseBy_++;

		setCapacity_(cap);

	}

	void String::decreaseCapacity_(const size_type n)
	{
		
	}

	void String::alloc_cstring_(char* &buffer,const size_type n) const
	{
		if(buffer)
			throw;
		DEBUG_PRINT(&buffer);
		buffer = new char[n + 1]();
		DEBUG_PRINT(&buffer);

	}

	void String::alloc_cstring_(char* &buffer,const size_type n, char c) const
	{
		alloc_cstring_(buffer, n);
		fill_str_(buffer, n, 0, c);
	}
	
	void String::fill_str_(char* other, const size_type len, const size_type pos, char c) const
	{
		size_type begin = pos;
		while(begin != len)
			other[begin++] = c;
		
		other[begin] = '\0';
	}

	void String::clear_str_(const size_type pos)
	{
		fill_str_(m_str_, m_len_, pos, '\0');
		m_len_ = pos;
	}
	
	int String::compare(const String& other) const
	{
		if(m_len_ < other.m_len_)
			return -1;
		if(m_len_ > other.m_len_)
			return 1;
		
		return lib::strcmp(m_str_, other.m_str_);
	}



	/*
	*	Outside functions
	*/

	/*
	*	comparison operators
	*/
	bool operator==(const String& lhs, String& rhs)
	{
		return lhs.compare(rhs) == 0;	
	}
    bool operator!=(const String& lhs, const String& rhs)
	{
		return lhs.compare(rhs) != 0;
	}
    bool operator<(const String& lhs, const String& rhs)
	{
		return lhs.compare(rhs) < 0;
	}
    bool operator>(const String& lhs, const String& rhs)
	{
		return lhs.compare(rhs) > 0;
	}
    bool operator<=(const String& lhs, const String& rhs)
	{
		return lhs.compare(rhs) <= 0;
	}
    bool operator>=(const String& lhs, const String& rhs)
	{
		return lhs.compare(rhs) >= 0;
	}


	String& operator+(String& lhs, const String& rhs)
	{
		lhs += rhs;
		return lhs;
	}

	std::ostream& operator<<(std::ostream& os, const String& str)
	{
		return os << str.m_str_;
	}

}
