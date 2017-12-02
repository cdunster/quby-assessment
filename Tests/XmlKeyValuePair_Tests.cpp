/**
 * @file
 * @brief		CppUTest style unit tests for XmlKeyValuePair.c
 */

#include "CppUTest/TestHarness.h"
#include <string.h>

extern "C"
{
#include "XmlKeyValuePair.h"
}

TEST_GROUP( XmlKeyValuePair )
{
    void setup( void )
    {
    }

    void teardown( void )
    {
    }
};

TEST( XmlKeyValuePair, Given_EmptyKey_When_TrySettingPair_Then_ReturnFalse )
{
    /* Given */
    XmlKeyValuePair pair;
    char key[] = "";
    char value[] = "20";

    /* When */
    bool result = XmlKeyValuePair_TrySetPair( &pair, key, value );

    /* Then */
    CHECK_EQUAL( false, result );
}

TEST( XmlKeyValuePair, Given_EmptyValue_When_TrySettingPair_Then_ReturnFalse )
{
    /* Given */
    XmlKeyValuePair pair;
    char key[] = "testKey";
    char value[] = "";

    /* When */
    bool result = XmlKeyValuePair_TrySetPair( &pair, key, value );

    /* Then */
    CHECK_EQUAL( false, result );
}

TEST( XmlKeyValuePair, Given_NoneEmptyKeyAndValue_When_TrySettingPair_Then_ReturnTrue )
{
    /* Given */
    XmlKeyValuePair pair;
    char key[] = "testKey";
    char value[] = "20";

    /* When */
    bool result = XmlKeyValuePair_TrySetPair( &pair, key, value );

    /* Then */
    CHECK_EQUAL( true, result );
}

TEST( XmlKeyValuePair, Given_KeyWithLengthOverMax_When_TrySettingPair_Then_ReturnFalse )
{
    /* Given */
    XmlKeyValuePair pair;
    char key[ MAX_KEY_LEN + 2 ];
    char value[] = "20";

    memset( key, '1', MAX_KEY_LEN + 1 );

    /* When */
    bool result = XmlKeyValuePair_TrySetPair( &pair, key, value );

    /* Then */
    CHECK_EQUAL( false, result );
}

TEST( XmlKeyValuePair, Given_ValueWithLengthOverMax_When_TrySettingPair_Then_ReturnFalse )
{
    /* Given */
    XmlKeyValuePair pair;
    char key[] = "testKey";
    char value[ MAX_VALUE_LEN + 2 ];

    memset( value, '1', MAX_VALUE_LEN + 1 );

    /* When */
    bool result = XmlKeyValuePair_TrySetPair( &pair, key, value );

    /* Then */
    CHECK_EQUAL( false, result );
}

TEST( XmlKeyValuePair, Given_ValidKeyAndValue_When_TrySettingPair_Then_KeyIsSet )
{
    /* Given */
    XmlKeyValuePair pair;
    char key[] = "testKey";
    char value[] = "testValue";

    /* When */
    XmlKeyValuePair_TrySetPair( &pair, key, value );

    /* Then */
    STRCMP_EQUAL( key, pair.Key );
}

TEST( XmlKeyValuePair, Given_ValidKeyAndValue_When_TrySettingPair_Then_ValueIsSet )
{
    /* Given */
    XmlKeyValuePair pair;
    char key[] = "testKey";
    char value[] = "testValue";

    /* When */
    XmlKeyValuePair_TrySetPair( &pair, key, value );

    /* Then */
    STRCMP_EQUAL( value, pair.Value );
}
