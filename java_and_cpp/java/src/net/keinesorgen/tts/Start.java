package net.keinesorgen.tts;

/**
 *
 */
public class Start {

    public static void main(String[] args) throws Exception {

        System.loadLibrary("SayLibrary");
        Tts tts = new Tts();

        try {
            SayResult en = tts.say("Vendor=IVONA Software Sp. z o. o.;Language=809", "This is example messsage");
            System.out.println("en=" + en);
        } catch (Exception ex) {
            System.err.println("Error " + ex);
        }
        try {
            SayResult de = tts.say("Vendor=IVONA Software Sp. z o. o.;Language=407", "Guten Tag. Ich heiße Martin. Ich habe die einfache Applikation gemacht.");
            System.out.println("de=" + de);
        } catch (Exception ex) {
            System.err.println("Error " + ex);
        }
        try {
            SayResult pl = tts.say("Vendor=IVONA Software Sp. z o. o.;Language=415", "Cześć. To jest prosta aplikacja.");
            System.out.println("pl=" + pl);
        } catch (Exception ex) {
            System.err.println("Error " + ex);
        }
    }

}
