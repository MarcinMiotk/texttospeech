package net.keinesorgen.tts;

/**
 *
 */
public class SayResult {
    private boolean success;
    private String message;

    public SayResult() {
    }

    @Override
    public String toString() {
        return success+", "+message;
    }

    
    
    
    /**
     * @return the success
     */
    public boolean isSuccess() {
        return success;
    }

    /**
     * @param success the success to set
     */
    public void setSuccess(boolean success) {
        this.success = success;
    }

    /**
     * @return the message
     */
    public String getMessage() {
        return message;
    }

    /**
     * @param message the message to set
     */
    public void setMessage(String message) {
        this.message = message;
    }
    
    
}
