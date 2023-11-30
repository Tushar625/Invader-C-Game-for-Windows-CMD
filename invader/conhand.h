/*
	CONHANDLING gives protection if this header file is included multiple times in a source code

	this will make sure that the contents of the header file are included only once
*/

#ifndef CONHANDLING

#define CONHANDLING

// this header file contains several macros that can handle console output

#include<Windows.h>

#include<stdlib.h>

#include<stdio.h>

#include<string.h>

#include<conio.h>

#include<time.h>

#include"loop.h"


#define IN_RNG(Lrng, x, Hrng) ((x) >= (Lrng) && (x) <= (Hrng)) // if x is between Lrng and Hrng it gives 1 else 0



#ifndef COLOURS_HERE

#define COLOURS_HERE

typedef enum colortext {BLACK, BLUE, GREEN, CYAN, RED, MAGENTA, BROWN, LIGHTGRAY, GRAY, LIGHTBLUE, LIGHTGREEN, LIGHTCYAN, LIGHTRED, LIGHTMAGENTA, YELLOW, WHITE} colortext;



/*
	!!!!! If you don't know bitwise operator then use the macros given below !!!!!

	color is a colortext type data this macro basically converts a text color into
	its background color, now this background color can be used with textcolor()
	macro to change background, or can be combined with text color using '|' i.e.,
	bitwise OR operator to generate attribute for CHAR_INFO or textcolor() macro
	like, color | bg(color)
*/

#define bg(color) ((color) << 4)

#endif // COLOURS_HERE



/*
	this macro can change the color of the characters printed on console,
	(with black as the background color)
	needs windows.h to operate

	BLACK 			= 0
	BLUE 			= 1
	GREEN 			= 2
	CYAN			= 3
	RED				= 4
	MAGENTA			= 5
	BROWN			= 6
	LIGHTGRAY		= 7
	GRAY			= 8
	LIGHTBLUE		= 9
	LIGHTGREEN		= 10
	LIGHTCYAN		= 11
	LIGHTRED		= 12
	LIGHTMAGENTA	= 13
	YELLOW			= 14
	WHITE			= 15

	these are the colors corresponding to the values of x (int)

	once this macro is called with a certain color then all the text below
	will be printed in that color, until we change the text color again

	a text color can also be combined with a background color created by bg()
	as, color | bg(color), if only a color used with out any background color
	then the background will be black

	for ease of handling the enumerated data type and bg() macro has been
	declared above
*/



#ifndef textcolor

#define textcolor(x) (SetConsoleTextAttribute(GetStdHandle(STD_OUTPUT_HANDLE),(x)))

#endif // textcolor



/*
	this macro can generate the color attribute of the characters printed on console,
	needs windows.h to operate

	color: the color of the text

	back: color of the background

	color convention for both text and background is same as before

	for ease of handling the enumerated data type has been declared above

	this generated attribute can be used with CHAR_INFO data type or SetConsoleTextAttribute()
	as text attribute to generate proper text color and background
*/

#ifndef attribute_for_textcolor_with_background

#define attribute_for_textcolor_with_background(color, back) ((color) | bg(back))

#endif // attribute_for_textcolor_with_background



/*
	this macro can change the color of the characters printed on console,
	as well as the background color
	needs windows.h to operate

	color: the color of the text

	back: color of the background

	color convention for both text and background is same as before

	for ease of handling the enumerated data type has been declared above
*/

#ifndef textcolor_with_background

#define textcolor_with_background(color, back) (textcolor(attribute_for_textcolor_with_background(color, back)))

#endif // textcolor_with_background



/*
	this macro can print a colorful character, using textcolor(x) macro
	defined earlier, the color of the character depends on the value of
	color, one can use colortext, bg(), attribute_for_textcolor_with_background(color, back)
	to set the color and the background

	only difference is that only the character ch is printed in that color
	after printing it the text color is set to white
*/

#ifndef putcharcolor

#define putcharcolor(ch, color) (textcolor(color), putchar((ch)), textcolor(15))

#endif // putcharcolor



/*
	this function can change the color of the characters printed at proper position on console,
	as well as the background color
	needs windows.h to operate

	x, y : coordinates of the position

	color: the color of the text

	back: color of the background

	color convention for both text and background is same as before

	for ease of handling the enumerated data type has been declared above
*/

bool textcolor_with_background_pos(short x, short y, WORD color, WORD background)
{
	WORD attribute = attribute_for_textcolor_with_background(color, background);

	DWORD num;

	COORD point = {x, y};

	return WriteConsoleOutputAttribute(GetStdHandle(STD_OUTPUT_HANDLE), &attribute, 1, point, &num);
}



/*
	this function sets the position of the cursor in the screen, according to the
	given coordinates (x, y), (0, 0) is the top left end of the screen
*/

void cursor(short x, short y)
{
	COORD pt = {x, y};

	SetConsoleCursorPosition(GetStdHandle(STD_OUTPUT_HANDLE), pt);
}



/*
	this macro set the position of the cursor in the screen, according to the
	given coordinates (x, y), (1, 1) is the top left end of the screen
*/

#ifndef gotoxy

#define gotoxy(x, y) cursor((x) - 1, (y) - 1)

#endif // gotoxy



// display cursor if showFlag is 1 else the cursor vanishes if showFlag is 0

void show_console_cursor(bool showFlag)
{
    HANDLE out = GetStdHandle(STD_OUTPUT_HANDLE);

    CONSOLE_CURSOR_INFO cursorInfo;

    GetConsoleCursorInfo(out, &cursorInfo);

    cursorInfo.bVisible = showFlag; // set the cursor visibility

    SetConsoleCursorInfo(out, &cursorInfo);
}



// clear the entire screen

#ifndef clrscr

#define clrscr() system("cls")

#endif // clrscr



// delay any excuting operation by x milisecond

#ifndef delay

#define delay(x) do{\
				double t1, t2;\
				for(t1 = t2 = clock(); TIME_FROM_CLOCK_MILISECOND(t1, t2) < (x); t2 = clock());\
} while(0)

#endif // delay





// GETTING_CURSOR_POSITION gives protection for cursor position detection section

#ifndef GETTING_CURSOR_POSITION

#define GETTING_CURSOR_POSITION



/*
	collected function to get the position of the cursor on
	the console screen,

	returns a COORD (a structure) type data containing the
	coordinates of the cursor on the screen if successful
	else the returned data contains (-1, -1)
*/

COORD GetConsoleCursorPosition(HANDLE hConsoleOutput)
{
    CONSOLE_SCREEN_BUFFER_INFO cbsi;

    if (GetConsoleScreenBufferInfo(hConsoleOutput, &cbsi))
    {
		return cbsi.dwCursorPosition;
    }
    else
    {
		// The function failed. Call GetLastError() for details.

		COORD invalid = { -1, -1 };

		return invalid;
    }
}



