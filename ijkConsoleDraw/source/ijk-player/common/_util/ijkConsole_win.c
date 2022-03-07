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

	ijkConsole_win.c
	Console management source for Windows.
*/

#include "ijkConsole.h"
#if ijk_platform_is(WINDOWS)

#include <io.h>
#include <stdio.h>
#include <Windows.h>


//-----------------------------------------------------------------------------

// redirect with settings
ijk_inl void ijkConsoleInternalRedirectToggle(ijkConsole* const console, bln const redirectInput, bln const redirectOutput, bln const redirectError)
{
	FILE* str = 0;
	i32 i = -1, j = -1;

	// redirect input
	i = 0;
	if (redirectInput)
	{
		if (GetStdHandle(STD_INPUT_HANDLE) != INVALID_HANDLE_VALUE && !console->handle[i])
		{
			// flush buffer, duplicate handle and reopen stream to console
			//j = fprintf(stdin, "\n STDIN =/= DEFAULT \n");
			j = fflush(stdin);
			j = _dup(i);
			str = freopen("CONIN$", "r+", stdin);
			if (str)
			{
				// store values and configure
				console->handle[i] = str;
				console->io[i] = j;
				j = setvbuf(stdin, NULL, _IONBF, 0);
				//j = fprintf(stdin, "\n STDIN == CONSOLE \n");
			}
		}
	}
	else
	{
		if (GetStdHandle(STD_INPUT_HANDLE) != INVALID_HANDLE_VALUE && console->handle[i])
		{
			// flush and reopen
			//j = fprintf(stdin, "\n STDIN =/= CONSOLE \n");
			j = fflush(stdin);
			str = freopen("NUL:", "r+", stdin);
			if (str)
			{
				// duplicate handle and reconfigure stream, reset variables
				j = _dup2(console->io[i], i);
				j = setvbuf(stdin, NULL, _IONBF, 0);
				//j = fprintf(stdin, "\n STDIN == DEFAULT \n");
				console->handle[i] = 0;
				console->io[i] = -1;
			}
		}
	}

	// redirect output
	i = 1;
	if (redirectOutput)
	{
		if (GetStdHandle(STD_OUTPUT_HANDLE) != INVALID_HANDLE_VALUE && !console->handle[i])
		{
			// flush buffer, duplicate handle and reopen stream to console
			//j = fprintf(stdout, "\n STDOUT =/= DEFAULT \n");
			j = fflush(stdout);
			j = _dup(i);
			str = freopen("CONOUT$", "a+", stdout);
			if (str)
			{
				// store values and configure
				console->handle[i] = str;
				console->io[i] = j;
				j = setvbuf(stdout, NULL, _IONBF, 0);
				//j = fprintf(stdout, "\n STDOUT == CONSOLE \n");
			}
		}
	}
	else
	{
		if (GetStdHandle(STD_OUTPUT_HANDLE) != INVALID_HANDLE_VALUE && console->handle[i])
		{
			// flush and reopen
			//j = fprintf(stdout, "\n STDOUT =/= CONSOLE \n");
			j = fflush(stdout);
			str = freopen("NUL:", "a+", stdout);
			if (str)
			{
				// duplicate handle and reconfigure stream, reset variables
				j = _dup2(console->io[i], i);
				j = setvbuf(stdout, NULL, _IONBF, 0);
				//j = fprintf(stdout, "\n STDOUT == DEFAULT \n");
				console->handle[i] = 0;
				console->io[i] = -1;
			}
		}
	}

	// redirect error
	i = 2;
	if (redirectError)
	{
		if (GetStdHandle(STD_ERROR_HANDLE) != INVALID_HANDLE_VALUE && !console->handle[i])
		{
			// flush buffer, duplicate handle and reopen stream to console
			//j = fprintf(stderr, "\n STDERR =/= DEFAULT \n");
			j = fflush(stderr);
			j = _dup(i);
			str = freopen("CONOUT$", "a+", stderr);
			if (str)
			{
				// store values and configure
				console->handle[i] = str;
				console->io[i] = j;
				j = setvbuf(stderr, NULL, _IONBF, 0);
				//j = fprintf(stderr, "\n STDERR == CONSOLE \n");
			}
		}
	}
	else
	{
		if (GetStdHandle(STD_ERROR_HANDLE) != INVALID_HANDLE_VALUE && console->handle[i])
		{
			// flush and reopen
			//j = fprintf(stderr, "\n STDERR =/= CONSOLE \n");
			j = fflush(stderr);
			str = freopen("NUL:", "a+", stderr);
			if (str)
			{
				// duplicate handle and reconfigure stream, reset variables
				j = _dup2(console->io[i], i);
				j = setvbuf(stderr, NULL, _IONBF, 0);
				//j = fprintf(stderr, "\n STDERR == DEFAULT \n");
				console->handle[i] = 0;
				console->io[i] = -1;
			}
		}
	}
}


