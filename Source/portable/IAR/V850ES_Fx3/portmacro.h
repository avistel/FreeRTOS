/*
	FreeRTOS.org V5.1.1 - Copyright (C) 2003-2008 Richard Barry.

	This file is part of the FreeRTOS.org distribution.

	FreeRTOS.org is free software; you can redistribute it and/or modify
	it under the terms of the GNU General Public License as published by
	the Free Software Foundation; either version 2 of the License, or
	(at your option) any later version.

	FreeRTOS.org is distributed in the hope that it will be useful,
	but WITHOUT ANY WARRANTY; without even the implied warranty of
	MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
	GNU General Public License for more details.

	You should have received a copy of the GNU General Public License
	along with FreeRTOS.org; if not, write to the Free Software
	Foundation, Inc., 59 Temple Place, Suite 330, Boston, MA  02111-1307  USA

	A special exception to the GPL can be applied should you wish to distribute
	a combined work that includes FreeRTOS.org, without being obliged to provide
	the source code for any proprietary components.  See the licensing section
	of http://www.FreeRTOS.org for full details of how and when the exception
	can be applied.

    ***************************************************************************
    ***************************************************************************
    *                                                                         *
    * SAVE TIME AND MONEY!  We can port FreeRTOS.org to your own hardware,    *
    * and even write all or part of your application on your behalf.          *
    * See http://www.OpenRTOS.com for details of the services we provide to   *
    * expedite your project.                                                  *
    *                                                                         *
    ***************************************************************************
    ***************************************************************************

	Please ensure to read the configuration and relevant port sections of the
	online documentation.

	http://www.FreeRTOS.org - Documentation, latest information, license and
	contact details.

	http://www.SafeRTOS.com - A version that is certified for use in safety
	critical systems.

	http://www.OpenRTOS.com - Commercial support, development, porting,
	licensing and training services.
*/

#ifndef PORTMACRO_H
#define PORTMACRO_H

#ifdef __cplusplus
extern "C" {
#endif

/*-----------------------------------------------------------
 * Port specific definitions.
 *
 * The settings in this file configure FreeRTOS correctly for the
 * given hardware and compiler.
 *
 * These settings should not be altered.
 *-----------------------------------------------------------
 */

/* Type definitions. */
#define portCHAR        char
#define portFLOAT       float
#define portDOUBLE      double
#define portLONG        long
#define portSHORT       short
#define portSTACK_TYPE  unsigned int
#define portBASE_TYPE   int


#if (configUSE_16_BIT_TICKS==1)
	typedef unsigned portSHORT portTickType;
	#define portMAX_DELAY ( portTickType ) 0xffff
#else
	typedef unsigned portLONG portTickType;
	#define portMAX_DELAY ( portTickType ) 0xffffffff
#endif
/*-----------------------------------------------------------*/	

/* Interrupt control macros. */
#define portDISABLE_INTERRUPTS() __asm ( "DI" )
#define portENABLE_INTERRUPTS()	 __asm ( "EI" )
/*-----------------------------------------------------------*/

/* Critical section control macros. */
#define portNO_CRITICAL_SECTION_NESTING		( ( unsigned portBASE_TYPE ) 0 )

#define portENTER_CRITICAL()								\
{											\
extern volatile /*unsigned portSHORT*/ portSTACK_TYPE usCriticalNesting;					\
											\
	portDISABLE_INTERRUPTS();							\
											\
	/* Now interrupts are disabled ulCriticalNesting can be accessed */		\
	/* directly.  Increment ulCriticalNesting to keep a count of how many */	\
	/* times portENTER_CRITICAL() has been called. */				\
	usCriticalNesting++;								\
}

#define portEXIT_CRITICAL()								\
{											\
extern volatile /*unsigned portSHORT*/ portSTACK_TYPE usCriticalNesting;					\
											\
	if( usCriticalNesting > portNO_CRITICAL_SECTION_NESTING )			\
	{										\
		/* Decrement the nesting count as we are leaving a critical section. */	\
		usCriticalNesting--;							\
											\
		/* If the nesting level has reached zero then interrupts should be */	\
		/* re-enabled. */							\
		if( usCriticalNesting == portNO_CRITICAL_SECTION_NESTING )		\
		{									\
			portENABLE_INTERRUPTS();					\
		}									\
	}										\
}
/*-----------------------------------------------------------*/

/* Task utilities. */
extern void vPortYield( void );
extern void vPortStart( void );
extern void portSAVE_CONTEXT( void );
extern void portRESTORE_CONTEXT( void );
//#define portYIELD()	vPortYield()
#define portYIELD()	__asm ( "trap 0" )
#define portNOP()	__asm ( "NOP" )
/*-----------------------------------------------------------*/

/* Hardwware specifics. */
#define portBYTE_ALIGNMENT	4
#define portSTACK_GROWTH	( -1 )
#define portTICK_RATE_MS	( ( portTickType ) 1000 / configTICK_RATE_HZ )		
/*-----------------------------------------------------------*/

/* Task function macros as described on the FreeRTOS.org WEB site. */
#define portTASK_FUNCTION_PROTO( vFunction, pvParameters ) void vFunction( void *pvParameters )
#define portTASK_FUNCTION( vFunction, pvParameters ) void vFunction( void *pvParameters )


static __interrupt void MD_INTP0(void);


#ifdef __cplusplus
}
#endif

#endif /* PORTMACRO_H */

