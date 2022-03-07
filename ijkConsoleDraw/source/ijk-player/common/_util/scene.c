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

	scene.c
	Simple scene implementation.
*/

#include "scene.h"


//-----------------------------------------------------------------------------

void fSphereInit(sScene* const scene, ui16 const shapeIndex, float_t const x, float_t const y, float_t const z, float_t const radius, ijkConsoleColor const color_base)
{
	ijk_assert(shapeIndex < scene_numSpheres);

	sSphere* const sphere = scene->sphere + shapeIndex;
	vec3fInit(scene->location[sphere->i_location].v, x, y, z);
	scene->radius[sphere->i_radius] = radius;
	scene->color[sphere->i_color].color[0] = color_base & ~ijkConsoleColor_a;
	scene->color[sphere->i_color].color[1] = color_base | ijkConsoleColor_a;
}

void fCylinderInit(sScene* const scene, ui16 const shapeIndex, float_t const x0, float_t const y0, float_t const z0, float_t const x1, float_t const y1, float_t const z1, float_t const radius, ijkConsoleColor const color_base)
{
	ijk_assert(shapeIndex < scene_numCylinders);

	sCylinder* const cylinder = scene->cylinder + shapeIndex;
	vec3fInit(scene->location[cylinder->i_location_cap0].v, x0, y0, z0);
	vec3fInit(scene->location[cylinder->i_location_cap1].v, x1, y1, z1);
	scene->radius[cylinder->i_radius] = radius;
	scene->color[cylinder->i_color].color[0] = color_base & ~ijkConsoleColor_a;
	scene->color[cylinder->i_color].color[1] = color_base | ijkConsoleColor_a;
}

void fPointLightInit(sScene* const scene, ui16 const shapeIndex, float_t const x, float_t const y, float_t const z)
{
	ijk_assert(shapeIndex < scene_numPointLights);

	sPointLight* const pointLight = scene->pointLight + shapeIndex;
	vec3fInit(scene->location[pointLight->i_location].v, x, y, z);
}

void fSphereGet(sScene const* const scene, ui16 const shapeIndex, vec3f* const location_out, float_t* const radius_out)
{
	ijk_assert(shapeIndex < scene_numSpheres);

	sSphere const* const sphere = scene->sphere + shapeIndex;
	*location_out = scene->location[sphere->i_location];
	*radius_out = scene->radius[sphere->i_radius];
}

void fSphereGetColor(sScene const* const scene, ui16 const shapeIndex, sColor* const color_out)
{
	ijk_assert(shapeIndex < scene_numSpheres);

	sSphere const* const sphere = scene->sphere + shapeIndex;
	*color_out = scene->color[sphere->i_color];
}

void fCylinderGet(sScene const* const scene, ui16 const shapeIndex, vec3f* const location_cap0_out, vec3f* const location_cap1_out, float_t* const radius_out)
{
	ijk_assert(shapeIndex < scene_numCylinders);

	sCylinder const* const cylinder = scene->cylinder + shapeIndex;
	*location_cap0_out = scene->location[cylinder->i_location_cap0];
	*location_cap1_out = scene->location[cylinder->i_location_cap1];
	*radius_out = scene->radius[cylinder->i_radius];
}

void fCylinderGetColor(sScene const* const scene, ui16 const shapeIndex, sColor* const color_out)
{
	ijk_assert(shapeIndex < scene_numCylinders);

	sCylinder const* const cylinder = scene->cylinder + shapeIndex;
	*color_out = scene->color[cylinder->i_color];
}

void fPointLightGet(sScene const* const scene, ui16 const shapeIndex, vec3f* const location_out)
{
	ijk_assert(shapeIndex < scene_numPointLights);

	sPointLight const* const pointLight = scene->pointLight + shapeIndex;
	*location_out = scene->location[pointLight->i_location];
}

void fSceneInit(sScene* const scene)
{
	// link objects
	ui16 count_object, count_location = 0, count_radius = 0, count_color = 0;
	for (count_object = 0; count_object < scene_numSpheres; ++count_object)
	{
		scene->sphere[count_object].i_location = count_location++;
		scene->sphere[count_object].i_radius = count_radius++;
		scene->sphere[count_object].i_color = count_color++;
	}
	for (count_object = 0; count_object < scene_numCylinders; ++count_object)
	{
		scene->cylinder[count_object].i_location_cap0 = count_location++;
		scene->cylinder[count_object].i_location_cap1 = count_location++;
		scene->cylinder[count_object].i_radius = count_radius++;
		scene->cylinder[count_object].i_color = count_color++;
	}
	for (count_object = 0; count_object < scene_numPointLights; ++count_object)
	{
		scene->pointLight[count_object].i_location = count_location++;
	}
	ijk_assert(count_location == ijk_arrlen(scene->location));
	ijk_assert(count_radius == ijk_arrlen(scene->radius));
	ijk_assert(count_color == ijk_arrlen(scene->color));

	// assign values
	fSphereInit(scene, 0,  0.0f,  0.0f, -9.0f, 2.0f, ijkConsoleColor_red);
	fSphereInit(scene, 1, -2.0f,  0.0f, -6.0f, 1.0f, ijkConsoleColor_blue);

	fCylinderInit(scene, 0, +1.0f, -2.0f, -9.0f, -1.0f, +2.0f, -9.0f, 2.0f, ijkConsoleColor_magenta);
	fCylinderInit(scene, 1, +1.5f, -0.5f, -5.0f, +2.5f, +0.5f, -7.0f, 1.5f, ijkConsoleColor_cyan);

	fPointLightInit(scene, 0, +5.0f, +4.0f, -1.0f);

	// assign background
	scene->color_bg = ijkConsoleColor_grey_d;
}


//-----------------------------------------------------------------------------
