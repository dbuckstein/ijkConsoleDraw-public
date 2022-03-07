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

	scene.h
	Simple scene interface.
*/

#ifndef _SCENE_H_
#define _SCENE_H_

#include "vec3f.h"
#include "ijkConsole.h"


#ifdef __cplusplus
extern "C" {
#endif	// __cplusplus


//-----------------------------------------------------------------------------

// Shape types
typedef enum eShape_t
{
	shape_sphere,
	shape_cylinder,
} eShape;

// Describe sphere in list
typedef struct sSphere_t
{
	ui16 i_location, i_radius, i_color;
} sSphere;

// Describe cylinder in list
typedef struct sCylinder_t
{
	ui16 i_location_cap0, i_location_cap1, i_radius, i_color;
} sCylinder;

// Describe point light in main list
typedef struct sPointLight_t
{
	ui16 i_location;
} sPointLight;

#define scene_numSpheres		2
#define scene_numCylinders		2
#define scene_numPointLights	1
#define scene_numObjects		scene_numSpheres + scene_numCylinders + scene_numPointLights

// Cnsole color ramp
typedef struct sColor_t
{
	ijkConsoleColor color[2];	// dark, light
} sColor;

// Main scene
typedef struct sScene_t
{
	sSphere sphere[scene_numSpheres];
	sCylinder cylinder[scene_numCylinders];
	sPointLight pointLight[scene_numPointLights];

	vec3f location[scene_numObjects + scene_numCylinders];
	float_t radius[scene_numSpheres + scene_numCylinders];
	sColor color[scene_numSpheres + scene_numCylinders];

	ijkConsoleColor color_bg;
} sScene;


// Initialize sphere shape descriptor
void fSphereInit(sScene* const scene, ui16 const shapeIndex, float_t const x, float_t const y, float_t const z, float_t const radius, ijkConsoleColor const color_base);
// Initialize cylinder shape descriptor
void fCylinderInit(sScene* const scene, ui16 const shapeIndex, float_t const x0, float_t const y0, float_t const z0, float_t const x1, float_t const y1, float_t const z1, float_t const radius, ijkConsoleColor const color_base);
// Initialize point light shape descriptor
void fPointLightInit(sScene* const scene, ui16 const shapeIndex, float_t const x, float_t const y, float_t const z);
// Get sphere shape info
void fSphereGet(sScene const* const scene, ui16 const shapeIndex, vec3f* const location_out, float_t* const radius_out);
// Get sphere color ramp
void fSphereGetColor(sScene const* const scene, ui16 const shapeIndex, sColor* const color_out);
// Get cylinder shape info
void fCylinderGet(sScene const* const scene, ui16 const shapeIndex, vec3f* const location_cap0_out, vec3f* const location_cap1_out, float_t* const radius_out);
// Get cylinder color ramp
void fCylinderGetColor(sScene const* const scene, ui16 const shapeIndex, sColor* const color_out);
// Get point light shape info
void fPointLightGet(sScene const* const scene, ui16 const shapeIndex, vec3f* const location_out);
// Initialize scene
void fSceneInit(sScene* const scene);


//-----------------------------------------------------------------------------


#ifdef __cplusplus
}
#endif	// __cplusplus


#endif	// !_SCENE_H_