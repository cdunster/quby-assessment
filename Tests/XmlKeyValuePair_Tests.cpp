/**
 * @file
 * @brief		CppUTest style unit tests for XmlKeyValuePair.c
 */

#include "CppUTest/TestHarness.h"
#include <string.h>

extern "C"
{
#include "XmlKeyValuePair.h"
#include "XmlKeyValuePair.c"
}

TEST_GROUP( Create )
{
};

TEST( Create, When_CreatingXmlKeyValuePair_Then_ReturnNoneNullPointer )
{
    /* When */
    XmlKeyValuePair* pair = XmlKeyValuePair_Create();

    /* Then */
    CHECK( NULL != pair );
    XmlKeyValuePair_Destroy( pair );
}

TEST_GROUP( TrySetPair )
{
    XmlKeyValuePair* pair;

    void setup( void )
    {
        pair = XmlKeyValuePair_Create();
    }

    void teardown( void )
    {
        XmlKeyValuePair_Destroy( pair );
    }
};

TEST( TrySetPair, Given_EmptyKey_When_TrySettingPair_Then_ReturnFalse )
{
    /* Given */
    char key[] = "";
    char value[] = "20";

    /* When */
    bool result = XmlKeyValuePair_TrySetPair( pair, key, value );

    /* Then */
    CHECK_EQUAL( false, result );
}

TEST( TrySetPair, Given_EmptyValue_When_TrySettingPair_Then_ReturnTrue )
{
    /* Given */
    char key[] = "testKey";
    char value[] = "";

    /* When */
    bool result = XmlKeyValuePair_TrySetPair( pair, key, value );

    /* Then */
    CHECK_EQUAL( true, result );
}

TEST( TrySetPair, Given_NoneEmptyKeyAndValue_When_TrySettingPair_Then_ReturnTrue )
{
    /* Given */
    char key[] = "testKey";
    char value[] = "20";

    /* When */
    bool result = XmlKeyValuePair_TrySetPair( pair, key, value );

    /* Then */
    CHECK_EQUAL( true, result );
}

TEST( TrySetPair, Given_KeyWithLengthOverMax_When_TrySettingPair_Then_ReturnFalse )
{
    /* Given */
    char key[ MAX_KEY_LEN + 2 ];
    char value[] = "20";

    memset( key, '1', MAX_KEY_LEN + 1 );

    /* When */
    bool result = XmlKeyValuePair_TrySetPair( pair, key, value );

    /* Then */
    CHECK_EQUAL( false, result );
}

TEST( TrySetPair, Given_ValueWithLengthOverMax_When_TrySettingPair_Then_ReturnFalse )
{
    /* Given */
    char key[] = "testKey";
    char value[ MAX_VALUE_LEN + 2 ];

    memset( value, '1', MAX_VALUE_LEN + 1 );

    /* When */
    bool result = XmlKeyValuePair_TrySetPair( pair, key, value );

    /* Then */
    CHECK_EQUAL( false, result );
}

TEST( TrySetPair, Given_ValidKeyAndValue_When_TrySettingPair_Then_KeyIsSet )
{
    /* Given */
    char key[] = "testKey";
    char value[] = "testValue";

    /* When */
    XmlKeyValuePair_TrySetPair( pair, key, value );

    /* Then */
    STRCMP_EQUAL( key, pair->Key );
}

TEST( TrySetPair, Given_ValidKeyAndValue_When_TrySettingPair_Then_ValueIsSet )
{
    /* Given */
    char key[] = "testKey";
    char value[] = "testValue";

    /* When */
    XmlKeyValuePair_TrySetPair( pair, key, value );

    /* Then */
    STRCMP_EQUAL( value, pair->Value );
}

TEST_GROUP( IsKeyValid )
{
    XmlKeyValuePair* pair;

    void setup( void )
    {
        pair = XmlKeyValuePair_Create();
    }

    void teardown( void )
    {
        XmlKeyValuePair_Destroy( pair );
    }
};

