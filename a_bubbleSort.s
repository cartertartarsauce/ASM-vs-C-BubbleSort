//@ Carter Froning
//@ Subroutine a_bubbleSort: Provided a pointer to an array of integers,
//@      a_bubbleSort will sort the given array and return it to x0.
//@ X0: Must point to an array of quads
//@ X1: Contains the length of the array
//@ LR: Must contain the return address
//@ All AAPCS required registers are preserved,  r19-r29 and SP.

	.data
	.global	a_bubbleSort
	.text

a_bubbleSort:
	// AAPCS REGISTERS PRESERVED
	str	x19, [SP, #-16]!		// Save x19 register to stack
	str	x20, [SP, #-16]!		// Save x20 register to stack
	str	x21, [SP, #-16]!		// Save x21 register to stack
	str	x22, [SP, #-16]!		// Save x22 register to stack
	str	x23, [SP, #-16]!		// Save x23 register to stack
	str	x24, [SP, #-16]!		// Save x24 register to stack
	str	x25, [SP, #-16]!		// Save x25 register to stack
	str	x26, [SP, #-16]!		// Save x26 register to stack
	str	x27, [SP, #-16]!		// Save x27 register to stack
	str	x28, [SP, #-16]!		// Save x28 register to stack
	str	x29, [SP, #-16]!		// Save x29 register to stack
	str	x30, [SP, #-16]!		// Save LR (Link Register) to stack

//	CONVERT C++ FUNCTION TO ASSEMBLY
/*--------------------------------------------
void BubbleSort (long long a[], int length)
{
    long long i, j, temp;

    for (i = 0; i < length; i++)
    {
        for (j = 0; j < length - i - 1; j++)
        {
            if (a[j + 1] < a[j])
            {
                temp = a[j];
                a[j] = a[j + 1];
                a[j + 1] = temp;
            }
        }
    }
}
--------------------------------------------*/
	//GIVEN:
	// x0 = address of array
	// x1 = array.size()
	//CREATED:
	// x20 = i
	// x21 = j
	// x22 = temp
	// x23 = tempLength (temp register for offset of j)

	mov	x20, #0			//set i to 0
	mov	x21, #0			//set j to 0

// for (x20 = 0; x20 < x1; x20++)
bubble_loop_i:
	cmp	x20, x1			// if (i >= length)
	bge	exit_bubble_loop	// then exit loop

	mov	x21, #0			//reset j to 0

	//else continue loop
	// for (x21 = 0; x21 < x1 - i - 1; x21++)
bubble_loop_j:

	//x23 = tempLength = (length - i - 1)
	mov	x23, x1			//move value of length to x23
	sub	x23, x23, x20		// x23 = x23 - i
	sub	x23, x23, #1		// x23 = x23 - 1

	//Ensuring that j stays within bounds
	cmp	x21, x23		// if (j >= length-i-1)
	bge	continue_i_loop		// then increment i
	b	incr_to_next_values	// else
continue_i_loop:
	add	x20, x20, #1		// i++
	b	bubble_loop_i		//branch back to start of loop
incr_to_next_values:
	// PREPARE SWAP
	// x21 = j
	// x24 = address of array
	// x25 = address of next item in array
	// x26 = value in array at j:		a[j]
	// x27 = next value in array:		a[j+1]

        add     x24, x0, x21, lsl #3    // increment and set x24 to the address of a[j]: x24 = x21 * 8
        add     x25, x24, #8            // increment and set x25 to the address of a[j+1] by adding 8 bytes to x24

	ldr	x26, [x24]		// load value at address x26 into x26
	ldr	x27, [x25]		// load value at address x27 into x27

        //check if we need to swap
	cmp	x26, x27		// if (a[j] <= a[j+1])	//If the next number is less than or equal to than the current number, skip swap
	ble	continue_j_loop		// then branch back to skip the swap and continue
	b	swap			// else swap them
continue_j_loop:
	add	x21, x21, #1		// j++
	b	bubble_loop_j		// go back to start of j loop
swap:
	//reassign current values to the correct addresses
	str	x27, [x24]		//a[j] = a[j+1] //stores the value at a[j+1] in place of the value at address a[j]
	str	x26, [x25]		//a[j+1] = temp	//stores the value in temp in place of the value at address a[j+1]

	b	continue_j_loop		// then branch back to continue

exit_bubble_loop:
	// POPPED IN REVERSE ORDER (LIFO)
	ldr	x30, [SP], #16		// Restore LR from stack
	ldr	x29, [SP], #16		// Restore x29 from stack
	ldr	x28, [SP], #16		// Restore x28 from stack
	ldr	x27, [SP], #16		// Restore x27 from stack
	ldr	x26, [SP], #16		// Restore x26 from stack
	ldr	x25, [SP], #16		// Restore x25 from stack
	ldr	x24, [SP], #16		// Restore x24 from stack
	ldr	x23, [SP], #16		// Restore x23 from stack
	ldr	x22, [SP], #16		// Restore x22 from stack
	ldr	x21, [SP], #16		// Restore x21 from stack
	ldr	x20, [SP], #16		// Restore x20 from stack
	ldr	x19, [SP], #16		// Restore x19 from stack

	RET	LR			// Return to caller
	.end
