/**
 * @file
 * @brief       Where the XML data is stored from the Measuring Clients.
 *
 * The file that contains the XML data from the Measuring Clients and the helper
 * functions to modify and retrieve the data from the store.
 */

#include "XmlDataStore.h"

#define MAX_NUM_KEYS        128

static XmlKeyValuePair* DataStore[ MAX_NUM_KEYS ];
static uint16_t NumberOfKeys;

/**
 * @brief       Initialise the data store.
 *
 * Allocate a section of memory that is the size of the data store.
 */
void XmlDataStore_Init( void )
{
    /* *DataStore = (XmlKeyValuePair*) malloc( MAX_NUM_KEYS * sizeof ( *DataStore ) ); */
    int i;
    for ( i = 0; i < MAX_NUM_KEYS; i++ )
    {
        DataStore[ i ] = XmlKeyValuePair_Create();
    }
}

/**
 * @brief       Deinitialise the data store.
 *
 * Free the section of memory that is used for the data store.
 */
void XmlDataStore_DeInit( void )
{
    /* free( *DataStore ); */
    int i;
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
