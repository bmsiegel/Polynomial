#define CATCH_CONFIG_MAIN

#include <cstdlib>
#include <ctime>
#include "catch.hpp"
#include <memory>
#include "LinkedList.hpp"


TEST_CASE( "Test construction" )
{
	INFO( "Hint: Checking basic construction" );
	LinkedList<int> ll;
	REQUIRE( ll.isEmpty() );
	REQUIRE( ll.getLength() == 0 );
}
TEST_CASE("Tests insert")
{
	LinkedList<int> L;
	for (int c = 1; c < 10; c++)
	{
		L.insert(c,c);
	}
	L.insert(5,10);
	REQUIRE(L.getLength() == 10);
	REQUIRE(L.getEntry(5) == 10);
	L.insert(1,10);
	REQUIRE(L.getEntry(1) == 10);
	REQUIRE(L.getEntry(2) == 1);
	REQUIRE(L.getEntry(6) == 10);
}
TEST_CASE("Tests remove")
{
	LinkedList<int> L;
	for (int c = 1; c < 10; c++)
	{
		L.insert(c,c);
	}
	L.remove(5);
	REQUIRE(L.getEntry(5) == 6);
	REQUIRE(L.getEntry(4) == 4);
	L.remove(L.getLength());
	REQUIRE(L.getEntry(L.getLength()) == 8);
	L.remove(1);
	REQUIRE(L.getEntry(1) == 2);
}
TEST_CASE("Test replace")
{
	LinkedList<int> L;
	for (int c = 1; c < 10; c++)
	{
		L.insert(c,c);
	}
	L.replace(1,10);
	L.replace(7, 12);
	REQUIRE(L.getEntry(7) == 12);
	REQUIRE(L.getEntry(1) == 10);
}
TEST_CASE("Tests Exception Handling")
{
	LinkedList<int> L;
	REQUIRE_THROWS(L.getEntry(4));
	REQUIRE_THROWS(L.remove(4));
	REQUIRE_THROWS(L.replace(4,5));
	REQUIRE_THROWS(L.insert(4,5));
}
TEST_CASE("Tests Clear")
{
	LinkedList<int> L;
	for (int c = 1; c < 10; c++)
	{
		L.insert(c,c);
	}
	L.clear();
	REQUIRE(L.getLength() == 0);
	REQUIRE(L.isEmpty());
	REQUIRE_THROWS(L.getEntry(9));
}
TEST_CASE("Tests copy constructor and copy-swap paradigm")
{
	LinkedList<int> L;
	LinkedList<int> Q;
	for (int c = 1; c < 10; c++)
	{
		L.insert(c,c);
	}
	for (int c = 1; c < 100; c++)
	{
		Q.insert(c,c);
	}
	LinkedList<int> Check = L;
	Q = L;
	for (int c = 1; c < 10; c++)
	{
		REQUIRE(L.getEntry(c) == Q.getEntry(c));
		REQUIRE(L.getEntry(c) == Check.getEntry(c));
	}
	REQUIRE(Q.getLength() == 9);
	REQUIRE(L.getLength() == Q.getLength());
	REQUIRE(L.getLength() == Check.getLength());
}
