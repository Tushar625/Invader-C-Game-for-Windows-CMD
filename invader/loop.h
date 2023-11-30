#pragma once

#include<time.h>
#include<stdio.h>
#include<conio.h>
#include<stdlib.h>
#include<math.h>
#include<stdbool.h>


/*
    here lots of function templates can be found

    try to make functions from those templates before any #define
    statement in the source code, where you have included this
    header file as, the function definitions created by those templates
    can't be seen (i.e., will be created in compile time). They can
    contain variables with same name as a macro defined before them,
    that will obviously cause an error which can't be detected easily.

    Another alternative is that always name the macros with UPPER CASE
    alphabets this will never cause any problem as none of the function
    templates contain indentifiers with upper case letters
*/

/*
    here most of the operations are done in macros

    cause:-

    we can use any datatype and it is much faster than functions

    but we can not declare variables inside a macro so sometimes
    those expressions are evaluated multiple times, so those expressions
    must not have any term that changes value when evaluated multiple times
    like i++ + 4, here the value of i will changes if evaluated multiple times
    so avoid expressions with increment or decrement operators and similar things
*/

/*
	these provide the argument list for make_function, for more arguments

	declare similar macros
*/

#define arg_list_1(arg_type, a) arg_type a

#define arg_list_2(arg_type, a, b) arg_type a, arg_type b

#define arg_list_3(arg_type, a, b, c) arg_type a, arg_type b, arg_type c

#define arg_list_4(arg_type, a, b, c, d) arg_type a, arg_type b, arg_type c, arg_type d

#define arg_list_5(arg_type, a, b, c, d, e) arg_type a, arg_type b, arg_type c, arg_type d, arg_type e

/*
	this macro solves the afore-said probs for those macros which do not modify its arguments

	it can make a function from them

    !!!!! if the macro takes different types of arguments then please look for its given function alternative or make one !!!!!

	return_type: return type of the function cannot be void

	macro_name: name of the macro that will be functionified

	tag_name: unique name for each created funtion

	arg_type: type of the formal arguments of the functions (all arguments is of the same type)

	arg_num: no. of arguments, must be correct

	...: the arguments of the macro

	*** note: the macro must return some thing, else use make_function_void if the macro returns nothing

	example:

	make_function(int, AP_ROT, _int, int, 3, a, d, n)

	-> the statement creats a funtion, int AP_ROT_int(int a, int d, int n)

	make_function(int, ADV_ROT_RNG, _int, int, 4, start, adv, startrng, endrng)

	-> the statement creats a funtion, int ADV_ROT_RNG_int(int start, int adv, int startrng, int endrng)

    make_function_void(swaping, _int, int, 2, *a, *b)

    -> the statement creats a funtion, void swaping_int(int * a, int * b)

    make_function(int, increment_rot, _int, int, 2, * x, n)

    -> the statement creats a funtion, int increment_rot_int(int * x, int n)
*/

#define make_function(return_type, macro_name, tag_name, arg_type, arg_num, ...) return_type macro_name##tag_name(arg_list_##arg_num(arg_type, __VA_ARGS__))\
{\
	return (return_type)macro_name(__VA_ARGS__);\
}

#define make_function_void(macro_name, tag_name, arg_type, arg_num, ...) void macro_name##tag_name(arg_list_##arg_num(arg_type, __VA_ARGS__))\
{\
	macro_name(__VA_ARGS__);\
}



#ifndef IN_RNG
#define IN_RNG(Lrng, x, Hrng) ((x) >= (Lrng) && (x) <= (Hrng)) // if x is between Lrng and Hrng it gives 1 else 0
#endif // IN_RNG



#ifndef ADV_ROT
#define ADV_ROT(p, adv, num) (((p) + (adv)) % (num)) // advances p by adv while keeping it in between 0 and (num - 1)
#endif // ADV_ROT

// p must be between 0 and (num - 1)

#ifndef REV_ROT
#define REV_ROT(p, rev, num) ADV_ROT(p, (num) - (rev) % (num), num) // ((p - rev % num + num) % num) reverses p by rev while keeping it in between 0 and (num - 1)
#endif // REV_ROT

#ifndef ADV_ROT_RNG
#define ADV_ROT_RNG(start, adv, startrng, endrng) (ADV_ROT((start) - (startrng), adv, (endrng) - (startrng) + 1) + (startrng))	// advances start by adv while keeping it in between startrng and endrng
#endif // ADV_ROT_RNG

// start must be between startrng and endrng or it will fail

#ifndef REV_ROT_RNG
#define REV_ROT_RNG(start, rev, startrng, endrng) (REV_ROT((start) - (startrng), rev, (endrng) - (startrng) + 1) + (startrng))	// reverses start by rev while keeping it in between startrng and endrng
#endif // REV_ROT_RNG


/*
	advances or reverses a by d while keeping it in between 0 and (n - 1)

	a & d must be 0 and (n - 1) else it will malfunction
*/

#ifndef AP_ROT
#define AP_ROT(a, d, n) ( (((a) + (d)) >= (n)) ? (((a) + (d)) - (n)) : ( (((a) + (d)) < 0) ? ((n) + ((a) + (d))) : ((a) + (d)) ) )
#endif // AP_ROT

#ifndef increment_rot
#define increment_rot(x, n) ((x) = AP_ROT(x, 1, n))
#endif // increment_rot

// increments or decrements x by 1 while keeping it in between 0 and (n - 1)

#ifndef decrement_rot
#define decrement_rot(x, n) ((x) = AP_ROT(x, -1, n))
#endif // decrement_rot

/*
	advances or reverses start by adv while keeping it in between startrng, endrng

	start & adv must be startrng, endrng else it will malfunction
*/

#ifndef AP_ROT_RNG
#define AP_ROT_RNG(start, adv, startrng, endrng) (AP_ROT((start) - (startrng), adv, (endrng) - (startrng) + 1) + (startrng))
#endif // AP_ROT_RNG

#ifndef increment_rot_rng
#define increment_rot_rng(x, startrng, endrng) ((x) = AP_ROT_RNG(x, 1, startrng, endrng))
#endif // increment_rot_rng

// increments or decrements x by 1 while keeping it in between startrng, endrng

#ifndef decrement_rot_rng
#define decrement_rot_rng(x, startrng, endrng) ((x) = AP_ROT_RNG(x, -1, startrng, endrng))
#endif // decrement_rot_rng



/*
    if its false, we may exit but not stop the program
    as, the i/p is not logically invalid and it not a
    fatal error
*/

#ifndef valid_arr_arg
#define valid_arr_arg(arr, num) ((arr) && (num) > 0)	// checks if the basic arguments given to a array related function is valid or not, gives 1 for valid 0 for invalid
#endif // valid_arr_arg