TEST( IsKeyValid, Given_EmptyKey_When_CheckingIsKeyValid_Then_ReturnFalse )
{
    /* Given */
    strcpy( pair->Key, "" );

    /* When */
    bool result = XmlKeyValuePair_IsKeyValid( pair );

    /* Then */
    CHECK_EQUAL( false, result );
}

TEST( IsKeyValid, Given_ValidKey_When_CheckingIsKeyValid_Then_ReturnTrue )
{
    /* Given */
    strcpy( pair->Key, "key123" );

    /* When */
    bool result = XmlKeyValuePair_IsKeyValid( pair );

    /* Then */
    CHECK_EQUAL( true, result );
}

TEST_GROUP( TrySetValue )
{
    XmlKeyValuePair* pair;

    void setup( void )
    {
        pair = XmlKeyValuePair_Create();
    }

    void teardown( void )
    {
        XmlKeyValuePair_Destroy( pair );
    }
};

TEST( TrySetValue, Given_ValidValue_When_TrySetValue_Then_ReturnTrue )
{
    /* Given */
    char value[] = "testValue";

    /* When */
    bool result = XmlKeyValuePair_TrySetValue( pair, value );

    /* Then */
    CHECK_EQUAL( true, result );
}

TEST( TrySetValue, Given_EmptyValue_When_TrySetValue_Then_ReturnTrue )
{
    /* Given */
    char value[] = "";

    /* When */
    bool result = XmlKeyValuePair_TrySetValue( pair, value );

    /* Then */
    CHECK_EQUAL( true, result );
}

TEST( TrySetValue, Given_ValueWithLengthOverMax_When_TrySetValue_Then_ReturnFalse )
{
    /* Given */

    char value[ MAX_VALUE_LEN + 2 ];

    memset( value, '1', MAX_VALUE_LEN + 1 );

    /* When */
    bool result = XmlKeyValuePair_TrySetValue( pair, value );

    /* Then */
    CHECK_EQUAL( false, result );
}

TEST( TrySetValue, Given_ValidValue_When_TrySetValue_Then_ValueIsSet )
{
    /* Given */
    strcpy( pair->Value, "value" );
    char value[] = "testValue";

    /* When */
    XmlKeyValuePair_TrySetValue( pair, value );

    /* Then */
    STRCMP_EQUAL( value, pair->Value );
}

TEST( TrySetValue, Given_EmptyValue_When_TrySetValue_Then_ValueIsSet )
{
    /* Given */
    strcpy( pair->Value, "value" );
    char value[] = "";

    /* When */
    XmlKeyValuePair_TrySetValue( pair, value );

    /* Then */
    STRCMP_EQUAL( value, pair->Value );
}

TEST( TrySetValue, Given_ValueWithLengthOverMax_When_TrySetValue_Then_ValueNotSet )
{
    /* Given */
    strcpy( pair->Value, "value" );
    char value[ MAX_VALUE_LEN + 2 ];

    memset( value, '1', MAX_VALUE_LEN + 1 );

    /* When */
    XmlKeyValuePair_TrySetValue( pair, value );

    /* Then */
    STRCMP_EQUAL( "value", pair->Value );
}

TEST_GROUP( TryCopy )
{
    XmlKeyValuePair* sourcePair;

    void setup( void )
    {
        sourcePair = XmlKeyValuePair_Create();
    }

    void teardown( void )
    {
        XmlKeyValuePair_Destroy( sourcePair );
    }
};

TEST( TryCopy, Given_ValidSource_When_TryCopy_Then_ReturnTrue )
{
    XmlKeyValuePair* destinationPair = XmlKeyValuePair_Create();

    /* Given */
    strcpy( sourcePair->Key, "key" );
    strcpy( sourcePair->Value, "42" );

    /* When */
    bool result = XmlKeyValuePair_TryCopy( destinationPair, sourcePair );

    /* Then */
    CHECK_EQUAL( true, result );

    XmlKeyValuePair_Destroy( destinationPair );
}
