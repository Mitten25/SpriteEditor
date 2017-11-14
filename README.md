Team Colonel's Sprite Editor v1.0
System Requirements:
C++ compiler
OS: Windows 10


## Code architecture
Formatting:
I.1. All function names will be written in a manner where the first letter is always lowercase and the subsequent words follow with no intermediary characters and start with uppercase letters (camel case)
Example: getPixel()

I.2. All variable names will be written in a manner similar to the function names, camel case. 
Example: int bluePixel;

I.3. All private member variables will be written with an underscore following their end as to differentiate them from argument/parameter variables that have the same name
Example: private int pixel_;  

I.4. All Brackets following class or method declarations/definitions will come after a newline instead of being on the same line as the method or class definition.
Example: 
Class Frame() 
{
}


I.5. Commenting: In line commenting will occur using “//” and will be used above the lines of code it describes. Method and class comment definitions will use “/*” and “*/”
Example:
/* returns a pixel */
int getPixel()
{
// Returns pixel
return pixel;
}
