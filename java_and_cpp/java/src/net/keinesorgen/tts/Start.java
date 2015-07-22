package net.keinesorgen.tts;

/**
 *
 */
public class Start {

    public static void main(String[] args) {
        // TODO code application logic here
        System.loadLibrary("SayLibrary");
        
        Tts tts = new Tts();
        SayResult en = tts.say("Vendor=IVONA Software Sp. z o. o.;Language=809", "Hello. This is simple application. I connect Java code and C++ code.");
        System.out.println(en);
        SayResult de = tts.say("Vendor=IVONA Software Sp. z o. o.;Language=407", "Guten Tag. Ich heiße Martin. Ich habe die einfache Applikation gemacht.");
        System.out.println(de);
        SayResult pl = tts.say("Vendor=IVONA Software Sp. z o. o.;Language=415", "Cześć. To jest prosta aplikacja.");
        System.out.println(pl);
        
    }

}
