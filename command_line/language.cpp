//#pragma once 
#include "stdafx.h"
#include "language.h"

wchar_t * getLanguage(wchar_t * languageShortcut) throw (wchar_t*)
{	
	if (wcscmp(languageShortcut, L"EN") == 0) {
		return L"Vendor=IVONA Software Sp. z o. o.;Language=809";
	}
	else if(wcscmp(languageShortcut, L"DE") == 0){
		return L"Vendor=IVONA Software Sp. z o. o.;Language=407";
	}
	else if (wcscmp(languageShortcut, L"PL") == 0) {
		return L"Vendor=IVONA Software Sp. z o. o.;Language=415";
	}
	else {
		throw L"I don't uderstand your language";
	}
}