// returns the y coordinate of the cursor position, (1, 1) is the top left end of the screen

short wherey()
{
	COORD p;

	p = GetConsoleCursorPosition(GetStdHandle(STD_OUTPUT_HANDLE));

	return p.Y + 1;
}



// returns the x coordinate of the cursor position, (1, 1) is the top left end of the screen

short wherex()
{
	COORD p;

	p = GetConsoleCursorPosition(GetStdHandle(STD_OUTPUT_HANDLE));

	return p.X + 1;
}



/*
	returns the x & y coordinates of the cursor position using call by value method,
	(1, 1) is the top left end of the screen
*/

void wherexy(short *x, short *y)
{
	COORD p;

	p = GetConsoleCursorPosition(GetStdHandle(STD_OUTPUT_HANDLE));

	*x = p.X + 1;

	*y = p.Y + 1;
}



// this macro gives the x coordinate of the cursor position, (0, 0) is the top left end of the screen

#ifndef CURSOR_POS_X

#define CURSOR_POS_X (wherex() - 1)

#endif // CURSOR_POS_X



// this macro gives the y coordinate of the cursor position, (0, 0) is the top left end of the screen

#ifndef CURSOR_POS_Y

#define CURSOR_POS_Y (wherey() - 1)

#endif // CURSOR_POS_Y



/*
	this macro gives the x & y coordinates of the cursor position
	using call by value method, x & y point to two short type variables,
	(0, 0) is the top left end of the screen
*/

#ifndef CURSOR_POS_XY

#define CURSOR_POS_XY(x, y) (wherexy((x), (y)), --*(x), --*(y))

#endif // CURSOR_POS_XY



#endif // GETTING_CURSOR_POSITION





// console o/p window manipulation and mouse and keyboard i/p functions

#ifdef _WIN32_WINNT

#undef _WIN32_WINNT

#endif // _WIN32_WINNT

#define _WIN32_WINNT 0x0500

/*
	sets the pixels per character

	fontw: width of each character

	fonth: height of each character

	weight: mention the weight of the characters
	can be between 1 - 10, normal weight 4, bold
	weight 7

	face: the font name like Consolas, Courier or Arial
	it is a wide character type array so put an L before
	"Consolas" like L"Consolas", L"Arial", L"Terminal",
	L"8514oem"

	return 0 for failure and 1 for success
*/

bool set_font_size_weight_face(short fonth, short fontw, short weight, const wchar_t face[])
{
	if(fonth >= 1 && fontw >= 1 && IN_RNG(1, weight, 10))	// if fonth and fontw and weight are valid
	{
		HANDLE m_hConsole = GetStdHandle(STD_OUTPUT_HANDLE);

		// Set the font size now that the screen buffer has been assigned to the console

		CONSOLE_FONT_INFOEX cfi;

		cfi.cbSize = sizeof(cfi);

		// getting current font info

		if (!GetCurrentConsoleFontEx(m_hConsole, false, &cfi))
			return 0;

		// changing current font info

		cfi.dwFontSize.X = fontw;

		cfi.dwFontSize.Y = fonth;

		cfi.FontFamily = FF_DONTCARE;

		cfi.FontWeight = weight * 100;

		wcscpy_s(cfi.FaceName, LF_FACESIZE, face);

		// setting current font info

		if (!SetCurrentConsoleFontEx(m_hConsole, false, &cfi))
			return 0;

		return 1;
	}

	return 0;
}





/*
	this macro is to make use of set_font_size_weight_face() easier
*/

#define set_font_size_pixel(fonth, fontw) (set_font_size_weight_face((fonth), (fontw), 4, L"Consolas"))




/*
	changes the size of the console window

	makes it

	row unit high

	col unit wide

	returns nonzero for success, 0 for failure
*/

#define set_console_window_size(height, width) (((height) >= 1 && (width) >= 1) ? (MoveWindow(GetConsoleWindow(), 100, 10, (short) (width), (short) (height), false)) : 0)





/*
	set of the position of the console window in the screen

	x, y is in screen pixels (0, 0) top left corner of the screen

	returns nonzero for success, 0 for failure
*/

bool set_window_pos(short x, short y)
{
	HWND console = GetConsoleWindow();

	RECT r;

	GetWindowRect(console, &r); //stores the console's current dimensions

	return MoveWindow(console, x, y, r.right - r.left, r.bottom - r.top, TRUE);
}





/*
	set the size of the console window

	makes it

	row characters high

	col characters wide

	**** does not specified works if window size is too small
	**** if it resizes the window then the characters written in window previously is lost
	**** call it only at the start of the program

	returns nonzero for success, 0 for failure
*/

bool create_console_window(short row, short col)
{
	if(row >= 1 && col >= 1)	// if row and col are valid
	{
		// makes the size of the console window very small
/*
		if(!set_console_window_size(1, 1))	// this makes window size very small but makes the app not reliable
			return 0;
*/
		HANDLE m_hConsole = GetStdHandle(STD_OUTPUT_HANDLE);

		COORD coord = { (short)col, (short)row};

		SMALL_RECT m_rectWindow = { 0, 0, 1, 1 };

		if(!SetConsoleWindowInfo(m_hConsole, TRUE, &m_rectWindow))	// this makes window size small and makes the app very reliable
			return 0;

		// setting new screen buffer size

		if (!SetConsoleScreenBufferSize(m_hConsole, coord))
		{
			/*
				if this function fails when the size of the buffer is too small
				then we set the size of the screen to an optimal size

				and display this message
			*/

			set_console_window_size(200, 400);

			printf("!!!! Failed to create screen buffer !!!!");

			printf("\n\nIncrease size, press any key");

			_getch();

			exit(0);

			return 0;
		}

		// Assign screen buffer to the console

		CONSOLE_SCREEN_BUFFER_INFOEX csbi;

		csbi.cbSize = sizeof(csbi);

		// getting info about screen buffer

		if (!GetConsoleScreenBufferInfoEx(m_hConsole, &csbi))
			return 0;

		//printf("%d, %d", csbi.dwMaximumWindowSize.Y, csbi.dwMaximumWindowSize.X);

		// setting the window size to max

		/*SMALL_RECT*/ //m_rectWindow = { 0, 0, (short)(csbi.dwMaximumWindowSize.X - 1), (short)(csbi.dwMaximumWindowSize.Y - 1) };

		m_rectWindow.Left = 0;

		m_rectWindow.Top = 0;

		m_rectWindow.Right = (short)(csbi.dwMaximumWindowSize.X - 1);

		m_rectWindow.Bottom = (short)(csbi.dwMaximumWindowSize.Y - 1);

		if (!SetConsoleWindowInfo(m_hConsole, TRUE, &m_rectWindow))
			return 0;

		return 1;
	}

	return 0;
}





/*
	set the position of the window, disable resize or menu then call it to build the console window for best results
*/