// if its false, must exit and stop the program

#ifndef is_valid_arr_arg
#define is_valid_arr_arg(arr, num) ((arr) && (num) >= 0)	// checks if the basic arguments given to a array related function is valid or not, gives 1 for valid 0 for invalid
#endif // valid_arr_arg



#ifndef BIT_VLU
#define BIT_VLU(...) (!!(__VA_ARGS__))//((__VA_ARGS__) ? 1 : 0) // if input nonzero gives 1 else 0
#endif // BIT_VLU

#ifndef ABS_VLU
#define ABS_VLU(x) (((x) >= 0) ? (x) : -(x)) // absolute value
#endif // ABS_VLU

#ifndef get_int_part
#define get_int_part(fnum) ((int) (fnum))
#endif // get_int_part

#ifndef get_int_part_type
#define get_int_part_type(fnum, type) ((type) (fnum))
#endif // get_int_part

#ifndef get_decimal_part
#define get_decimal_part(fnum) ((fnum) - (int) (fnum))
#endif // get_decimal_part

#ifndef get_decimal_part_type
#define get_decimal_part_type(fnum, type) ((fnum) - (type) (fnum))
#endif // get_decimal_part

/*
    get the digit at a specific position of an integer according to the base, pos of LSB is 0 and increases towards left
    !!!!! it is not reliable for getting digits after point for floating point numbers !!!!!

    type (integer) depends on the size of the integer part of the number for very size use long long
*/

#ifndef get_digit_base_type
#define get_digit_base_type(num, base, pos, type) ((type)((num) / pow((base), (pos))) % (base))
#endif

#ifndef get_digit_base
#define get_digit_base(num, base, pos) get_digit_base_type(num, base, pos, int)
#endif

#ifndef get_digit_type
#define get_digit_type(num, pos, type) get_digit_base_type(num, 10, pos, type)
#endif

#ifndef get_digit
#define get_digit(num, pos) get_digit_base(num, 10, pos)
#endif

#ifndef get_floor
#define get_floor(num) (((num) >= 0) ? (int) (num) : ((int) (num) - 1))
#endif // get_floor

#ifndef get_ceil
#define get_ceil(num) (((num) < 0) ? (int) (num) : ((int) (num) + 1))
#endif // get_ceil

#ifndef get_closest_int
#define get_closest_int(x) ((int)(((x) >= 0) ? ((x) + .5) : ((x) - .5)))
#endif

#ifndef swaping
#define swaping(a, b) do{typeof(a) temp; temp = a; a = b; b = temp;} while(0)
#endif // swaping

#ifndef newl
#define newl putchar('\n')
#endif // newl

#ifndef newl2
#define newl2 printf("\n\n")
#endif // newl2

#ifndef newl3
#define newl3 printf("\n\n\n")
#endif // newl3

#ifndef newl4
#define newl4 printf("\n\n\n\n")
#endif // newl4

#ifndef newl5
#define newl5 printf("\n\n\n\n\n")
#endif // newl5

#ifndef newls
#define newls(num) do{for(int i = (num); i >= 1; i--) putchar('\n');} while(0)
#endif // newls


/*
	the macro below calculate the time taken by a function to complete its operation
	stdio.h and time.h is required for its operation

	t1: must be a variable to store the beginning time
	t2: must be a variable to store the ending time
	function: is the function concerned

	it gives the time (long double) taken by the function to execute in seconds
*/

#ifndef TIME_CALC
#define TIME_CALC(t1, function, t2)((t1) = clock(), function, (t2) = clock(), ((double)((t2) - (t1)) / CLOCKS_PER_SEC))
#endif // TIME_CALC



/*
	t2 is the previous clock() o/p

	t1 is the new clock() o/p

	TIME_FROM_CLOCK_SECOND(t1, t2) calculate
	the time passed between the calls for t1 & t2
	in seconds
*/

#ifndef TIME_FROM_CLOCK_SECOND
#define TIME_FROM_CLOCK_SECOND(t1, t2) ((double)((t2) - (t1)) / CLOCKS_PER_SEC)
#endif // TIME_FROM_CLOCK_SECOND



/*
	t2 is the previous clock() o/p

	t1 is the new clock() o/p

	TIME_FROM_CLOCK_SECOND(t1, t2) calculate
	the time passed between the calls for t1 & t2
	in miliseconds
*/

#ifndef TIME_FROM_CLOCK_MILISECOND
#define TIME_FROM_CLOCK_MILISECOND(t1, t2) ((double)((t2) - (t1)) / CLOCKS_PER_SEC * 1000)
#endif // TIME_FROM_CLOCK_MILISECOND



/*
	t2 is the previous clock() o/p

	t1 is the new clock() o/p

	TIME_FROM_CLOCK_SECOND(t1, t2) calculate
	the time passed between the calls for t1 & t2
	in microseconds
*/

#ifndef TIME_FROM_CLOCK_MICROSECOND
#define TIME_FROM_CLOCK_MICROSECOND(t1, t2) ((double)((t2) - (t1)) / CLOCKS_PER_SEC * 1000 * 1000)
#endif // TIME_FROM_CLOCK_MICROSECOND



// gives the time passed since last call (starting of execution for first call) in seconds

double time_passed()
{
	static double t0 = 0, time;

	time = (double)(clock() - t0) / CLOCKS_PER_SEC;

	t0 = clock();

	return time;
}



#ifndef odd
#define odd(x) ((x) & 1) // gives 1 if odd, 0 if even
#endif // odd

#ifndef even
#define even(x) (~(x) & 1/* !odd(x) */) // gives 0 if odd, 1 if even
#endif // even



// gives the size of a static array

#ifndef sizeof_static_array_type
#define sizeof_static_array_type(arr, type) (type)(sizeof(arr) / sizeof(arr[0]))
#endif // sizeof_static_array_type

#ifndef sizeof_static_array
#define sizeof_static_array(arr) sizeof_static_array_type(arr, int)
#endif // sizeof_static_array



/*
    sum: stores the sum
    num: no. of elements in the array
    index: an index must be set for the inner loop
    elem: the elements to be added, it looks like arr[index], arr[index].x
*/

#define arr_sum(sum, num, elem, index) do{\
    sum = 0;\
    arrayscan(num, index)\
        sum += elem;\
} while(0);

/*
    same as before just sum of elem1 -> sum1, elem2 -> sum2
*/

#define arr_sum_2(sum1, sum2, num, elem1, elem2, index) do{\
    sum1 = sum2 = 0;\
    arrayscan(num, index)\
    {\
        sum1 += elem1;\
        sum2 += elem2;\
    }\
} while(0);

