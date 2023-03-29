# Arduino_without_IDE

Yes, we are doing it today. In order to better understand it, we will take the difficult route.  🎓🎓  

Arduino ♾️ is a widely used platform for building electronic projects, and the Arduino Integrated Development Environment (IDE) is the most popular way to write and upload code to an Arduino board. However, there are other ways to write Arduino code that don’t require the IDE. In this blog, we will discuss two alternative methods for writing Arduino code.

- [x] Method 1: Using Linux terminal to imitate an Arduino make file
- [x] Method 2: Using VSCode Arduino Extension
- [x] Method 3: Using Raspberry Pi with Arduino.mk 

## 1️⃣ Method 1: Using Linux terminal to imitate an Arduino Makefile
The Arduino IDE is built on top of a command-line tool called “avr-gcc”, which is used to compile and upload code to the Arduino board. By using the terminal, we can imitate an Arduino makefile to compile and upload the code to the board.

Here are the steps to follow:

### Step 1: Install the required tools🧰

To compile and upload code to the Arduino board, we need to install the avr-gcc toolchain, avrdude, and make. We can install these tools on Ubuntu or Debian by running the following command:
```bash 
sudo apt-get install gcc-avr avr-libc avrdude make
```

### Step 2: Create a new file 📁

Create a new file in your favorite text editor (Nano, Vim, gedit) and save it with a “.c” extension. For example, if you want to create a program to blink an LED connected to pin 13, you can create a file called “blink.c” with the following code:

I have a folder called “Projects” that I will use to organize my files. You may choose whatever suits you.

