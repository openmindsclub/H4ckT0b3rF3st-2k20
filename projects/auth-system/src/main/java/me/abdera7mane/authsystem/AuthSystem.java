package me.abdera7mane.authsystem;

import com.sun.javafx.application.PlatformImpl;
import com.sun.javafx.css.StyleManager;

import javafx.animation.Animation;
import javafx.animation.Transition;
import javafx.application.Application;
import javafx.application.Platform;
import javafx.fxml.FXMLLoader;
import javafx.geometry.Pos;
import javafx.geometry.Rectangle2D;
import javafx.scene.Parent;
import javafx.scene.Scene;
import javafx.scene.control.Alert;
import javafx.scene.control.Button;
import javafx.scene.control.ChoiceBox;
import javafx.scene.control.Label;
import javafx.scene.image.Image;
import javafx.scene.layout.StackPane;
import javafx.scene.layout.VBox;
import javafx.scene.shape.Circle;
import javafx.stage.Screen;
import javafx.stage.Stage;
import javafx.util.Duration;

import me.abdera7mane.authsystem.control.ExceptionDialog;
import me.abdera7mane.authsystem.scenes.ConnectionMenu;
import me.abdera7mane.authsystem.theme.Theme;
import me.abdera7mane.authsystem.util.sql.SqlStorageService;

import java.io.BufferedReader;
import java.io.IOException;
import java.io.InputStream;
import java.io.InputStreamReader;
import java.sql.SQLException;
import java.util.ArrayList;
import java.util.List;

public class AuthSystem extends Application implements AuthStateChangeListener {
    private static AuthSystem instance;
    public static final String DEFAULT_STYLE_PATH = "styles/default.css";
    public static final Image APP_ICON = new Image("assets/app.png");
    public static final Image KEY_ICON = new Image("assets/key.png");

    public final List<Theme> themes = new ArrayList<>();
    private Stage primaryStage;
    private SqlStorageService database;
    private AuthState authState;
    private ConnectionMenu connectionMenu;
    private Stage connectionStage;
    private Label helloLabel= new Label("Waiting to connect...");
    private Circle transistionCircle;

    public static void main(String[] args) {
        launch(args);
    }

    @Override
    public void start(Stage primaryStage) {
        instance = this;
        this.primaryStage = primaryStage;
        loadThemes();

        Screen screen = Screen.getPrimary();

        StackPane root = new StackPane();

        Button connectButton = new Button("connect");
        connectButton.setId("recommanded");
        connectButton.setOnAction(action -> this.connectionStage.show());

        VBox vBox = new VBox();
        vBox.setAlignment(Pos.CENTER);

        VBox subVBox = new VBox();
        subVBox.setAlignment(Pos.CENTER);
        subVBox.getChildren().addAll(
                this.helloLabel,
                connectButton
        );

        ChoiceBox<Theme> choiceBox = new ChoiceBox<>();
        choiceBox.setValue(themes.get(0));
        choiceBox.getItems().addAll(themes);
        choiceBox.setOnAction(action -> choiceBox.getValue().setDefault());

        vBox.getChildren().addAll(
                choiceBox,
                subVBox
        );



        root.getChildren().add(vBox);

        Scene main = new Scene(root);

        primaryStage.setTitle("AuthSystem");
        primaryStage.getIcons().add(APP_ICON);
        primaryStage.setScene(main);
        primaryStage.setWidth(800.00);
        primaryStage.setHeight(500.00);
        primaryStage.show();
        primaryStage.centerOnScreen();
        primaryStage.setOnCloseRequest(event -> {
            try {
                Platform.exit();
            } catch (RuntimeException e) {
                new ExceptionDialog("", e);
            }
        });

        this.connectionMenu = new ConnectionMenu(new StackPane());
        connectionMenu.registerListener(this);

        this.connectionStage = new Stage();
        connectionStage.setTitle("connection menu");
        connectionStage.getIcons().add(KEY_ICON);
        connectionStage.setScene(connectionMenu);
        connectionStage.centerOnScreen();
        connectionStage.show();

        this.setupDatabase();

        PlatformImpl.setDefaultPlatformUserAgentStylesheet();
        StyleManager.getInstance().addUserAgentStylesheet(DEFAULT_STYLE_PATH);

        // my little circle :D
        this.transistionCircle = new Circle(0.00d);
        this.transistionCircle.setId("bubblo");
        Rectangle2D bounds = screen.getBounds();
        this.transistionCircle.setTranslateX(bounds.getMaxX());
        this.transistionCircle.setTranslateY(bounds.getMaxY());

        root.getChildren().add(this.transistionCircle);
    }

