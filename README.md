## Tetris in C++ for Mac(0.0)

#### Motivation:
	In Fall 2016, I took Hardware Laboratory at school. For the final project of 
	that course, I had to build a Tetris game with my partner. We used a NIOS-II 
	microprocessor and connected it with a VGA moitor and a USB-keyboard. We 
	programmed the game all in System Verilog.

	However, our game was not fully functioning. We did not have time to finish 
	the condition to check the end of the game. The move of each piece was also 
	kind of buggy.

	And more importantly, my partner definitely did more work than I did. I kind
	of felt upset because I was really bad at System Verilog. *So my first 
	motivation would be to do something I did not do well last time.*

	During the "design process" of that final project, I first suggest writing 
	the game logic all in c and merely used VGA as printf(), keyboard as scanf().
	But to get more difficulty points and fulfilled the purpose of that *Hardware* 
	course, we later went with System Verilog. *So my second motivation would be
	to finish something I came up with.*

	*The third motivation is to see what I can do with my current coding skills.*
	I always felt that what I learned in school is not that "realistic". So I 
	kind of wanted to write something that is of some use.


###### resource:
	This folder contains the image file and font file I used for this project.


###### Usage:
	
	Right now this game only supports MacOS user. (Maybe also Linux users, I did not have a Linux machine to try).

	1. Download all the files from https://github.com/he44/Tetris

	2. Open up a terminal

	3. type "cd /Downloading Path/Tetris", hit enter

	4. type "make", hit enter

	5. type "./tetris", hit enter

	6. Play the game


###### Reference:

	1. 	The video stuff is all done with SFML(Simple and Fast Multimedia Library).
		More information can be found at https://www.sfml-dev.org/index.php

	2.	All the logos used is downloaded online, found by Google.

	3. 	The fonts Consolas I used is also downloaded online, also found by Google.
