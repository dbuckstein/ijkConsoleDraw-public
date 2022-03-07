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

	ijk-player.c
	Default source for player application.
*/

#include "_util/scene.h"

#include <stdio.h>


//-----------------------------------------------------------------------------
// DATA STRUCTURES

// Viewport descriptor
//	-> NOTE: viewport orientation: x is right, y is down, z is into screen; 
//		this is flipped for the viewer in the scene, so y is up and z is out
typedef struct sViewport_t
{
	ui16 width, height;			// Raw dimensions of viewport
	f32 aspect;					// Aspect ratio (width/height)
	f32 widthInv, heightInv;	// Inverse dimensions of viewport
	f32 viewWidth;				// Width of viewport in viewer space
	f32 viewHeight;				// Height of viewport in viewer space
	f32 viewDist;				// Distance to viewport in viewer space
} sViewport;

// Initialize viewport
ijk_inl bool fViewportInit(sViewport* const viewport, ui16 const width, ui16 const height, f32 const viewHeight, f32 const viewDist)
{
	if (!viewport || !width || !height || viewHeight <= 0.0f || viewDist <= 0.0f)
		return false;

	viewport->width = width;
	viewport->height = height;
	viewport->aspect = (f32)width / (f32)height;
	viewport->widthInv = 1.0f / (f32)width;
	viewport->heightInv = 1.0f / (f32)height;
	viewport->viewDist = viewDist;
	viewport->viewHeight = viewHeight;
	viewport->viewWidth = viewport->aspect * viewport->viewHeight;
	return true;
}

// Convert location in viewport to scene view coord
ijk_inl bool fViewportGetViewCoord(sViewport const* const viewport, float3_t coord_out, ui16 const x_viewport, ui16 const y_viewport)
{
	if (!viewport || !viewport->width || !coord_out)
		return false;

	float_t const u = (float_t)(x_viewport) * viewport->widthInv;
	float_t const v = (float_t)(viewport->height - 1 - y_viewport) * viewport->heightInv;
	float_t const x_ndc = (u * 2.0f - 1.0f);
	float_t const y_ndc = (v * 2.0f - 1.0f);
	coord_out[0] = x_ndc * 0.5f * viewport->viewWidth;
	coord_out[1] = y_ndc * 0.5f * viewport->viewHeight;
	coord_out[2] = -viewport->viewDist;
	return true;
}


// Ray descriptor
typedef struct sRay_t
{
	vec3f origin;
	vec3f direction;
} sRay;

// Initialize ray in perspective projection given 
//	center of viewer's space (center_eye) and viewport coordinate in viewer's space (viewport_eye)
ijk_inl bool fRayInitPersp(sRay* const ray, float3_t const center_eye, float3_t const viewport_eye)
{
	if (!ray)
		return false;

	vec3fCopy(ray->origin.v, center_eye);
	vec3fSub(ray->direction.v, viewport_eye, center_eye);
	return true;
}

// Initialize ray in orthographic projection given 
//	center of viewer's space (center_eye) and viewport coordinate in viewer's space (viewport_eye)
ijk_inl bool fRayInitOrtho(sRay* const ray, float3_t const center_eye, float3_t const viewport_eye)
{
	if (!ray)
		return false;

	vec3fAdd(ray->origin.v, center_eye, viewport_eye);
	vec3fInit(ray->direction.v, 0.0f, 0.0f, viewport_eye[2]);
	return true;
}


//-----------------------------------------------------------------------------
// DISPLAY

// Ray hit record
typedef struct sRecord_t
{
	ui16 type, index;
	float_t dist;
} sRecord;

// Test ray against sphere
ijk_inl bool fRayTestSphere(sRay const* const ray, sScene const* const scene, ui16 const shapeIndex, sRecord* const hit_out)
{
	assert(shapeIndex < scene_numSpheres);

	vec3f location;
	float_t radius;
	fSphereGet(scene, shapeIndex, &location, &radius);

	return true;
}

// Test ray against finite cylinder
ijk_inl bool fRayTestCylinderFinite(sRay const* const ray, sScene const* const scene, ui16 const shapeIndex, sRecord* const hit_out)
{
	assert(shapeIndex < scene_numCylinders);

	vec3f location_cap0;
	vec3f location_cap1;
	float_t radius;
	fCylinderGet(scene, shapeIndex, &location_cap0, &location_cap1, &radius);

	return true;
}

// Calculate final color from ray in scene
ijk_inl void fRayCalcColor(sRay const* const ray, sScene const* const scene, ijkConsoleColor* const color_out)
{
	*color_out = scene->color_bg;
}


//-----------------------------------------------------------------------------

ijk_inl void ijkConsoleDrawPixel(ijkConsole const* const console, ijkConsoleColor const color, i16 const x_viewport, i16 const y_viewport)
{
	ijkConsoleSetCursorColor(x_viewport * 2, y_viewport * 1, color, color);
	printf("  ");
}

iret ijkConsoleDraw(ijkConsole const* const console)
{
	ui16 const width = 48, height = 27;
	f32 const viewHeight = 2.0f, viewDist = 3.0f;

	ui16 x = 0, y = 0;
	float3_t coord = { 0 };
	ijkConsoleColor color = ijkConsoleColor_black;

	sViewport viewport;
	fViewportInit(&viewport, width, height, viewHeight, viewDist);

	sScene scene;
	fSceneInit(&scene);

	sRay ray;

	//------------------------------------
	do
	{
		//ijkConsoleDrawTestPatch();
		ijkConsoleClear();
		for (y = 0; y < height; ++y)
		{
			//color = (ijkConsoleColor)(y % 16); // test rows
			for (x = 0; x < width; ++x)
			{
				fViewportGetViewCoord(&viewport, coord, x, y);
				fRayInitPersp(&ray, vec3f0.v, coord);
				fRayCalcColor(&ray, &scene, &color);
				//color = (ijkConsoleColor)(((x % 16) + y) % 16); // test pattern
				ijkConsoleDrawPixel(console, color, x, y);
			}
		}
		ijkConsoleDrawPixel(console, ijkConsoleColor_black, x, y);
	} while (!getchar());
	//------------------------------------

	return ijk_success;
}


//-----------------------------------------------------------------------------

iret ijkPlayerMain()
{
	iret status = -1;
	i32 i = -1;

	// data structures for management
	ijkConsole console[1] = { 0 };

	// constants
	status = ijkConsoleCreateMain(console);
	status = ijkConsoleDraw(console);
	status = ijkConsoleReleaseMain(console);

	// done
	return status;
}


//-----------------------------------------------------------------------------
