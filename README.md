# KeySwap - Effortlessly Swap Text Between Languages

## Overview

Have you ever started writing something only to realize it’s in the wrong language, ending up with text like:
_nh akt tufk phmv go tbbx kt neck phmv cfkk!_

KeySwap is here to solve that problem for you!

KeySwap is a straightforward program that converts the text you’ve copied from one language to another.

### Example

Write `xccv`, copy it, run the program, and paste it back. You should now see `סבבה`.

### Note

The program only supports conversions between English and Hebrew and I do not intend to add anything else.

## How to Use

### Building

1. Clone the repository:
   ```sh
   git clone https://github.com/Idsa0/KeySwap.git
   ```
2. Navigate to the repository directory:
    ```sh
    cd <repository_directory>
    ```
3. Compile the program:
   - If you have makefile installed:
     ```sh
     make
     ```
   - Otherwise with gcc:
     ```sh
     gcc -O3 clipboard.c keyboard.c main.c -o KeySwap.exe
     ```

### Using

1. Copy the text you want to swap.
2. Run the KeySwap program.
3. Paste the text back, and it should now be in the correct language.
