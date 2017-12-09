#pragma once

#include <string>
#include <vector>

using std::size_t;

class gap_buffer
{
private:
	std::vector<char> front;
	std::vector<char> middle;
	std::vector<char> back;
	size_t m_pos;
public:
	gap_buffer() : m_pos(0) {}
	void put( char sym );
	char get( size_t pos );
	size_t size() { return front.size() + middle.size() + back.size(); }
	size_t get_pos() { return m_pos; }
	void set_pos( size_t pos );
	void move( int mv );
	std::string print();
	void remove( size_t amount = 1 );
	~gap_buffer() {}
};
