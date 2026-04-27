# Advent 2025
See [Advent Code 2025](https://adventofcode.com/2025/)
I try to do them, but it is 2026.
I do them in C to challenge myself.

For each day go in the folder and run `make` and then `./prog`

# Summary for each day:

## Day 1
Really easy, the biggest difficulty was the modular computations. The C % operator did not work if number were negative so I did it in "dumb" way (see `loop_it_back` function).

 ## Day 2
 I don't understand the example so for now so it's a skip.

 ## Day 3 
 A bit harder than excepted. We had to account for the order of the maximum. Due to some edge case, prototypes were hard to concieve. I did need to use gdb to debug it.

## Day 4
The challenge itself was not really hard, but implementing it WAS hard. The 2D grid made me had nightmares. Alloction and indexing were hard. But once that was implemented, the challenge was just counting cell in a huge grid. In this challenge, I do multiple passes on the file, which is not very optimized but I didn't see any other way.

 ## Day 5
 Really easy, no big difficulty. i went a bit crazy doing a linked-list, because we actually can know the size of the array before allocating it. (in this case, we still will need to read the file twice: one to know the lenght of the array, and to to fill the array. in my current implemation we only read the file once).
 
 Valgrind says my program has +400 errors, but at least I have no memory leaks.
 I feel like this specific day can be done really easily in Rust (with Iterator and Range).

 
## Day 6
To do.


## Day 7
To do.


## Day 8
To do.


## Day 9
To do.


## Day 10
To do.


## Day 11
To do.


## Day 12
To do.
