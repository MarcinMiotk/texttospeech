// SayLibrary.cpp : Defines the exported functions for the DLL application.
//

#include "stdafx.h"
#include "SayLibrary.h"
#include <sapi.h>
#include <sphelper.h>

SAYLIBRARY_API SayResult say(const wchar_t * language, const wchar_t * text)
{
	SayResult result;

	// using SAPI 5
	ISpVoice *pVoice(NULL);
	ISpObjectToken *cpToken(NULL);

	// COM initialize
	if (SUCCEEDED(::CoInitialize(NULL))) {

		if (SUCCEEDED(CoCreateInstance(CLSID_SpVoice, NULL, CLSCTX_ALL, IID_ISpVoice, (void **)&pVoice))) {

			// find voice
			if (SUCCEEDED(SpFindBestToken(SPCAT_VOICES, language, L"", &cpToken))) {

				// set the voice

				if (SUCCEEDED(pVoice->SetVoice(cpToken))) {

					// speak it

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
			result.message = "I can not create Voice instance";
		}





		// COM uninitialize and resources releasing

		if (NULL != pVoice) {
			pVoice->Release();
			pVoice = NULL;
		}
		if (NULL != cpToken) {
			cpToken->Release();
			cpToken = NULL;
		}

		::CoUninitialize();
	}
	else {
		result.success = false;
		result.message = "I can not initialize COM";
	}


	return result;
}