/*
    same as before just sum of elem1 -> sum1, elem2 -> sum2, elem3 -> sum3
*/

#define arr_sum_3(sum1, sum2, sum3, num, elem1, elem2, elem3, index) do{\
    sum1 = sum2 = sum3 = 0;\
    arrayscan(num, index)\
    {\
        sum1 += elem1;\
        sum2 += elem2;\
        sum3 += elem3;\
    }\
} while(0);

/*make similar macro if needed more*/




/*
    avg: stores the average
    num: no. of elements in the array
    index: an index must be set for the inner loop
    elem: the elements to be added, it looks like arr[index], arr[index].x
*/

#define arr_avg(avg, num, elem, index) do{\
    avg = 0;\
    arrayscan(num, index)\
        avg += elem;\
    avg /= num;\
} while(0);

/*
    same as before just average of elem1 -> avg1, elem2 -> avg2
*/

#define arr_avg_2(avg1, avg2, num, elem1, elem2, index) do{\
    avg1 = avg2 = 0;\
    arrayscan(num, index)\
    {\
        avg1 += elem1;\
        avg2 += elem2;\
    }\
    avg1 /= num;\
    avg2 /= num;\
} while(0);

/*
    same as before just average of elem1 -> avg1, elem2 -> avg2, elem3 -> avg3
*/

#define arr_avg_3(avg1, avg2, avg3, num, elem1, elem2, elem3, index) do{\
    avg1 = avg2 = avg3 = 0;\
    arrayscan(num, index)\
    {\
        avg1 += elem1;\
        avg2 += elem2;\
        avg3 += elem3;\
    }\
    avg1 /= num;\
    avg2 /= num;\
    avg3 /= num;\
} while(0);

/*make similar macro if needed more*/



// ------ to use loops with style ------



// different implementation for the loops below

/*
	never change the loop counter in the loop body [it is usually not required],
	as it will affect its operation

	-------- this limitation is not solved to maintain efficiency of the loops --------
*/

typedef const char * p_const_char;  // the name will be sent as the type name in the macros below



#ifndef COUNTTYPE

#define COUNTTYPE

/*
	** a for loop, that counts from start to end

    ** index will be the loop counter

	---- acctually it will be taken as a variable name which will be declared and used in the loop
	---- so please follow the rules for identifiers, and if there is a variable declared earlier
	---- with same name as index then that variable won't be available in the loop

	here the data type of the loop counter can
	be sepcified with the type argument

    note that the type argument must not contain '*' symbol, if you need to include it
    use typedef to give a different name to the datatype as shown below

    typedef const char * p_const_char;


    here start, end, interval expression are evaluated before starting the loop
    and don't mess with the loop counter i.e., index, in a loop
*/

// here start, end, interval and loop counter is of a specified type

#define countascndinterval_type(start, end, interval, index, type) for(type index = (start), stop_872__2_0_##index = (end), incr_874__3_0_##index = (interval); index <= stop_872__2_0_##index; index += incr_874__3_0_##index) // start <= end

#define countdscndinterval_type(start, end, interval, index, type) for(type index = (start), stop_891__2_0_##index = (end), decr_874__3_0_##index = (interval); index >= stop_891__2_0_##index; index -= decr_874__3_0_##index) // start >= end

#define countascndtype(start, end, index, type) countascndinterval_type(start, end, 1, index, type) // start <= end

#define countdscndtype(start, end, index, type) countdscndinterval_type(start, end, 1, index, type) // start >= end

// scan a string from left to right starting from str[start] (no floating point type is allowed)

#define stringscantype(start, str, index, type) for(type index = (start); (str)[index]; index++)

// scan an array from left to right partially

#define arrayscanparttype(start, num, index, type) for(type index = (start), no_of_elements_9__x87_91##index = (num); index < no_of_elements_9__x87_91##index; index++)

// scan an array from right to left completely

#define arrayscanrevtype(num, index, type) for(type index = (num) - 1; index >= 0; index--)

// loop to cycle from one point to another (no floating point type is allowed, only int like types are allowed)

#define countascndcycletype(start, end, num, index, type) for(type index = (start), END__8_YU_8172##index = (end), NUM_1__uo##index = (num) - 1, flag_56_9n_h##index = IN_RNG(0, index, NUM_1__uo##index) && IN_RNG(0, END__8_YU_8172##index, NUM_1__uo##index) ? 1 : 0; flag_56_9n_h##index; index = 0) for(; flag_56_9n_h##index && index <= NUM_1__uo##index; flag_56_9n_h##index = index == END__8_YU_8172##index ? 0 : 1, index++) // start <= end

// start, end, startrng, endrng must be positive; start, end must be between startrng and endrng else it will malfunction (no floating point type is allowed, only int like types are allowed)

#define countdscndcycletype(start, end, num, index, type) for(type index = (start), END_4__YU_8_32##index = (end), NUM_18_io##index = (num) - 1, flag_5t_0n_y##index = IN_RNG(0, index, NUM_18_io##index) && IN_RNG(0, END_4__YU_8_32##index, NUM_18_io##index) ? 1 : 0; flag_5t_0n_y##index; index = NUM_18_io##index) for(; flag_5t_0n_y##index && index >= 0; flag_5t_0n_y##index = index == END_4__YU_8_32##index ? 0 : 1, index--) // start >= end

// loop to cycle from one point to another (no floating point type is allowed, only int like types are allowed)

#define countascndrngcycletype(startrng, endrng, start, end, index, type) for(type index = (start), END_90_Y__75##index = (end), i_p_start_rng_9_45##index = (startrng), i_p_end_rng_0_42##index = (endrng), STARTRNG_89_u_yt##index = i_p_start_rng_9_45##index <= i_p_end_rng_0_42##index ? i_p_start_rng_9_45##index : i_p_end_rng_0_42##index, ENDRNG_ty_77__8##index = i_p_start_rng_9_45##index <= i_p_end_rng_0_42##index ? i_p_end_rng_0_42##index : i_p_start_rng_9_45##index, flag_9__6y_y##index = IN_RNG(STARTRNG_89_u_yt##index, index, ENDRNG_ty_77__8##index) && IN_RNG(STARTRNG_89_u_yt##index, END_90_Y__75##index, ENDRNG_ty_77__8##index) ? 1 : 0; flag_9__6y_y##index; index = STARTRNG_89_u_yt##index) for(; flag_9__6y_y##index && index <= ENDRNG_ty_77__8##index; flag_9__6y_y##index = index == END_90_Y__75##index ? 0 : 1, index++) // start <= end

// start, end, startrng, endrng must be positive; start, end must be between startrng and endrng else it will malfunction (no floating point type is allowed, only int like types are allowed)