    @Override
    public void stop() throws Exception {
        super.stop();
        this.database.stop();
    }

    private void setupDatabase() {
        this.database = new SqlStorageService();

        Alert alert = null;
        try {
            this.database.setup();
        } catch (SQLException e) {
            alert = new ExceptionDialog("Database error", e);
        } catch (ClassNotFoundException e) {
            alert = new ExceptionDialog("Database driver error", e);
        } finally {
            if (alert != null) alert.showAndWait();
        }

    }

    public Stage getPrimaryStage() {
        return this.primaryStage;
    }

    @SuppressWarnings("ConstantConditions")
    @Override
    public void onAuthStateChange(AuthState newState) {
        Parent userProfile;
        try {
            userProfile = FXMLLoader.load(this.getClass().getClassLoader().getResource("scenes/user_profile.fxml"));
        } catch (IOException | NullPointerException e) {
            new ExceptionDialog("Couldn't load user_profile.fxml", e).showAndWait();
            return;
        }

        AuthStateChangeListener.super.onAuthStateChange(newState);
        this.connectionStage.close();
        if (!getAuthState().isConnected()) {
            return;
        }
        this.helloLabel.setText("Connected");

        final Animation animation = new Transition() {
            {
                this.setCycleDuration(Duration.millis(2_000d));
            }

            protected void interpolate(double frac) {
                final Circle circle = AuthSystem.this.transistionCircle;
                final double radius = circle.getRadius();
                final double additionalRadius = 200.00d;

                circle.setRadius(radius + additionalRadius * frac);
            }

        };
        animation.play();
        animation.setOnFinished(event -> getPrimaryStage().setScene(new Scene(userProfile)));
    }

    @Override
    public void setAuthState(AuthState newState) {
        this.authState = newState;
    }

    @Override
    public AuthState getAuthState() {
        return this.authState;
    }

    public static AuthSystem getInstance() {
        return instance;
    }

    public SqlStorageService getDatabase() {
        return this.database;
    }

    public Theme getTheme(String name) {
        Theme result = null;
        for (Theme theme : this.themes) {
            if (theme.getName().equalsIgnoreCase(name)) {
                result = theme;
                break;
            }
        }
        return result;
    }

    private void loadThemes() {
        themes.clear();
        final String themesDir = "styles";
        try {
            this.getResourceFiles(themesDir).forEach(
                    fileName -> {
                        if (fileName.endsWith(".css")) {
                            Theme theme = new Theme(
                                    fileName.substring(0, Math.max(0, fileName.length() - 4)),
                                    themesDir + "/" + fileName
                            );
                            themes.add(theme);
                        }
                    }
            );
        } catch (IOException e) {
            new ExceptionDialog("Couldn't load themes", e);
        }
    }

    private List<String> getResourceFiles(String path) throws IOException {
        List<String> fileNames = new ArrayList<>();

        try (
                InputStream inputStream = getResourceAsStream(path);
                BufferedReader bufferedReader = new BufferedReader(new InputStreamReader(inputStream))) {
            String resource;

            while ((resource = bufferedReader.readLine()) != null) {
                fileNames.add(resource);
            }
        }

        return fileNames;
    }

    private InputStream getResourceAsStream(String resource) {
        final InputStream inputStream
                = getContextClassLoader().getResourceAsStream(resource);

        return inputStream == null ? getClass().getResourceAsStream(resource) : inputStream;
    }

    private ClassLoader getContextClassLoader() {
        return Thread.currentThread().getContextClassLoader();
    }
}
