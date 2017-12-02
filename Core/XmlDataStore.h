/**
 * @file
 * @brief       The header file for the XmlDataStore.c source.
 */

#pragma once

#include <stdint.h>
#include <stdbool.h>
#include "XmlKeyValuePair.h"

uint16_t XmlDataStore_GetNumberOfKeys( void );
bool XmlDataStore_TryAdd( XmlKeyValuePair pair );