#define countdscndrngcycletype(startrng, endrng, start, end, index, type) for(type index = (start), END_90_X__76##index = (end), i_p_start_rng_x_75##index = (startrng), i_p_end_rng_p_v2##index = (endrng), STARTRNG__9_o_9t##index = i_p_start_rng_x_75##index <= i_p_end_rng_p_v2##index ? i_p_start_rng_x_75##index : i_p_end_rng_p_v2##index, ENDRNG_th_07__o##index = i_p_start_rng_x_75##index <= i_p_end_rng_p_v2##index ? i_p_end_rng_p_v2##index : i_p_start_rng_x_75##index, flag_80_po_u##index = IN_RNG(STARTRNG__9_o_9t##index, index, ENDRNG_th_07__o##index) && IN_RNG(STARTRNG__9_o_9t##index, END_90_X__76##index, ENDRNG_th_07__o##index) ? 1 : 0; flag_80_po_u##index; index = ENDRNG_th_07__o##index) for(; flag_80_po_u##index && index >= STARTRNG__9_o_9t##index; flag_80_po_u##index = index == END_90_X__76##index ? 0 : 1, index--) // start >= end

// loop through random i/p data of same datatype

#define countrandtype(elem, type, ...) for(type arr_9__8_hO##elem[] = {__VA_ARGS__}, *ptr_9_7__hu##elem = arr_9__8_hO##elem, *ptrend_9_o_8__##elem = arr_9__8_hO##elem + sizeof_static_array(arr_9__8_hO##elem), elem = *ptr_9_7__hu##elem; ptr_9_7__hu##elem < ptrend_9_o_8__##elem; ptr_9_7__hu##elem++, elem = *ptr_9_7__hu##elem)

/*counts the digits of a decimal integer for any base from LSD to MSD, type can be any int similar type*/

#define countdigitbasetype(num, base, index, type) for(type base_0__9__uy_##index = (base), nm___9ii_0_i##index = base_0__9__uy_##index > 1 ? (num) : 0, index = nm___9ii_0_i##index % base_0__9__uy_##index; nm___9ii_0_i##index > 0; nm___9ii_0_i##index /= base_0__9__uy_##index, index = nm___9ii_0_i##index % base_0__9__uy_##index)

/*extract 'no_of_digits' no. of digits after the point in a given base from num of type typef, starting from the digit right after the point*/

#define countdigitbase_aftpoint_type(num, no_of_digits, base, index, typef) for(typef base__9_oo_p##index = (base), nm_i9i_09##index = (num), count_o_87_0##index = base__9_oo_p##index > 1 ? (no_of_digits) : 0, index = (int)(nm_i9i_09##index = get_decimal_part_type(nm_i9i_09##index, long long) * base__9_oo_p##index); count_o_87_0##index > 0; index = (int)(nm_i9i_09##index = get_decimal_part(nm_i9i_09##index) * base__9_oo_p##index), count_o_87_0##index -= 1)

#endif  // COUNTTYPE



#ifndef COUNT

#define COUNT

/*
	a for loop, that counts from start to end
	index will be the loop counter

	---- acctually it will be taken as a variable name which will be declared and used in the loop
	---- so please follow the rules for identifiers, and if there is a variable declared earlier
	---- with same name as index then that variable won't be available in the loop

	here loop counter is an integer except the last two
	that has loop counter as double
*/

#define countascnd(start, end, index) countascndtype(start, end, index, int) // start <= end

#define countdscnd(start, end, index) countdscndtype(start, end, index, int) // start >= end

// scan a string from left to right starting from str[start]

#define stringscan(start, str, index) stringscantype(start, str, index, int)

// scan an array from left to right completely

#define arrayscan(num, index) arrayscanparttype(0, num, index, int)

// scan an array from left to right partially

#define arrayscanpart(start, num, index) arrayscanparttype(start, num, index, int)

// scan an array from right to left completely

#define arrayscanrev(num, index) arrayscanrevtype(num, index, int)

// loop to cycle from one point to another

#define countascndcycle(start, end, num, index) countascndcycletype(start, end, num, index, int) // start <= end

// start, end, num must be positive; start, end must be between 0 and num - 1 else it will malfunction

#define countdscndcycle(start, end, num, index) countdscndcycletype(start, end, num, index, int) // start >= end

// loop to cycle from one point to another (no floating point type is allowed, only int like types are allowed)

#define countascndrngcycle(startrng, endrng, start, end, index) countascndrngcycletype(startrng, endrng, start, end, index, int)

// start, end, startrng, endrng must be positive; start, end must be between startrng and endrng (startrng <= endrng) else it will malfunction (no floating point type is allowed, only int like types are allowed)

#define countdscndrngcycle(startrng, endrng, start, end, index) countdscndrngcycletype(startrng, endrng, start, end, index, int)

// here start, end, interval and loop counter is integer

#define countascndinterval_int(start, end, interval, index) countascndinterval_type(start, end, interval, index, int) // start <= end

#define countdscndinterval_int(start, end, interval, index) countdscndinterval_type(start, end, interval, index, int) // start >= end

// start, end, interval can be and loop counter is floating point no.

#define countascndinterval_double(start, end, interval, index) countascndinterval_type(start, end, interval, index, double) // start <= end

#define countdscndinterval_double(start, end, interval, index) countdscndinterval_type(start, end, interval, index, double) // start >= end

// loop through random i/p data of same datatype

#define countrandchar(elem, ...) countrandtype(elem, char, __VA_ARGS__)

#define countrandint(elem, ...) countrandtype(elem, int, __VA_ARGS__)

#define countranddouble(elem, ...) countrandtype(elem, double, __VA_ARGS__)

#define countrandstr(elem, ...) countrandtype(elem, p_const_char, __VA_ARGS__)

/*counts the digits of a decimal integer for any base from LSD to MSD*/

#define countdigitbase(num, base, index) countdigitbasetype(num, base, index, int)

/*counts the digits of an integer from LSD to MSD*/

#define countdigit(num, index) countdigitbasetype(num, 10, index, int)

/*extract 'no_of_digits' no. of digits after the point in a given base from num of type double, starting from the digit right after the point*/

#define countdigitbase_aftpoint(num, no_of_digits, base, index) countdigitbase_aftpoint_type(num, no_of_digits, base, index, double)

/*extract 'no_of_digits' no. of digits after the point in base 10 from num of type double, starting from the digit right after the point*/

#define countdigit_aftpoint(num, no_of_digits, index) countdigitbase_aftpoint_type(num, no_of_digits, 10, index, double)

#endif  // COUNT



#ifndef LOOP

#define LOOP

