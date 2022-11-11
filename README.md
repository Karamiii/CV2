# Mini scale hotel reservation project

This project was done with C++ and currently uses Windows only libraries.
If you want to run this porgram, you can use Visual Studio for example.

## Description

In this reservation program you can reserve room/rooms with your name from a hotell. 
Program uses structured arrays containing slots for name and reservation number.

The idea behind the reservation is pretty simple. Array size is the amount of rooms, and each room contains a name and a reservation number. After you have reserved a room, you can check, cancel or add your reservations by using your name or the reservation number that was generated to you.

When the program checks your input, it will simply go over the array and compare the index value of the name/res.number to the user input value.


## Needs fixing

- When i first completed the projcet, i used goto commands to navigate the the code. Later on i discovered that goto commands are not part of good coding etiquette, so i have started to get rid of them and replacing them with boolean controlled while loops. There are still some gotos left but most of them are replaced.

- Translatin the code, comments and the user interface from Finnish to English.

- Adding proper documentation for the project.








