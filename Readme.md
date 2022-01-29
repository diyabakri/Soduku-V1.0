# Terminal Soduku v1.0

Termnal Soduku v1.0 the first version of a personal projct created the soduku game in the terminal
with the use of event based key detection all done in the C language for Unix

## Compile

```bash
make
```
## Run


```bash
make run

or

sudo ./Soduku
```
Note:this program needs sudo in order to access the events folder for unix 

## GAME START

Upon Starting the exe the game will generate a new board and the termnal will show the game board 
with instructuons 
Note: numpad keys are also supported

```bash
			 possible values: 2 4 7 8 
			-----------------------------
			| ||#||#| |#||1||#| |#||9||#| 
			|#||6||#| |9|| || | |4||8|| | 
			|3||9||5| |8|| || | | || || | 
			-----------------------------
			|#|| || | | ||9|| | | ||6|| | 
			|1|| ||3| | ||6|| | |7|| || | 
			|6|| ||9| |7|| ||5| | ||1||4| 
			-----------------------------
			|#|| || | |6|| || | | || ||2| 
			|9|| ||2| | || || | | || || | 
			|#||7|| | |2||3|| | |8|| || | 
			-----------------------------
			Press arrow keys to move position
		 Press number keys to change the value of a box
		Press the backspace key to remove number from box
		 Press the s key to automaticly solve the puzzle
```

## GAME OVER

Upon finishing a game by filing all the numbers the player can press y for a new game or n to end the game

```bash
			 possible values: 
			-----------------------------
			|7||4||8| |5||1||2| |6||9||3| 
			|2||6||1| |9||7||3| |4||8||5| 
			|3||9||5| |8||4||6| |1||2||7| 
			-----------------------------
			|4||5||7| |3||9||1| |2||6||8| 
			|1||2||3| |4||6||8| |7||5||9| 
			|6||8||9| |7||2||5| |3||1||4| 
			-----------------------------
			|8||1||4| |6||5||7| |9||3||2| 
			|9||3||2| |1||8||4| |5||7||6| 
			|5||7||6| |2||3||9| |8||4||1| 
			-----------------------------
			 Play new game ? (y/n)

```

## Contributing
Pull requests are welcome. For major changes, please open an issue first to discuss what you would like to change.
note for each change in any of the .c files there is a need to recompile the code before the changes are applied
compile using the [gcc](https://gcc.gnu.org/) compiler with the use of makefile any added files need to be also added 
to the makefile


```bash
```
