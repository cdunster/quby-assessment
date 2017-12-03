/**
 * @file
 * @brief       Where the XML data is stored from the Measuring Clients.
 *
 * The file that contains the XML data from the Measuring Clients and the helper
 * functions to modify and retrieve the data from the store.
 */

#include "XmlDataStore.h"
#include <string.h>

#define MAX_NUM_KEYS        128U

static XmlKeyValuePair* DataStore[ MAX_NUM_KEYS ];
static uint16_t NumberOfKeys;

/**
 * @brief       Initialise the data store.
 *
 * Allocate a section of memory that is the size of the data store.
 */
void XmlDataStore_Init( void )
{
    uint16_t i;
    for ( i = 0; i < MAX_NUM_KEYS; i++ )
    {
        DataStore[ i ] = XmlKeyValuePair_Create();
    }
    NumberOfKeys = 0;
}

/**
 * @brief       Deinitialise the data store.
 *
 * Free the section of memory that is used for the data store.
 */
void XmlDataStore_DeInit( void )
{
    uint16_t i;
    for ( i = 0; i < MAX_NUM_KEYS; i++ )
    {
        XmlKeyValuePair_Destroy( DataStore[ i ] );
    }
}

/**
 * @brief       Get the current number of keys in the data store.
 * @return      Value of NumberOfKeys static.
 */
uint16_t XmlDataStore_GetNumberOfKeys( void )
{
    return NumberOfKeys;
}

/**
 * @brief       Try add the new data item to the data store.
 *
 * @param[in]   pair
 *              The XmlKeyValuePair to be added to the store.
 *
 * @return      true if the value is added to the data store.
 */
bool XmlDataStore_TryAdd( XmlKeyValuePair* pair )
{
    if ( MAX_NUM_KEYS <= NumberOfKeys )
    {
        return false;
    }

    if ( false == XmlKeyValuePair_IsKeyValid( pair ) )
    {
        return false;
    }

    if ( false == XmlKeyValuePair_TryCopy( DataStore[ NumberOfKeys ], pair ) )
    {
        return false;
    }

    NumberOfKeys++;

    return true;
}

/**
 * @brief       Get the index of the passed key in the data store.
 *
 * @param[in]   key
 *              The key to look for in the data store.
 *
 * @return      The index of the key or -1 if the key cannot be found.
 */
int32_t XmlDataStore_GetIndexOfKey( const char* const key )
{
    uint16_t i;
    for ( i = 0; i < NumberOfKeys; i++ )
    {
        if ( 0 == strcmp( XmlKeyValuePair_GetKey( DataStore[ i ] ), key ) )
        {
            return i;
        }
    }

    return KEY_NOT_FOUND;
}

/**
 * @brief       Try to get the value of the passed key from the data store.
 *
 * @param[in]   key
 *              The key to look for the value of in the data store.
 *
 * @param[out]  value
 *              Pointer to the value of the passed key from the data store.
 *
 * @return      true if the value is found.
 */
bool XmlDataStore_TryGetValueOfKey( const char* const key, const char** const value )
{
    int32_t indexOfKey = XmlDataStore_GetIndexOfKey( key );
    if ( KEY_NOT_FOUND == indexOfKey )
    {
        return false;
    }

    *value = XmlKeyValuePair_GetValue( DataStore[ indexOfKey ] );

    return true;
}
