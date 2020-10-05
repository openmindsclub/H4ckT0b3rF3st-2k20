package me.abdera7mane.authsystem.scenes;

import javafx.animation.Animation;
import javafx.animation.Transition;
import javafx.collections.ObservableList;
import javafx.event.ActionEvent;
import javafx.geometry.Insets;
import javafx.geometry.Pos;
import javafx.geometry.Rectangle2D;
import javafx.scene.Node;
import javafx.scene.Scene;
import javafx.scene.control.Button;
import javafx.scene.control.CheckBox;
import javafx.scene.control.Label;
import javafx.scene.control.PasswordField;
import javafx.scene.control.TextField;
import javafx.scene.effect.Bloom;
import javafx.scene.layout.HBox;
import javafx.scene.layout.StackPane;
import javafx.scene.layout.VBox;
import javafx.scene.paint.Paint;
import javafx.scene.shape.Circle;
import javafx.stage.Screen;
import javafx.util.Duration;

import me.abdera7mane.authsystem.AuthState;
import me.abdera7mane.authsystem.AuthStateChangeListener;
import me.abdera7mane.authsystem.User;
import me.abdera7mane.authsystem.util.UserUtils;

import java.util.LinkedList;
import java.util.List;

@SuppressWarnings("unused")
public class ConnectionMenu extends Scene {
    private final Label title;
    private final Label messageLabel;
    private final TextField usernameField;
    private final PasswordField passwordField;
    private final Button loginButton;
    private final CheckBox registerCheckBox;
    private final List<AuthStateChangeListener> listeners = new LinkedList<>();

    public ConnectionMenu(StackPane root) {
        this(root, 600.00d, 400.00d);
    }

    public ConnectionMenu(StackPane root, double width, double height) {
        this(root, width, height, Paint.valueOf("WHITE"));
    }

    public ConnectionMenu(StackPane root, Paint fill) {
        this(root, 500.00d, 300.00d, fill);
    }

    public ConnectionMenu(StackPane root, double width, double height, Paint fill) {
        super(root, width, height, fill);

        StackPane pane = ((StackPane) this.getRoot());

        this.decorateRoot(pane);

        this.title = new Label();
        this.title.setId("title");
        this.title.setPadding(new Insets(0.00d, 20.00d, 20.00d, 20.00d));

        this.setTitle("Welcome back !");

        this.messageLabel = new Label();
        this.messageLabel.setId("warning");

        this.usernameField = new TextField();
        this.usernameField.setPromptText("Enter your username");

        VBox vBox = new VBox();
        vBox.setSpacing(8.00d);
        vBox.setAlignment(Pos.CENTER);

        VBox subVBox = new VBox();
        subVBox.setMaxWidth(360.00d);
        subVBox.setSpacing(5.00d);
        subVBox.setAlignment(Pos.BASELINE_LEFT);

        Label usernameLabel = new Label("_Username");
        usernameLabel.setLabelFor(this.usernameField);
        usernameLabel.setMnemonicParsing(true);
        usernameLabel.setMaxWidth(Double.MAX_VALUE);

        this.passwordField = new PasswordField();
        this.passwordField.setPromptText("Enter the password");

        Label passwordLabel = new Label("_Password");
        passwordLabel.setMnemonicParsing(true);
        passwordLabel.setLabelFor(this.passwordField);
        passwordLabel.setMaxWidth(Double.MAX_VALUE);

        this.loginButton = new Button("Connect");
        this.loginButton.setId("recommanded");
        this.loginButton.setOnAction(this::onLoginButtonClick);

        this.registerCheckBox = new CheckBox("New account");

        HBox hBox = new HBox();
        hBox.setPadding(new Insets(10.00d, 0.00d, 0.00d, 0.00d));
        hBox.setMinHeight(60.00d);
        hBox.setSpacing(5.00d);
        hBox.setAlignment(Pos.CENTER);
        hBox.getChildren().addAll(this.registerCheckBox, this.loginButton);

        subVBox.getChildren().addAll(
                usernameLabel, this.usernameField,
                passwordLabel, this.passwordField
        );

        ObservableList<Node> children = vBox.getChildren();
        children.addAll(
                this.title,
                this.messageLabel,
                subVBox
        );
        children.add(hBox);

        pane.getChildren().add(vBox);

    }

