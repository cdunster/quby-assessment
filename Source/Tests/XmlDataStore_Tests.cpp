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

TEST_GROUP( Init )
{
};

TEST( Init, Given_NumberOfKeysNotZero_When_Initialised_Then_NumberOfKeysIsZero )
{
    /* Given */
    NumberOfKeys = 3;

    /* When */
    XmlDataStore_Init();

    /* Then */
    CHECK_EQUAL( 0, NumberOfKeys );

    XmlDataStore_DeInit();
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
    XmlKeyValuePair_TrySetPair( DataStore[0], "a", "b" );

    /* Given */
    XmlKeyValuePair_TrySetPair( pair, "", "newValue" );

    /* When */
    XmlDataStore_TryAdd( pair );

    /* Then */
    STRCMP_EQUAL( "a", XmlKeyValuePair_GetKey( DataStore[ 0 ] ) );
    STRCMP_EQUAL( "b", XmlKeyValuePair_GetValue( DataStore[ 0 ] ) );
}

TEST( TryAdd, Given_ValidPair_When_TryAddingNewData_Then_StorePair )
{
    /* Given */
    XmlKeyValuePair_TrySetPair( pair, "helloKey", "newValue" );

    /* When */
    XmlDataStore_TryAdd( pair );

    /* Then */
    STRCMP_EQUAL( "helloKey", XmlKeyValuePair_GetKey( DataStore[ 0 ] ) );
    STRCMP_EQUAL( "newValue", XmlKeyValuePair_GetValue( DataStore[ 0 ] ) );
}

TEST( TryAdd, Given_ValidPairWithEmptyValue_When_TryAddingNewData_Then_StorePair )
{
    /* Given */
    XmlKeyValuePair_TrySetPair( pair, "helloKey", "" );

    /* When */
    XmlDataStore_TryAdd( pair );

    /* Then */
    STRCMP_EQUAL( "helloKey", XmlKeyValuePair_GetKey( DataStore[ 0 ] ) );
    STRCMP_EQUAL( "", XmlKeyValuePair_GetValue( DataStore[ 0 ] ) );
}

TEST( TryAdd, Given_DataStoreNotEmpty_When_TryAddingNewDataPair_Then_NumberOfKeysIncremented )
{
    /* Given */
    XmlKeyValuePair_TrySetPair( pair, "Key1", "Value1" );
    XmlDataStore_TryAdd( pair );

    /* When */
    XmlKeyValuePair* pair2 = XmlKeyValuePair_Create();
    XmlKeyValuePair_TrySetPair( pair2, "Key2", "Value2" );
    XmlDataStore_TryAdd( pair2 );

    /* Then */
    CHECK_EQUAL( 2, NumberOfKeys );

    XmlKeyValuePair_Destroy( pair2 );
}

TEST( TryAdd, Given_TwoValidPairs_When_TryAddingTwoNewDataPairs_Then_StorePairs )
{
    /* Given */
    XmlKeyValuePair_TrySetPair( pair, "Key1", "Value1" );

    XmlKeyValuePair* pair2 = XmlKeyValuePair_Create();
    XmlKeyValuePair_TrySetPair( pair2, "Key2", "Value2" );

    /* When */
    XmlDataStore_TryAdd( pair );
    XmlDataStore_TryAdd( pair2 );

    /* Then */
    STRCMP_EQUAL( "Key1", XmlKeyValuePair_GetKey( DataStore[ 0 ] ) );
    STRCMP_EQUAL( "Value1", XmlKeyValuePair_GetValue( DataStore[ 0 ] ) );
    STRCMP_EQUAL( "Key2", XmlKeyValuePair_GetKey( DataStore[ 1 ] ) );
    STRCMP_EQUAL( "Value2", XmlKeyValuePair_GetValue( DataStore[ 1 ] ) );

    XmlKeyValuePair_Destroy( pair2 );
}

TEST_GROUP( GetIndexOfKey )
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

TEST( GetIndexOfKey, Given_KeyInDataStore_When_GettingIndexOfKey_Then_ReturnIndex )
{
    /* Given */
    XmlKeyValuePair_TrySetPair( pair, "helloKey", "newValue" );
    XmlDataStore_TryAdd( pair );

    /* When */
    int32_t index = XmlDataStore_GetIndexOfKey( "helloKey" );

    /* Then */
    CHECK_EQUAL( 0, index );
}

TEST( GetIndexOfKey, Given_KeyNotInDataStore_When_GettingIndexOfKey_Then_ReturnKeyNotFound )
{
    /* Given */

    /* When */
    int32_t index = XmlDataStore_GetIndexOfKey( "helloKey" );

    /* Then */
    CHECK_EQUAL( KEY_NOT_FOUND, index );
}

TEST( GetIndexOfKey, Given_KeyAtIndexThreeInDataStore_When_GettingIndexOfKey_Then_ReturnThree )
{
    /* Given */
    XmlKeyValuePair_TrySetPair( pair, "key1", "value1" );
    XmlDataStore_TryAdd( pair );

    XmlKeyValuePair_TrySetPair( pair, "key2", "value2" );
    XmlDataStore_TryAdd( pair );

    XmlKeyValuePair_TrySetPair( pair, "key3", "value3" );
    XmlDataStore_TryAdd( pair );

    XmlKeyValuePair_TrySetPair( pair, "key4", "value4" );
    XmlDataStore_TryAdd( pair );

    /* When */
    int32_t index = XmlDataStore_GetIndexOfKey( "key4" );

    /* Then */
    CHECK_EQUAL( 3, index );
}
