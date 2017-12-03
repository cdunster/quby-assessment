/**
 * @file
 * @brief       CppUTest style unit tests for XmlDataStore.
 */

#include "CppUTest/TestHarness.h"
#include <string.h>

extern "C"
{
#include "XmlDataStore.h"
#include "XmlDataStore.c"
}

TEST_GROUP( GetNumberOfKeys )
{
};

TEST( GetNumberOfKeys, When_GettingNumberOfKeys_Then_ReturnNumberOfKeys )
{
    NumberOfKeys = 5;

	/* When */
    uint16_t result = XmlDataStore_GetNumberOfKeys();

	/* Then */
    CHECK_EQUAL( 5, result );
}

TEST_GROUP( TryAdd )
{
    XmlKeyValuePair* pair;

    void setup( void )
    {
        pair = XmlKeyValuePair_Create();
        XmlDataStore_Init();
    }

    void teardown( void )
    {
        XmlKeyValuePair_Destroy( pair );
        XmlDataStore_DeInit();
    }
};

TEST( TryAdd, Given_NumberOfKeysIsZero_When_TryAddingNewData_Then_NumberOfKeysIncremented )
{
    /* Given */
    XmlKeyValuePair_TrySetPair( pair, "key", "42" );
    NumberOfKeys = 0;

    /* When */
    XmlDataStore_TryAdd( pair );

    /* Then */
    CHECK_EQUAL( 1, NumberOfKeys );
}

TEST( TryAdd, Given_NumberOfKeysIsMax_When_TryAddingNewData_Then_NumberOfKeysIsNotChanged )
{
    NumberOfKeys = MAX_NUM_KEYS;

    /* Given */
    XmlKeyValuePair_TrySetPair( pair, "key", "42" );

    /* When */
    XmlDataStore_TryAdd( pair );

    /* Then */
    CHECK_EQUAL( MAX_NUM_KEYS, NumberOfKeys );
}

TEST( TryAdd, Given_ValidPairAndNumberOfKeysBelowMax_When_TryAddingNewData_Then_ReturnTrue )
{
    /* Given */
    XmlKeyValuePair_TrySetPair( pair, "key", "42" );
    NumberOfKeys = 0;

    /* When */
    bool result = XmlDataStore_TryAdd( pair );

    /* Then */
    CHECK_EQUAL( true, result );
}

TEST( TryAdd, Given_ValidPairButNumberOfKeysIsMax_When_TryAddingNewData_Then_ReturnFalse )
{
    /* Given */
    XmlKeyValuePair_TrySetPair( pair, "key", "42" );
    NumberOfKeys = MAX_NUM_KEYS;

    /* When */
    bool result = XmlDataStore_TryAdd( pair );

    /* Then */
    CHECK_EQUAL( false, result );
}

TEST( TryAdd, Given_PairKeyIsEmpty_When_TryAddingNewData_Then_ReturnFalse )
{
    /* Given */
    XmlKeyValuePair* newPair = XmlKeyValuePair_Create();    // Create new pair to force empty Key.

    /* When */
    bool result = XmlDataStore_TryAdd( newPair );

    /* Then */
    CHECK_EQUAL( false, result );

    XmlKeyValuePair_Destroy( newPair );
}

TEST( TryAdd, Given_PairKeyIsEmpty_When_TryAddingNewData_Then_DontStorePair )
{
    XmlKeyValuePair_TrySetPair( DataStore[ 0 ], "helloKey", "42" );

    /* Given */
    XmlKeyValuePair_TrySetPair( pair, "", "newValue" );

    /* When */
    XmlDataStore_TryAdd( pair );

    /* Then */
    STRCMP_EQUAL( "helloKey", XmlKeyValuePair_GetKey( DataStore[ 0 ] ) );
    STRCMP_EQUAL( "42", XmlKeyValuePair_GetValue( DataStore[ 0 ] ) );
}

TEST( TryAdd, Given_ValidPair_When_TryAddingNewData_Then_StorePair )
{
    XmlKeyValuePair_TrySetPair( DataStore[ 0 ], "key", "42" );

    /* Given */
    XmlKeyValuePair_TrySetPair( pair, "helloKey", "newValue" );

    /* When */
    XmlDataStore_TryAdd( pair );

    /* Then */
    STRCMP_EQUAL( "helloKey", XmlKeyValuePair_GetKey( DataStore[ 0 ] ) );
    STRCMP_EQUAL( "newValue", XmlKeyValuePair_GetValue( DataStore[ 0 ] ) );
}
