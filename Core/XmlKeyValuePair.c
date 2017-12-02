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
bool XmlKeyValuePair_TrySetPair( XmlKeyValuePair* const pair, const char* const key, const char* const value )
{
    size_t keyLen = strlen( key );

    if ( 0 == keyLen || MAX_KEY_LEN < keyLen )
    {
        return false;
    }

    if ( false == XmlKeyValuePair_TrySetValue( pair, value ))
    {
        return false;
    }

    strcpy( pair->Key, key );

    return true;
}

/**
 * @brief       Try and assign the passed contents to the passed XmlKeyValuePair Value member.
 *
 * @param[in]   pair
 *              Pointer to the XmlKeyValuePair to assign the contents to.
 *
 * @param[in]   value
 *              The content to assign to the Value member of the passed XmlKeyValuePair.
 *
 * @return      true if the contents of value were assigned to pair.
 */
bool XmlKeyValuePair_TrySetValue( XmlKeyValuePair* const pair, const char* const value )
{
    size_t valueLen = strlen( value );

    if ( MAX_VALUE_LEN < valueLen )
    {
        return false;
    }

    strcpy( pair->Value, value );

    return true;
}

/**
 * @brief       Check that the passed XmlKeyValuePair has a valid key.
 *
 * @param[in]   pair
 *              The XmlKeyValuePair to check.
 *
 * @return      true if the key of the passed XmlKeyValuePair is valid.
 */
bool XmlKeyValuePair_IsKeyValid( const XmlKeyValuePair* const pair )
{
    size_t keyLen = strlen( pair->Key );

    if ( 0 == keyLen )
    {
        return false;
    }

    return true;
}

/**
 * @brief       Try to copy the contents of one XmlKeyValuePair to another.
 *
 * @param[out]  dest
 *              Pointer to the destination XmlKeyValuePair.
 *
 * @param[in]   source
 *              Pointer to the source XmlKeyValuePair.
 *
 * @return      true if the contents are copied.
 */
bool XmlKeyValuePair_TryCopy( XmlKeyValuePair* const dest, const XmlKeyValuePair* const source )
{
    return XmlKeyValuePair_TrySetPair( dest, source->Key, source->Value );
}
