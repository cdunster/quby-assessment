/**
 * @file
 * @brief		CppUTest style unit tests for XmlMessage.c
 */

#include "CppUTest/TestHarness.h"

extern "C"
{
#include "XmlMessage.h"
#include "XmlMessage.c"
}

TEST_GROUP( XmlMessage_Create )
{
    void setup(void)
    {
    }

    void teardown(void)
    {
    }
};

TEST( XmlMessage_Create, When_CreatingXmlMessage_Then_ReturnNoneNullPointer )
{
    /* When */
    XmlMessage* message = XmlMessage_Create();

    /* Then */
    CHECK( NULL != message );

    XmlMessage_Destroy( message );
}

TEST_GROUP( XmlMessage_TryAddData )
{
    void setup(void)
    {
    }

    void teardown(void)
    {
    }
};

TEST( XmlMessage_TryAddData, Given_ValidMessage_When_TryingToAddNewData_Then_ReturnTrue )
{
    /* Given */
    XmlMessage* message = XmlMessage_Create();
    XmlKeyValuePair* pair = XmlKeyValuePair_Create();
    CHECK( XmlKeyValuePair_TrySetPair( pair, "key1", "value1" ) );

    /* When */
    bool result = XmlMessage_TryAddData( message, pair );

    /* Then */
    CHECK_EQUAL( true, result );

    XmlMessage_Destroy( message );
    XmlKeyValuePair_Destroy( pair );
}

TEST( XmlMessage_TryAddData, Given_InvalidMessage_When_TryingToAddNewData_Then_ReturnFalse )
{
    /* Given */
    XmlMessage* message = NULL;
    XmlKeyValuePair* pair = XmlKeyValuePair_Create();

    /* When */
    bool result = XmlMessage_TryAddData( message, pair );

    /* Then */
    CHECK_EQUAL( false, result );

    XmlKeyValuePair_Destroy( pair );
}

TEST( XmlMessage_TryAddData, Given_InvalidKeyValuePair_When_TryingToAddNewData_Then_ReturnFalse )
{
    /* Given */
    XmlMessage* message = XmlMessage_Create();
    XmlKeyValuePair* pair = NULL;

    /* When */
    bool result = XmlMessage_TryAddData( message, pair );

    /* Then */
    CHECK_EQUAL( false, result );

    XmlMessage_Destroy( message );
}

TEST( XmlMessage_TryAddData, Given_ValidMessage_When_TryingToAddNewData_Then_DataAdded )
{
    /* Given */
    XmlMessage* message = XmlMessage_Create();
    XmlKeyValuePair* pair = XmlKeyValuePair_Create();
    CHECK( XmlKeyValuePair_TrySetPair( pair, "key1", "value1" ) );

    /* When */
    XmlMessage_TryAddData( message, pair );

    /* Then */
    STRCMP_EQUAL( "key1", XmlKeyValuePair_GetKey( message->Data[ 0 ] ) );
    STRCMP_EQUAL( "value1", XmlKeyValuePair_GetValue( message->Data[ 0 ] ) );

    XmlMessage_Destroy( message );
    XmlKeyValuePair_Destroy( pair );
}

TEST( XmlMessage_TryAddData, Given_ValidMessageAndData_When_TryingToAddNewData_Then_DataCountIncremented )
{
    /* Given */
    XmlMessage* message = XmlMessage_Create();
    XmlKeyValuePair* pair = XmlKeyValuePair_Create();
    CHECK( XmlKeyValuePair_TrySetPair( pair, "key1", "value1" ) );

    /* When */
    XmlMessage_TryAddData( message, pair );

    /* Then */
    CHECK_EQUAL( 1, message->DataCount );

    XmlMessage_Destroy( message );
    XmlKeyValuePair_Destroy( pair );
}

TEST( XmlMessage_TryAddData, Given_InvalidData_When_TryingToAddNewData_Then_DataCountNotChanged )
{
    /* Given */
    XmlMessage* message = XmlMessage_Create();
    XmlKeyValuePair* pair = NULL;

    /* When */
    XmlMessage_TryAddData( message, pair );

    /* Then */
    CHECK_EQUAL( 0, message->DataCount );

    XmlMessage_Destroy( message );
}

TEST( XmlMessage_TryAddData, Given_DataWithEmptyKey_When_TryingToAddNewData_Then_DataCountNotChanged )
{
    /* Given */
    XmlMessage* message = XmlMessage_Create();
    XmlKeyValuePair* pair = XmlKeyValuePair_Create();

    /* When */
    XmlMessage_TryAddData( message, pair );

    /* Then */
    CHECK_EQUAL( 0, message->DataCount );

    XmlMessage_Destroy( message );
    XmlKeyValuePair_Destroy( pair );
}

TEST( XmlMessage_TryAddData, Given_DataWithEmptyKey_When_TryingToAddNewData_Then_DataNotCopied )
{
    /* Given */
    XmlMessage* message = XmlMessage_Create();
    CHECK( XmlKeyValuePair_TrySetPair( message->Data[ 0 ], "key1", "value1" ) );
    XmlKeyValuePair* pair = XmlKeyValuePair_Create();

    /* When */
    XmlMessage_TryAddData( message, pair );

    /* Then */
    STRCMP_EQUAL( "key1", XmlKeyValuePair_GetKey( message->Data[ 0 ] ) );
    STRCMP_EQUAL( "value1", XmlKeyValuePair_GetValue( message->Data[ 0 ] ) );

    XmlMessage_Destroy( message );
    XmlKeyValuePair_Destroy( pair );
}
