
/********************************** (C) COPYRIGHT *******************************
* File Name          : USBHostHUB_KM.C
* Author             : WCH
* Version            : V2.0
* Date               : 2018/07/24
*******************************************************************************/

#include <ch554.h>
#include <debug.h>
#include "usbhost.h"
#include <ch554_usb.h>
#include <stdio.h>
#include <string.h>

__code uint8_t  SetupGetDevDescr[] = { USB_REQ_TYP_IN, USB_GET_DESCRIPTOR, 0x00, USB_DESCR_TYP_DEVICE, 0x00, 0x00, sizeof( USB_DEV_DESCR ), 0x00 };
__code uint8_t  SetupGetCfgDescr[] = { USB_REQ_TYP_IN, USB_GET_DESCRIPTOR, 0x00, USB_DESCR_TYP_CONFIG, 0x00, 0x00, 0x04, 0x00 };
__code uint8_t  SetupSetUsbAddr[] = { USB_REQ_TYP_OUT, USB_SET_ADDRESS, USB_DEVICE_ADDR, 0x00, 0x00, 0x00, 0x00, 0x00 };
__code uint8_t  SetupSetUsbConfig[] = { USB_REQ_TYP_OUT, USB_SET_CONFIGURATION, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00 };
__code uint8_t  SetupSetUsbInterface[] = { USB_REQ_RECIP_INTERF, USB_SET_INTERFACE, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00 };
__code uint8_t  SetupClrEndpStall[] = { USB_REQ_TYP_OUT | USB_REQ_RECIP_ENDP, USB_CLEAR_FEATURE, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00 };
__code uint8_t  SetupGetHubDescr[] = { HUB_GET_HUB_DESCRIPTOR, HUB_GET_DESCRIPTOR, 0x00, USB_DESCR_TYP_HUB, 0x00, 0x00, sizeof( USB_HUB_DESCR ), 0x00 };
__code uint8_t  SetupSetHIDIdle[]= { 0x21,HID_SET_IDLE,0x00,0x00,0x00,0x00,0x00,0x00 };
__code uint8_t  SetupGetHIDDevReport[] = { 0x81, USB_GET_DESCRIPTOR, 0x00, USB_DESCR_TYP_REPORT, 0x00, 0x00, 0xFF, 0x00 };
__code uint8_t  XPrinterReport[] = { 0xA1, 0, 0x00, 0, 0x00, 0x00, 0xF1, 0x03 };
__code uint8_t  GetProtocol[] = { 0xc0,0x33,0x00,0x00,0x00,0x00,0x02,0x00 };
__code uint8_t  TouchAOAMode[] = { 0x40,0x35,0x00,0x00,0x00,0x00,0x00,0x00 };

__code uint8_t  Sendlen[]= {0,4,16,35,39,53,67};
__code uint8_t  StringID[] = {'W','C','H',0x00,                                                                                //manufacturer name
                      'W','C','H','U','A','R','T','D','e','m','o',0x00,                                   //model name
                      0x57,0x43,0x48,0x20,0x41,0x63,0x63,0x65,0x73,0x73,0x6f,0x72,0x79,0x20,0x54,0x65,0x73,0x74,0x00,     //description
                      '1','.','0',0x00 ,                                                                       //version
                      0x68,0x74,0x74,0x70,0x3a,0x2f,0x2f,0x77,0x63,0x68,0x2e,0x63,0x6e,0,//URI
                      0x57,0x43,0x48,0x41,0x63,0x63,0x65,0x73,0x73,0x6f,0x72,0x79,0x31,0x00                               //serial number
                     };  
__code uint8_t  SetStringID[]= {0x40,0x34,0x00,0x00,0x00,0x00,0x04,0x00,
                        0x40,0x34,0x00,0x00,0x01,0x00,12,0x00,
                        0x40,0x34,0x00,0x00,0x02,0x00,19,0x00,
                        0x40,0x34,0x00,0x00,0x03,0x00,4,0x00,
                        0x40,0x34,0x00,0x00,0x04,0x00,0x0E,0x00,
                        0x40,0x34,0x00,0x00,0x05,0x00,0x0E,0x00
                       };

