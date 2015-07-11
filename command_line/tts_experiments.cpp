// tts_experiments.cpp : Defines the entry point for the console application.
//

#include "stdafx.h"
#include "language.h"
#include "speak.h"

using namespace std;

int wmain(int argc, wchar_t* argv[])
{

	if (FAILED(::CoInitialize(NULL)))
		return FALSE;

	if (argc == 3) {
		try {
			wchar_t * voice = getLanguage(argv[1]);
			wcout << "Choosed voice " << voice << endl;

			bool spoken = speak(argv[2], voice);
			wcout << "Result " << spoken << " returned by speaking process." << endl;
		}
		catch (wchar_t* ex) {
			wcout << "ERROR " << ex << endl;
		}
	}
	else {
		wcout << "ERROR " << " You made a mistake in arguments." << endl;
	}

	::CoUninitialize();

	return 0;
}

