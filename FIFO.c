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

#include "FIFO.h"

/*-------------------------------------------------------------*/
/*		Private function prototypes								*/
/*-------------------------------------------------------------*/
static void fifo_copyfrom(xFIFOHandle, const void *);
static void fifo_copyto(xFIFOHandle, const void *);

xFIFOHandle fifo_create(WORD itemcount, WORD itemsize)
{
	xFIFOHandle newfifo;
	if (itemcount > (WORD) 0) {

		if (NULL != (newfifo = (xFIFO *) malloc(sizeof( xFIFO)))) {
			WORD bytesize = (WORD) itemcount * itemsize; // Calculate the size in bytes of the buffer
			newfifo->pxHeadAddress = (BYTE *) malloc(bytesize); // Try to allocate space for the buffer data
			if (newfifo->pxHeadAddress != NULL) {
				newfifo->xItemSize = itemsize;
				newfifo->xByteSize = bytesize; // Initialize struct elements
				newfifo->xReadOffset = 0;
				newfifo->xWriteOffset = 0;
				newfifo->xStoredBytes = 0;
				return newfifo; // Return the pointer to the created structure
			} else {
				free(newfifo);
			}
		}
	}
	return NULL;
}

xFIFOHandle fifo_create_static(xFIFOHandle fifo, BYTE * buf, WORD itemcount, WORD itemsize)
{
	if (buf != NULL && fifo != NULL && itemcount != 0) // Sanity check for memory and element sizes
	{
		fifo->pxHeadAddress = buf;
		fifo->xItemSize = itemsize;
		fifo->xByteSize = itemcount * itemsize;
		fifo->xReadOffset = 0;
		fifo->xWriteOffset = 0;
		fifo->xStoredBytes = 0;
		return fifo;
	}
	return NULL;
}

BOOL fifo_add(xFIFOHandle fifo, const void * item)
{
	if (!fifo_full(fifo)) {
		fifo_copyto(fifo, item);
		fifo->xStoredBytes += fifo->xItemSize;
		return TRUE;
	} else {
		return FALSE;
	}
}

BOOL fifo_get(xFIFOHandle fifo, const void * item)
{
	if (!fifo_empty(fifo)) {
		fifo_copyfrom(fifo, item);
		fifo->xStoredBytes -= fifo->xItemSize;
		return TRUE;
	} else {
		return FALSE;
	}
}

BOOL fifo_full(xFIFOHandle fifo)
{
	if (fifo->xStoredBytes >= fifo->xByteSize)
		return TRUE;
	else
		return FALSE;
}

BOOL fifo_empty(xFIFOHandle fifo)
{
	if (fifo->xStoredBytes == 0)
		return TRUE;
	else
		return FALSE;
}

BOOL fifo_discard(xFIFOHandle fifo, WORD count, enum enBufferSide side)
{
	WORD iTemp;
	iTemp = fifo->xItemSize * count; // Compute byte size of elements to be deleted
	if (iTemp <= fifo->xStoredBytes) // Check if we can remove the requested ammount of data
	{
		if (side == BUFFER_BACK) {
			fifo->xReadOffset = (fifo->xReadOffset + iTemp) % fifo->xByteSize; // Increase read pointer n elements
			fifo->xStoredBytes -= iTemp; // Decrease stored bytes number
		} else if (side == BUFFER_FRONT) {
			fifo->xWriteOffset = (fifo->xWriteOffset - iTemp) % fifo->xByteSize; // Decrease write pointer n elements
			fifo->xStoredBytes -= iTemp; // Decrease stored bytes number
		}
		return TRUE;
	}
	return FALSE;
}

static void fifo_copyfrom(xFIFOHandle fifo, const void * item)
{
	memcpy(item, (void *) (fifo->pxHeadAddress + fifo->xReadOffset), (WORD) fifo->xItemSize);
	fifo->xReadOffset += fifo->xItemSize;
	if (fifo->xReadOffset >= fifo->xByteSize) {
		fifo->xReadOffset = 0;
	}
}

static void fifo_copyto(xFIFOHandle fifo, const void *item)
{
	memcpy((void *) (fifo->pxHeadAddress + fifo->xWriteOffset), item, (WORD) fifo->xItemSize);
	fifo->xWriteOffset += fifo->xItemSize;
	if (fifo->xWriteOffset >= fifo->xByteSize) {
		fifo->xWriteOffset = 0;
	}
}
