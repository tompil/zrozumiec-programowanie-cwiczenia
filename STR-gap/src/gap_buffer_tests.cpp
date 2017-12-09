#define BOOST_TEST_MODULE gap_buffer_test
#define BOOST_TEST_DYN_LINK
#define BOOST_TEST_MAIN
#include <boost/test/unit_test.hpp>

#include <gap_buffer.h>

#include <string>
#include <vector>

using std::size_t;

BOOST_AUTO_TEST_CASE( PutCharAndGetChar )
{
	char ch, tmp;
	gap_buffer gb;

	ch = 'a';
	gb.put( ch );
	tmp = gb.get( 0 );
	BOOST_CHECK_EQUAL( tmp, ch );

	ch = 'b';
	gb.put( ch );
	tmp = gb.get( 1 );
	BOOST_CHECK_EQUAL( tmp, ch );
}

BOOST_AUTO_TEST_CASE( GetCharOutOfRange )
{
	char tmp;
	gap_buffer gb;

	gb.put( 'x' );
	tmp = gb.get( 1 );
	BOOST_CHECK_EQUAL( tmp, '\0' );

	tmp = gb.get( 5 );
	BOOST_CHECK_EQUAL( tmp, '\0' );
}

BOOST_AUTO_TEST_CASE( GetCharFromEmptyBuffer )
{
	char tmp;
	gap_buffer gb;

	tmp = gb.get( 0 );
	BOOST_CHECK_EQUAL( tmp, '\0' );

	tmp = gb.get( 5 );
	BOOST_CHECK_EQUAL( tmp, '\0' );
}

BOOST_AUTO_TEST_CASE( GetSizeFromEmptyBuffer )
{
	size_t sz;
	gap_buffer gb;

	sz = gb.size();
	BOOST_CHECK_EQUAL( sz, 0 );
}

BOOST_AUTO_TEST_CASE( PutCharAndGetSize )
{
	size_t sz;
	gap_buffer gb;

	gb.put( 'x' );
	sz = gb.size();
	BOOST_CHECK_EQUAL( sz, 1 );

	gb.put( 'x' );
	sz = gb.size();
	BOOST_CHECK_EQUAL( sz, 2 );
}

BOOST_AUTO_TEST_CASE( GetPositionFromEmptyBuffer )
{
	gap_buffer gb;
	size_t pos = gb.get_pos();
	BOOST_CHECK_EQUAL( pos, 0 );
}

BOOST_AUTO_TEST_CASE( PutCharAndGetPosition )
{
	gap_buffer gb;
	gb.put( 'x' );
	size_t pos = gb.get_pos();
	BOOST_CHECK_EQUAL( pos, 1 );
}

BOOST_AUTO_TEST_CASE( SetPositionInEmptyBufferAndGetPosition )
{
	gap_buffer gb;
	gb.set_pos( 5 );
	size_t pos = gb.get_pos();
	BOOST_CHECK_EQUAL( pos, 0 );
}

BOOST_AUTO_TEST_CASE( SetPositionOutOfRangeAndGetPosition )
{
	gap_buffer gb;
	std::string in = "abcdefgh";
	for( char ch : in )
		gb.put( ch );

	gb.set_pos( 3 );
	gb.set_pos( 10 );
	size_t pos = gb.get_pos();
	BOOST_CHECK_EQUAL( pos, gb.size() );
}

BOOST_AUTO_TEST_CASE( SetPositionAtTheBeginningAndGetPosition )
{
	gap_buffer gb;
	std::string in = "abcdefgh";
	for( char ch : in )
		gb.put( ch );

	gb.set_pos( 0 );
	size_t pos = gb.get_pos();
	BOOST_CHECK_EQUAL( pos, 0 );
}

BOOST_AUTO_TEST_CASE( SetPositionAtTheEndAndGetPosition )
{
	gap_buffer gb;
	std::string in = "abcdefgh";
	for( char ch : in )
		gb.put( ch );

	gb.set_pos( 0 );
	gb.set_pos( 8 );
	size_t pos = gb.get_pos();
	BOOST_CHECK_EQUAL( pos, 8 );

	gb.set_pos( 7 );
	pos = gb.get_pos();
	BOOST_CHECK_EQUAL( pos, 7 );
}

BOOST_AUTO_TEST_CASE( SetPositionInTheMiddleAndGetPosition )
{
	gap_buffer gb;
	std::string in = "abcdefgh";
	for( char ch : in )
		gb.put( ch );

	gb.set_pos( 5 );
	size_t pos = gb.get_pos();
	BOOST_CHECK_EQUAL( pos, 5 );
}

BOOST_AUTO_TEST_CASE( PutCharInTheFront )
{
	std::string in = "ab";
	char ch = 'x';
	gap_buffer gb;
	for( char ch : in )
		gb.put( ch );

	gb.set_pos( 0 );
	gb.put( ch );
	char out = gb.get( 0 );
	BOOST_CHECK_EQUAL( ch, out );
	BOOST_CHECK_EQUAL( gb.size(), in.size() + 1 );
	BOOST_CHECK_EQUAL( gb.get_pos(), 1 );
}

BOOST_AUTO_TEST_CASE( PutCharInTheMiddle )
{
	std::string in = "ab";
	char ch = 'x';
	gap_buffer gb;
	for( char ch : in )
		gb.put( ch );

	gb.set_pos( 1 );
	gb.put( ch );
	char out = gb.get( 1 );
	BOOST_CHECK_EQUAL( ch, out );
	BOOST_CHECK_EQUAL( gb.size(), in.size() + 1 );
	BOOST_CHECK_EQUAL( gb.get_pos(), 2 );
}

