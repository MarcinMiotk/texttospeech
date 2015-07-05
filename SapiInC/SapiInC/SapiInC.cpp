#include "stdafx.h"
#include <iostream>
#include <sapi.h>
#include <sphelper.h>

using namespace std;


bool speak(LPCWSTR text, WCHAR * pszReqAttribs) {
	ISpVoice * pVoice = NULL;
	HRESULT stInitializing = CoCreateInstance(CLSID_SpVoice, NULL, CLSCTX_ALL, IID_ISpVoice, (void **)&pVoice);
	if (SUCCEEDED(stInitializing)) 
	{
		ISpObjectToken* cpToken(NULL);
		HRESULT stTokenFinding = SpFindBestToken(SPCAT_VOICES, pszReqAttribs, L"", &cpToken);
		if (SUCCEEDED(stTokenFinding)) 
		{
			HRESULT stVoiceSetting = pVoice->SetVoice(cpToken);
			if (SUCCEEDED(stVoiceSetting)) 
			{
				HRESULT stSpoken = pVoice->Speak(text, 0, NULL);
				if (SUCCEEDED(stSpoken))
				{
					cpToken->Release();
					cpToken = NULL;

					pVoice->Release();
					pVoice = NULL;

					return true;
				}
				else
				{
					cpToken->Release();
					cpToken = NULL;

					pVoice->Release();
					pVoice = NULL;

					cout << "Error, I couldn't play this text " << text << endl;
					return false;
				}
			}
			else
			{
				cpToken->Release();
				cpToken = NULL;

				pVoice->Release();
				pVoice = NULL;

				cout << "Error, I can't set this voice " << pszReqAttribs << endl;
				return false;
			}
		}
		else 
		{
			pVoice->Release();
			pVoice = NULL;

			cout << "Error, I can't find this voice " << pszReqAttribs << endl;
			return false;
		}
	} else {
		cout << "Error, I can't create Voice instance" << endl;
		return false;
	}

}


	int _tmain(int argc, _TCHAR* argv[])
	{
		if (FAILED(::CoInitialize(NULL)))
			return FALSE;

		{
			bool spokenGerman = speak(
				L"Griechenland ist schon lange ein fester Bestandteil der Tagesordnung im CDU-Präsidium, dem obersten Entscheidungsgremium der Kanzlerpartei. In den vergangenen fünf Jahren debattierten die Parteigranden ein ums andere Mal leidenschaftlich, ob der Verbleib der Griechen im Euro all die Milliarden und Anstrengungen wert sei. Vor allem Minister Wolfgang Schäuble setzt hier gern zu seinen berüchtigt weitschweifigen Vorträgen über die Lage der Weltfinanzen an und über alles sonstige, was ihn gerade beschäftigt.",
				L"Vendor=IVONA Software Sp. z o. o.;Language=407"
				);


			cout << "German version was spoken with status " << spokenGerman << endl;
		}
		{
			bool spokenPolish = speak(
				L"Prezydent Rosji Władimir Putin zaapelował dziś do przywódcy Stanów Zjednoczonych Baracka Obamy o dialog oparty na wzajemnym szacunku i równym traktowaniu. Putin złożył też Obamie życzenia z okazji święta upamiętniającego deklarację niepodległości. Eksperci podkreślają, że to istotny gest w sytuacji niezwykle napiętych kontaktów między Moskwą a Waszyngtonem.",
				L"Vendor=IVONA Software Sp. z o. o.;Language=415"
				);


			cout << "Polish version was spoken with status " << spokenPolish << endl;
		}
		{
			bool spokenEnglish = speak(
				L"Water is supposed to purify: Taking a shower, washing your face, and staying properly hydrated promote good hygiene and health. But sometimes water is the one that gets dirty. That’s why since 1972, when The Clean Water Act was passed, the U.S. Environmental Protection Agency (EPA) has regulated both water pollution and quality standards in an attempt to keep our H2O clean. \n\n\nAnd since summer is prime time for swimming, you may be wondering just exactly how clean the water you jump in really is.To fully understand that, you need to understand how water pollution is gauged — and how dangerous it is.",
				L"Vendor=IVONA Software Sp. z o. o.;Language=809"
				);

			cout << "English version was spoken with status " << spokenEnglish << endl;
		}

		::CoUninitialize();


		return 0;
	}