#define build_console_window(fonth, fontw, height, width) do{while(!set_font_size_pixel((fonth), (fontw))); while(!create_console_window((height), (width)));} while(0)





/*
	if its called in a program then the user
	won't be able to resize the output console window

	returns nonzero for success, 0 for failure
*/

int disable_window_resize()
{
	HWND consoleWindow = GetConsoleWindow();

	return SetWindowLongPtr(consoleWindow, GWL_STYLE, GetWindowLong(consoleWindow, GWL_STYLE) & ~WS_MAXIMIZEBOX & ~WS_SIZEBOX);
}


int enable_window_resize()
{
	HWND consoleWindow = GetConsoleWindow();

	return SetWindowLongPtr(consoleWindow, GWL_STYLE, GetWindowLong(consoleWindow, GWL_STYLE) | WS_MAXIMIZEBOX | WS_SIZEBOX);
}





/*
	if its called in a program then the user
	won't be able to access the menu of the
	output console window

	---- you may want to call it after disable_window_resize() to completely disable window resizing, font changing etc.

	*** in this mode the maximize, minimize box & exit button is not visible so,

	*** always keep an way to exit
	*** (ignore if you don't want to use select text feature) to select text on
		screen enable processed input (which is usually enabled by default, mind
		it only if you are using mouse) and press ctrl + a then click on the text
		to select
	*** closing or minimizing of the window can be done from its icon in task bar

	returns nonzero for success, 0 for failure
*/

int disable_window_menu()
{
	HWND consoleWindow = GetConsoleWindow();

	return SetWindowLongPtr(consoleWindow, GWL_STYLE, GetWindowLong(consoleWindow, GWL_STYLE) & ~WS_SYSMENU);
}

int enable_window_menu()
{
	HWND consoleWindow = GetConsoleWindow();

	return SetWindowLongPtr(consoleWindow, GWL_STYLE, GetWindowLong(consoleWindow, GWL_STYLE) | WS_SYSMENU);
}





/*
	to change the title of the console window
*/

#ifndef set_window_title
#define set_window_title SetConsoleTitle
#endif // set_window_title





/*use it to take the backup of the name of the console window and later set it as current name*/

void backup_console_title(bool take_backup)
{
	static TCHAR name[MAX_PATH + 1] = {0};

	if(take_backup)
    	GetConsoleTitle(name, MAX_PATH);
	else
		SetConsoleTitle(name);
}





/*use it to take the backup of the mode of the console window and later set it as current mode*/

void backup_console_i_p_mode(HANDLE hi_pconsole, bool take_backup)
{
	static DWORD mode;

	if(take_backup)
    	GetConsoleMode(hi_pconsole, &mode);
	else
		SetConsoleMode(hi_pconsole, mode);
}

void backup_console_o_p_mode(HANDLE ho_pconsole, bool take_backup)
{
	static DWORD mode;

	if(take_backup)
    	GetConsoleMode(ho_pconsole, &mode);
	else
		SetConsoleMode(ho_pconsole, mode);
}





/*use it to take the backup of the cursor of the console window and later set it as current cursor*/

void backup_console_cursor(HANDLE ho_pconsole, bool take_backup)
{
	static CONSOLE_CURSOR_INFO cursorInfo;

	if(take_backup)
    	GetConsoleCursorInfo(ho_pconsole, &cursorInfo);
	else
		SetConsoleCursorInfo(ho_pconsole, &cursorInfo);
}





/*use it to take the backup of the size of the console window and later set it as current size*/

void backup_console_screen_buffer_and_window_size(HANDLE ho_pconsole, bool take_backup)
{
	static CONSOLE_SCREEN_BUFFER_INFO cinfo;

	if(take_backup)
    	GetConsoleScreenBufferInfo(ho_pconsole, &cinfo);
	else
	{
		create_console_window(cinfo.dwSize.Y, cinfo.dwSize.X);

		SMALL_RECT m_rectWindow = cinfo.srWindow;

		SetConsoleWindowInfo(ho_pconsole, TRUE, &m_rectWindow);
	}
}




/*use it to take the backup of the mode of the console window and later set it as current mode*/

void backup_window_properties(bool take_backup)
{
	static LONG property;

	if(take_backup)
    {
		property = GetWindowLong(GetConsoleWindow(), GWL_STYLE);
	}
	else
	{
		SetWindowLongPtr(GetConsoleWindow(), GWL_STYLE, property);
	}
}




/*use it to take the backup of the font of the o/p console buffer and later set it as current font*/

bool backup_console_font(HANDLE ho_pconsole, bool take_backup)
{
	// Set the font size now that the screen buffer has been assigned to the console

	static CONSOLE_FONT_INFOEX cfi;

	if(take_backup)
    {
		cfi.cbSize = sizeof(cfi);

		// getting current font info

		if (!GetCurrentConsoleFontEx(ho_pconsole, false, &cfi))
			return 0;	/*fail*/
	}
	else
	{
		// setting current font info

		if (!SetCurrentConsoleFontEx(ho_pconsole, false, &cfi))
			return 0;	/*fail*/
	}

	return 1;	/*success*/
}




/*takes backup of everything*/

void total_backup(HANDLE hi_pconsole, HANDLE ho_pconsole, bool take_backup)
{
	backup_console_title(take_backup);

	backup_console_i_p_mode(hi_pconsole, take_backup);

	backup_console_o_p_mode(ho_pconsole, take_backup);

	backup_console_cursor(ho_pconsole, take_backup);

	backup_window_properties(take_backup);

	backup_console_font(ho_pconsole, take_backup);

	backup_console_screen_buffer_and_window_size(ho_pconsole, take_backup);
}





#define total_backup_std(take_backup) total_backup(GetStdHandle(STD_INPUT_HANDLE), GetStdHandle(STD_OUTPUT_HANDLE), (take_backup))

/*
	place it at the starting point of a console program,
	especially if it changes the size and properties of
	the console window
*/

#define take_backup_and_start do{total_backup_std(1); system("cls"); total_backup_std(0);} while(0)

#define take_backup do{total_backup_std(1);} while(0)

/*
	place it at the ending point of a console program,
	especially if it changes the size and properties of
	the console window to restore the console window to
	its initial form
*/

#define put_backup_and_end do{FLUSH_CONSOLE_INPUT_BUFFER; system("cls"); total_backup_std(0); exit(0);} while(0)

#define put_backup do{FLUSH_CONSOLE_INPUT_BUFFER; system("cls"); total_backup_std(0);} while(0)



/*
	change the mode of the console so that
	it can take mouse input without affecting
	its ability to take processed input as used
	in conventional c / c++

	use it only if you want to use mouse_keyboard_input
	as getch(), i.e., to take text i/p or if any type
	of text input is to be taken in the program with
	standard c/c++ input functions that uses stdin
*/

