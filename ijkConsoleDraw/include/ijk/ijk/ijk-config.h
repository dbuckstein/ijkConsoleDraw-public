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

	ijk-config.h
	Common configuation.
*/

#ifndef _IJK_CONFIG_H_
#define _IJK_CONFIG_H_


//-----------------------------------------------------------------------------

// Set macro for architecture.
///
#if (defined _M_IX86 || defined __i386__)		// 32-bit
#define __ijk_cfg_instrset				x86
#define __ijk_cfg_archbits				32

#elif (defined _M_X64 || defined __x86_64__)	// 64-bit
#define __ijk_cfg_instrset				x86_64
#define __ijk_cfg_archbits				64

#else											// !32-/64-bit
#error "ERROR: UNKNOWN/INVALID INSTRUCTION SET AND ARCHITECTURE"

#endif	// 32-/64-bit


// Set macros for development environment.
///
#if (defined _WIN32)	// Windows, MSVC
#define __ijk_cfg_platform				WINDOWS
#define __ijk_cfg_compiler				MSVC

#else
#error "ERROR: UNKNOWN/INVALID PLATFORM AND COMPILER"

#endif	// platform


// Set macros for build configuration.
///
#if (defined _DEBUG && !defined NDEBUG)
#define __ijk_cfg_buildcfg				Debug
#else
#define __ijk_cfg_buildcfg				Release
#endif	// config


// Global other macros.
///
#define __ijk_cfg_tokenstr(x)			#x
#define __ijk_cfg_tokencat(x, y)		x##y


//-----------------------------------------------------------------------------

// Token stringify and concatenate.
///
#define ijk_tokenstr(x)					__ijk_cfg_tokenstr(x)				// Stringify token x.
#define ijk_tokencat(x,y)				__ijk_cfg_tokencat(x,y)				// Concatenate tokens x and y.
#define ijk_tokencat_arch(x)			ijk_tokencat(x,__ijk_cfg_archbits)	// Concatenate token x with architecture bits.


// Platform and configuration checks.
///
#define ijk_platform_is(x)				(__ijk_cfg_platform == (x))			// Platform comparison.
#define ijk_platform_isn(x)				(__ijk_cfg_platform != (x))			// Platform not comparison.
#define ijk_platform_fn(f)				ijk_tokencat(f,__ijk_cfg_platform)	// Platform-specific function.
#define ijk_buildcfg_is(x)				(__ijk_cfg_buildcfg == (x))			// Build configuration comparison.
#define ijk_buildcfg_isn(x)				(__ijk_cfg_buildcfg != (x))			// Build configuration not comparison.
#define ijk_buildcfg_fn(f)				ijk_tokencat(f,__ijk_cfg_buildcfg)	// Build configuration-specific function.


// General symbol qualifiers.
///
#define ijk_inl_ext						extern inline	// Tag external and inline; useful for compilation with local inlining.
#define ijk_inl_s						static inline	// Tag internal (static) inline; useful for local inlining.
#define ijk_inl							ijk_inl_s		// Tag inline.
#define ijk_ext							extern			// Tag external.


//-----------------------------------------------------------------------------

// If defined, framework has been full pre-built to libraries.
// Inline files are not available to be included in headers.
//#define IJK_PRECOMPILED


//-----------------------------------------------------------------------------


#endif	// !_IJK_CONFIG_H_