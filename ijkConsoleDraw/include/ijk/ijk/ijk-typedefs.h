/*
   Copyright 2020-2022 Daniel S. Buckstein

   Licensed under the Apache License, Version 2.0 (the "License");
   you may not use this file except in compliance with the License.
   You may obtain a copy of the License at

	   http://www.apache.org/licenses/LICENSE-2.0

	Unless required by applicable law or agreed to in writing, software
	distributed under the License is distributed on an "AS IS" BASIS,
	WITHOUT WARRANTIES OR CONDITIONS OF ANY KIND, either express or implied.
	See the License for the specific language governing permissions and
	limitations under the License.
*/

/*
	ijk: an open-source, cross-platform, light-weight,
		c-based rendering framework
	By Daniel S. Buckstein

	ijk-typedefs.h
	Common shorthand type definitions.
*/

#ifndef _IJK_TYPEDEFS_H_
#define _IJK_TYPEDEFS_H_


#include <stddef.h>
#include <stdint.h>
#include <stdbool.h>


//-----------------------------------------------------------------------------

// Core type aliases.
///
typedef		uint8_t			byte, ui8;		// Convenient alias for 8-bit unsigned byte.
typedef		uint16_t		word, ui16;		// Convenient alias for 16-bit unsigned short integer.
typedef		uint32_t		dword, ui32;	// Convenient alias for 32-bit unsigned long integer or double-word.
typedef		uint64_t		qword, ui64;	// Convenient alias for 64-bit unsigned long-long integer or quad-word.
typedef		int8_t			i8;				// Convenient alias for 8-bit signed byte.
typedef		int16_t			i16;			// Convenient alias for 16-bit signed short integer.
typedef		int32_t			i32;			// Convenient alias for 32-bit signed long integer.
typedef		int64_t			i64;			// Convenient alias for 64-bit signed long-long integer.
typedef		unsigned int	uint;			// Convenient alias for standard unsigned integer.
typedef		bool			bln, tf8;		// Convenient alias for standard boolean.
typedef		float			flt, f32;		// Convenient alias for 32-bit single-precision floating point number.
typedef		double			dbl, f64;		// Convenient alias for 64-bit double-precision floating point number.
typedef		void*			ptr;			// Convenient alias for generic pointer.
typedef		void const*		kptr;			// Convenient alias for generic pointer to constant.
typedef		char*			str;			// Convenient alias for generic character string (c-string).
typedef		char const*		kstr;			// Convenient alias for generic constant character string (c-string).


//-----------------------------------------------------------------------------

#include "ijk-macros.h"


// Additional integer type abbreviations and aliases.
///
typedef		i8				sbyte, asciicode;				// Alias for signed single byte.
typedef		i32				iret;							// Alias for signed long integer/double-word (four bytes).
typedef		i64				intl;							// Alias for signed long-long integer/quad-word (eight bytes).
typedef		ui8				ubyte, keycode;					// Alias for unsigned single byte.
typedef		ui32			uint;							// Alias for unsigned long integer/double-word (four bytes).
typedef		ui64			uintl;							// Alias for unsigned long-long integer/quad-word (eight bytes).


// Convenient types sized for current architecture.
///
typedef		ptrdiff_t		schomp, index, itr, flag;		// Aliases based on signed integer that has same size as pointer.
typedef		size_t			uchomp, chomp, uitr, uindex;	// Aliases based on unsigned integer that has same size as pointer.
typedef		byte			* pbyte;						// Alias for pointer to byte.
typedef		byte const		* kpbyte;						// Alias for pointer to constant byte.
typedef		chomp			* pchomp, * cbuff;				// Alias for pointer to pointer-sized integer.
typedef		chomp const		* kpchomp, * kcbuff;			// Alias for pointer to pointer-sized constant integer.


// Convenient size abbreviations and calculators.
///
#define		ijk_bytes2chomps(b)	(((b)+sizeof(void*)-1)/sizeof(void*))		// Convert size in bytes to size in chomps (4:1 or 8:1).
#define		ijk_chomps2bytes(c)	((c)*sizeof(void*))							// Convert size in chomps to size in bytes (1:4 or 1:8).
#define		ijk_arrlen(arr)		(sizeof(arr)/sizeof(*arr))					// Get number of elements in array (does not work on raw pointers).
#define		ijk_cbufflen(buf)	ijk_bytes2chomps(sizeof(buf))				// Get buffer size in chomps (does not work on raw pointers).