/*
	a for loop, that counts from start to end
	id is used to distinguished loop counter
	like,
	if id: 1 then loop counter i1
	if id: o then loop counter io
	here loop counter is an integer except the last two
	that has loop counter as double
*/

#define loopascnd(start, end, id) countascndtype(start, end, i##id, int) // start <= end

#define loopdscnd(start, end, id) countdscndtype(start, end, i##id, int) // start >= end

// scan a string from left to right starting from str[start]

#define stringloop(start, str, id) stringscantype(start, str, i##id, int)

// scan an array from left to right completely

#define arrayloop(num, id) arrayscanparttype(0, num, i##id, int)

// scan an array from left to right partially

#define arraylooppart(start, num, id) arrayscanparttype(start, num, i##id, int)

// scan an array from right to left completely

#define arraylooprev(num, id) arrayscanrevtype(num, i##id, int)

// loop to cycle from one point to another

#define loopascndcycle(start, end, num, id) countascndcycletype(start, end, num, i##id, int) // start <= end

// start, end, num must be positive; start, end must be between 0 and num - 1 else it will malfunction

#define loopdscndcycle(start, end, num, id) countdscndcycletype(start, end, num, i##id, int) // start >= end

// loop to cycle from one point to another (no floating point type is allowed, only int like types are allowed)

#define loopascndrngcycle(startrng, endrng, start, end, id) countascndrngcycletype(startrng, endrng, start, end, i##id, int)

// start, end, startrng, endrng must be positive; start, end must be between startrng and endrng (startrng <= endrng) else it will malfunction (no floating point type is allowed, only int like types are allowed)

#define loopdscndrngcycle(startrng, endrng, start, end, id) countdscndrngcycletype(startrng, endrng, start, end, i##id, int)

// here start, end, interval and loop counter is integer

#define loopascndinterval_int(start, end, interval, id) countascndinterval_type(start, end, interval, i##id, int) // start <= end

#define loopdscndinterval_int(start, end, interval, id) countdscndinterval_type(start, end, interval, i##id, int) // start >= end

// start, end, interval can be and loop counter is floating point no.

#define loopascndinterval_double(start, end, interval, id) countascndinterval_type(start, end, interval, i##id, double) // start <= end

#define loopdscndinterval_double(start, end, interval, id) countascndinterval_type(start, end, interval, i##id, double) // start >= end

// loop through random i/p data of same datatype

#define looprandchar(id, ...) countrandtype(i##id, char, __VA_ARGS__)

#define looprandint(id, ...) countrandtype(i##id, int, __VA_ARGS__)

#define loopranddouble(id, ...) countrandtype(i##id, double, __VA_ARGS__)

#define looprandstr(id, ...) countrandtype(i##id, const char *, __VA_ARGS__)

/*counts the digits of a decimal integer for any base from LSD to MSD*/

#define loopdigitbase(num, base, index) countdigitbasetype(num, base, i##index, int)

/*counts the digits of an integer from LSD to MSD*/

#define loopdigit(num, index) countdigitbasetype(num, 10, i##index, int)

/*extract 'no_of_digits' no. of digits after the point in a given base from num of type double, starting from the digit right after the point*/

#define loopdigitbase_aftpoint(num, no_of_digits, base, index) countdigitbase_aftpoint_type(num, no_of_digits, base, i##index, double)

/*extract 'no_of_digits' no. of digits after the point in base 10 from num of type double, starting from the digit right after the point*/

#define loopdigit_aftpoint(num, no_of_digits, index) countdigitbase_aftpoint_type(num, no_of_digits, 10, i##index, double)

#endif  // LOOP



// if it fails all allocated spaces are freed and matx is assigned with NULL

#ifndef allocate_matrix_numtype
#define allocate_matrix_numtype(matx, row, col, matxtype, numtype) do{\
    if(matx != NULL)/*may cause danging pointer error*/\
        error_exit("\n\n!!!! %s given to allocate_matrix is not NULL, it may contain an allocated memory location !!!!", #matx);\
    numtype c_P_0_8 = (col);\
    numtype r__V_J9_00 = (row);\
	(matx) = (typeof(matxtype) **)calloc(r__V_J9_00, sizeof(typeof(matxtype) *));\
    if(matx)\
        arrayscanparttype(0, r__V_J9_00, i___o99000, numtype)\
        {\
            (matx)[i___o99000] = (typeof(matxtype) *)calloc(c_P_0_8, sizeof(typeof(matxtype)));\
            if((matx)[i___o99000] == NULL)\
            {/*if fails to allocate an array clearing all previous arrays and the matx*/\
                arrayscanparttype(0, i___o99000, j_hhh_k____90, numtype)\
                    free((matx)[j_hhh_k____90]);\
                free(matx);\
                (matx) = NULL;\
                break;\
            }\
        }\
} while(0)
#endif // allocate_matrix_numtype

#ifndef allocate_matrix
#define allocate_matrix(matx, row, col) allocate_matrix_numtype(matx, row, col, typeof(**(matx)), int)
#endif // allocate_matrix

#ifndef allocate_matrix_fun
#define allocate_matrix_fun(matx_type, num_type, type_name)\
bool allocate_matrix_##type_name(typeof(matx_type) ***matx, num_type row, num_type col)\
{\
    if(matx == NULL || row < 0 || col < 0)\
        error_exit("\n\n!!!! Invalid argument send to allocate_matrix_%s !!!!\n\n", #type_name);\
    allocate_matrix_numtype(*matx, row, col, typeof(matx_type), num_type);\
    if(*matx)\
        return 0;/*space allocated successfully*/\
    else\
        return 1;/*failed to allocate space*/\
}
#endif // allocate_matrix_fun



// need function

#ifndef free_matrix
#define free_matrix(matx, row) do{\
	arrayscan((row), i__88u__)\
	{\
        /*printf("\n%d", i__88u__);*/\
        free((matx)[i__88u__]);\
    }\
	free(matx);\
} while(0)
#endif // free_matrix



/*
    to copy matrix_destination into matrix_destination, col row should be same for
    both of them or preferably be the size of matrix_destination

    need function
*/

#ifndef matrix_cpy_numtype
#define matrix_cpy_numtype(matrix_destination, matrix_source, row, col, numtype)do{\
    numtype c_P_0k098__u = (col);\
    arrayscanparttype(0, row, i_ppojj___, numtype)\
        arr_cpy((matrix_destination)[i_ppojj___], (matrix_source)[i_ppojj___], c_P_0k098__u);\
} while(0)
#endif // matrix_cpy_numtype

#ifndef matrix_cpy
#define matrix_cpy(matrix_destination, matrix_source, row, col) matrix_cpy_numtype(matrix_destination, matrix_source, row, col, int)
#endif // matrix_cpy




