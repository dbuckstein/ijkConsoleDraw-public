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

	ijk-macros.h
	Common macros.
*/

#ifndef _IJK_MACROS_H_
#define _IJK_MACROS_H_


#include "ijk-config.h"
#include <assert.h>


// General flags and checks.
///
#define ijk_istrue(x)					(!!(x))			// Check if value represents true (non-zero).
#define ijk_isfalse(x)					(!(x))			// Check if value represents false (zero).
#define ijk_issuccess(x)				((x) == 0)		// Check if value represents success code (zero).
#define ijk_isfailure(x)				((x) <  0)		// Check if value represents failure code (negative).
#define ijk_iswarning(x)				((x) >  0)		// Check if value represents warning code (positive).
#define ijk_isnfailure(x)				((x) >= 0)		// Check if value represents non-failure code (non-negative).

#define ijk_flagraise(x,f)				((x) | (f))				// Raise flag (f) on base value (x).
#define ijk_flaglower(x,f)				((x) & ~(f))			// Lower flag (f) from base value (x).
#define ijk_flagch(x,f)					(((x) & (f)) != 0)		// Check whether flag (f) is partially raised in base value (x).
#define ijk_flagnch(x,f)				(((x) & (f)) == 0)		// Check whether all bits in flag (f) are lowered in base value (x).
#define ijk_flageq(x,f)					(((x) & (f)) == (f))	// Check whether all bits in flag (f) are raised in base value (x).
#define ijk_flagneq(x,f)				(((x) & (f)) != (f))	// Check whether flag (f) is partially lowered in base value (x).
#define ijk_flagidx(x,i)				(i=-1); if(x) while(!((x)&(1<<++i)))	// Search bits for raised flag, incrementing index until found.


// Simple global logical operations.
///
#define ijk_squared(x)						((x) * (x))							// Square value x.
#define ijk_minimum(x,y)					((x) < (y) ? (x) : (y))				// Minimum value of x and y.
#define ijk_maximum(x,y)					((x) > (y) ? (x) : (y))				// Maximum value of x and y.
#define ijk_isunbound(x_min,x_max,x)		((x) < (x_min) || (x) > (x_max))	// Check if value is not between x_min and x_max.
#define ijk_isbound(x_min,x_max,x)			((x) >= (x_min) && (x) <= (x_max))	// Check if value x is between x_min and x_max.
#define ijk_clamp(x_min,x_max,x)			((x) >= (x_min) ? (x) <= (x_max) ? (x) : (x_max) : (x_min))						// Clamp value x between x_min and x_max.
#define ijk_clamp_inv(x_min,x_max,x0,x)		((x) >= (x_max) || (x) <= (x_min) ? (x) : ((x) >= (x0) ? (x_max) : (x_min)))	// Clamp value x to limit x_min or x_max based on origin x0 if value is clamped.
#define ijk_clamp_loop(x_min,x_max,dx,x)	(x); while((x) > (x_max)) x -= (dx); while((x) < (x_min)) x += (dx)				// Clamp value x by looping by dx to end up between x_min and x_max.
#define ijk_swap2(x,y,tmp)					(tmp=x);x=y;y=tmp					// Swap two values x and y using placeholder tmp.
#define ijk_swap3(x,y,z,tmp)				(tmp=x);x=y;y=z;z=tmp				// Swap/rotate three values x, y and z using placeholder tmp.
#define ijk_swap4(x,y,z,w,tmp)				(tmp=x);x=y;y=z;z=w;w=tmp			// Swap/rotate four values x, y, z and w using placeholder tmp.


// Simplifying data structure creation.
///
#define IJK_DECL_STRUCT(name)				typedef struct name##_struct_t name;	struct name##_struct_t		// Declare a struct using consistent format.
#define IJK_DECL_UNION(name)				typedef union name##_union_t name;		union name##_union_t		// Declare a union using consistent format.
#define IJK_DECL_ENUM(name)					typedef enum name##_enum_t name;		enum name##_enum_t			// Declare an enum using consistent format.
#ifdef __cplusplus
#define IJK_DECL_CLASS(name)				typedef class name##_class_t name;		class name##_class_t		// Declare a class using consistent format (C++ only).
#endif	// __cplusplus


// Standardized error and warning handling.
///
#define IJK_FAILURELIST(name)				IJK_DECL_ENUM(name##_failure)	// Declare failure list for named data type.
#define IJK_WARNINGLIST(name)				IJK_DECL_ENUM(name##_warning)	// Declare warning list for named data type.
#define ijk_success							0								// Code when function exits successfully, no errors or warnings (zero).
#define ijk_warncode(code)					(1<<(code))						// Code for warning due to specified reason.
#define ijk_fail_invalidparam				0								// Code for failure due to invalid parameter.
#define ijk_fail_allocation					1								// Code for failure due to invalid memory allocation.
#define ijk_fail_specified					2								// Code for failure due to interface specified reason (enum).
#define ijk_failcode(code)					(-(ijk_warncode(code)))			// Code for failure reason.
#define ijk_failcodespec(code)				(-(ijk_warncode(ijk_fail_specified)|ijk_warncode((code)+ijk_fail_specified+1)))	// Code for failure reason with specified flag.