BOOST_AUTO_TEST_CASE( MoveByZeroSteps )
{
	std::string in = "abcdefgh";
	gap_buffer gb;
	for( char ch : in )
		gb.put( ch );

	gb.set_pos ( 0 );
	gb.move( 0 );
	BOOST_CHECK_EQUAL( gb.get_pos(), 0 );

	gb.set_pos( 3 );
	gb.move( 0 );
	BOOST_CHECK_EQUAL( gb.get_pos(), 3 );

	gb.set_pos( 7 );
	gb.move( 0 );
	BOOST_CHECK_EQUAL( gb.get_pos(), 7 );

	gb.set_pos( 8 );
	gb.move( 0 );
	BOOST_CHECK_EQUAL( gb.get_pos(), 8 );
}

BOOST_AUTO_TEST_CASE( MoveForwardInsideTheBuffer )
{
	std::string in = "abcdefgh";
	gap_buffer gb;
	for( char ch : in )
		gb.put( ch );
	
	gb.set_pos( 0 );
	gb.move( 1 );
	BOOST_CHECK_EQUAL( gb.get_pos(), 1 );

	gb.move( 5 );
	BOOST_CHECK_EQUAL( gb.get_pos(), 6 );
}

BOOST_AUTO_TEST_CASE( MoveBackInsideTheBuffer )
{
	std::string in = "abcdefgh";
	gap_buffer gb;
	for( char ch : in )
		gb.put( ch );

	gb.move( -1 );
	BOOST_CHECK_EQUAL( gb.get_pos(), 7 );

	gb.move( -3 );
	BOOST_CHECK_EQUAL( gb.get_pos(), 4 );
}

BOOST_AUTO_TEST_CASE( MoveForwardOutsideTheBuffer )
{
	std::string in = "abcdefgh";
	gap_buffer gb;
	for( char ch : in )
		gb.put( ch );

	gb.move( 1 );
	BOOST_CHECK_EQUAL( gb.get_pos(), 8 );

	gb.move( 5 );
	BOOST_CHECK_EQUAL( gb.get_pos(), 8 );
}

BOOST_AUTO_TEST_CASE( MoveBackOutsideTheBuffer )
{
	std::string in = "abcdefgh";
	gap_buffer gb;
	for( char ch : in )
		gb.put( ch );

	gb.set_pos( 0 );
	gb.move( -1 );
	BOOST_CHECK_EQUAL( gb.get_pos(), 0 );

	gb.move( -5 );
	BOOST_CHECK_EQUAL( gb.get_pos(), 0 );
}

BOOST_AUTO_TEST_CASE( PrintEmptyBuffer )
{
	gap_buffer gb;
	std::string out = gb.print();
	BOOST_CHECK_EQUAL( out, "" );
}

BOOST_AUTO_TEST_CASE( PrintBuffer )
{
	std::string in = "abcdefgh";
	gap_buffer gb;
	for( char ch : in )
		gb.put( ch );

	std::string out = gb.print();
	BOOST_CHECK_EQUAL( in, out );
}

BOOST_AUTO_TEST_CASE( RemoveZeroChars )
{
	std::string in = "abcdefgh";
	gap_buffer gb;
	for( char ch : in )
	    gb.put( ch );

	gb.set_pos( 0 );
	gb.remove( 0 );
	std::string out = gb.print();
	BOOST_CHECK_EQUAL( in, out );

	gb.set_pos( 3 );
	gb.remove( 0 );
	out = gb.print();
	BOOST_CHECK_EQUAL( in, out );

	gb.set_pos( 7 );
	gb.remove( 0 );
	out = gb.print();
	BOOST_CHECK_EQUAL( in, out );

	gb.set_pos( 8 );
	gb.remove( 0 );
	out = gb.print();
	BOOST_CHECK_EQUAL( in, out );
}

BOOST_AUTO_TEST_CASE( RemoveFromFront )
{
	std::string in = "abcdefgh";
	gap_buffer gb;
	for( char ch : in )
	    gb.put( ch );

	gb.set_pos( 0 );

	gb.remove();
	in.erase( 0, 1 );
	std::string out = gb.print();
	BOOST_CHECK_EQUAL( in, out );
	
	gb.remove( 3 );
	out = gb.print();
	in.erase( 0, 3 );
	BOOST_CHECK_EQUAL( in, out );
}

BOOST_AUTO_TEST_CASE( RemoveFromCenter )
{
	std::string in = "abcdefgh";
	gap_buffer gb;
	for( char ch : in )
	    gb.put( ch );

	gb.set_pos( 2 );

	gb.remove();
	in.erase( 2, 1 );
	std::string out = gb.print();
	BOOST_CHECK_EQUAL( in, out );
	
	gb.remove( 3 );
	out = gb.print();
	in.erase( 2, 3 );
	BOOST_CHECK_EQUAL( in, out );
}

BOOST_AUTO_TEST_CASE( RemoveFromEnd )
{
	std::string in = "abcdefgh";
	gap_buffer gb;
	for( char ch : in )
	    gb.put( ch );

	gb.remove();
	std::string out = gb.print();
	BOOST_CHECK_EQUAL( in, out );
	
	gb.set_pos( 7 );
	gb.remove();
	out = gb.print();
	in.erase( 7, 1 );
	BOOST_CHECK_EQUAL( in, out );

	gb.set_pos( 4 );
	gb.remove( 3 );
	out = gb.print();
	in.erase( 4, 3 );
	BOOST_CHECK_EQUAL( in, out );
}