    public void setTitle(String title) {
        this.title.setText(title);
    }

    public String getTitle() {
        return this.title.getText();
    }

    public void registerListener(AuthStateChangeListener listener) {
        this.listeners.add(listener);
    }

    public void unregisterListener(AuthStateChangeListener listener) {
        this.listeners.remove(listener);
    }

    private void onLoginButtonClick(ActionEvent event) {

        String username = this.usernameField.getText();
        String password = this.passwordField.getText();
        if (username.isEmpty() || password.isEmpty()) {
            this.setWarningMessage("Fill the missing forms");
        }
        else if (this.registerCheckBox.isSelected()) {
            if (UserUtils.findUser(username) != null) {
                this.setWarningMessage("A user with the same username is already registered");
                return;
            }
            this.disableAllForms(true);
            this.setWarningMessage("Creating ...");
            UserUtils.register(username, password);
            User createdUser = UserUtils.findUser(username);
            if (createdUser != null) {
                this.setWarningMessage("");
                this.notifyListeners(new AuthState(true, createdUser));
            } else {
                this.setWarningMessage("Registration Failed, retry again");
            }
        }
        else {
            User user = UserUtils.findUser(username);
            if (user == null) {
                this.setWarningMessage("couldn't find that account, register maybe ?");
            }
            else if (UserUtils.matchPassword(password, user)) {
                this.notifyListeners(new AuthState(true, user));
            } else {
                this.setWarningMessage("Bad credentials");
            }
        }
        this.disableAllForms(false);
    }

    private void disableAllForms(boolean value) {
        this.usernameField.setEditable(!value);
        this.passwordField.setEditable(!value);
        this.loginButton.setDisable(value);
        this.registerCheckBox.setDisable(value);
    }

    private void decorateRoot(StackPane pane) {
        Rectangle2D bounds = Screen.getPrimary().getBounds();
        double xBound = bounds.getMaxX();
        double yBound = bounds.getMaxY();
        double minX = bounds.getMinX();
        double minY = bounds.getMinY();

        double innerWidth = bounds.getWidth() * 0.50d;
        double innerHeight = bounds.getHeight() * 0.7d;
        Rectangle2D innerBounds =
                new Rectangle2D(
                        minX - innerWidth / 2,
                        minY - innerHeight / 2,
                        innerWidth,
                        innerHeight
                );

        ObservableList<Node> nodes = pane.getChildren();
        for (int i = 0; i < 50; i++) {
            double maxRadius = 90.00d;
            double minRadius = 5.00d;
            double radius = Math.max(minRadius, Math.random() * maxRadius);

            Circle circle = new Circle(Math.random() * 100.00d);
            circle.setId("bubblo");

            float green = (float) (Math.random() * 0.85d);
            float blue = (float) Math.max(0.75f, Math.random() * 0.85d);
//            circle.setFill(new Color(1.0f, green, blue, Math.random()));
            circle.setOpacity(Math.random());

            double translateX = Math.random() * xBound - xBound / 2;
            double translateY = Math.random() * yBound - yBound / 2;
            if (innerBounds.contains(translateX, translateY)) {
                continue;
            }

            circle.setTranslateX(translateX);
            circle.setTranslateY(translateY);
            circle.setEffect(new Bloom(0.10d));
            nodes.add(circle);
            Animation floatAnimation = getFloatAnimation(circle);
            floatAnimation.play();
        }
    }

    protected void notifyListeners(AuthState newState) {
        listeners.forEach(listener -> listener.onAuthStateChange(newState));
    }

    public void setWarningMessage(String message) {
        this.messageLabel.setText(message);
    }

    protected Animation getFloatAnimation(Node node) {
        final Transition transition = new Transition() {
            private final double initYPos;
            private final double top = 20.00d * Math.random();
            {
                this.initYPos = node.getTranslateY();
                this.setCycleDuration(Duration.millis(3_000d));
            }

            @Override
            protected void interpolate(double frac) {
                node.setTranslateY(initYPos + top * Math.sin(Math.PI * frac));
            }
        };
        transition.setAutoReverse(true);
        transition.setCycleCount(Animation.INDEFINITE);
        return transition;
    }
}