// Convenient short c-string and wide character string type abbreviations and aliases.
///
typedef		byte			tag[sizeof(dword) * sizeof(qword)], * ptag;		// Alias for tag or short name made of bytes.
typedef		byte const		ktag[sizeof(dword) * sizeof(qword)], * kptag;	// Alias for constant tag or short name made of bytes.
typedef		word			wtag[sizeof(tag)], * pwtag, * wcstr;			// Alias for wide tag or short name made of short integers.
typedef		word const		kwtag[sizeof(tag)], * kpwtag, * kwcstr;			// Alias for constant wide tag or short name made of short integers.


// Convenient short dynamic (architecture-dependent) c-string abbreviations and aliases.
///
typedef		byte			dtag[sizeof(chomp) * sizeof(qword)], * pdtag, * dcstr;		// Alias for dynamic tag whose size is dependent on architecture.
typedef		byte const		kdtag[sizeof(chomp) * sizeof(qword)], * kpdtag, * kdcstr;	// Alias for constant dynamic tag whose size is dependent on architecture.
typedef		word			dwtag[sizeof(dtag)], * pdwtag, * dwcstr;					// Alias for wide dynamic tag whose size is dependent on architecture.
typedef		word const		kdwtag[sizeof(dtag)], * kpdwtag, * kdwcstr;					// Alias for constant wide dynamic tag whose size is dependent on architecture.


// Simple copy operations.
///
#define		ijk_copyb(dst, src, offset)			(*((byte*)(dst) + (offset)) = *((byte const *)(src) + (offset)))	// Copy single byte from src to dst at offset.
#define		ijk_copyw(dst, src, offset)			(*((word*)(dst) + (offset)) = *((word const *)(src) + (offset)))	// Copy word from src to dst at offset.
#define		ijk_copydw(dst, src, offset)		(*((dword*)(dst) + (offset)) = *((dword const*)(src) + (offset)))	// Copy double-word from src to dst at offset.
#define		ijk_copyqw(dst, src, offset)		(*((qword*)(dst) + (offset)) = *((qword const*)(src) + (offset)))	// Copy quad-word from src to dst at offset.
#define		ijk_copyc(dst, src, offset)			(*((chomp*)(dst) + (offset)) = *((chomp const*)(src) + (offset)))	// Copy single chomp from src to dst at offset.
#define		ijk_copytag(dst, src)				ijk_copyqw(dst,src,0);ijk_copyqw(dst,src,1);ijk_copyqw(dst,src,2);ijk_copyqw(dst,src,3)		// Copy tag from src to dst.
#define		ijk_copywtag(dst, src)				ijk_copytag((ptag)(dst),(kptag)(src));ijk_copytag((ptag)(dst)+sizeof(tag),(kptag)(src)+sizeof(tag))		// Copy wide tag frm src to dst.
#define		ijk_copydtag(dst, src)				ijk_copyc(dst,src,0);ijk_copyc(dst,src,1);ijk_copyc(dst,src,2);ijk_copyc(dst,src,3);ijk_copyc(dst,src,4);ijk_copyc(dst,src,5);ijk_copyc(dst,src,6);ijk_copyc(dst,src,7)	// Copy dynamic tag from src to dst.
#define		ijk_copydwtag(dst, src)				ijk_copydtag((ptag)(dst),(kptag)(src));ijk_copydtag((ptag)(dst)+sizeof(dtag),(kptag)(src)+sizeof(dtag))	// Copy wide dynamic tag frm src to dst.


// Language-appropriate constant reference.
///
#ifdef __cplusplus
#define constref								const&		// C++ constant reference: "const&"
#else	// __cplusplus
#define constref								const		// C constant reference: "const" (no actual references allowed)
#endif	// __cplusplus


//-----------------------------------------------------------------------------


#endif	// !_IJK_TYPEDEFS_H_