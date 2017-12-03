/**
 * @file
 * @brief       Header file for XmlMessage.c source.
 */

#pragma once

#include <stdint.h>
#include <stdbool.h>
#include "XmlKeyValuePair.h"

typedef struct XmlMessage XmlMessage;

XmlMessage* XmlMessage_Create( void );
void XmlMessage_Destroy( XmlMessage* const message );
bool XmlMessage_TryAddData( XmlMessage* const message, XmlKeyValuePair* const pair );