![image](https://miro.medium.com/v2/resize:fit:640/0*xAou7ekCEhuZ-Hkb) 

> blink.c looks like this:

```c#
#include <avr/io.h>
#include <util/delay.h>
int main(void)
{
 DDRB |= (1 << PB5); // Set pin 13 as an output, refer schematics for the port configs
 while (1) {
 PORTB ^= (1 << PB5); // Toggle pin 13
 _delay_ms(500);
 }
 return 0;
}
``` 

### Step 3: Create a makefile 📁

Create a new file called “Makefile” in the same directory as your “blink.c” file, and add the following code:

```mk
MCU = atmega328p
F_CPU = 16000000UL
PROGRAMMER = arduino
PORT = /dev/ttyACM0
CC = avr-gcc
CFLAGS = -Wall -Os -DF_CPU=$(F_CPU) -mmcu=$(MCU)
OBJCOPY = avr-objcopy
OBJCOPYFLAGS = -j .text -j .data -O ihex
AVRDUDE = avrdude
AVRDUDEFLAGS = -p $(MCU) -c $(PROGRAMMER) -P $(PORT)
all: blink.hex
blink.hex: blink.elf
 $(OBJCOPY) $(OBJCOPYFLAGS) $< $@
blink.elf: blink.o
 $(CC) $(CFLAGS) -o $@ $<
blink.o: blink.c
 $(CC) $(CFLAGS) -c $<
upload: blink.hex
 $(AVRDUDE) $(AVRDUDEFLAGS) -U flash:w:$<
clean:
 rm -f blink.o blink.elf blink.hex
```

Err: Don’t use space, instead use Tab in the necessary places, or else you may arrive at the following error message :

![image](https://miro.medium.com/v2/resize:fit:640/0*Ho47F6wKFsG7m5pJ)

### Step 4: Compile and upload the code 🗃️

Open a terminal and navigate to the directory where your “blink.c” and “Makefile” files are located. Run the following command to compile the code:
```
make
```
Terminal output for make:

![image](https://miro.medium.com/v2/resize:fit:720/0*0mv6YclCMSM0dxZj)

This will generate a “.hex” file in the same directory. To upload the code to the Arduino board, run the following command:
```
make upload
``` 
Terminal output for upload:

![image](https://miro.medium.com/v2/resize:fit:1400/0*NMLrcj8ECFjSQTrA)

This will upload the code to the board using the specified programmer and port.

Here are a few commands that might be useful if you are a beginner to Linux:

To view the arduino port and provide read/write access to the user, You can use 777 to give all users the same rights

![image](https://miro.medium.com/v2/resize:fit:720/0*Rh_gpdzBdp229cBf)

## 2️⃣️ Method 2: Using VSCode Arduino Extension
VSCode (Visual Studio Code) is a popular code editor that supports many programming languages, including Arduino. The VSCode Arduino extension provides a powerful and easy-to-use environment for writing and uploading Arduino code.

![image](https://miro.medium.com/v2/resize:fit:720/0*YqINbXsuNrZd6vVS)

> Steps: Create a folder, add two files, blink.ino, and Makefile. They are the same as in the previous method. 🗄️🗃️📁

⚠️ The name of “*.ino” file should be similar to that of the folder name.

![iamge](https://miro.medium.com/v2/resize:fit:1400/0*XvrtT1pXgetyPlIh)

Verify and upload the code similar to arduino-ide using the icons on top right corner.

|![image](https://miro.medium.com/v2/resize:fit:458/0*H1irikjH6d36LA8E)|![image](https://miro.medium.com/v2/resize:fit:458/0*nJ6XLna54igP7GYo)|
|:-:|:-:|

![image](https://miro.medium.com/v2/resize:fit:720/0*BRiKs4t1iT5-529J)

## 3️⃣ Method 3: Using Raspberry Pi with Arduino.mk

If you have a Raspberry Pi, you can use it to compile and upload Arduino code using the Arduino.mk *“Makefile”.* This method requires a bit of setup, but once it’s done, it provides a flexible and powerful way to develop Arduino projects.

Here are the steps to follow:

### Step 1: Install the required tools🧰

On your Raspberry Pi, install the required tools by running the following command:  
```bash
sudo apt-get install arduino arduino-mk
```  
This will install the Arduino IDE and the <b>Arduino.mk Makefile.</b>

### Step 2: Create a new project directory 🗄️

Create a new directory for your Arduino project by running the following command:
```
mkdir blink
```
### Step 3: Create a new file 📁

Create a new file in your favorite text editor and save it with a <b>“.ino”</b> extension. For example, if you want to create a program to blink an LED connected to pin 13, you can create a file called “blink.ino” with the following code:

The code is similar to the arduino code of **method 2**.  
```c#
void setup() {
 pinMode(13, OUTPUT);
}
void loop() {
 digitalWrite(13, HIGH);
 delay(500);
 digitalWrite(13, LOW);
 delay(500);
}
```
  
### Step 4: Create a Makefile 📁

Create a new file called “Makefile” in the same directory as your “blink.ino” file, and add the following code:  
```
BOARD_TAG = uno
ARDUINO_PORT = /dev/ttyACM0

include /usr/share/arduino/Arduino.mk
```  
This Makefile specifies the board and serial port to use, and includes the Arduino.mk Makefile.

### Step 5: Compile and upload the code 🗃️

Open a terminal and navigate to the directory where your “blink.ino” and “Makefile” files are located. Run the following command to compile the code:  
```
make
```  
This will generate a “.hex” file in the same directory. To upload the code to the Arduino board, run the following command:  
```
make upload
```  
This will upload the code to the board using the specified serial port.  

That’s it! With these steps, you can write and upload Arduino code using the Raspberry Pi and the Arduino.mk Makefile. This method can also be used with other Arduino-compatible boards, as long as you specify the correct board and serial port in the Makefile.  

Run the following command after uploading if you want to reuse the code:  
```
make clean monitor upload
```  
Additionally, a serial monitor using “Screen” would be opened. This will be covered in later blogs.

* You can find the [blog](https://medium.com/@dev-ansh-r/write-arduino-code-without-arduino-ide-14cf6021e816) here.

    * Ping me on [LinkedIn](https://www.linkedin.com/in/dev-ansh-r/) for any further assistance. Seeeeee yaa!!! 😁👋🏾😁