/*
    ...: mention the string to print here like, "%lf\t"

    !!!! j indexes the row and i indexes the column so be carefull matrix must not be an expression with i !!!!

    need function
*/

#ifndef print_matrix
#define print_matrix(matrix, row, col, ...)do{\
    arrayscan(row, j)\
    {\
        print_array(col, __VA_ARGS__, (matrix)[j][i]);\
        newl;\
    }\
} while(0)
#endif



// initialise an array with some elements, replace ... with the elements (use less as its not efficient)
// need function

#ifndef matx_initialize_numtype
#define matx_initialize_numtype(matx, row, col, numtype/*may someone use short instead of int as per his requirement*/, ...) do\
{\
    numtype c_P_0k_o = (col), j_oo_uu_8 = 0;\
    numtype r__V_J9i00 = (row), i__00_ooo = 0;\
    if((matx) == NULL || r__V_J9i00 < 0 || c_P_0k_o < 0)\
        error_exit("\n\n!!!! Invalid argument send to matx_initialize !!!!\n\n");\
    if(r__V_J9i00 == 0 || c_P_0k_o == 0)\
        break;\
    countrandtype(elem__jj_kkk___op, typeof(matx[0][0]), __VA_ARGS__)\
    {\
        matx[i__00_ooo][j_oo_uu_8++] = elem__jj_kkk___op;\
        if(j_oo_uu_8 >= c_P_0k_o)\
        {\
            i__00_ooo++;\
            j_oo_uu_8 = 0;\
        }\
        if(i__00_ooo >= r__V_J9i00)\
            break;\
    }\
} while(0)
#endif // matx_initialize_numtype

#ifndef matx_initialize
#define matx_initialize(matx, row, col, ...) matx_initialize_numtype(matx, row, col, int, __VA_ARGS__)
#endif // matx_initialize



/*
    =======================================================================

      These are some macros that makes the job of displaying a lot easier (need to be rewritten)

    =======================================================================
*/




/*
    ------- base macro -------

    this is a macro to print a circular array, it can also print
    linear array or a part of it

    str_empty: message to print if the array is empty like, "!!!!! Enpty Array !!!!!"

    num: size of the array for stattic array, (sizeof(arr) / sizeof(typeof(arr[0])))
    if num is 0 then the array is taken to be empty

    starting_index: index of the element to be printed first

    ending_index: index of the element to be printed last

    ---- if the indexes are not in between 0 - (num - 1) the array is taken to be empty

    ...: this represents that this macro can take variable no. of arguments
    the string to be printed for each array element like, "%g ", arr[i] (arr is the name of the actual array)
    ***** (here i is the array index of the loop inside) *****
    actually you put here what you write in the printf() function to print each element of the array with array index i

    !!!!! if wrong parameters are given it will fail to execute !!!!!

    it does not return anything

    ***** to print the array in reverse, use (num - 1 - i) as the array index *****
    ***** works only with print array macros *****
*/

#ifndef array_display_base
#define array_display_base(str_empty, num, starting_index, ending_index, ...) do{\
	int STARTING_INDEX_9i_j_ = (starting_index), ENDING_INDEX_9i_j_ = (ending_index), NUM_8__9_o_i_p = (num);\
    if(IN_RNG(0, STARTING_INDEX_9i_j_, NUM_8__9_o_i_p - 1) && IN_RNG(0, ENDING_INDEX_9i_j_, NUM_8__9_o_i_p - 1))\
    {\
        int i;\
        for(i = STARTING_INDEX_9i_j_; i != ENDING_INDEX_9i_j_; i = (i == (NUM_8__9_o_i_p - 1)) ? 0 : i + 1)\
            printf(__VA_ARGS__);\
        printf(__VA_ARGS__);/*printing last element*/\
    }\
    else\
        printf(str_empty);/*if the indexes are out of range the array is taken to be empty*/\
} while(0)
#endif // array_display_base




/*
    ---------------------------------------------------------------------

    lite array printing macros

    ---------------------------------------------------------------------
*/

/*
    prints a circular array using array_display_base() macro, it can also print
    linear array or a part of it
*/

#ifndef display_array
#define display_array(num, starting_index, ending_index, ...) array_display_base("!!!!! Its empty !!!!!", (num), (starting_index), (ending_index), __VA_ARGS__)
#endif // display_array

