package me.abdera7mane.authsystem;

public interface AuthStateChangeListener {

    default void onAuthStateChange(AuthState newState)  {
        this.setAuthState(newState);
    }

    void setAuthState(AuthState newState);

    AuthState getAuthState();
}
