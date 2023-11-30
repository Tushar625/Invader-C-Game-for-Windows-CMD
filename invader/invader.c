#include<stdio.h>

#include<stdlib.h>

#include<conio.h>

#include<math.h>

#include"conhand.h"

#define WIDTH 64	// width of the field

#define HEIGHT 23	// height of the field

#define OFFSETX 5	 // must be >= 3

#define OFFSETY 4	// must be >= 3

// canon will be placed at HEIGHT + OFFSETY

#define DELAY_NUM 100

// prints the current score at proper position

#define PRNT_SCORE (textcolor(LIGHTGREEN), cursor(WIDTH + OFFSETX + 12, OFFSETY + 19), printf("%d", score))


// required user defined data types



// structure to store the y coordinate of a bullet in a circular linked list

typedef struct node
{
	int d;

	struct node *l;
}node;



/*
	keeps the y coordinate of all the bullets in a
	particular x column,

	there will be a circular linked list queue that will
	store the said y coordinates

	new bullets will be added from the end so for
	a particular time collision can be checked only
	with the last bullet, which is pointed by tailY -> l
*/

typedef struct bullet_node
{
	node *tailY;

	int i_l;
}bullet_node;



/*
	here all the intruders will be stored in a linked list

	this is the structure to store the x & y coordinates
	of a intruder in a linked list
*/

typedef struct intruders
{
	short x, y;

	struct intruders *l;
}intruders;



// required global data



bullet_node bullets[WIDTH] = {0};

intruders *invader = NULL, *dart = NULL;

int b_head = -1, score = 0;

short canon_x = WIDTH / 2 + OFFSETX, inveder_count = 0;



// required basic functions



/*
	creates a node containg data

	returns the address of the node

	if fails returns NULL
*/

node *get_circular_link_node(int data)
{
	node *temp;

	temp = (node *)malloc(sizeof(node));

	if(temp)
	{
		temp -> d = data;

		temp -> l = temp;
	}

	return temp;
}



/*
	adds a node at the front of the circular linked list pointed by tail

	returns 0 if success or 1 if failure
*/

bool addfront_circular(node **tail, int data)
{
	node *temp;

	temp = get_circular_link_node(data);

	if(temp)
	{
		if(!*tail)
			*tail = temp;
		else
		{
			temp -> l = (*tail) -> l;

			(*tail) -> l = temp;
		}

		return 0;
	}

	return 1;
}



/*
	adds a node at the end of the circular link list pointed by tail

	returns 0 if success or 1 if failure
*/

bool addend_circular(node **tail, int data)
{
	if(addfront_circular(tail, data))
		return 1;

	*tail = (*tail) -> l;

	return 0;
}



/*
	deletes and frees the node at the front of the circular link list
	pointed by tail

	returns 0 if success or 1 if failure
*/

bool delfront_circular(node **tail)
{
	if(*tail)
	{
		if(*tail == (*tail) -> l)
		{
			free(*tail);

			*tail = NULL;
		}
		else
		{
			node *temp;

			temp = (*tail) -> l;

			(*tail) -> l = temp -> l;

			free(temp);
		}

		return 0;
	}

	return 1;
}



/*
	creates a node containg data

	returns the address of the node

	if fails returns NULL
*/

intruders *get_link_node(short x, short y)
{
	intruders *temp;

	temp = (intruders *)malloc(sizeof(intruders));

	if(temp)
	{
		temp -> x = x;

		temp -> y = y;

		temp -> l = NULL;
	}

	return temp;
}



/*
	adds a node at the front of the link list pointed by start

	returns 0 if success or 1 if failure
*/

bool addfront(intruders **start, short x, short y)
{
	intruders *temp;

	temp = get_link_node(x, y);

	if(temp)
	{
		temp -> l = *start;

		*start = temp;

		return 0;
	}

	return 1;
}



// adding objects here



// adding bullets for a particular x and also printing it for the 1st time



void add_bullet(short x)
{
	x -= OFFSETX;

	//printf("%d", x);

	// if bullets[x].tailY is NULL then the bullet node is empty

	if(!bullets[x].tailY)
	{
		bullets[x].i_l = b_head;

		b_head = x;
	}

	addend_circular(&bullets[x].tailY, HEIGHT + OFFSETY - 1);

	cursor(x + OFFSETX, HEIGHT + OFFSETY - 1);

	textcolor(LIGHTGREEN);

	putchar(30);
}



// adding given no. of intruders and also printing them for the 1st time



void add_invaders(short num)
{
	for(; num; num--)
	{
		addfront(&invader, rand() % WIDTH + OFFSETX, OFFSETY);

		cursor(invader -> x, OFFSETY);

		textcolor(RED);

		putchar('#');

		inveder_count++;
	}
}