#ifndef display_array_fun
#define display_array_fun(arr_type/*type of array*/, num_type, type_name, .../*here 'arr' is the array and 'i' is its index and 'num' no. of elements*/)\
void display_array_##type_name(typeof(arr_type) arr[], num_type num, num_type starting_index, num_type ending_index)\
{\
    if(!is_valid_arr_arg(arr, num) || starting_index < 0 || ending_index < 0)\
        error_exit("\n\n!!!! Invalid argument send to display_array_%s !!!!\n\n", #type_name);\
    display_array(num, starting_index, ending_index, __VA_ARGS__);\
}
#endif // display_array_fun

/*
    prints a linear array using display_array() macro

    num: no. of elements in the array

    to print array in reverse see the description of the array_display_base
*/

#ifndef print_array
#define print_array(num, ...) display_array((num), 0, ((num) - 1), __VA_ARGS__)
#endif // print_array

#ifndef print_array_fun
#define print_array_fun(arr_type/*type of array*/, num_type, type_name, .../*here 'arr' is the array and 'i' is its index and 'num' no. of elements*/)\
void print_array_##type_name(typeof(arr_type) arr[], num_type num)\
{\
    if(!is_valid_arr_arg(arr, num))\
        error_exit("\n\n!!!! Invalid argument send to print_array_%s !!!!\n\n", #type_name);\
    print_array(num, __VA_ARGS__);\
}
#endif // print_array_fun





/*
    --------------------------------------------------------------------------

    advanced array printing macros

    the below two functions do the same job as the above two but we can add
    an extra text with them to print before printing the array and we heve
    to input the array-empty-statement seperately for the below macros

    --------------------------------------------------------------------------
*/

/*
    prints a circular array using array_display_base() macro, it can also print
    linear array or a part of it

    str_head: heading string to print like, "\n\nEnements of the array: "
*/

#ifndef display_array_adv
#define display_array_adv(str_head, str_empty, num, starting_index, ending_index, ...) do{printf(str_head); array_display_base(str_empty, (num), (starting_index), (ending_index), __VA_ARGS__);}while(0)
#endif // display_array_adv

#ifndef display_array_adv_fun
#define display_array_adv_fun(arr_type/*type of array*/, num_type, type_name, .../*here 'arr' is the array and 'i' is its index and 'num' no. of elements*/)\
void display_array_adv_##type_name(const char *str_head, const char *str_empty, typeof(arr_type) arr[], num_type num, num_type starting_index, num_type ending_index)\
{\
    if(!is_valid_arr_arg(arr, num) || starting_index < 0 || ending_index < 0 || str_head == NULL || str_empty == NULL)\
        error_exit("\n\n!!!! Invalid argument send to display_array_adv_%s !!!!\n\n", #type_name);\
    display_array_adv(str_head, str_empty, num, starting_index, ending_index, __VA_ARGS__);\
}
#endif // display_array_adv_fun

/*
    prints a linear array using display_array_adv() macro

    str_head: heading string to print like, "\n\nEnements of the array: "

    str_empty: mesage to print if the array is empty like, "!!!!! Enpty Array !!!!!"

    num: no. of elements in the array

    to print array in reverse see the description of the array_display_base
*/

#ifndef print_array_adv
#define print_array_adv(str_head, str_empty, num, ...) display_array_adv(str_head, str_empty, (num), 0, (num - 1), __VA_ARGS__)
#endif // print_array_adv

#ifndef print_array_adv_fun
#define print_array_adv_fun(arr_type/*type of array*/, num_type, type_name, .../*here 'arr' is the array and 'i' is its index and 'num' no. of elements*/)\
void print_array_adv_##type_name(const char *str_head, const char *str_empty, typeof(arr_type) arr[], num_type num)\
{\
    if(!is_valid_arr_arg(arr, num) || str_head == NULL || str_empty == NULL)\
        error_exit("\n\n!!!! Invalid argument send to print_array_adv_%s !!!!\n\n", #type_name);\
    print_array_adv(str_head, str_empty, num, __VA_ARGS__);\
}
#endif // print_array_adv_fun




/*
    to copy arr_source into arr_destination, num should be same for
    arr_destination, arr_source or preferably be the size of arr_destination
*/

#ifndef arr_cpy_numtype
#define arr_cpy_numtype(arr_destination, arr_source, num, numtype) do{\
    numtype num___90l__jki = (num);\
    if((arr_destination) == NULL || (arr_source) == NULL || num___90l__jki < 0)\
        error_exit("\n\n!!!! Invalid argument send to arr_cpy !!!!\n\n");\
    if(num___90l__jki == 0)/*we have elements in array*/\
        break;\
    arrayscanparttype(0, num___90l__jki, i_8yt_0o, numtype)\
        (arr_destination)[i_8yt_0o] = (arr_source)[i_8yt_0o];\
} while(0)
#endif // arr_cpy_numtype

#ifndef arr_cpy
#define arr_cpy(arr_destination, arr_source, num) arr_cpy_numtype(arr_destination, arr_source, num, int)
#endif // arr_cpy

#ifndef arr_cpy_fun
#define arr_cpy_fun(arr_type, num_type, type_name)\
void arr_cpy_##type_name(typeof(arr_type) arr_destination[], typeof(arr_type) arr_source[], num_type num)\
{\
        arr_cpy_numtype(arr_destination, arr_source, num, num_type);\
}
#endif // arr_cpy_fun




// initialise an array with some elements, replace ... with the elements (use less as its not efficient)
// need function

#ifndef arr_initialize_numtype
#define arr_initialize_numtype(arr, num, numtype/*may someone use short instead of int as per his requirement*/, ...) do{\
    numtype num___98__jki = (num);\
    if((arr) == NULL || num___98__jki < 0)\
        error_exit("\n\n!!!! Invalid argument send to arr_initialize !!!!\n\n");\
    if(num___98__jki == 0)\
        break;\
    typeof((arr)[0]) ARRX_o__Y[] = {__VA_ARGS__};\
    arrayscan((sizeof_static_array(ARRX_o__Y) < num___98__jki) ? sizeof_static_array(ARRX_o__Y) : num___98__jki, i____00ar_p)\
        (arr)[i____00ar_p] = ARRX_o__Y[i____00ar_p];\
} while(0)
#endif // arr_initialize_numtype

#ifndef arr_initialize
#define arr_initialize(arr, num, ...) arr_initialize_numtype(arr, num, int, __VA_ARGS__)
#endif // arr_initialize




/*
	reverses the array
*/

#ifndef arr_rev_numtype
#define arr_rev_numtype(arr, num, numtype) do\
{\
    numtype num_h_j_5__ii = (num);\
	if(!is_valid_arr_arg(arr, num_h_j_5__ii))\
		error_exit("\n\n!!!! Invalid argument send to arr_rev !!!!\n\n");\
	if(num_h_j_5__ii == 0)\
        break;\
	for(numtype i__90__98_I = 0, j__oi_OP0_9 = num_h_j_5__ii - 1; i__90__98_I < j__oi_OP0_9; i__90__98_I++, j__oi_OP0_9--)\
        swaping((arr)[j__oi_OP0_9], (arr)[i__90__98_I]);\
} while(0)
#endif // arr_rev_numtype

#ifndef arr_rev
#define arr_rev(arr, num) arr_rev_numtype(arr, num, int)
#endif // arr_rev




// creates a dynamic array and initialise it with some elements, replace ... with the elements (use less as its not efficient)

#ifndef dyn_arr_create_initialize
#define dyn_arr_create_initialize(arr, ...) do{\
    if((arr) != NULL)/*it may hold some allocated memory*/\
        error_exit("\n\n!!!! Invalid argument send to dyn_arr_create_initialize, arr is not NULL !!!!\n\n");\
    typeof(*(arr)) ARRX_p__Y[] = {__VA_ARGS__};\
    int num = sizeof_static_array(ARRX_p__Y);\
    arr = (typeof(arr)) calloc(num, sizeof(ARRX_p__Y[0]));\
    arrayscan(num, i_000ju)\
        (arr)[i_000ju] = ARRX_p__Y[i_000ju];\
} while(0)
#endif // arr_initialize




/*
	takes input in a range

	str: main string to display

	ipstr: string for scanf containing datatype specifiers

	errstr: displayed if invalid i/p is given

	num: takes the input

	min, max: range of input
*/

#ifndef ranged_input
#define ranged_input(str, ipstr, errstr, num, min, max) do{\
    double mn9__h_9____oii = (double) (min);\
    double mx___h0gtf = (double) (max);\
	printf("%s MIN(%g) MAX(%g): ", str, mn9__h_9____oii, mx___h0gtf);\
	fflush(stdin);\
	scanf(ipstr, &(num));\
	if(IN_RNG(mn9__h_9____oii, (num), mx___h0gtf))\
		break;\
	else\
		printf(errstr);\
} while(1)
#endif // ranged_input