//-----------------------------------------------------------------------------

iret ijkConsoleCreateMain(ijkConsole* const console)
{
	ijk_assertparamptr(console);

	// if console not already open
	ptr handle = GetConsoleWindow();
	bln create = !handle && !console->handle[3];
	ijk_warnreturniff(create, ijk_warn_console_exist);

	// allocate and show console
	create = AllocConsole();
	ijk_assertspectrue(create, ijk_fail_console_init);

	// reset flags
	console->handle[0] = console->handle[1] = console->handle[2] = 0;
	console->io[0] = console->io[1] = console->io[2] = -1;

	// init flag
	console->handle[3] = handle = GetConsoleWindow();

	// disable closing console manually because doing this kills 
	//	the whole application; could also start a new process, 
	//	but then there's also that to manage
	DeleteMenu(GetSystemMenu(handle, FALSE), SC_CLOSE, MF_BYCOMMAND);

	// redirect to new console (in/out, not err)
	ijkConsoleInternalRedirectToggle(console, 1, 1, 0);
	return ijk_success;
}


iret ijkConsoleRedirectMain(ijkConsole* const console, bln const redirectInput, bln const redirectOutput, bln const redirectError)
{
	ijk_assertparamptr(console);

	kptr const handle = GetConsoleWindow();
	bln const redirect = (console->handle[3] == handle) && handle;
	ijk_assertspectrue(redirect, ijk_fail_console_init);

	// redirect toggle
	ijkConsoleInternalRedirectToggle(console, redirectInput, redirectOutput, redirectError);
	return ijk_success;
}


iret ijkConsoleReleaseMain(ijkConsole* const console)
{
	ijk_assertparamptr(console);

	kptr const handle = GetConsoleWindow();
	bln const exists = (console->handle[3] == handle) && handle;
	ijk_warnreturniff(exists, ijk_warn_console_exist);

	// reset to original standard i/o
	ijkConsoleInternalRedirectToggle(console, 0, 0, 0);

	// delete console instance
	// console will hide when all standard handles are closed
	bln const released = FreeConsole();
	ijk_assertspectrue(released, ijk_fail_console_init);

	// reset
	console->handle[3] = 0;
	return ijk_success;
}


//-----------------------------------------------------------------------------

iret ijkConsoleGetCursor(i16* const x_out, i16* const y_out)
{
	ijk_assertparamptr(x_out);
	ijk_assertparamptr(y_out);

	CONSOLE_SCREEN_BUFFER_INFO screenBufferInfo[1];
	HANDLE const stdHandle = GetStdHandle(STD_OUTPUT_HANDLE), console = GetConsoleWindow();
	bln const completed = stdHandle && console &&
		GetConsoleScreenBufferInfo(stdHandle, screenBufferInfo);
	ijk_assertspectrue(completed, ijk_fail_console_manip);

	*x_out = screenBufferInfo->dwCursorPosition.X;
	*y_out = screenBufferInfo->dwCursorPosition.Y;
	return ijk_success;
}


iret ijkConsoleSetCursor(i16 const x, i16 const y)
{
	COORD const pos = { x, y };
	HANDLE const stdHandle = GetStdHandle(STD_OUTPUT_HANDLE), console = GetConsoleWindow();
	bln const completed = stdHandle && console &&
		SetConsoleCursorPosition(stdHandle, pos);
	ijk_assertspectrue(completed, ijk_fail_console_manip);

	return ijk_success;
}