// adding a dart and also printing it for the 1st time



#define add_dart(x, y) (addfront(&dart, x, y), textcolor(MAGENTA), cursor(x, y), putchar(248))



// printing the display



/*
	printing the invaders and deleting them if needed

	returns 0 if game is not over

	returns 1 if game is over
*/

bool invader_print()
{
	intruders **curr, *temp;

	node *bullet_y;

	//srand(time(0));

	textcolor(RED);

	for(curr = &invader; *curr;)
	{
		/*
			(*curr) -> y is the y coordinate of the previous position
			which is checked for deletion and then y is updated and
			the next position is printed
		*/

		// checking if hits a bullet

		bullet_y = bullets[(*curr) -> x - OFFSETX] . tailY;

		/*
			if we have any bullet for that particular x then
			bullets[(*curr) -> x - OFFSETX] . tailY will not be NULL

			and is stored in bullet_y so, bullet_y will point to the
			last node of the list, as it is a circular linked list
			bullet_y -> l will give the first node of the list which
			is the node at the top of the x column and should be
			checked with (*curr) -> y
		*/

		if(bullet_y && (bullet_y -> l -> d == (*curr) -> y || bullet_y -> l -> d == (*curr) -> y + 1))
		{
			temp = *curr;

			*curr = (*curr) -> l;

			free(temp);

			score++;

			// printing updated score

			PRNT_SCORE;

			inveder_count--;

			textcolor(RED);

			continue;
		}

		// printing and updating y

		if(!(rand() % 14))
		{
			cursor((*curr) -> x, (*curr) -> y);

			putchar('+');

			// updating y and printing it

			(*curr) -> y++;

			cursor((*curr) -> x, (*curr) -> y);

			putchar('#');

			// game is over when invader reach the level of canon i.e., HEIGHT + OFFSETY

			if((*curr) -> y == HEIGHT + OFFSETY)
				return 1;
		}

		if(!(rand() % 50) || (canon_x == (*curr) -> x && !(rand() % 5)))
		{
			// add one dart in front of it and also print it

			add_dart((*curr) -> x, (*curr) -> y + 1);

			textcolor(RED);
		}

		curr = &(* curr) -> l;
	}

	return 0;
}



/*
	printing the darts and deleting them and the bullets if needed

	returns 0 if game is not over

	returns 1 if game is over
*/

bool dart_print()
{
	intruders **curr, *temp;

	node *bullet_y;

	int x;

	//srand(time(0));

	textcolor(MAGENTA);

	for(curr = &dart; *curr;)
	{
		/*
			(*curr) -> y is the y coordinate of the previous position
			which is checked for deletion and then y is updated and
			the next position is printed
		*/

		// the current position of dart is always cleared with space

		cursor((*curr) -> x, (*curr) -> y);

		putchar(' ');

		// if goes to the canon's level but fails to hit it, the dart is deleted

		if((*curr) -> y == HEIGHT + OFFSETY)
		{
			// game is over if dart hits the canon

			if((*curr) -> x == canon_x)
				return 1;

			temp = *curr;

			*curr = (*curr) -> l;

			free(temp);

			continue;
		}

		// checking dart hits a bullet

		bullet_y = bullets[(*curr) -> x - OFFSETX] . tailY;

		/*
			if we have any bullet for that particular x then
			bullets[(*curr) -> x - OFFSETX] . tailY will not be NULL

			and is stored in bullet_y so, bullet_y will point to the
			last node of the list, as it is a circular linked list
			bullet_y -> l will give the first node of the list which
			is the node at the top of the x column and should be
			checked with (*curr) -> y
		*/

		if(bullet_y && (bullet_y -> l -> d == (*curr) -> y || bullet_y -> l -> d == (*curr) -> y + 1))
		{
			// delete the bullet first

			cursor((*curr) -> x, bullet_y -> l -> d);

			putchar(' ');	// printing space over the bullet

			delfront_circular(&(bullets[(*curr) -> x - OFFSETX] . tailY));

			// now deleting the node

			temp = *curr;

			*curr = (*curr) -> l;

			free(temp);

			continue;
		}

		// updating y and printing current dart

		(*curr) -> y++;

		cursor((*curr) -> x, (*curr) -> y);

		putchar(248);

		// game is over when dart hits the canon

		if((*curr) -> y == HEIGHT + OFFSETY && (*curr) -> x == canon_x)
			return 1;

		curr = &((*curr) -> l);
	}

	return 0;
}



// printing bullets and deleting bullets or bullet nodes if necessary

