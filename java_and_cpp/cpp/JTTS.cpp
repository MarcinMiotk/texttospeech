#include "stdafx.h"
#include "JTTS.h"
#include "SayLibrary.h"

using namespace std;

jobject create(JNIEnv * env, bool success, char* message) {
	// result 
	jclass resultClass = env->FindClass("net/keinesorgen/tts/SayResult");
	jmethodID resultClassConstructor = env->GetMethodID(resultClass, "<init>", "()V");
	jobject result = env->NewObject(resultClass, resultClassConstructor);

	env->CallVoidMethod(result, env->GetMethodID(resultClass, "setSuccess", "(Z)V"), success);
	jstring resultMessage = env->NewStringUTF(message);
	env->CallVoidMethod(result, env->GetMethodID(resultClass, "setMessage", "(Ljava/lang/String;)V"), resultMessage);

	return result;
}

const wstring convertJStringToWchar(JNIEnv * env, jstring candidate) {
	const jchar *raw = env->GetStringChars(candidate, 0);
	jsize len = env->GetStringLength(candidate);
	wstring result;
	result.assign(raw, raw + len);
	env->ReleaseStringChars(candidate, raw);
	return result;
}

JNIEXPORT jobject JNICALL Java_net_keinesorgen_tts_Tts_say(JNIEnv * env, jobject jo, jstring language, jstring text)
{
		// convert jstring -> wchar_t *
		wstring pLanguage = convertJStringToWchar(env, language);
		wstring pText = convertJStringToWchar(env, text);

		SayResult result = say(pLanguage, pText);

		return create(env, result.success, result.message);
}