#define USE_MOUSE_WITH_PROCESSED_INPUT (SetConsoleMode(GetStdHandle(STD_INPUT_HANDLE), ENABLE_PROCESSED_INPUT | ENABLE_INSERT_MODE | ENABLE_LINE_INPUT | ENABLE_ECHO_INPUT | ENABLE_EXTENDED_FLAGS | ENABLE_WINDOW_INPUT | ENABLE_MOUSE_INPUT))





/*
	change the mode of the console so that
	it can take mouse input but cannot take processed input as used
	in conventional c / c++, the i/ps taken
	will only be characters and no extra processing
	will be done on them like ctrl + c won't have
	any extra meaning, enter will be taken as '\r' carriage return
	so standard i/p functions of C/c++ which uses stdin won't work

	use it if you need only the character
*/

#define USE_MOUSE_WITH_UNPROCESSED_INPUT (SetConsoleMode(GetStdHandle(STD_INPUT_HANDLE), ENABLE_INSERT_MODE | ENABLE_LINE_INPUT | ENABLE_ECHO_INPUT | ENABLE_EXTENDED_FLAGS | ENABLE_WINDOW_INPUT | ENABLE_MOUSE_INPUT))





/*
	***** attention *****

	before using this function call any of the USE_MOUSE_... macro defined above
	as per requirement, most preferably before each call to this function,

	otherwise this function won't work

	*********************

	gives the current position of the mouse cursor in the screen
	using call by value method

	*x will contain the X coordinate of the mouse cursor

	*y will contain the Y coordinate of the mouse cursor

	the two holding macros can be used with it

	never flush the console i/p buffer before calling it

	if there is no i/p event then it waits for the next i/p event

	mouse_kbhit() can be used with it
*/

void mouse_cursor_pos(short *xout, short *yout)
{
	HANDLE m_hConsoleIn = GetStdHandle(STD_INPUT_HANDLE);

	static short x = 0, y = 0;

	// Handle Mouse Input - Check for window events

	INPUT_RECORD inBuf;

	DWORD events = 0, read_event;

	GetNumberOfConsoleInputEvents(m_hConsoleIn, &events);

	// taking the latest position of the mouse cursor by checking all the events till now

	for (DWORD i = 0; i < events; i++)
	{
		ReadConsoleInput(m_hConsoleIn, &inBuf, 1, &read_event);

		if(inBuf.EventType == MOUSE_EVENT && inBuf.Event.MouseEvent.dwEventFlags == MOUSE_MOVED)	// read only mouse events
		{
			x = inBuf.Event.MouseEvent.dwMousePosition.X;

			y = inBuf.Event.MouseEvent.dwMousePosition.Y;
		}
	}

	// if no mouse event is found then store the previous data

	*xout = x;

	*yout = y;
}





//========================================================

//******** starting of key press detection module ********

//========================================================

// returns 1 if the key is just pressed else 0

#define is_pressed(vcode) (keystate[(vcode)].newstate && !keystate[(vcode)].oldstate)

// returns 1 if the key is pressed and held down else 0

#define is_held(vcode) (keystate[vcode].newstate)

// returns in seconds how long it was held down (floating point no.)

#define how_long_down(vcode) (keystate[vcode].timedown)

// returns in seconds how long it was up (floating point no.)

#define how_long_up(vcode) (keystate[vcode].timeup)

// returns 1 if the key is just released else 0

#define is_released(vcode) (!keystate[vcode].newstate && keystate[vcode].oldstate)

/*
	to store the state of all the keys to get the state of a
	particular key or multiple keys

	first call key_detect() function

	then get the state of that key by passing its virtual key code
	to the macros

	is_pressed(vcode)

	is_held(vcode)

	how_long_down(vcode)

	how_long_up(vcode)

	is_released(vcode)

	to know its current state

	to flush or clear all previous key states
	call flush_key_state() function
*/

typedef struct KEYSTATE
{
	/*
		the current and old state of the key is:-

		1 the key down

		0 the key up
	*/

	int vk_code;	// virtual key code

	bool newstate, oldstate;

	double timedown;	// how long this key was held down

	double timeup;	// how long this key was up till the first call of key_detect() after flush_key_state()

	/*
		t0 is the no. of clocks when the state
		of the key was changed for the last time
	*/

	double t0;
} KEYSTATE;

/*
	as we are using global data so we take care to
	eleminate unnecessary wastage of space so we use
	dynamic array which will be created right when
	required

	and will be deleted by flush_key_state() when not in use
*/

KEYSTATE *keystate = NULL;	// to store general key state

int size_of_keystate_array;	// to store the size of keystate array

// to flush all key states and free allocated memory

void flush_key_state()
{
	free(keystate); keystate = NULL;

	size_of_keystate_array = 0;
}

/*
	this macro can be used to initialize buffer of
	key_detect() before using it with required keys
	only, then we can simply call key_detect() and
	use the array index in the place of virtual key
	code with the above macros to do their job

	this case only those keys will be scaned so, its
	more efficient
*/

#define initialize_key_detect(...) do{\
	int arr[] = {__VA_ARGS__};\
	size_of_keystate_array = sizeof_static_array(arr);\
	if(keystate)/*if keystate array is not empty make it empty*/\
		free(keystate);\
	keystate = (KEYSTATE *) calloc(size_of_keystate_array, sizeof(KEYSTATE));\
	if(!keystate)\
		error_exit("!!!! Failed to allocate memory for initialize_key_detect macro");\
	loopascnd(0, size_of_keystate_array - 1, 1)\
		keystate[i1].vk_code = arr[i1];\
} while(0)

// detects the states of the keys and stores info in keystate array

void key_detect()
{
	// allocating space for required global data

	if(!keystate)
	{
		keystate = (KEYSTATE *) calloc(256, sizeof(KEYSTATE));

		if(!keystate)
			error_exit("!!!! Failed to allocate memory for initialize_key_detect macro");

		loopascnd(0, 255, 1)
			keystate[i1].vk_code = i1;

		size_of_keystate_array = 256;
	}

	// check for the states of 256 virtual keys

	for (int i = 0; i < size_of_keystate_array; i++)
	{
		if(!keystate[i].t0)
			keystate[i].t0 = clock();

		keystate[i].oldstate = keystate[i].newstate;

		keystate[i].newstate = (GetKeyState(keystate[i].vk_code) & 0x8000) ? 1 : 0;

		if(keystate[i].newstate == keystate[i].oldstate)
		{
			/*
				if current state is = old state then the key or button is
				neither pressed nor released
			*/

			// counting how long has been since this key was pressed or released

			/*
				if the key is held down so update time of
				timedown keeping timeup unchanged

				if the key is up so update time of timeup
				keeping timedown unchanged
			*/

			if(is_held(i))
				keystate[i].timedown = ((double)(clock() - keystate[i].t0) / CLOCKS_PER_SEC);
			else
				keystate[i].timeup = ((double)(clock() - keystate[i].t0) / CLOCKS_PER_SEC);

			//((is_held(i)) ? keystate[i].timedown : keystate[i].timeup) = ((double)(clock() - keystate[i].t0) / CLOCKS_PER_SEC);
		}
		else
		{
			// the button is either just pressed or released

			/*
				as the key state changes,

				keystate[i].t0 is initialised to current no. of cpu clock tics
			*/

			keystate[i].t0 = clock();
		}
	}
}