void bullet_print()
{
	int *i;

	node *curr;

	textcolor(LIGHTGREEN);

	for(i = &b_head; *i != -1;)
	{
		curr = bullets[*i].tailY;

		// if the first bullet is at the top delete it and print ' ' on it

		if(curr && curr -> l -> d == OFFSETY)
		{
			cursor(*i + OFFSETX, curr -> l -> d);

			putchar(' ');

			delfront_circular(&(bullets[*i].tailY));
		}

		// if the bullets[*i].tailY is NULL then no bullet in this node so remove it from array linked list

		if(!bullets[*i].tailY)
		{
			*i = bullets[*i].i_l;

			continue;
		}

		// the control comes here if we have any bullets to print, printing them

		for(curr = bullets[*i].tailY -> l;; curr = curr -> l)
		{
			// clearing previous position of the bullet

			cursor(*i + OFFSETX, curr -> d);

			putchar(' ');

			// decrement the y to advance the bullet

			curr -> d--;

			// printing the new bullet

			cursor(*i + OFFSETX, curr -> d);

			putchar(30);

			if(curr == bullets[*i].tailY)
				break;
		}

		i = &bullets[*i].i_l;
	}
}



// cannon operator functions



// prints the cannon

void canon_print()
{
	// level 1:

	cursor(canon_x - 1, HEIGHT + OFFSETY);

	textcolor(LIGHTGREEN);

	printf(" %c ", 219);

	// level 2:

	cursor(canon_x - 2, HEIGHT + OFFSETY + 1);

	printf(" %c", 222);

	textcolor(LIGHTBLUE);

	printf("%c", 219);

	textcolor(LIGHTGREEN);

	printf("%c ", 221);

	// level 3:

	cursor(canon_x - 3, HEIGHT + OFFSETY + 2);

	printf(" %c", 222);

	textcolor(LIGHTBLUE);

	printf("%c%c%c", 219, 223, 219);

	textcolor(LIGHTGREEN);

	printf("%c ", 221);
}



// moves the cannon right or left

void move_canon(bool right)
{
	if(right && canon_x < WIDTH + OFFSETX - 1)
	{
		canon_x++;

		canon_print();
	}

	if(!right && canon_x > OFFSETX)
	{
		canon_x--;

		canon_print();
	}
}



// line & box printing functions



/*
	prints a given character ch, i times
*/

void char_prnt(short ch, int i)
{
	for(; i; i--)
		putchar(ch);
}



/*
	prints a given character ch, i times, vertically up or down

	from the position (x, y)

	if up nonzero prints up else prints down

	takes the cursor to the position down (for down) or up (for up)
	the printed line after its done
*/

void char_prnt_verti(short x, short y, short ch, int i, bool up)
{
	for(; i; i--, (up) ? (y--) : (y++))
	{
		cursor(x, y);

		putchar(ch);
	}

	cursor(x, y);
}



/*
	can print a nice box at the specified coordinates

	x, y, depth, width all must be 0 or +ve

	depth represents the no. of lines that can be written
	inside the box

	width represents the no. of characters that can be
	written in a single line inside the box

	returns 1 for failure

	returns 0 for success
*/

char nice_box(short x, short y, short depth, short width)
{
	// if any of the input arguments are wrong

	if(x < 0 || y < 0 || depth < 0 || width < 0)
		return 1;

	// first line:-

	cursor(x, y++);

	putchar(218);

	char_prnt(196, width);

	putchar(183);

	// middle lines:-

	for(; depth--;)
	{
		cursor(x, y);

		putchar(179);

		cursor((short)(x + width + 1), y++);

		putchar(186);
	}

	// last line:-

	cursor(x, y);

	putchar(212);

	char_prnt(205, width);

	putchar(188);

	return 0;
}



// status of the game

void status(char st)
{
	cursor(WIDTH + OFFSETX + 5, OFFSETY + 17);

	switch(st)
	{
		case 0: textcolor(RED); printf("--- Paused --- "); break;

		case 1: textcolor(LIGHTGREEN); printf("--- Playing ---"); break;

		case 2: textcolor(RED); printf("!! Destroyed !!"); break;

		case 3: textcolor(RED); printf("!! Defeated !! "); break;
	}
}



// game over message

void game_over()
{
	textcolor(YELLOW);

	cursor(WIDTH / 2 + OFFSETX + 4 - 20, OFFSETY + 10);

	printf("!!!! Game is Over, Press Enter !!!!");

	Beep(1500, 100);

	Beep(1500, 250);

	cursor(0, 0);
}



