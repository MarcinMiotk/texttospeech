// SayLibrary.cpp : Defines the exported functions for the DLL application.
//

#include "stdafx.h"
#include "SayLibrary.h"

SAYLIBRARY_API SayResult say(const wchar_t *language, const wchar_t * text)
{
	ISpVoice *pVoice(NULL);
	ISpObjectToken *cpToken(NULL);
	SayResult result;

	// COM initialize
	if (SUCCEEDED(::CoInitialize(NULL))) {
		// play

		if (SUCCEEDED(CoCreateInstance(CLSID_SpVoice, NULL, CLSCTX_ALL, IID_ISpVoice, (void **)&pVoice))) {
			if (SUCCEEDED(SpFindBestToken(SPCAT_VOICES, language, L"", &cpToken))) {
				if (SUCCEEDED(pVoice->SetVoice(cpToken))) {
					// speak
					if (SUCCEEDED(pVoice->Speak(text, 0, NULL))) {
						result.success = true;
						result.message = "Success";
					}
					else {
						result.success = false;
						result.message = "I can not speak this text with this voice";
					}
				}
				else {
					result.success = false;
					result.message = "I can not set this voice";
				}
			}
			else {
				result.success = false;
				result.message = "I can not find this voice";
			}
		}
		else {
			result.success = false;
			result.message = "I can not create SpVoice COM instance";
		}


		// resources release
		if (NULL != pVoice) {
			pVoice->Release();
			pVoice = NULL;
		}
		if (NULL != cpToken) {
			cpToken->Release();
			cpToken = NULL;
		}

		// COM uninitialize
		::CoUninitialize();
	}
	else {
		result.success = false;
		result.message = "I can not initialize COM";
	}

	return result;
}
