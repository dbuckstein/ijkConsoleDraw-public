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

	vec3f.inl
	Simple 3D float vector implementation.
*/

#ifdef _VEC3F_H_
#ifndef _VEC3F_INL_
#define _VEC3F_INL_


#ifdef __cplusplus
extern "C" {
#endif	// __cplusplus


//-----------------------------------------------------------------------------
	
ijk_inl bool fIsZero(float_t const s)
{
	return ((s * s) <= epsf);
}

ijk_inl bool fIsNonZero(float_t const s)
{
	return ((s * s) > epsf);
}

ijk_inl float_t fRecip(float_t const s)
{
	return (fIsNonZero(s) ? 1.0f / s : 0.0f);
}

ijk_inl float_t fSqrt(float_t const s)
{
	extern f64 sqrt(f64);
	return (float_t)sqrt((f64)s);
}

ijk_inl float_t fSqrtInv(float_t const s)
{
	return (fIsNonZero(s) ? 1.0f / fSqrt(s) : 0.0f);
}

ijk_inl float_t fLerp(float_t const s0, float_t const s1, float_t const u)
{
	return (s0 + (s1 - s0) * u);
}

ijk_inl float_t fMad(float_t const s0, float_t const ds, float_t const u)
{
	return (s0 + ds * u);
}


//-----------------------------------------------------------------------------

ijk_inl floatv_t vec3fZero(float3_t v_out)
{
	v_out[0] = v_out[1] = v_out[2] = 0.0f;
	return v_out;
}

ijk_inl floatv_t vec3fInit(float3_t v_out, float_t const x, float_t const y, float_t const z)
{
	v_out[0] = x;
	v_out[1] = y;
	v_out[2] = z;
	return v_out;
}

ijk_inl floatv_t vec3fCopy(float3_t v_out, float3_t const v)
{
	v_out[0] = v[0];
	v_out[1] = v[1];
	v_out[2] = v[2];
	return v_out;
}

ijk_inl floatv_t vec3fNegate(float3_t v_out, float3_t const v)
{
	v_out[0] = -v[0];
	v_out[1] = -v[1];
	v_out[2] = -v[2];
	return v_out;
}

ijk_inl float_t vec3fDot(float3_t const v_lh, float3_t const v_rh)
{
	return (v_lh[0] * v_rh[0] + v_lh[1] * v_rh[1] + v_lh[2] * v_rh[2]);
}

ijk_inl floatv_t vec3fCross(float3_t v_out, float3_t const v_lh, float3_t const v_rh)
{
	float3_t const cross = {
		(v_lh[1] * v_rh[2] - v_lh[2] * v_rh[1]),
		(v_lh[2] * v_rh[0] - v_lh[0] * v_rh[2]),
		(v_lh[0] * v_rh[1] - v_lh[1] * v_rh[0]),
	};
	return vec3fCopy(v_out, cross);
}

ijk_inl float_t vec3fLenSq(float3_t const v)
{
	return vec3fDot(v, v);
}

ijk_inl float_t vec3fLen(float3_t const v)
{
	return fSqrt(vec3fLenSq(v));
}

ijk_inl float_t vec3fLenSqInv(float3_t const v)
{
	float_t const lenSq = vec3fLenSq(v);
	return (lenSq > epsf ? 1.0f / lenSq : 0.0f);
}

ijk_inl float_t vec3fLenInv(float3_t const v)
{
	float_t const lenSq = vec3fLenSq(v);
	return (lenSq > epsf ? 1.0f / fSqrt(lenSq) : 0.0f);
}

ijk_inl floatv_t vec3fAdd(float3_t v_out, float3_t const v_lh, float3_t const v_rh)
{
	v_out[0] = v_lh[0] + v_rh[0];
	v_out[1] = v_lh[1] + v_rh[1];
	v_out[2] = v_lh[2] + v_rh[2];
	return v_out;
}

ijk_inl floatv_t vec3fSub(float3_t v_out, float3_t const v_lh, float3_t const v_rh)
{
	v_out[0] = v_lh[0] - v_rh[0];
	v_out[1] = v_lh[1] - v_rh[1];
	v_out[2] = v_lh[2] - v_rh[2];
	return v_out;
}

ijk_inl floatv_t vec3fMul(float3_t v_out, float3_t const v_lh, float_t const s_rh)
{
	v_out[0] = v_lh[0] * s_rh;
	v_out[1] = v_lh[1] * s_rh;
	v_out[2] = v_lh[2] * s_rh;
	return v_out;
}

ijk_inl floatv_t vec3fDiv(float3_t v_out, float3_t const v_lh, float_t const s_rh)
{
	return vec3fMul(v_out, v_lh, fRecip(s_rh));
}

ijk_inl floatv_t vec3fLerp(float3_t v_out, float3_t const v0, float3_t const v1, float_t const u)
{
	v_out[0] = fLerp(v0[0], v1[0], u);
	v_out[1] = fLerp(v0[1], v1[1], u);
	v_out[2] = fLerp(v0[2], v1[2], u);
	return v_out;
}

ijk_inl floatv_t vec3fMad(float3_t v_out, float3_t const v0, float3_t const dv, float_t const u)
{
	v_out[0] = fMad(v0[0], dv[0], u);
	v_out[1] = fMad(v0[1], dv[1], u);
	v_out[2] = fMad(v0[2], dv[2], u);
	return v_out;
}

ijk_inl float_t vec3fProjs(float3_t const v_base, float3_t const v)
{
	float_t const lenSq = vec3fLenSq(v_base);
	return (lenSq > epsf ? vec3fDot(v_base, v) / lenSq : 0.0f);
}

ijk_inl floatv_t vec3fProj(float3_t v_out, float3_t const v_base, float3_t const v)
{
	return vec3fMul(v_out, v_base, vec3fProjs(v_base, v));
}

ijk_inl floatv_t vec3fUnit(float3_t v_out, float3_t const v)
{
	return vec3fMul(v_out, v, vec3fLenInv(v));
}

ijk_inl float_t vec3fDistSq(float3_t const v_lh, float3_t const v_rh)
{
	float3_t dv;
	return vec3fLenSq(vec3fSub(dv, v_lh, v_rh));
}

ijk_inl float_t vec3fDist(float3_t const v_lh, float3_t const v_rh)
{
	float3_t dv;
	return vec3fLen(vec3fSub(dv, v_lh, v_rh));
}

ijk_inl bool vec3fIsZero(float3_t const v)
{
	return (vec3fLenSq(v) <= epsf);
}

ijk_inl bool vec3fIsNonZero(float3_t const v)
{
	return (vec3fLenSq(v) > epsf);
}

ijk_inl bool vec3fIsUnit(float3_t const v)
{
	return fIsZero(vec3fLenSq(v) - 1.0f);
}

ijk_inl bool vec3fIsNonUnit(float3_t const v)
{
	return fIsNonZero(vec3fLenSq(v) - 1.0f);
}


//-----------------------------------------------------------------------------


#ifdef __cplusplus
}
#endif	// __cplusplus


#endif	// !_VEC3F_INL_
#endif	// _VEC3F_H_