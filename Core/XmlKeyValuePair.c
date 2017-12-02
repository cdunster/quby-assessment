/**
 * @file
 * @brief       Structure and helper functions for XmlKeyValuePair.
 *
 * The XmlKeyValuePair structure holds the name of the XML key and it's value.
 * This file also contains helper functions to manipulate the structure.
 */

#include "XmlKeyValuePair.h"
#include <string.h>

/**
 * @brief       Try and assign the passed contents to the passed XmlKeyValuePair.
 *
 * @param[in]   pair
 *              Pointer to the XmlKeyValuePair to assign the contents to.
 *
 * @param[in]   key
 *              The content to assign to the Key member of the passed XmlKeyValuePair.
 *
 * @param[in]   value
 *              The content to assign to the Value member of the passed XmlKeyValuePair.
 *
 * @return      true if the contents of key and value were assigned to pair.
 */
bool XmlKeyValuePair_TrySetPair( XmlKeyValuePair* pair, const char* const key, const char* const value )
{
    size_t keyLen = strlen( key );
    size_t valueLen = strlen( value );

    if ( 0 == keyLen || MAX_KEY_LEN < keyLen )
    {
        return false;
    }

    if ( 0 == valueLen || MAX_VALUE_LEN < valueLen )
    {
        return false;
    }

    strcpy( pair->Key, key );
    strcpy( pair->Value, value );

    return true;
}