#define ijk_earlyreturn(cond,...)			if (!(cond)) return __VA_ARGS__										// Early return if condition is false.
#define ijk_warnreturniff(cond,code)		ijk_earlyreturn(cond,ijk_warncode(code))							// Early return with warning if condition is false.
#define ijk_warnreturn(code)				return ijk_warncode(code)											// Return with warning immediately.
#define ijk_assert(cond)					assert(cond)														// Assert if condition is false.
#define ijk_assertreturniff(cond,...)		ijk_assert(cond); ijk_earlyreturn(cond,__VA_ARGS__)					// Assert or return if condition is false.
#define ijk_assertparam(cond)				ijk_assertreturniff(cond,ijk_failcode(ijk_fail_invalidparam))		// Assert or return invalid parameter.

#define ijk_assertrange(val,min,max,...)	ijk_assertreturniff((val)>=(min)&&(val)<=(max),__VA_ARGS__)			// Assert or return if value is out of range.
#define ijk_assertcount(val,count,...)		ijk_assertreturniff((val)>=0&&(val)<(count),__VA_ARGS__)			// Assert or return if value exceeds counter (enum).
#define ijk_asserteq(val,cmp,...)			ijk_assertreturniff((val)==(cmp),__VA_ARGS__)						// Assert or return if values are different.
#define ijk_assertneq(val,cmp,...)			ijk_assertreturniff((val)!=(cmp),__VA_ARGS__)						// Assert or return if values are the same.
#define ijk_asserteq0(val,...)				ijk_assertreturniff((val)==0,__VA_ARGS__)							// Assert or return if value is non-zero.
#define ijk_assertneq0(val,...)				ijk_assertreturniff((val)!=0,__VA_ARGS__)							// Assert or return if value is zero.
#define ijk_assertgeq0(val,...)				ijk_assertreturniff((val)>=0,__VA_ARGS__)							// Assert or return if value is non-zero.
#define ijk_assertleq0(val,...)				ijk_assertreturniff((val)<=0,__VA_ARGS__)							// Assert or return if value is non-zero.
#define ijk_assertptr(p,...)				ijk_assertreturniff((p)!=NULL,__VA_ARGS__)							// Assert or return if pointer is null.
#define ijk_assertnull(p,...)				ijk_assertreturniff((p)==NULL,__VA_ARGS__)							// Assert or return if pointer is not null.
#define ijk_assertptreq0(pp,...)			ijk_assertreturniff((pp)&&!*(pp),__VA_ARGS__)						// Assert or return if value pointed at is non-zero.
#define ijk_assertptrneq0(pp,...)			ijk_assertreturniff((pp)&&*(pp),__VA_ARGS__)						// Assert or return if value pointed at is zero.
#define ijk_assertstr(s,...)				ijk_assertptrneq0(s,__VA_ARGS__)									// Assert or return if string is invalid.

#define ijk_assertparamrange(val,min,max)	ijk_assertrange(val,min,max,ijk_failcode(ijk_fail_invalidparam))	// Parameter assert if value is out of range.
#define ijk_assertparamcount(val,count)		ijk_assertcount(val,count,ijk_failcode(ijk_fail_invalidparam))		// Parameter assert if value exceeds counter (enum).
#define ijk_assertparameq(val,cmp)			ijk_asserteq(val,cmp,ijk_failcode(ijk_fail_invalidparam))			// Parameter assert if values are different.
#define ijk_assertparamneq(val,cmp)			ijk_assertneq(val,cmp,ijk_failcode(ijk_fail_invalidparam))			// Parameter assert if values are the same.
#define ijk_assertparameq0(val)				ijk_asserteq0(val,ijk_failcode(ijk_fail_invalidparam))				// Parameter assert if value is non-zero.
#define ijk_assertparamneq0(val)			ijk_assertneq0(val,ijk_failcode(ijk_fail_invalidparam))				// Parameter assert if value is zero.
#define ijk_assertparamgeq0(val)			ijk_assertgeq0(val,ijk_failcode(ijk_fail_invalidparam))				// Parameter assert if value is zero.
#define ijk_assertparamleq0(val)			ijk_assertleq0(val,ijk_failcode(ijk_fail_invalidparam))				// Parameter assert if value is zero.
#define ijk_assertparamptr(p)				ijk_assertptr(p,ijk_failcode(ijk_fail_invalidparam))				// Parameter assert if pointer is null.
#define ijk_assertparamnull(p)				ijk_assertnull(p,ijk_failcode(ijk_fail_invalidparam))				// Parameter assert if pointer is not null.
#define ijk_assertparamptreq0(pp)			ijk_assertptreq0(pp,ijk_failcode(ijk_fail_invalidparam))			// Parameter assert if value pointed at is non-zero.
#define ijk_assertparamptrneq0(pp)			ijk_assertptrneq0(pp,ijk_failcode(ijk_fail_invalidparam))			// Parameter assert if value pointed at is zero.
#define ijk_assertparamstr(s)				ijk_assertstr(s,ijk_failcode(ijk_fail_invalidparam))				// Parameter assert if string is invalid.

#define ijk_assertallocptr(p)				ijk_assertptr(p,ijk_failcode(ijk_fail_allocation))					// Allocation assert if pointer is null.

#define ijk_assertspectrue(val,code)		ijk_assertneq0(val,ijk_failcodespec(code))							// Specified assert if value is true.
#define ijk_assertspecsuccess(val,code)		ijk_assertspectrue(ijk_issuccess(val),code)							// Specified assert if value represents success.


#endif	// !_IJK_MACROS_H_