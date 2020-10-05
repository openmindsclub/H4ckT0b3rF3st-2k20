module auth.system {
    requires java.sql;
    requires javafx.controls;
    requires javafx.graphics;
    requires javafx.base;
    requires javafx.fxml;
    requires com.h2database;
    requires spring.security.crypto;
    requires com.google.gson;

    exports me.abdera7mane.authsystem;

}