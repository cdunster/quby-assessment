/**
 * @file
 * @brief	    Header file for the XmlKeyValuePair.c source.
 */

#pragma once

#include <stdbool.h>

#define MAX_KEY_LEN     64
#define MAX_VALUE_LEN   64

typedef struct XmlKeyValuePair
{
    char Key[ MAX_KEY_LEN + 1 ];
    char Value[ MAX_VALUE_LEN + 1 ];
} XmlKeyValuePair;

bool XmlKeyValuePair_TrySetPair( XmlKeyValuePair* pair, const char* const key, const char* const value );
bool XmlKeyValuePair_TrySetValue( XmlKeyValuePair* pair, const char* const value );
