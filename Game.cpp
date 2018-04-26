// Term Project.cpp : Defines the entry point for the console application.
//
#include "stdafx.h"
#include "GameManager.h"

int main()
{
Start:
	GameManager gameManager(1920,1080);
	if (gameManager.Start()) {
		goto Start;
	}
    return 0;
}

