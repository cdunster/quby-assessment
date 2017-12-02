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
};

TEST( TryAdd, Given_NumberOfKeysIsZero_When_TryAddingNewData_Then_NumberOfKeysIncremented )
{
    XmlKeyValuePair pair;

    /* Given */
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
    XmlKeyValuePair pair;

    /* When */
    XmlDataStore_TryAdd( pair );

    /* Then */
    CHECK_EQUAL( MAX_NUM_KEYS, NumberOfKeys );
}

TEST( TryAdd, Given_ValidPairAndNumberOfKeysBelowMax_When_TryAddingNewData_Then_ReturnTrue )
{
    /* Given */
    XmlKeyValuePair pair =
    {
        "key"
    };
    NumberOfKeys = 0;

    /* When */
    bool result = XmlDataStore_TryAdd( pair );

    /* Then */
    CHECK_EQUAL( true, result );
}

TEST( TryAdd, Given_ValidPairButNumberOfKeysIsMax_When_TryAddingNewData_Then_ReturnFalse )
{
    /* Given */
    XmlKeyValuePair pair;
    NumberOfKeys = MAX_NUM_KEYS;

    /* When */
    bool result = XmlDataStore_TryAdd( pair );

    /* Then */
    CHECK_EQUAL( false, result );
}

TEST( TryAdd, Given_PairKeyIsEmpty_When_TryAddingNewData_Then_ReturnFalse )
{
    /* Given */
    XmlKeyValuePair pair =
    {
        "", // Key
        ""  // Value
    };

    /* When */
    bool result = XmlDataStore_TryAdd( pair );

    /* Then */
    CHECK_EQUAL( false, result );
}

TEST( TryAdd, Given_PairKeyIsEmpty_When_TryAddingNewData_Then_DontStorePair )
{
    strcpy( DataStore[ 0 ].Key, "helloKey" );
    strcpy( DataStore[ 0 ].Value, "42" );

    /* Given */
    XmlKeyValuePair pair =
    {
        "", // Key
        ""  // Value
    };

    /* When */
    XmlDataStore_TryAdd( pair );

    /* Then */
    STRCMP_EQUAL( "helloKey", DataStore[ 0 ].Key );
    STRCMP_EQUAL( "42", DataStore[ 0 ].Value );
}

TEST( TryAdd, Given_ValidPair_When_TryAddingNewData_Then_StorePair )
{
    /* Given */
    XmlKeyValuePair pair =
    {
        "helloKey",
        "42"
    };

    /* When */
    XmlDataStore_TryAdd( pair );

    /* Then */
    STRCMP_EQUAL( "helloKey", DataStore[ 0 ].Key );
    STRCMP_EQUAL( "42", DataStore[ 0 ].Value );
}
