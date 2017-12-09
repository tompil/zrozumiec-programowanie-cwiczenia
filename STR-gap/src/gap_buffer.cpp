#include <gap_buffer.h>

using std::size_t;

void gap_buffer::put( char ch )
{
	middle.push_back( ch );
	m_pos++; // integer overflow danger
}

char gap_buffer::get( size_t pos )
{
	if( size() == 0 || size() <= pos )
		return '\0';

	if( pos < front.size() )
		return front[pos];

	pos -= front.size();
	
	if( pos < middle.size() )
		return middle[pos];

	pos -= middle.size();
	return back[pos];
}		

void gap_buffer::set_pos( size_t pos )
{
	if(m_pos == pos )
		return;

	if( pos > size() )
		pos = size();

	m_pos = pos;
	front.insert( front.end(), middle.begin(), middle.end() );
	middle.clear();

	if( pos < front.size() )
	{
		back.insert( back.begin(), front.begin() + pos, front.end() );
		front.resize( pos );
	}
	else if( pos > front.size() )
	{
		pos -= front.size();
		front.insert( front.end(), back.begin(), back.begin() + pos );
		back.erase( back.begin(), back.begin() + pos );
	}
}

void gap_buffer::move( int mv )
{
	if( mv < 0 && abs( mv ) > m_pos )
		set_pos( 0 );
	else
		set_pos( m_pos + mv );
}

std::string gap_buffer::print()
{
	std::string tmp( front.begin(), front.end() );
	tmp.append( middle.begin(), middle.end() );
	tmp.append( back.begin(), back.end() );
	return tmp;
}

void gap_buffer::remove( size_t amount )
{
	if( amount >= back.size() )
		back.clear();
	else
		back.erase( back.begin(), back.begin() + amount );
}
