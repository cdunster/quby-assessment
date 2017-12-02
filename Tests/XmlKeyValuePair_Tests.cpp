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

TEST_GROUP( TrySetPair )
{
};

TEST( TrySetPair, Given_EmptyKey_When_TrySettingPair_Then_ReturnFalse )
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

TEST( TrySetPair, Given_EmptyValue_When_TrySettingPair_Then_ReturnTrue )
{
    /* Given */
    XmlKeyValuePair pair;
    char key[] = "testKey";
    char value[] = "";

    /* When */
    bool result = XmlKeyValuePair_TrySetPair( &pair, key, value );

    /* Then */
    CHECK_EQUAL( true, result );
}

TEST( TrySetPair, Given_NoneEmptyKeyAndValue_When_TrySettingPair_Then_ReturnTrue )
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

TEST( TrySetPair, Given_KeyWithLengthOverMax_When_TrySettingPair_Then_ReturnFalse )
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

TEST( TrySetPair, Given_ValueWithLengthOverMax_When_TrySettingPair_Then_ReturnFalse )
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

TEST( TrySetPair, Given_ValidKeyAndValue_When_TrySettingPair_Then_KeyIsSet )
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

TEST( TrySetPair, Given_ValidKeyAndValue_When_TrySettingPair_Then_ValueIsSet )
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

TEST_GROUP( TrySetValue )
{
};

TEST( TrySetValue, Given_ValidValue_When_TrySetValue_Then_ReturnTrue )
{
    /* Given */
    XmlKeyValuePair pair;
    char value[] = "testValue";

    /* When */
    bool result = XmlKeyValuePair_TrySetValue( &pair, value );

    /* Then */
    CHECK_EQUAL( true, result );
}

TEST( TrySetValue, Given_EmptyValue_When_TrySetValue_Then_ReturnTrue )
{
    /* Given */
    XmlKeyValuePair pair;
    char value[] = "";

    /* When */
    bool result = XmlKeyValuePair_TrySetValue( &pair, value );

    /* Then */
    CHECK_EQUAL( true, result );
}

TEST( TrySetValue, Given_ValueWithLengthOverMax_When_TrySetValue_Then_ReturnFalse )
{
    /* Given */
    XmlKeyValuePair pair;
    char value[ MAX_VALUE_LEN + 2 ];

    memset( value, '1', MAX_VALUE_LEN + 1 );

    /* When */
    bool result = XmlKeyValuePair_TrySetValue( &pair, value );

    /* Then */
    CHECK_EQUAL( false, result );
}

TEST( TrySetValue, Given_ValidValue_When_TrySetValue_Then_ValueIsSet )
{
    /* Given */
    XmlKeyValuePair pair =
    {
        "Key",
        "value"
    };
    char value[] = "testValue";

    /* When */
    XmlKeyValuePair_TrySetValue( &pair, value );

    /* Then */
    STRCMP_EQUAL( value, pair.Value );
}

TEST( TrySetValue, Given_EmptyValue_When_TrySetValue_Then_ValueIsSet )
{
    /* Given */
    XmlKeyValuePair pair =
    {
        "Key",
        "value"
    };
    char value[] = "";

    /* When */
    XmlKeyValuePair_TrySetValue( &pair, value );

    /* Then */
    STRCMP_EQUAL( value, pair.Value );
}

TEST( TrySetValue, Given_ValueWithLengthOverMax_When_TrySetValue_Then_ValueNotSet )
{
    /* Given */
    XmlKeyValuePair pair =
    {
        "Key",
        "value"
    };
    char value[ MAX_VALUE_LEN + 2 ];

    memset( value, '1', MAX_VALUE_LEN + 1 );

    /* When */
    XmlKeyValuePair_TrySetValue( &pair, value );

    /* Then */
    STRCMP_EQUAL( "value", pair.Value );
}
