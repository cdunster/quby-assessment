/**
 * @file
 * @brief	    Header file for the XmlKeyValuePair.c source.
 */

#pragma once

#include <stdbool.h>

typedef struct XmlKeyValuePair XmlKeyValuePair;

XmlKeyValuePair* XmlKeyValuePair_Create( void );
void XmlKeyValuePair_Destroy( const XmlKeyValuePair* const pair );
bool XmlKeyValuePair_TrySetPair( XmlKeyValuePair* const pair, const char* const key, const char* const value );
bool XmlKeyValuePair_IsKeyValid( const XmlKeyValuePair* const pair );
bool XmlKeyValuePair_TrySetValue( XmlKeyValuePair* const pair, const char* const value );
bool XmlKeyValuePair_TryCopy( XmlKeyValuePair* const dest, const XmlKeyValuePair* const source );
const char* const XmlKeyValuePair_GetKey( const XmlKeyValuePair* const pair );
const char* const XmlKeyValuePair_GetValue( const XmlKeyValuePair* const pair );