//======================================================

//******** ending of key press detection module ********

//======================================================





/*
	prints the basic console mouse cursor on the screen

	x, y: coordinates of the mouse cursors current position

	original_attribute: original attribute of the previous position of the cursor

	cursor_attribute: attribute of the cursor
*/

void cursor_prnt(short x, short y, WORD original_attribute, WORD cursor_attribute)
{
	static short xp, yp;

	/*
		basically the concept of printing a cursor is that
		the attribute of that place is swapped with some other
		attribute when the mouse cursor in on it later it is
		swapped back to it proper attribute when cursor goes
		to other position
	*/

	/*
		if the position of the cursor changes restoring the text
		color and background color of the previous cursor position
	*/

	if(xp != x || yp != y)
	{
		textcolor_with_background_pos(xp, yp, original_attribute, 0);

		// at the position of cursor we are changing the text color and background color

		textcolor_with_background_pos(x, y, cursor_attribute, 0);

		xp = x; yp = y;	// backup of previous cursor position
	}
}





/*
	clears the console input buffer call it before calling
	mouse_keyboard_input() if you need to clear console
	input buffer calling it
*/

#define FLUSH_CONSOLE_INPUT_BUFFER FlushConsoleInputBuffer(GetStdHandle(STD_INPUT_HANDLE))





/*
	mouse_keyboard_input():-

	***** attention *****

	before using this function call any of the USE_MOUSE_... macro defined above
	as per requirement, most preferably before each call to this function,

	otherwise this function won't work

	*********************

	this function is for dedicated keyboard and mouse management
	in console application made with c/c++

	what it does?

	after being called this function returns when there is a key
	board or mouse event, i.e., it can detect any given keyboard
	or mouse input after calling it and returns some value that
	says what has happened

	it returns 1 if any mouse input is given or 0 if any keyboard
	input is given

	*** and rest of the data are returned by call by value

	for keyboard inputs:-

	they will store

	*character: unicode value of the key pressed

	*key_state: it stores, if the key is pressed (1), held (2), released (0)

	for mouse inputs:-

	they will store

	*x: the x coordinate of the mouse cursor

	*y: the y coordinate of the mouse cursor

	*key_state: it stores, if any mouse button is pressed (1), released (0), pressed for double click(3)

	*complete_click_detect: it store 1 if the mouse button click or key press
	is complete key press i.e., there will be no i/p events between key or
	mouse button press and release, it must be checked when the key or button is
	released i.e., key_state is 0 to detect complete complete key press the code
	should be (!key_state && !complete_click_detect) if true it was complete key
	press else it isn't

	the i/p events that can ruin a complete key press

	- any mouse button press or key press
	- movement of mouse cursor beyond the character on which the key or button was
	pressed

	*mouse_button: 	indicate the mouse button that is pressed or released
					0 for left button
					1 for middle button
					2 for right button

	*mouse_move: the function to return whenever the mouse is moves and stores true(1)
	from x, y we can get the current position of mouse cursor, stores false(0) if the
	function stops due to other event

	*mouse_wheel: whenever the mouse wheel moves the function returns it its not a
	NULL pointer then it takes NO_MOVE, UP, DOWN (for vertical mouse wheel), LEFT,
	RIGHT (for horizontal mouse wheel) indicating the movement of the mouse wheels
	we can disable it by giving false(0) as formal attribute

	*double_ckick_detect: it is 1 if the key is double clicked and if that particular
	key is released after being double clicked

	other common o/p attributes:-

	*virtual_key_code: stores the virtual key code of the input button or key

	*control_key_state: current state of the control keys (usually not used)

	*** notes:

	if you want to use as getch then take the key input when the keystate is
	geater than 0, in this mode you can call any input function that doesn't
	take input from console i.e., uses standard input buffer (stdin) in between
	two successive calls to this function

	if you want to use the key hold feature then either take the input when
	the key is released (may use complete key press feature) or don't use any
	input function that doesn't take input from console i.e., uses standard
	input buffer (stdin) in between two successive calls to this function as
	while using standard input functions all the i/ps goes to stdin buffer none
	of them reaches console input buffer not even a mouse click or mouse movement

	Keyboard input events are generated when any key, including control keys,
	is pressed or released. However, the ALT key when pressed and released
	without combining with another character, has special meaning to the
	system and is not passed through to the application. Also, the CTRL+C key
	combination is not passed through if the input handle is in processed mode
	(ENABLE_PROCESSED_INPUT).

	to clear console input buffer call FLUSH_CONSOLE_INPUT_BUFFER

	if we need to clear all previous mouse key states call flush_mouse_key_state()
	!!!! please note that if flush_mouse_key_state() and mouse_keyboard_input() is
	!!!! called simultaneously while some keys or mouse buttons are pressed down then
	!!!! mouse_keyboard_input()'s o/p won't be accurate.

	while using this function to take mouse input make sure that only one
	mouse button is pressed at a time

	if any of the o/p attributes are not required to be used then give NULL or
	0 as the formal argument to disable it

	while designing a menu driven console app using it follow the examples

	this can be used for other type of apps also

	so to while using it if we need to hold control at a place we use

	hold_while_key_pressed(nVirtKey)

	hold_before_key_pressed(nVirtKey)

	take care to notice if we need to use flush_mouse_key_state() after them

	this holding process can be done by mouse_keyboard_input() function also

	help:-

	to detect mouse click and key press check the example: GUI_MENU_TST.C,
	CONSOLE_MOUSE_CURSOR.C, GUI_NUMPAD_TST.C

	to use it place it inside a for loop and take the desired i/p and then break

	for(;;)	// loop to take i/p
	{
		if(mouse_keyboard_input(...valid argumemts...))	// getting the i/p data
		{
			---- mouse event operations ----
			---- break if desired i/p comes ----
		}
		else
		{
			---- keyboard event operations ----
			---- break if desired i/p comes ----
		}
	}
*/

// global data required

/*
	dynamic arrays:-

	button_press:-

	0 = button not pressed, 1 = button pressed

	index 0 for l_button, 1 for m_button, 2 for r_button,

	key_press:-

	similar to button_press, but has place for
	65536 unicode characters

	they are used to indicate if the key or button is just
	pressed or released or held down
*/

bool *button_press = NULL, *key_press = NULL;

// stores the previous general state of the mouse buttons

char previous_button_state_backup = 0;

// to store the previous cursor posiition used to initialise x, y

short back_up_mouse_cursor_position_X = -1, back_up_mouse_cursor_position_Y = -1;