iret ijkConsoleToggleCursor(bln const visible)
{
	CONSOLE_CURSOR_INFO cursorInfo[1];
	HANDLE const stdHandle = GetStdHandle(STD_OUTPUT_HANDLE), console = GetConsoleWindow();
	bln completed = stdHandle && console &&
		GetConsoleCursorInfo(stdHandle, cursorInfo);
	ijk_assertspectrue(completed, ijk_fail_console_manip);

	cursorInfo->bVisible = visible;
	completed = SetConsoleCursorInfo(stdHandle, cursorInfo);
	ijk_assertspectrue(completed, ijk_fail_console_manip);

	return ijk_success;
}


iret ijkConsoleGetColor(ijkConsoleColor* const fg_out, ijkConsoleColor* const bg_out)
{
	ijk_assertparamptr(fg_out);
	ijk_assertparamptr(bg_out);

	CONSOLE_SCREEN_BUFFER_INFO screenBufferInfo[1];
	HANDLE const stdHandle = GetStdHandle(STD_OUTPUT_HANDLE), console = GetConsoleWindow();
	bln const completed = stdHandle && console &&
		GetConsoleScreenBufferInfo(stdHandle, screenBufferInfo);
	ijk_assertspectrue(completed, ijk_fail_console_manip);

	*fg_out = (ijkConsoleColor)(screenBufferInfo->wAttributes & 0xf);
	*bg_out = (ijkConsoleColor)(screenBufferInfo->wAttributes >> 4 & 0xf);
	return ijk_success;
}


iret ijkConsoleSetColor(ijkConsoleColor const fg, ijkConsoleColor const bg)
{
	HANDLE const stdHandle = GetStdHandle(STD_OUTPUT_HANDLE), console = GetConsoleWindow();
	bln const completed = stdHandle && console &&
		SetConsoleTextAttribute(stdHandle, (i16)(fg | bg << 4));
	ijk_assertspectrue(completed, ijk_fail_console_manip);

	return ijk_success;
}


iret ijkConsoleResetColor()
{
	return ijkConsoleSetColor(ijkConsoleColor_white, ijkConsoleColor_black);
}


iret ijkConsoleGetCursorColor(i16* const x_out, i16* const y_out, ijkConsoleColor* const fg_out, ijkConsoleColor* const bg_out)
{
	ijk_assertparamptr(x_out);
	ijk_assertparamptr(y_out);
	ijk_assertparamptr(fg_out);
	ijk_assertparamptr(bg_out);

	CONSOLE_SCREEN_BUFFER_INFO screenBufferInfo[1];
	HANDLE const stdHandle = GetStdHandle(STD_OUTPUT_HANDLE), console = GetConsoleWindow();
	bln const completed = stdHandle && console &&
		GetConsoleScreenBufferInfo(stdHandle, screenBufferInfo);
	ijk_assertspectrue(completed, ijk_fail_console_manip);

	*x_out = screenBufferInfo->dwCursorPosition.X;
	*y_out = screenBufferInfo->dwCursorPosition.Y;
	*fg_out = (ijkConsoleColor)(screenBufferInfo->wAttributes & 0xf);
	*bg_out = (ijkConsoleColor)(screenBufferInfo->wAttributes >> 4 & 0xf);
	return ijk_success;
}


iret ijkConsoleSetCursorColor(i16 const x, i16 const y, ijkConsoleColor const fg, ijkConsoleColor const bg)
{
	COORD const pos = { x, y };
	HANDLE const stdHandle = GetStdHandle(STD_OUTPUT_HANDLE), console = GetConsoleWindow();
	bln const completed = stdHandle && console &&
		SetConsoleCursorPosition(stdHandle, pos) &&
		SetConsoleTextAttribute(stdHandle, (i16)(fg | bg << 4));
	ijk_assertspectrue(completed, ijk_fail_console_manip);

	return ijk_success;
}


