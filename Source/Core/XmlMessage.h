/**
 * @file
 * @brief       Header file for XmlMessage.c source.
 */

#pragma once

#include <stdint.h>

typedef struct XmlMessage XmlMessage;

XmlMessage* XmlMessage_Create( uint16_t numberOfKeys );
void XmlMessage_Destroy( XmlMessage* const message );