/*
	COMPLETE_KB_PRESS is used to detect a complete key or mouse button press

	i.e., there will be no i/p events between key or mouse button press and
	release

	how its done:-

	-if mouse moves COMPLETE_KB_PRESS = 0
	 return 0

	-if the key or the button is just pressed COMPLETE_KB_PRESS = virtual key code of it
	 return 0

	-if the key or the button is just released:-

	 if(COMPLETE_KB_PRESS == virtual key code of it)
	  return 1

	 if(COMPLETE_KB_PRESS != virtual key code of it)
	  return 0

	 COMPLETE_KB_PRESS = 0

	the return process is done in call by value method when required
*/

unsigned char COMPLETE_KB_PRESS = 0;

/*
	if the current click is a double click then its bits will indicate it

	1st LSB is for left button

	2nd LSB is for middle button

	3rd LSB is for right button

	these bits are 1 if corresponding button is double clicked and they are
	made 0 when that button is released
*/

unsigned char double_click = 0;

// to free and flush key and button states to be used with mouse_keyboard_input()

void flush_mouse_key_state()
{
	// do not flush console i/p buffer

	//FLUSH_CONSOLE_INPUT_BUFFER;

	free(button_press); button_press = NULL;

	free(key_press); key_press = NULL;

	previous_button_state_backup = 0;

	// set the backup cursor position to (-1, -1) an invalid position

	back_up_mouse_cursor_position_X = back_up_mouse_cursor_position_Y = -1;

	// 0 is not the virtual key code of any key

	COMPLETE_KB_PRESS = 0;

	// initially there should not be any double click

	double_click = 0;
}

// data type to give mouse wheel movement

typedef enum MOUSE_WHEEL_MOVEMENT {NO_MOVE, UP, DOWN, LEFT, RIGHT} MOUSE_WHEEL_MOVEMENT;

#ifndef MOUSE_HWHEELED	// it should be defined in windows.h but if not then we do it

#define MOUSE_HWHEELED 0x0008

#endif // MOUSE_HWHEELED

/*
	last update:

	formal argument *character is now of WCHAR type

	key_press array will not be allocated if *character is 0

	if *character is 0 key event is not studied

	it is now more memory efficient than before
*/