iret ijkConsoleGetSize(i16* const w_out, i16* const h_out)
{
	ijk_assertparamptr(w_out);
	ijk_assertparamptr(h_out);

	CONSOLE_SCREEN_BUFFER_INFO screenBufferInfo[1];
	HANDLE const stdHandle = GetStdHandle(STD_OUTPUT_HANDLE), console = GetConsoleWindow();
	bln const completed = stdHandle && console &&
		GetConsoleScreenBufferInfo(stdHandle, screenBufferInfo);
	ijk_assertspectrue(completed, ijk_fail_console_manip);

	*w_out = screenBufferInfo->dwSize.X;
	*h_out = screenBufferInfo->dwSize.Y;
	return ijk_success;
}


iret ijkConsoleSetSize(i16 const w, i16 const h)
{
	COORD const sz = { w, h };
	HANDLE const stdHandle = GetStdHandle(STD_OUTPUT_HANDLE), console = GetConsoleWindow();
	bln const completed = stdHandle && console &&
		SetConsoleScreenBufferSize(stdHandle, sz);
	ijk_assertspectrue(completed, ijk_fail_console_manip);

	return ijk_success;
}


iret ijkConsoleDrawTestPatch()
{
	HANDLE const stdHandle = GetStdHandle(STD_OUTPUT_HANDLE), console = GetConsoleWindow();
	bln const exists = stdHandle && console;
	ijk_assertspectrue(exists, ijk_fail_console_manip);

	// test all colors and shifts
	i16 x, y;
	ijkConsoleColor fg, bg;
	for (y = 0; y < 16; ++y)
	{
		for (x = 0; x < 16; ++x)
		{
			fg = (ijkConsoleColor)y;
			bg = (ijkConsoleColor)x;
			ijkConsoleSetColor(fg, bg);
			ijkConsoleSetCursor(x * 2, y);
			printf("%x", (i32)x);
			ijkConsoleSetCursorColor(x * 2 + 1, y, fg, bg);
			printf("%x", (i32)y);
		}
	}
	ijkConsoleGetCursor(&x, &y);
	ijkConsoleGetColor(&fg, &bg);
	ijkConsoleGetCursorColor(&x, &y, &fg, &bg);
	ijkConsoleResetColor();
	printf("[]=(%d, %d) \n", (i32)x, (i32)y);

	// done
	return ijk_success;
}


iret ijkConsoleClear()
{
	// help to avoid using system("cls"): https://docs.microsoft.com/en-us/windows/console/clearing-the-screen 
	CONSOLE_SCREEN_BUFFER_INFO buffer[1];
	HANDLE const stdHandle = GetStdHandle(STD_OUTPUT_HANDLE), console = GetConsoleWindow();
	bln completed = stdHandle && console &&
		GetConsoleScreenBufferInfo(stdHandle, buffer);
	ijk_assertspectrue(completed, ijk_fail_console_manip);

	// simple clear
	//system("cls");

	COORD const coord = { 0, 0 };
	dword const sz = (buffer->dwSize.X * buffer->dwSize.Y);
	dword write[1] = { 0 };
	completed = FillConsoleOutputCharacterA(stdHandle, ' ', sz, coord, write) &&
		GetConsoleScreenBufferInfo(stdHandle, buffer) &&
		FillConsoleOutputAttribute(stdHandle, buffer->wAttributes, sz, coord, write) &&
		SetConsoleCursorPosition(stdHandle, coord);
	ijk_assertspectrue(completed, ijk_fail_console_manip);

	return ijk_success;
}


//-----------------------------------------------------------------------------

iret ijkConsolePrintDebug(kstr const format, ...)
{
	ijk_assertparamptr(format);

	byte str[256] = { 0 };
	va_list args = 0;
	iret result = 0;

	// fill buffer with formatted arguments
	va_start(args, format);
	result = _vsnprintf(str, sizeof(str), format, args);
	va_end(args);

	// internal print
	OutputDebugStringA(str);

	// return length
	return result;
}


//-----------------------------------------------------------------------------


#endif	// WINDOWS