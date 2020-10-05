package me.abdera7mane.authsystem.theme;

import com.sun.javafx.application.PlatformImpl;
import com.sun.javafx.css.StyleManager;

public class Theme {
    private final String name;
    private final String stylePath;

    public Theme(String name, String stylePath) {
        this.name = name;
        this.stylePath = stylePath;
    }

    public String getName() {
        return this.name;
    }

    public String getStylePath() {
        return this.stylePath;
    }

    public void setDefault() {
        PlatformImpl.setDefaultPlatformUserAgentStylesheet();
        StyleManager.getInstance().addUserAgentStylesheet(stylePath);
    }

    @Override
    public String toString() {
        return this.name;
    }
}
