/**
 * @file
 * @brief       Header file for XmlMessage.c source.
 */

#pragma once

#include <stdint.h>
#include <stdbool.h>
#include "XmlKeyValuePair.h"

typedef struct XmlMessage XmlMessage;

typedef enum XmlMessageType
{
    MSG_TYPE_INVALID,
    MSG_TYPE_UPDATE,
    MSG_TYPE_RETRIEVE,
    MSG_TYPE_STATUS,

    MSG_TYPE_OUT_OF_BOUNDS
} XmlMessageType;

XmlMessage* XmlMessage_Create( XmlMessageType messageType );
void XmlMessage_Destroy( XmlMessage* const message );
bool XmlMessage_TryAddData( XmlMessage* const message, XmlKeyValuePair* const pair );
XmlMessageType XmlMessage_GetMessageType( const XmlMessage* const message );