/*
	takes input after checking a condition

	str: main string to display

	errstr: displayed if invalid i/p is given

	condition: condition to be put in if statement
				if its true the loop breaks else it
				shows errstr and askes for i/p again

	...: string for scanf containing datatype specifiers and address of the required variables
*/

#ifndef conditional_input
#define conditional_input(str, errstr, condition, ...) do{\
	printf(str);\
	fflush(stdin);\
	scanf(__VA_ARGS__);\
	if(condition)\
		break;\
	else\
		printf(errstr);\
} while(1)
#endif // conditional_input




/*
    if error occurres then display a message and
    wait for enter before continuing
*/

#ifndef error_wait
#define error_wait(...) do{\
    printf(__VA_ARGS__);\
    fflush(stdin);\
    getchar();\
} while(0)
#endif // error_wait




/*
    if error occurres then display a message and
    wait for enter before exiting
*/

#ifndef error_exit
#define error_exit(...) do{\
    printf(__VA_ARGS__);\
    fflush(stdin);\
    getchar();\
    exit(1);\
} while(0)
#endif // error_exit




/*
    !!!!! below 4 are not a safe thing to use !!!!!
    !!!!! use them at your own risk !!!!!

    !!!!! only to be used at the end of a inifinite loop to !!!!!
    !!!!! be used as a loop breaker, avoid to use them with if !!!!!
    !!!!! statement, while using them always remember the !!!!!
    !!!!! statements uder these macros are not enclosed with !!!!!
    !!!!! any kind of bracets !!!!!

    cond_operator: a relational operator to match
    i/p with ch (a char type data), if the condition is
    successfull then break the loop else the loop
    continues

    ...: the prompt message to be shown (using printf)
*/



// ****** this one uses getchar to take i/p ******

#ifndef loop_break_inp
#define loop_break_inp(cond_operator, ch, ...) printf(__VA_ARGS__);\
    fflush(stdin);\
    if(getchar() cond_operator ch)\
        break       // !!!!! <- notice ';' is missing here so dont forget to put it at the end of the macro !!!!!
#endif // loop_break_inp



// ****** this one uses getch to take i/p ******

#ifndef loop_break_press_inp
#define loop_break_press_inp(cond_operator, ch, ...) printf(__VA_ARGS__);\
    if(getch() cond_operator ch)\
        break       // !!!!! <- notice ';' is missing here so dont forget to put it at the end of the macro !!!!!
#endif // loop_break_press_inp



// ------ the 2 below have continueto perform when the condition fails ------



// ****** this one uses getchar to take i/p ******

#ifndef loop_break_else_conti_inp
#define loop_break_else_conti_inp(cond_operator, ch, ...) printf(__VA_ARGS__);\
    fflush(stdin);\
    if(getchar() cond_operator ch)\
        break;\
    else\
        continue       // !!!!! <- notice ';' is missing here so dont forget to put it at the end of the macro !!!!!
#endif // loop_break_else_conti_inp



// ****** this one uses getch to take i/p ******

#ifndef loop_break_else_conti_press_inp
#define loop_break_else_conti_press_inp(cond_operator, ch, ...) printf(__VA_ARGS__);\
    if(getch() cond_operator ch)\
        break;\
    else\
        continue       // !!!!! <- notice ';' is missing here so dont forget to put it at the end of the macro !!!!!
#endif // loop_break_else_conti_press_inp



/*
    ------ these macros are to deal with command line arguments easily ------

    get_cmd_arg and get_cmd_arg_const are to be placed as the formal argument list
    of main()

    argc: it gives the actual no. of cmd line arguments including the file name itself

    arg_num: it gives the no. of cmd line arguments excluding the file name

    arg[i] (array of strings): gives the ith cmd line argument as a string,
    arg[0] is the filename, to get rest of them i = 1, 2, 3, ..., arg_num

    use the rest of the macros to convert these arguments into other datatypes
*/

#ifndef get_cmd_arg
#define get_cmd_arg int argc, char *arg[]
#endif // get_cmd_arg

#ifndef get_cmd_arg_const   // can't modify the cmd line arguments
#define get_cmd_arg_const const int argc, const char *arg[]
#endif // get_cmd_arg_const

#ifndef arg_num
#define arg_num (argc - 1)
#endif // arg_num

/*
    this loop generates the indexes corrosponding to all
    the cmd line arguments except the name of the command
    sequentially

    i.e., 1, 2, 3,..., arg_num, now use the index with arg[]
    to get the cmd line arguments
*/

#ifndef cmd_arg_loop
#define cmd_arg_loop(index) arrayscanpart(1, argc, i)
#endif // cmd_arg_loop

// converting arguments into given type using their indexes:

#ifndef arg_i
#define arg_i(i) atoi(arg[i])   // int
#endif // arg_i

#ifndef arg_l
#define arg_l(i) atol(arg[i])   // long int
#endif // arg_l

#ifndef arg_ll
#define arg_ll(i) atoll(arg[i]) // long long int
#endif // arg_ll

#ifndef arg_f
#define arg_f(i) atof(arg[i])   // double
#endif // arg_f



/*
    template function to convert a string to any type of data

    to create a function instace call ato with,

    type: tergate datatype
    format_specifier_str: string containing the format specifier
    of the tergate type
    tname: name of the type tobe added with function name

    like,

    ato(unsigned, "%u", u), will create

    unsigned int ato_u(const char *str);
*/

#ifndef ato
#define ato(type, format_specifier_str, tname) type ato_##tname(const char *str)\
{\
    type elem;\
    sscanf(str, format_specifier_str, &elem);\
    return elem;\
}
#endif // ato




/*
    c tyle template for calculating the no. of digits of integral no.
*/

#ifndef no_of_digit
#define no_of_digit(type, type_name)\
int no_of_digit_##type_name(type num)\
{\
    int n = 0;\
    if(num < 0)\
        num -= -1;\
    for(; num; num /= 10, n++);\
    return n;\
}
#endif // no_of_digit




/*
    c tyle template for calculating the reverse of an integral no.
*/

#ifndef rev_number
#define rev_number(type, type_name)\
type rev_number_##type_name(type num)\
{\
    type sum = 0;\
    /*countdigit(num, i)*/\
    countdigitbasetype(num, 10, i, type)\
        sum = sum * 10 + i;\
    return sum;\
}
#endif // no_of_digit




/*
    c tyle template for calculating the reverse of an integral no.
*/

#ifndef rev_number_base
#define rev_number_base(type, type_name)\
type rev_number_##type_name(type num, char base)\
{\
    type sum = 0;\
    /*countdigit(num, i)*/\
    countdigitbasetype(num, base, i, type)\
        sum = sum * base + i;\
    return sum;\
}
#endif // no_of_digit
