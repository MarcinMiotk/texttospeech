#include "stdafx.h"
#include <iostream>
#include <sapi.h>
#include <sphelper.h>

using namespace std;

int _tmain(int argc, _TCHAR* argv[])
{
	cout << "Marcin Miotk is testing tts" << endl;

	ISpVoice * pVoice = NULL;

	if (FAILED(::CoInitialize(NULL)))
		return FALSE;

	HRESULT hr = CoCreateInstance(CLSID_SpVoice, NULL, CLSCTX_ALL, IID_ISpVoice, (void **)&pVoice);
	if (SUCCEEDED(hr))
	{
		cout << "Playing in english" << endl;

		{
			ISpObjectToken* cpTokenEng(NULL);
			SpFindBestToken(SPCAT_VOICES, L"Vendor=IVONA Software Sp. z o. o.;Language=809", L"", &cpTokenEng);
			HRESULT setresult = pVoice->SetVoice(cpTokenEng);
			cout << "Result EN: " << setresult << endl;
			hr = pVoice->Speak(L"Water is supposed to purify: Taking a shower, washing your face, and staying properly hydrated promote good hygiene and health. But sometimes water is the one that gets dirty. That’s why since 1972, when The Clean Water Act was passed, the U.S. Environmental Protection Agency (EPA) has regulated both water pollution and quality standards in an attempt to keep our H2O clean. \n\n\nAnd since summer is prime time for swimming, you may be wondering just exactly how clean the water you jump in really is.To fully understand that, you need to understand how water pollution is gauged — and how dangerous it is.", 0, NULL);
			cpTokenEng->Release();
		}


		{

			ISpObjectToken* cpTokenPol(NULL);
			SpFindBestToken(SPCAT_VOICES, L"Vendor=IVONA Software Sp. z o. o.;Language=415", L"", &cpTokenPol);

			cout << "Playing in polish" << endl;
			HRESULT setresult = pVoice->SetVoice(cpTokenPol);
			cout << "Result EN: " << setresult << endl;
			hr = pVoice->Speak(L"Prezydent Rosji Władimir Putin zaapelował dziś do przywódcy Stanów Zjednoczonych Baracka Obamy o dialog oparty na wzajemnym szacunku i równym traktowaniu. Putin złożył też Obamie życzenia z okazji święta upamiętniającego deklarację niepodległości. Eksperci podkreślają, że to istotny gest w sytuacji niezwykle napiętych kontaktów między Moskwą a Waszyngtonem.", 0, NULL);
			cpTokenPol->Release();

		}
		cout << "The text was played" << endl;

		pVoice->Release();
		pVoice = NULL;

		cout << "Application releases the pVoice" << endl;
	}
	else
	{
		cout << "Not succeeded" << endl;
	}

	::CoUninitialize();


	return 0;
}


