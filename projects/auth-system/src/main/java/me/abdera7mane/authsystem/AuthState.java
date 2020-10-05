package me.abdera7mane.authsystem;

public class AuthState {
    private boolean connected;
    private final User user;

    public AuthState(boolean connected, User user) {
        this.connected = connected;
        this.user = user;
    }

    public User getUser() {
        return this.user;
    }

    public boolean isConnected() {
        return this.connected;
    }

    public void setConnected(boolean connected) {
        this.connected = connected;
    }
}