int main()
{
	take_backup_and_start;

	set_font_size_pixel(19, 9);

	set_window_pos(150, 50);

	create_console_window(32, 123);

	disable_window_resize();

	disable_window_menu();

	set_window_title("Space Invader by - Tushar Das (Prototype Version)");

	show_console_cursor(0);

	short n;

	short dly;

	bool p1, p2, p3, p4, p5;

	char fpsstr[71];

	srand(time(0));

	n = (short)pow(2, sizeof(short) * 8 - 1);

	// initial display module

	canon_print();

	textcolor(WHITE);

	cursor(OFFSETX - 3, OFFSETY - 1);

	putchar(201);

	char_prnt_verti(OFFSETX - 3, OFFSETY, 186, HEIGHT - 1, 0);

	putchar(200);

	nice_box(WIDTH + OFFSETX + 3, OFFSETY - 1, 22, 17);

	// INSTRUCTIONS

	// # 1

	cursor(WIDTH + OFFSETX + 4, OFFSETY + 1);

	textcolor(YELLOW);

	printf(" Press ESC");

	cursor(WIDTH + OFFSETX + 4, OFFSETY + 2);

	printf(" to Exit________");

	// # 2

	cursor(WIDTH + OFFSETX + 4, OFFSETY + 4);

	textcolor(LIGHTCYAN);

	printf(" Press P to Play");

	cursor(WIDTH + OFFSETX + 4, OFFSETY + 5);

	printf(" or Pause Game__");

	// # 3

	cursor(WIDTH + OFFSETX + 4, OFFSETY + 7);

	textcolor(YELLOW);

	printf(" Press Space");

	cursor(WIDTH + OFFSETX + 4, OFFSETY + 8);

	printf(" or Up to Shoot_");

	// # 4

	cursor(WIDTH + OFFSETX + 4, OFFSETY + 10);

	textcolor(LIGHTCYAN);

	printf(" Press Left,");

	cursor(WIDTH + OFFSETX + 4, OFFSETY + 11);

	printf(" Right to Move__");

	// # 5

	cursor(WIDTH + OFFSETX + 5, OFFSETY + 13);

	textcolor(WHITE);

	char_prnt(205, 15);

	// # 6

	cursor(WIDTH + OFFSETX + 4, OFFSETY + 15);

	printf(" Status:");

	status(0);

	// # 7

	textcolor(WHITE);

	cursor(WIDTH + OFFSETX + 4, OFFSETY + 19);

	printf(" Score:");

	PRNT_SCORE;

	// wait before starting

	textcolor(YELLOW);

	cursor(WIDTH / 2 + OFFSETX + 4 - 18, OFFSETY + 10);

	printf("---- Press a key to Start ----");

	getch();

	cursor(WIDTH / 2 + OFFSETX + 4 - 18, OFFSETY + 10);

	printf("                              ");

	status(1);

	add_invaders(8);

	for(;;)
	{
		time_passed();

		p1 = p2 = p3 = 1;

		// printing module

		if(invader_print())
		{
			status(3);

			game_over();

			fflush(stdin);

			getchar();

			textcolor(WHITE);

			put_backup_and_end;
		}

		if(dart_print())
		{
			status(2);

			game_over();

			fflush(stdin);

			getchar();

			textcolor(WHITE);

			put_backup_and_end;
		}

		bullet_print();

		if(!inveder_count || !(rand() % 50))
			add_invaders(4);

		for(dly = DELAY_NUM; dly > 0; dly -= 50)
		{
			key_detect();

			if(p1 && (is_held(VK_LEFT)))
			{
				// move the cannon left

				move_canon(0);

				p1 = 0;

				dly = DELAY_NUM;	// start delay count again after taking i/p
			}

			if(p2 && (is_held(VK_RIGHT)))
			{
				// move the cannon right

				move_canon(1);

				p2 = 0;

				dly = DELAY_NUM;
			}

			if(p3 && (is_held(VK_UP) || is_held(VK_SPACE)))
			{
				// fire a bullet

				add_bullet(canon_x);

				p3 = 0;

				dly = DELAY_NUM;
			}

			if(is_held(VK_ESCAPE))
			{
				//exit

				textcolor(WHITE);

				put_backup_and_end;
			}

			if(is_held('P'))
			{
				//pause

				status(0);

				Beep(1500, 150);

				hold_while_key_pressed('P');	// breaks if the key is realised

				hold_before_key_pressed('P');	// breaks if the key is pressed

				//play

				status(1);

				Beep(1500, 150);

				hold_while_key_pressed('P');	// checks if the key is pressed

				fflush(stdin);
			}

			delay(45);
		}

		cursor(0, 0);

		textcolor(LIGHTRED);

		sprintf(fpsstr, "Space Invader by - Tushar Das (Prototype Version), FPS: %lf", 1 / time_passed());

		set_window_title(fpsstr);
	}
}
