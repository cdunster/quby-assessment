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

TEST( XmlMessage_Create, Given_SizeIsZero_When_CreatingXmlMessage_Then_ReturnNullPointer )
{
	/* Given */
    uint16_t numberOfKeys = 0;

	/* When */
    XmlMessage* message = XmlMessage_Create( numberOfKeys );

	/* Then */
    POINTERS_EQUAL( NULL, message );

    XmlMessage_Destroy( message );
}

TEST( XmlMessage_Create, Given_SizeIsAboveMaxNumberOfKeys_When_CreatingXmlMessage_Then_ReturnNullPointer )
{
    /* Given */
    uint16_t numberOfKeys = MAX_NUM_KEYS + 1;

    /* When */
    XmlMessage* message = XmlMessage_Create( numberOfKeys );

    /* Then */
    POINTERS_EQUAL( NULL, message );

    XmlMessage_Destroy( message );
}

TEST( XmlMessage_Create, Given_ValidSize_When_CreatingXmlMessage_Then_ReturnNoneNullPointer )
{
    /* Given */
    uint16_t numberOfKeys = 1;

    /* When */
    XmlMessage* message = XmlMessage_Create( numberOfKeys );

    /* Then */
    CHECK( NULL != message );

    XmlMessage_Destroy( message );
}

TEST( XmlMessage_Create, Given_ValidSize_When_CreatingXmlMessage_Then_NumberOfKeysIsSet )
{
    /* Given */
    uint16_t numberOfKeys = 3;

    /* When */
    XmlMessage* message = XmlMessage_Create( numberOfKeys );

    /* Then */
    CHECK_EQUAL( numberOfKeys, message->NumberOfKeys );

    XmlMessage_Destroy( message );
}
