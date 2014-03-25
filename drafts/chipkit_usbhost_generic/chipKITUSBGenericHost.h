/************************************************************************/
/*																		*/
/*	chipKITUSBGenericHost.h	-- USB Generic Host Class                           */
/*                         Generic Host Class thunk layer to the MAL        */
/*																		*/
/************************************************************************/
/*	Author: 	Keith Vogel 											*/
/*	Copyright 2011, Digilent Inc.										*/
/************************************************************************/
/*
  This library is free software; you can redistribute it and/or
  modify it under the terms of the GNU Lesser General Public
  License as published by the Free Software Foundation; either
  version 2.1 of the License, or (at your option) any later version.

  This library is distributed in the hope that it will be useful,
  but WITHOUT ANY WARRANTY; without even the implied warranty of
  MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the GNU
  Lesser General Public License for more details.

  You should have received a copy of the GNU Lesser General Public
  License along with this library; if not, write to the Free Software
  Foundation, Inc., 51 Franklin St, Fifth Floor, Boston, MA  02110-1301  USA
*/
/************************************************************************/
/*  Module Description: 												*/
/*  Just a class wrapper of the MAL Generic HOST code                       */
/*																		*/
/************************************************************************/
/*  Revision History:													*/
/*																		*/
/*	9/06/2011(KeithV): Created											*/
/*																		*/
/************************************************************************/
#ifndef _CHIPKITUSBGENERICHOSTCLASS_H
#define _CHIPKITUSBGENERICHOSTCLASS_H

#ifdef __cplusplus
     extern "C"
    {
    #undef BYTE             // Arduino defines BYTE as 0, not what we want for the MAL includes
    #define BYTE uint8_t    // for includes, make BYTE something Arduino will like     
#else
    #define uint8_t BYTE    // in the MAL .C files uint8_t is not defined, but BYTE is correct
#endif

// must have previously included ChipKITUSBHost.h in all .C or .CPP files that included this file
#include "USB/usb_host_generic.h"

#ifdef __cplusplus
    #undef BYTE
    #define BYTE 0      // put this back so Arduino Serial.print(xxx, BYTE) will work.
    // also replace all BYTE data types usages with uint8_t
    }
#endif

#ifdef __cplusplus

    class ChipKITUSBGenericHost 
    {
    public:
        BOOL Init ( uint8_t address, DWORD flags, uint8_t clientDriverID );
        BOOL EventHandler ( uint8_t address, USB_EVENT event, void *data, DWORD size );
        BOOL GetDeviceAddress(GENERIC_DEVICE_ID *pDevID);
        uint8_t Read( uint8_t deviceAddress, void *buffer, DWORD length);
        BOOL RxIsComplete( uint8_t deviceAddress,
                                    uint8_t *errorCode, DWORD *byteCount );
#ifndef USB_ENABLE_TRANSFER_EVENT
        void Tasks( void );
#endif
        BOOL TxIsComplete( uint8_t deviceAddress, uint8_t *errorCode );
        uint8_t Write( uint8_t deviceAddress, void *buffer, DWORD length);
    };

// pre-instantiated Class for the sketches
extern ChipKITUSBGenericHost USBGenericHost;

#endif
#endif
