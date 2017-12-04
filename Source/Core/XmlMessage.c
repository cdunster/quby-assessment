/**
 * @file
 * @brief       Structure and helper functions for XmlMessage.
 */

#include "XmlMessage.h"
#include <stdlib.h>

#define MAX_NUM_DATA_SLOTS      128U

struct XmlMessage
{
    XmlMessageType MessageType;
    XmlKeyValuePair* Data[ MAX_NUM_DATA_SLOTS ];
    uint16_t DataCount;
};

/**
 * @brief       Create a new XmlMessage by memory allocation.
 *
 * @param[in]   messageType
 *              The type of message to create.
 *
 * @return      Pointer to the area of memory that contains the new XmlMessage.
 */
XmlMessage* XmlMessage_Create( XmlMessageType messageType )
{
    if ( MSG_TYPE_INVALID == messageType || MSG_TYPE_OUT_OF_BOUNDS <= messageType )
    {
        return NULL;
    }

    XmlMessage* message = (XmlMessage*) malloc( sizeof(XmlMessage) );

    uint16_t i;
    for ( i = 0; i < MAX_NUM_DATA_SLOTS; i++ )
    {
        message->Data[ i ] = XmlKeyValuePair_Create();
    }

    message->DataCount = 0;
    message->MessageType = messageType;

    return message;
}

/**
 * @brief       Destroy the passed XmlMessage by freeing the memory allocated to it.
 *
 * @param[in]   message
 *              Pointer to the XmlMessage to destroy.
 */
void XmlMessage_Destroy( XmlMessage* const message )
{
    if ( NULL == message )
    {
        return;
    }

    uint16_t i;
    for ( i = 0; i < MAX_NUM_DATA_SLOTS; i++ )
    {
        XmlKeyValuePair_Destroy( message->Data[ i ] );
    }

    free( message );
}

/**
 * @brief       Try to copy the passed XmlKeyValuePair to the data of the XmlMessage.
 *
 * @param[in]   message
 *              The XmlMessage to copy the XmlKeyValuePair to.
 *
 * @param[in]   pair
 *              The XmlKeyValuePair to copy.
 *
 * @return      true if the XmlKeyValuePair is copied to the XmlMessage.
 */
bool XmlMessage_TryAddData( XmlMessage* const message, XmlKeyValuePair* const pair )
{
    if ( NULL == message || NULL == pair )
    {
        return false;
    }

    if ( false == XmlKeyValuePair_TryCopy( message->Data[ message->DataCount ], pair ) )
    {
        return false;
    }

    message->DataCount++;

    return true;
}
