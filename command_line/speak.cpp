#include "stdafx.h"
#include "speak.h"

using namespace std;

bool speak(wchar_t * text, wchar_t * pszReqAttribs)
{
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

					wcout << "Error, I couldn't play this text " << text << endl;
					return false;
				}
			}
			else
			{
				cpToken->Release();
				cpToken = NULL;

				pVoice->Release();
				pVoice = NULL;

				wcout << "Error, I can't set this voice " << pszReqAttribs << endl;
				return false;
			}
		}
		else
		{
			pVoice->Release();
			pVoice = NULL;

			wcout << "Error, I can't find this voice " << pszReqAttribs << endl;
			return false;
		}
	}
	else {
		wcout << "Error, I can't create Voice instance" << endl;
		return false;
	}
}
