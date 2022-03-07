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

#include "_util/ijkConsole.h"

#include <stdio.h>


//-----------------------------------------------------------------------------

iret ijkConsoleDraw(ijkConsole const* const console)
{
	do
	{
		ijkConsoleDrawTestPatch();
	} while (!getchar());

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
