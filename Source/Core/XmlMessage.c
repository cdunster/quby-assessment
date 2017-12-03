/**
 * @file
 * @brief       Structure and helper functions for XmlMessage.
 */

#include "XmlMessage.h"
#include <stdlib.h>

#define MAX_NUM_KEYS        128U

struct XmlMessage
{
    uint16_t NumberOfKeys;
};

/**
 * @brief       Create a new XmlMessage with the passed number of keys by memory allocation.
 *
 * @param[in]   numberOfKeys
 *              The number of keys to be contained in the message.
 *
 * @return      Pointer to the area of memory that contains the new XmlMessage.
 */
XmlMessage* XmlMessage_Create( uint16_t numberOfKeys )
{
    if ( 0 >= numberOfKeys || MAX_NUM_KEYS <= numberOfKeys )
    {
        return NULL;
    }

    XmlMessage* message = (XmlMessage*) malloc( sizeof(XmlMessage) );
    message->NumberOfKeys = numberOfKeys;

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
    free( message );
}