bool mouse_keyboard_input(short *x, short *y, char *mouse_button, bool *mouse_move, char *mouse_wheel, bool *double_ckick_detect/*mouse*/, WCHAR *character/*key board*/, char *key_state, bool *complete_click_detect, int *virtual_key_code, DWORD *control_key_state/*common*/)
{
	HANDLE m_hConsoleIn = GetStdHandle(STD_INPUT_HANDLE);

	// Handle Mouse Input - Check for window events

	INPUT_RECORD inBuf;

	DWORD events = 0;

	// allocating space for global data

	if(!button_press)
	{
		button_press = (bool *) calloc (3, sizeof(bool));

		if(!button_press)
			error_exit("!!!! Failed to allocate memory for mouse_keyboard_input function (button_press)");
	}

	if(!key_press && character)
	{
		key_press = (bool *) calloc (65536, sizeof(bool));

		if(!key_press)
			error_exit("!!!! Failed to allocate memory for mouse_keyboard_input function (key_press)");
	}

	// initializing o/p carriers before storing new data in them

	if(character)
		*character = 0;

	if(x)
		*x = back_up_mouse_cursor_position_X;

	if(y)
		*y = back_up_mouse_cursor_position_Y;

	if(mouse_button)
		*mouse_button = -1;

	if(virtual_key_code)
		*virtual_key_code = 0;

	if(key_state)
		*key_state = -1;

	if(mouse_wheel)
		*mouse_wheel = 0;

	if(mouse_move)
		*mouse_move = 0;

	if(double_ckick_detect)
		*double_ckick_detect = 0;

	if(complete_click_detect)
		*complete_click_detect = 0;

	/*
		Handle events - we only care about mouse clicks (single clicks) and key presses
	*/

	for(;;)
	{
		ReadConsoleInput(m_hConsoleIn, &inBuf, 1, &events);	// reading one mouse or keyboard event

		switch (inBuf.EventType)
		{
			case KEY_EVENT:

						//putchar(inBuf.Event.KeyEvent.uChar.UnicodeChar);

						// control comes here if a key is pressed, down or released

						if(character)
								*character = inBuf.Event.KeyEvent.uChar.UnicodeChar;
						else
							continue;	// if user doesn't want key i/p don't go ahead

						if(virtual_key_code)
								*virtual_key_code = inBuf.Event.KeyEvent.wVirtualKeyCode;

						if(inBuf.Event.KeyEvent.bKeyDown)
						{
							/*
								if the key is down, but it is found that it was not newly pressed
								i.e., key_press[inBuf.Event.KeyEvent.uChar.UnicodeChar] is 1

								then store 2 in *key_state

								else store 1
							*/

							if(!key_press[inBuf.Event.KeyEvent.uChar.UnicodeChar])
							{
								// if the key is just pressed store its virtual key code into COMPLETE_KB_PRESS

								COMPLETE_KB_PRESS = inBuf.Event.KeyEvent.wVirtualKeyCode;	// collecting data for complete key press
							}

							if(key_state)
								*key_state = (key_press[inBuf.Event.KeyEvent.uChar.UnicodeChar]) ? 2 : 1;

							key_press[inBuf.Event.KeyEvent.uChar.UnicodeChar] = 1;
						}
						else
						{
							/*
								if the key is released then make key_press[inBuf.Event.KeyEvent.uChar.UnicodeChar]
								and *key_state 0 to indicate that it's up
							*/

							if(key_state)
								*key_state = 0;

							key_press[inBuf.Event.KeyEvent.uChar.UnicodeChar] = 0;

							// if the key is just released

							if(COMPLETE_KB_PRESS == inBuf.Event.KeyEvent.wVirtualKeyCode)
							{
								// if its virtual key code == that stored in COMPLETE_KB_PRESS complete key press detected

								if(complete_click_detect)
									*complete_click_detect = 1;
							}
							else
							{
								// if its virtual key code != that stored in COMPLETE_KB_PRESS complete key press not detected

								if(complete_click_detect)
									*complete_click_detect = 0;
							}

							COMPLETE_KB_PRESS = 0;
						}

						//printf("\n\t%c %d\t", inBuf.Event.KeyEvent.uChar.UnicodeChar, key_press[inBuf.Event.KeyEvent.uChar.UnicodeChar]);

						if(control_key_state)
								*control_key_state = inBuf.Event.KeyEvent.dwControlKeyState;

						return 0;

			case MOUSE_EVENT:

						switch (inBuf.Event.MouseEvent.dwEventFlags)
						{
							case MOUSE_HWHEELED:

								if(mouse_wheel)
								{
									// if we need mouse wheel movement information

									//printf("\n\n\t%d\t", inBuf.Event.MouseEvent.dwButtonState);

									/*
										if inBuf.Event.MouseEvent.dwButtonState is +ve the wheel
										is rotated roght , it its -ve then the wheel is rotated left
									*/

									*mouse_wheel = ((int)inBuf.Event.MouseEvent.dwButtonState >= 0L) ? RIGHT : LEFT;
								}

								break;

							case MOUSE_WHEELED:

								if(mouse_wheel)
								{
									// if we need mouse wheel movement information

									//printf("\n\n\t%d\t", inBuf.Event.MouseEvent.dwButtonState);

									/*
										if inBuf.Event.MouseEvent.dwButtonState is +ve the wheel
										is rotated forward away from the user, it its -ve then
										the wheel is rotated backward towards the user
									*/

									*mouse_wheel = ((int)inBuf.Event.MouseEvent.dwButtonState >= 0L) ? DOWN : UP;
								}

								break;

							case MOUSE_MOVED:

								//putchar('#');

								if(back_up_mouse_cursor_position_X != inBuf.Event.MouseEvent.dwMousePosition.X || back_up_mouse_cursor_position_Y != inBuf.Event.MouseEvent.dwMousePosition.Y)
								{
									// if mouse is moved to another character position store 0 into COMPLETE_KB_PRESS, its no longer a complete key press

									COMPLETE_KB_PRESS = 0;	// collecting data for complete key press
								}

								// taking backup of current mouse cursor position

								back_up_mouse_cursor_position_X = inBuf.Event.MouseEvent.dwMousePosition.X;

								back_up_mouse_cursor_position_Y = inBuf.Event.MouseEvent.dwMousePosition.Y;

								// updating the position of the mouse cursor on the screen

								if(x)
									*x = inBuf.Event.MouseEvent.dwMousePosition.X;

								if(y)
									*y = inBuf.Event.MouseEvent.dwMousePosition.Y;

								if(mouse_move)
								{
									// if we need mouse movement information

									*mouse_move = 1;
								}

								break;

							case DOUBLE_CLICK:

								//printf("\n--- 0 ---\n\n");

								/*
									double click and single click are considered almost same
									for double click *key_state will store 3

									and double_ckick_detect is 1 to indicate a double click
									has occurred
								*/

								double_click |= 8;	// making 4th LSB 1 to indicate a double click has occurred

								if(double_ckick_detect)
									*double_ckick_detect = 1;

								if(key_state)
									*key_state = 3;

							case 0:

								// control comes here if mouse button is pressed or released, not while holding

								// getting the virtual key code, key state, and no. of the button

								//printf("\n\n\t%x\t", inBuf.Event.MouseEvent.dwButtonState);

								//printf("\n\n\t%x\t", previous_button_state_backup);

								switch(inBuf.Event.MouseEvent.dwButtonState ^ previous_button_state_backup) // this gives the button in question
								{
									case FROM_LEFT_1ST_BUTTON_PRESSED:

												// Left button

												if(mouse_button)
													*mouse_button = 0;

												if(virtual_key_code)
													*virtual_key_code = VK_LBUTTON;

												// if the button is already pressed

												if(button_press[0])
													button_press[0] = 0;	// release it
												else
													button_press[0] = 1;	// press it

												if(button_press[0])
												{
													// if the key is just pressed store its virtual key code into COMPLETE_KB_PRESS

													if(double_click & 8)	// if it was a double click store key value
														double_click = (double_click & ~8) | 1;

													COMPLETE_KB_PRESS = VK_LBUTTON;	// collecting data for complete key press
												}
												else
												{
													// if the key is just released

													if(double_click & 1)	// if the double clicked button is released
													{
														double_click &= ~1;	// turn off 1st bit

														if(double_ckick_detect)
															*double_ckick_detect = 1;
													}

													if(COMPLETE_KB_PRESS == VK_LBUTTON)
													{
														// if its virtual key code == that stored in COMPLETE_KB_PRESS complete key press detected

														if(complete_click_detect)
															*complete_click_detect = 1;
													}
													else
													{
														// if its virtual key code != that stored in COMPLETE_KB_PRESS complete key press not detected

														if(complete_click_detect)
															*complete_click_detect = 0;
													}

													COMPLETE_KB_PRESS = 0;
												}

												if(key_state && *key_state != 3)
													*key_state = button_press[0];

												break;

									case FROM_LEFT_2ND_BUTTON_PRESSED:

												// middle button

												if(mouse_button)
													*mouse_button = 1;

												if(virtual_key_code)
													*virtual_key_code = VK_MBUTTON;

												// if the button is already pressed

												if(button_press[1])
													button_press[1] = 0;	// release it
												else
													button_press[1] = 1;	// press it

												if(button_press[1])
												{
													// if the key is just pressed store its virtual key code into COMPLETE_KB_PRESS

													if(double_click & 8)	// if it was a double click store key value
														double_click = (double_click & ~8) | 2;

													COMPLETE_KB_PRESS = VK_MBUTTON;	// collecting data for complete key press
												}
												else
												{
													// if the key is just released

													if(double_click & 2)	// if the double clicked button is released
													{
														double_click &= ~2;	// turn off 2nd bit

														if(double_ckick_detect)
															*double_ckick_detect = 1;
													}

													if(COMPLETE_KB_PRESS == VK_MBUTTON)
													{
														// if its virtual key code == that stored in COMPLETE_KB_PRESS complete key press detected

														if(complete_click_detect)
															*complete_click_detect = 1;
													}
													else
													{
														// if its virtual key code != that stored in COMPLETE_KB_PRESS complete key press not detected

														if(complete_click_detect)
															*complete_click_detect = 0;
													}

													COMPLETE_KB_PRESS = 0;
												}

												if(key_state && *key_state != 3)
													*key_state = button_press[1];

												break;

									// in a 3 button mouse we usually don't have these buttons

									case FROM_LEFT_3RD_BUTTON_PRESSED: break;

									case FROM_LEFT_4TH_BUTTON_PRESSED: break;

									case RIGHTMOST_BUTTON_PRESSED:

												// right button

												if(mouse_button)
													*mouse_button = 2;

												if(virtual_key_code)
													*virtual_key_code = VK_RBUTTON;

												// if the button is already pressed

												if(button_press[2])
													button_press[2] = 0;	// release it
												else
													button_press[2] = 1;	// press it

												if(button_press[2])
												{
													// if the key is just pressed store its virtual key code into COMPLETE_KB_PRESS

													if(double_click & 8)	// if it was a double click store key value
														double_click = (double_click & ~8) | 4;

													COMPLETE_KB_PRESS = VK_RBUTTON;	// collecting data for complete key press
												}
												else
												{
													// if the key is just released

													if(double_click & 4)	// if the double clicked button is released
													{
														double_click &= ~4;	// turn off 3rd bit

														if(double_ckick_detect)
															*double_ckick_detect = 1;
													}

													if(COMPLETE_KB_PRESS == VK_RBUTTON)
													{
														// if its virtual key code == that stored in COMPLETE_KB_PRESS complete key press detected

														if(complete_click_detect)
															*complete_click_detect = 1;
													}
													else
													{
														// if its virtual key code != that stored in COMPLETE_KB_PRESS complete key press not detected

														if(complete_click_detect)
															*complete_click_detect = 0;
													}

													COMPLETE_KB_PRESS = 0;
												}

												if(key_state && *key_state != 3)
													*key_state = button_press[2];

												break;
								}

								// storing the previous state before returning

								previous_button_state_backup = inBuf.Event.MouseEvent.dwButtonState;

								break;

							default: continue;
						}

						if(control_key_state)
							*control_key_state = inBuf.Event.MouseEvent.dwControlKeyState;

						return 1;
		}
	}
}





