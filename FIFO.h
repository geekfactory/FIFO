/*	Generic FIFO buffer Implementation
	Copyright (C) 2014 Jesus Ruben Santa Anna Zamudio.

	This program is free software: you can redistribute it and/or modify
	it under the terms of the GNU General Public License as published by
	the Free Software Foundation, either version 3 of the License, or
	(at your option) any later version.

	This program is distributed in the hope that it will be useful,
	but WITHOUT ANY WARRANTY; without even the implied warranty of
	MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
	GNU General Public License for more details.

	You should have received a copy of the GNU General Public License
	along with this program.  If not, see <http://www.gnu.org/licenses/>.

	Author website: http://geekfactory.mx
	Author e-mail: ruben at geekfactory dot mx
 */

/**
 * Generic FIFO buffer Implementation.
 * 
 * Source code for the implementation of a FIFO buffer. The fifo can contain any
 * type of data, including but not limited to: integers, floats, structures,
 * arrays, etc.
 * 
 * This data structure can be used on a variety of situations, for example:
 * It can be used with microcontroller peripherals for buffering, as a message
 * or event queue, can be used for task synchronization or comunications 
 * and more.
 */

#ifndef FIFO_H
#define FIFO_H
/*-------------------------------------------------------------*/
/*		Includes and dependencies			*/
/*-------------------------------------------------------------*/
#include <stdlib.h>
#include <string.h>
#include "Compiler.h"
/*-------------------------------------------------------------*/
/*		Macros and definitions				*/
/*-------------------------------------------------------------*/

/*-------------------------------------------------------------*/
/*		Typedefs enums & structs			*/
/*-------------------------------------------------------------*/

/**
 * This structure holds the data that denfines a circular buffer, and pointers
 * to access data on the buffer
 */
typedef struct xFIFOStruct {
	BYTE * pxHeadAddress; //!< Start address on memory for item space
	WORD xItemSize; //!< Size in bytes for each element in the buffer
	WORD xByteSize; //!< Size in bytes of the whole buffer
	WORD xReadOffset; //!< Memory offset from which we will read data
	WORD xWriteOffset; //!< Memory offset where data will be written
	WORD xStoredBytes; //!< Number of bytes used currently by stored items
} xFIFO;

/**
 * Defines the side of the buffer to perform some actions
 */
enum enBufferSide {
	BUFFER_FRONT,
	BUFFER_BACK,
};

typedef xFIFO * xFIFOHandle;

/*-------------------------------------------------------------*/
/*		Function prototypes				*/
/*-------------------------------------------------------------*/
/**
 * @brief Creates a FIFO using dynamic memory
 *
 * This function is used to create a buffer, it allocates memory for a buffer of
 * the requested size plus the size of the structure that contains the
 * information requeried by other API functions to access that buffer.
 *
 * @param itemcount The number of elements the buffer should be able to store
 * @param itemsize The size in bytes for each element contained in the buffer
 *
 * @return If a buffer is succesfully created, returns a pointer to the
 * structure that contains the buffer information (xFIFOHandle).
 * NULL is returned if something fails.
 */
xFIFOHandle fifo_create(WORD itemcount, WORD itemsize);

/**
 * @brief Creates a statically allocated FIFO buffer
 *
 * This function is similar to xFIFOCreate() but it difers from the last because
 * the memory allocation is static. A pointer to the buffer space and a pointer
 * to the control structure are required, both of them shoud be allocated
 * statically by the programmer.
 *
 * @param fifo The pointer to the structure holding FIFO data
 * @param buf Pointer to the memory used to store actual fifo items
 * @param itemcount The number of items to store on the FIFO
 * @param itemsize The size in bytes of each item on the buffer
 *
 * @return This function performs some basic validation on the parameters passed,
 * if something is wrong with it will return NULL.
 */
xFIFOHandle fifo_create_static(xFIFOHandle fifo, BYTE * buf, WORD itemcount, WORD itemsize);

/**
 * @brief Adds one item to the FIFO buffer
 *
 * This function writes an item to the fifo buffer front, This function
 * affects the write pointer and the stored items count.
 *
 * The number of bytes to be copied to the fifo buffer was defined when the
 * fifo buffer was created with the function fifo_create() (itemsize parameter).
 *
 * @param fifo Pointer to a xFIFOStruct structure.
 * @param item Pointer to a location that holds data to be written to the fifo
 * buffer.
 * 
 * @return  Returns TRUE if there is space in the FIFO to add the item. If the
 * buffer is full and no data can be copied it returns FALSE.
 */
BOOL fifo_add(xFIFOHandle fifo, const void * item);

/**
 * @brief Obtains one item from the FIFO buffer.
 *
 * This function reads an item from the fifo buffer back, This function affects
 * the read pointer and the stored items count.
 * 
 * The number of bytes to be copied to the provided buffer was defined when the
 * fifo buffer was created with the function fifo_create() (itemsize parameter).
 * 
 * @param fifo Pointer to a xFIFOStruct structure.
 * @param item Pointer to a location to hold the data read from the fifo buffer,
 * this buffer should be sized appropiately to accomodate the data.
 * 
 * @return  Returns TRUE if there is data available on the fifo buffer to be
 * copied, if the buffer is empty and no data can be read this returns FALSE.
 */
BOOL fifo_get(xFIFOHandle fifo, const void * item);

/**
 * @brief Checks if the FIFO is full.
 *
 * Check the space left on the buffer. Check if it can accept one item at least.
 *
 * @param fifo Pointer to a xFIFOStruct structure.
 *
 * @return TRUE if the buffer is full, FALSE otherwise.
 */
BOOL fifo_full(xFIFOHandle fifo);

/**
 * @brief Checks if the FIFO is empty
 *
 * Check if the buffer has no data stored in it.
 *
 * @param fifo Pointer to a xFIFOStruct structure.
 *
 * @return TRUE if the buffer is empty, FALSE otherwise.
 */
BOOL fifo_empty(xFIFOHandle fifo);

/**
 * @brief Discard data from the buffer
 *
 * This function discards data from the back or the front side of the buffer,
 * the side and the ammount of discarded data depends on the parameters passed.
 *
 * @param Pointer to a xFIFOStruct structure.
 * @param count The number of elements to discard from the buffer.
 * @param eSide Defines if data should be discarted from the front or back side
 * of the buffer.
 * 
 * @return Returns TRUE if the data was discarted, false if not.
 */
BOOL fifo_discard(xFIFOHandle fifo, WORD count, enum enBufferSide side);

#endif
// End of Header file