__xdata uint8_t  UsbDevEndp0Size;                                                       //* USB???????????????0?????????????????? */
__xdata __at (0x0000) uint8_t  RxBuffer[ MAX_PACKET_SIZE ];                              // IN, must even address
__xdata __at (0x0040) uint8_t  TxBuffer[ MAX_PACKET_SIZE ];                            // OUT, must even address

uint8_t Set_Port = 0;

__xdata _RootHubDev ThisUsbDev;                                                   //ROOT???
__xdata _DevOnHubPort DevOnHubPort[HUB_MAX_PORTS];                                // ??????:?????????1?????????HUB,????????????HUB?????????HUB_MAX_PORTS?????????(????????????)

__bit RootHubId;                                                                  // ?????????????????????root-hub?????????:0=HUB0,1=HUB1
__bit FoundNewDev;

void main( )
{
    uint8_t   i, s,k, len, endp;
    uint16_t  loc;
	CfgFsys( );	
	mDelaymS(50);
    mInitSTDIO( );                                                              //????????????????????????????????????????????????
    printf( "Start @ChipID=%02X\n", (uint16_t)CHIP_ID );
    InitUSB_Host( );
    FoundNewDev = 0;
    printf( "Wait Device In\n" );
    while ( 1 )
    {
        s = ERR_SUCCESS;
        if ( UIF_DETECT ){                                                       // ?????????USB???????????????????????????
            UIF_DETECT = 0;                                                      // ???????????????			
            s = AnalyzeRootHub( );                                               // ??????ROOT-HUB??????
            if ( s == ERR_USB_CONNECT ) FoundNewDev = 1;						
        }
        if ( FoundNewDev ){                                                      // ?????????USB????????????
            FoundNewDev = 0;
//          mDelaymS( 200 );                                                     // ??????USB???????????????????????????,?????????USB??????????????????,??????????????????
            s = EnumAllRootDevice( );                                            // ????????????ROOT-HUB?????????USB??????
            if ( s != ERR_SUCCESS ){						
                printf( "EnumAllRootDev err = %02X\n", (uint16_t)s );					
            }
        }

		/* ??????CH554??????????????????HUB???????????????HUB */
		s = EnumAllHubPort( );                                                // ????????????ROOT-HUB???????????????HUB????????????USB??????
		if ( s != ERR_SUCCESS ){                                              // ?????????HUB?????????
			printf( "EnumAllHubPort err = %02X\n", (uint16_t)s );
		}

		/* ????????????????????? */
		loc = SearchTypeDevice( DEV_TYPE_MOUSE );                             // ???ROOT-HUB????????????HUB?????????????????????????????????????????????????????????
		if ( loc != 0xFFFF ){                                                 // ?????????,???????????????MOUSE?????????????
			printf( "Query Mouse @%04X\n", loc );
			i = (uint8_t)( loc >> 8 );
			len = (uint8_t)loc;
			SelectHubPort( len );                                             // ?????????????????????ROOT-HUB??????,????????????USB??????????????????????????????USB??????
			endp = len ? DevOnHubPort[len-1].GpVar[0] : ThisUsbDev.GpVar[0];        // ?????????????????????,???7?????????????????????
			if ( endp & USB_ENDP_ADDR_MASK ){                                 // ????????????
				s = USBHostTransact( USB_PID_IN << 4 | endp & 0x7F, endp & 0x80 ? bUH_R_TOG | bUH_T_TOG : 0, 0 );// CH554????????????,????????????,NAK?????????
				if ( s == ERR_SUCCESS ){
					endp ^= 0x80;                                             // ??????????????????
					if ( len ) DevOnHubPort[len-1].GpVar[0] = endp;              // ?????????????????????
					else ThisUsbDev.GpVar[0] = endp;
					len = USB_RX_LEN;                                         // ????????????????????????
					if ( len ) {
						printf("Mouse data: ");
						for ( i = 0; i < len; i ++ ){
							printf("x%02X ",(uint16_t)(RxBuffer[i]) );
						}
						printf("\n");
					}
				}
				else if ( s != ( USB_PID_NAK | ERR_USB_TRANSFER ) ) {
					printf("Mouse error %02x\n",(uint16_t)s);                   // ??????????????????
				}
			}
			else {
				printf("Mouse no interrupt endpoint\n");
			}
			SetUsbSpeed( 1 );                                                 // ???????????????
		}


		/* ????????????????????? */
		loc = SearchTypeDevice( DEV_TYPE_KEYBOARD );                          // ???ROOT-HUB????????????HUB?????????????????????????????????????????????????????????
		if ( loc != 0xFFFF ){                                                 // ?????????,???????????????KeyBoard?????????????
			printf( "Query Keyboard @%04X\n", loc );
			i = (uint8_t)( loc >> 8 );
			len = (uint8_t)loc;
			SelectHubPort( len );                                             // ?????????????????????ROOT-HUB??????,????????????USB??????????????????????????????USB??????
			endp = len ? DevOnHubPort[len-1].GpVar[0] : ThisUsbDev.GpVar[0];        // ?????????????????????,???7?????????????????????
			printf("%02X  ",endp);
			if ( endp & USB_ENDP_ADDR_MASK ){                                 // ????????????
				s = USBHostTransact( USB_PID_IN << 4 | endp & 0x7F, endp & 0x80 ? bUH_R_TOG | bUH_T_TOG : 0, 0 );// CH554????????????,????????????,NAK?????????
				if ( s == ERR_SUCCESS ){
					endp ^= 0x80;                                             // ??????????????????
					if ( len ) DevOnHubPort[len-1].GpVar[0] = endp;              // ?????????????????????
					else ThisUsbDev.GpVar[0] = endp;
					len = USB_RX_LEN;                                         // ????????????????????????
					if ( len ){
						SETorOFFNumLock(RxBuffer);
						printf("keyboard data: ");
						for ( i = 0; i < len; i ++ ){
							printf("x%02X ",(uint16_t)(RxBuffer[i]) );
						}
						printf("\n");
					}
				}
				else if ( s != ( USB_PID_NAK | ERR_USB_TRANSFER ) ){
					printf("keyboard error %02x\n",(uint16_t)s);               // ??????????????????
				}
			}
			else{
				printf("keyboard no interrupt endpoint\n");
			}
			SetUsbSpeed( 1 );                                                // ???????????????
		}

		/* ??????USB????????? */
		if(TIN0 == 0){                                                          //P10?????????????????????
			memset(TxBuffer,0,sizeof(TxBuffer));
			TxBuffer[0]=0x1B;TxBuffer[1]=0x40;TxBuffer[2]=0x1D;TxBuffer[3]=0x55;TxBuffer[4]=0x42;TxBuffer[5]=0x02;TxBuffer[6]=0x18;TxBuffer[7]=0x1D;
			TxBuffer[8]=0x76;TxBuffer[9]=0x30;TxBuffer[10]=0x00;TxBuffer[11]=0x30;TxBuffer[12]=0x00;TxBuffer[13]=0x18;
			loc = SearchTypeDevice( USB_DEV_CLASS_PRINTER );                       // ???ROOT-HUB????????????HUB?????????????????????????????????????????????????????????
			if ( loc != 0xFFFF ){                                                  // ?????????,?????????????????????????????????????
				printf( "Query Printer @%04X\n", loc );
				i = (uint8_t)( loc >> 8 );
				len = (uint8_t)loc;
				SelectHubPort( len );                                              // ?????????????????????ROOT-HUB??????,????????????USB??????????????????????????????USB??????
				endp = len ? DevOnHubPort[len-1].GpVar[0] : ThisUsbDev.GpVar[0];         // ???????????????,???7?????????????????????
				printf("%02X  ",endp);  
				if ( endp & USB_ENDP_ADDR_MASK ){                                  // ????????????
					UH_TX_LEN = 64;                                                // ?????????????????????????????????IN										
					s = USBHostTransact( USB_PID_OUT << 4 | endp & 0x7F, endp & 0x80 ? bUH_R_TOG | bUH_T_TOG : 0, 0xffff );// CH554????????????,????????????,NAK??????
					if ( s == ERR_SUCCESS ){
						endp ^= 0x80;                                               // ??????????????????
						memset(TxBuffer,0,sizeof(TxBuffer));
						UH_TX_LEN = 64;                                             // ?????????????????????????????????IN										
						s = USBHostTransact( USB_PID_OUT << 4 | endp & 0x7F, endp & 0x80 ? bUH_R_TOG | bUH_T_TOG : 0, 0xffff );// CH554????????????,????????????,NAK??????   											
					}
					else if ( s != ( USB_PID_NAK | ERR_USB_TRANSFER ) ) printf("Printer error %02x\n",(uint16_t)s); // ??????????????????
				}
			}
		}				

		/* ??????HID???????????? */
		loc = SearchTypeDevice( USB_DEV_CLASS_HID );                          // ???ROOT-HUB????????????HUB?????????????????????????????????????????????????????????			
		if ( loc != 0xFFFF ){                                                 // ?????????
			printf( "Query USB_DEV_CLASS_HID @%04X\n", loc );	
			loc = (uint8_t)loc;                                                 //554????????????USB????????????????????????

			for(k=0;k!=4;k++)
			{	
				//?????????????????????
				endp = loc ? DevOnHubPort[loc-1].GpVar[k] : ThisUsbDev.GpVar[k];        // ?????????????????????,???7?????????????????????			
				if ( (endp & USB_ENDP_ADDR_MASK) == 0 ) break;

				printf("endp: %02X\n",(uint16_t)endp);
				SelectHubPort( loc );                                             // ?????????????????????ROOT-HUB??????,????????????USB??????????????????????????????USB??????
				s = USBHostTransact( USB_PID_IN << 4 | endp & 0x7F, endp & 0x80 ? bUH_R_TOG | bUH_T_TOG : 0, 0 );// CH554????????????,????????????,NAK?????????
				if ( s == ERR_SUCCESS ){
					endp ^= 0x80;                                             // ??????????????????
					if ( loc ) DevOnHubPort[loc-1].GpVar[k] = endp;              // ?????????????????????
					else ThisUsbDev.GpVar[k] = endp;
					len = USB_RX_LEN;                                         // ????????????????????????
					if ( len ){
						printf("keyboard data: ");
						for ( i = 0; i < len; i ++ ){
							printf("x%02X ",(uint16_t)(RxBuffer[i]) );
						}
						printf("\n");
					}
				}
				else if ( s != ( USB_PID_NAK | ERR_USB_TRANSFER ) ){
					printf("keyboard error %02x\n",(uint16_t)s);               // ??????????????????
				}

			}								
			SetUsbSpeed( 1 );                                                // ???????????????
		}            					


		/* ??????????????????????????????????????????????????????AOA???????????? */
		loc = SearchTypeDevice( DEF_AOA_DEVICE );                            // ??????AOA
		if ( loc != 0xFFFF ){                                                 // ?????????	
			loc = (uint8_t)loc;                                                 //??????USBHOST.C?????????ROOTHUB??????Android??????,????????????loc

			endp = ThisUsbDev.GpVar[0];                                       //????????????????????????IN???		
			if ( (endp & USB_ENDP_ADDR_MASK) != 0 )                           //????????????
			{
				SelectHubPort( 0 );                                             // ?????????????????????ROOT-HUB??????,????????????USB??????????????????????????????USB??????
				s = USBHostTransact( USB_PID_IN << 4 | endp & 0x7F, endp & 0x80 ? bUH_R_TOG | bUH_T_TOG : 0, 0 );// CH554????????????,????????????,NAK?????????
				if ( s == ERR_SUCCESS ){
					endp ^= 0x80;                                             // ??????????????????  
					ThisUsbDev.GpVar[0] = endp;                               // ?????????????????????
					len = USB_RX_LEN;                                         // ????????????????????????

					for ( i = 0; i < len; i ++ ){
						printf("x%02X ",(uint16_t)(RxBuffer[i]) );
					}
					printf("\n");					
					if ( len ){

						memcpy(TxBuffer,RxBuffer,len);                         //??????
						endp = ThisUsbDev.GpVar[2];                            //???????????????OUT???
						UH_TX_LEN = len; 
						s = USBHostTransact( USB_PID_OUT << 4 | endp & 0x7F, endp & 0x80 ? bUH_R_TOG | bUH_T_TOG : 0, 0xffff ); //?????????????????????
						if(s == ERR_SUCCESS)
						{
							endp ^= 0x80;                                       // ??????????????????  
							ThisUsbDev.GpVar[2] = endp;                         // ?????????????????????						
							printf("send back\n");
						}

					}
				}
				else if ( s != ( USB_PID_NAK | ERR_USB_TRANSFER ) ){
					printf("transmit error %02x\n",(uint16_t)s);               // ??????????????????
				}					
			}					
			SetUsbSpeed( 1 );                                                // ???????????????
		} 


    }
}
