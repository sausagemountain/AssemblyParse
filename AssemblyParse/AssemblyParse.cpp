#include "stdafx.h"
#include <stdlib.h>
#include <iostream>
#include <string>

using namespace std;

void main()
{
    cout << "enter a number, decimal point is a DOT" << endl;

    string input = "358";
    cin >> input;

    const int inpLength = input.length();
    char inpC[10];
    for (int i = 0; i < inpLength; i++)
        inpC[i] = input[i];

    int zero = '0';
    int nine = '9';
    int minus = '-';
    int dot = '.';

    bool output = true;
    bool floatN = false;
    double outputD;
    int outputNumber;
    int dud;

    _asm
    {
        xor edx, edx
        mov ecx, inpLength
        mov edi, 10

        xor esi, esi
        inc esi

        xor ebx, ebx
        po1 :
        xor edx, edx
        xor eax, eax
        dec ecx
        mov al, inpC[ecx]

        cmp eax, dot
            je floatingP
        cmp eax, minus
            je negative
        xor edx, edx

        sub eax, zero
        mul esi
        add ebx, eax

        mov eax, esi
        mul edi
        mov esi, eax 
        contCycle :
        inc ecx
            loop po1
        endLoop :
        mov edx, 1
        cmp floatN, dl
            je floatFin
        jmp notfin

        negative :
        mov edx, 1
        cmp floatN, dl
            je floatNeg
        contNegFloat :
        neg ebx
        jmp endloop

        floatingP :
        mov dud, ebx
        finit
        fild dud
        mov dud, esi
        fidiv dud
        xor ebx, ebx
        mov esi, 1
        mov floatN, 1
        jmp contCycle

        floatFin :
        mov dud, ebx
        fiadd dud
        fstp outputD
        jmp fin

        floatNeg :
        xor edx, edx
        dec edx
        mov dud, edx
        fimul dud
        jmp contNegFloat

        notfin :
        mov outputNumber, ebx
        fin:
    }

    if (output)
        if (!floatN)
            cout << outputNumber << endl;
        else
            cout << outputD << endl;
    else
        cout << "this is not a number" << endl;

    system("pause");
}