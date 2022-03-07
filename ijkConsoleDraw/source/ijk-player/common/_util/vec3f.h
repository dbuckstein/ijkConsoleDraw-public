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

	vec3f.h
	Simple 3D float vector interface.
*/

#ifndef _VEC3F_H_
#define _VEC3F_H_

#include "ijk/ijk/ijk-typedefs.h"


#ifdef __cplusplus
extern "C" {
#endif	// __cplusplus


//-----------------------------------------------------------------------------
	
typedef f32 float_t, float3_t[3], * floatv_t;
typedef union vec3f_t
{
	float3_t v;
	struct { float_t x, y, z; };
} vec3f;


//-----------------------------------------------------------------------------

#define epsf 1.19e-07f

bool fIsZero(float_t const s);
bool fIsNonZero(float_t const s);
float_t fRecip(float_t const s);
float_t fLerp(float_t const s0, float_t const s1, float_t const u);
float_t fMad(float_t const s0, float_t const ds, float_t const u);


//-----------------------------------------------------------------------------

extern vec3f const vec3f0;

floatv_t vec3fZero(float3_t v_out);
floatv_t vec3fInit(float3_t v_out, float_t const x, float_t const y, float_t const z);
floatv_t vec3fCopy(float3_t v_out, float3_t const v);
floatv_t vec3fNegate(float3_t v_out, float3_t const v);
float_t vec3fDot(float3_t const v_lh, float3_t const v_rh);
floatv_t vec3fCross(float3_t v_out, float3_t const v_lh, float3_t const v_rh);
float_t vec3fLenSq(float3_t const v);
float_t vec3fLen(float3_t const v);
float_t vec3fLenSqInv(float3_t const v);
float_t vec3fLenInv(float3_t const v);
floatv_t vec3fAdd(float3_t v_out, float3_t const v_lh, float3_t const v_rh);
floatv_t vec3fSub(float3_t v_out, float3_t const v_lh, float3_t const v_rh);
floatv_t vec3fMul(float3_t v_out, float3_t const v_lh, float_t const s_rh);
floatv_t vec3fDiv(float3_t v_out, float3_t const v_lh, float_t const s_rh);
floatv_t vec3fLerp(float3_t v_out, float3_t const v0, float3_t const v1, float_t const u);
floatv_t vec3fMad(float3_t v_out, float3_t const v0, float3_t const dv, float_t const u);
float_t vec3fProjs(float3_t const v_base, float3_t const v);
floatv_t vec3fProj(float3_t v_out, float3_t const v_base, float3_t const v);
floatv_t vec3fUnit(float3_t v_out, float3_t const v);
float_t vec3fDistSq(float3_t const v_lh, float3_t const v_rh);
float_t vec3fDist(float3_t const v_lh, float3_t const v_rh);
bool vec3fIsZero(float3_t const v);
bool vec3fIsNonZero(float3_t const v);
bool vec3fIsUnit(float3_t const v);
bool vec3fIsNonUnit(float3_t const v);


//-----------------------------------------------------------------------------


#ifdef __cplusplus
}
#endif	// __cplusplus


#include "vec3f.inl"


#endif	// !_VEC3F_H_