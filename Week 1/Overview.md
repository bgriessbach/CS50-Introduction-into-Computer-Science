# Week 1 CS50:

## mario.c
Write, in a file called mario.c in your ~/workspace/pset1 directory, a program that recreates these half-pyramids using hashes (#) for blocks.

To make things more interesting, first prompt the user for the half-pyramids' heights, a non-negative integer no greater than 23. (The height of the half-pyramids pictured above happens to be 4, the width of each half-pyramid 4, with an a gap of size 2 separating them.)

If the user fails to provide a non-negative integer no greater than 23, you should re-prompt for the same again.

Then, generate (with the help of printf and one or more loops) the desired half-pyramids.

Take care to left-align the bottom-left corner of the left-hand half-pyramid with the left-hand edge of your terminal window.

## water.c
Write, in a file called water.c, a program that prompts the user for the length of his or her shower in minutes (as a positive integer) and then prints the equivalent number of bottles of water (as an integer)

For simplicity, you may assume that the user will input a positive integer, so no need for error-checking (or any loops) this time! And no need to worry about overflow!

## credit.c
In credit.c, write a program that prompts the user for a credit card number and then reports (via printf) whether it is a valid American Express, MasterCard, or Visa card number, per the definitions of each’s format herein.

So that we can automate some tests of your code, we ask that your program’s last line of output be AMEX\n or MASTERCARD\n or VISA\n or INVALID\n, nothing more, nothing less, and that main always return 0.

For simplicity, you may assume that the user’s input will be entirely numeric (i.e., devoid of hyphens, as might be printed on an actual card).

Do not assume that the user’s input will fit in an int! Best to use get_long_long from CS50’s library to get users' input. (Why?)

## hello.c

Print Hello, World!