/*
	***** attention *****

	before using this function call any of the USE_MOUSE_... macro defined above
	as per requirement, most preferably before each call to this function,

	otherwise this function won't work

	*********************

	gives 0 if no i/p event has occurred else gives 1 value

	general form:-

	int main()
	{
		----- statements -----

		flush_mouse_key_state();	// use it here if required to reset mouse key state

		for(;;)
		{
			----- statements -----

			if(mouse_kbhit(1, 1) != 0)	// both mouse and key
			{
				// if there is an i/p event

				if(mouse_keyboard_input(...valid argumemts...))	// getting the i/p data
				{
					---- mouse event operations ----
				}
				else
				{
					---- keyboard event operations ----
				}
			}

			// if no i/p events

			----- statements -----
		}

		return 0;
	}

	while using this format mouse_keyboard_input() will be executed only when there is
	any i/p event else it causes the execution of the other parts of the loop body repeatedly

	this operates similar to kbhit() from conio.h

	and mouse_keyboard_input(...) is similar to getch()

	mouse: if 1 return at mouse events

	key: if 1 return at keyboard events
*/

bool mouse_kbhit(bool mouse, bool key)
{
	HANDLE m_hConsoleIn = GetStdHandle(STD_INPUT_HANDLE);

	// Handle Mouse Input - Check for window events

	INPUT_RECORD inBuf;

	DWORD events = 0;

	GetNumberOfConsoleInputEvents(m_hConsoleIn, &events);

	if(!events)	// if no events found
		return 0;

	PeekConsoleInput(m_hConsoleIn, &inBuf, 1, &events);	// reading one mouse or keyboard event)

	if(mouse && inBuf.EventType == MOUSE_EVENT || key && inBuf.EventType == KEY_EVENT)
		return 1;	// if the event is a mouse or key board event
	else
		ReadConsoleInput(m_hConsoleIn, &inBuf, 1, &events);	// discarding other event

	return 0;
}





/*
	this function can store time in 256 slots

	they may be used 256 buttons where the virtual keycode each key
	represents can be used to represent its slot

	or they can be used for other purposes also

	slot: slot no. of the slot whose time is asked

	reset: reset a particular slot if 1

	resetall: reset all slot

	if called with resetall = 1 it returns 0
	if resetall is 0 then it always returns the time stored in that slot
	no matter the value of reset

	each slot basically keeps time since its last reset
*/

double time_count(unsigned char slot, bool reset, bool resetall)
{
	static double t0[256] = {0};	// slots for all key and buttons

	double time;

	if(resetall)
	{
		// reset all clock slots

		for(int i = 0; i < 256; i++)
			t0[i] = clock();

		return 0;
	}

	// return time in a particular slot

	time = (double)(clock() - t0[slot]) / CLOCKS_PER_SEC;

	if(reset)
	{
		// reset particular clock slot

		t0[slot] = clock();
	}

	return time;
}





// takes the virtual key code of a key and runs till its not released

#define hold_while_key_pressed(nVirtKey) for(; (GetKeyState(nVirtKey) & 0x8000);)





// takes the virtual key code of a key and runs till its not pressed

#define hold_before_key_pressed(nVirtKey) for(; !(GetKeyState(nVirtKey) & 0x8000);)





// takes the virtual key code of a key and tells if its pressed (1) or not (0)

#define single_key_detect(nVirtKey) (GetKeyState(nVirtKey) & 0x8000)





// pause a loop if the key nVirtKey is pressed to resume the loop press it again

#define put_Pause(nVirtKey) do{if(single_key_detect(nVirtKey)){hold_while_key_pressed(nVirtKey); hold_before_key_pressed(nVirtKey); hold_while_key_pressed(nVirtKey);}} while(0)

// !!!!! don't use above three macros if there is a console input function (except mouse_cursor_pos) in the code !!!!!
// to use with console input functions use the below two functions






/*
	takes the virtual key code of a key and runs till its not released

	return 1 for complete press 0 for not complete press
*/

// it is more efficient to give key_i_p_involved 0 is vkcode is always a mouse button as the memory for key states are not allocated

bool hold_while_key_pressed_con(int vkcode, bool key_i_p_involved)
{
	USE_MOUSE_WITH_UNPROCESSED_INPUT;

	int releasedchar;

	char key_state;

	bool ckp = 0;

	WCHAR ch;

	for(;;)
	{
		if(key_i_p_involved)
			mouse_keyboard_input(0, 0, 0, 0, 0, 0, &ch, &key_state, &ckp, &releasedchar, 0);
		else
			mouse_keyboard_input(0, 0, 0, 0, 0, 0, 0, &key_state, &ckp, &releasedchar, 0);

		if(!key_state && (vkcode == releasedchar))	// only if the pressed key is released
		{
			// when the mouse button or key is released break

			break;
		}
	}

	return ckp;
}





// takes the virtual key code of a key and runs till its not pressed
// it is more efficient to give key_i_p_involved 0 is vkcode is always a mouse button as the memory for key states are not allocated

void hold_before_key_pressed_con(int vkcode, bool key_i_p_involved)
{
	USE_MOUSE_WITH_UNPROCESSED_INPUT;

	int releasedchar;

	char key_state;

	WCHAR ch;

	for(;;)
	{
		if(key_i_p_involved)
			mouse_keyboard_input(0, 0, 0, 0, 0, 0, &ch, &key_state, 0, &releasedchar, 0);
		else
			mouse_keyboard_input(0, 0, 0, 0, 0, 0, 0, &key_state, 0, &releasedchar, 0);

		if(key_state == 1 && (vkcode == releasedchar))	// only if the pressed key is released
		{
			// when the mouse button or key is released break

			break;
		}
	}
}





// pause a loop if the key nVirtKey is pressed to resume the loop press it again

#define put_Pause_con(nVirtKey) do {if(mouse_kbhit(0, 1)){hold_while_key_pressed_con(nVirtKey); hold_before_key_pressed_con(nVirtKey); hold_while_key_pressed_con(nVirtKey);}} while(0)




#endif // CONHANDLING
