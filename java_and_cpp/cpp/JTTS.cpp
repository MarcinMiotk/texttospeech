#include "stdafx.h"
#include "JTTS.h"
#include "SayLibrary.h"
#include <iostream>

using namespace std;

void javaException(JNIEnv * env, const char* message) {
	env->ThrowNew(env->FindClass("java/lang/Exception"), message);
}

jobject createResult(JNIEnv * env, bool success, const char* message) {
	// create net.keinesorgen.tts.SayResult instance
	jobject result(NULL);
	jclass resultClass = env->FindClass("net/keinesorgen/tts/SayResult");
	if (NULL != resultClass) {
		jmethodID resultClassConstructor = env->GetMethodID(resultClass, "<init>", "()V");
		if (NULL != resultClassConstructor) {
			result = env->NewObject(resultClass, resultClassConstructor);
			if (NULL != result) {
				env->CallVoidMethod(result, env->GetMethodID(resultClass, "setSuccess", "(Z)V"), success);
				jstring jMessage = env->NewStringUTF(message);
				env->CallVoidMethod(result, env->GetMethodID(resultClass, "setMessage", "(Ljava/lang/String;)V"), jMessage);
			}
			else {
				javaException(env, "I can not create result instance");
			}
		}
		else {
			javaException(env, "I can not constructor for result instance");
		}
	}
	else {
		javaException(env, "I can not find result type");
	}
	return result;
}



wstring convertJString(JNIEnv * env, jstring candidate) {
	const jchar *raw = env->GetStringChars(candidate, 0);
	jsize len = env->GetStringLength(candidate);
	wstring result;
	result.assign(raw, raw + len);
	env->ReleaseStringChars(candidate, raw);
	return result;
}


JNIEXPORT jobject JNICALL Java_net_keinesorgen_tts_Tts_say(
	JNIEnv * env, jobject jo, jstring language, jstring text)
{

	// convert jstring into const wchar_t *

	// say
	wstring sayLanguage = convertJString(env, language);
	wstring sayText = convertJString(env, text);

	SayResult result = say(sayLanguage.c_str(), sayText.c_str());
	return createResult(env, result.success, result.message);
}
