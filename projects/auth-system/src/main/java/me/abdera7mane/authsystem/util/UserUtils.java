package me.abdera7mane.authsystem.util;

import me.abdera7mane.authsystem.AuthSystem;
import me.abdera7mane.authsystem.User;
import me.abdera7mane.authsystem.control.ExceptionDialog;

import org.springframework.security.crypto.bcrypt.BCrypt;

import java.sql.Connection;
import java.sql.PreparedStatement;
import java.sql.ResultSet;
import java.sql.SQLException;
import java.util.Collections;
import java.util.Date;
import java.util.HashSet;
import java.util.List;
import java.util.Set;

@SuppressWarnings({"SqlDialectInspection", "SqlNoDataSourceInspection"})
public class UserUtils {
    private static final AuthSystem authSystem = AuthSystem.getInstance();

    public static User findUser(String name) {
        User user = null;
        
        Connection connection = authSystem.getDatabase().getConnection();
        String sql = "SELECT * from users";
        try {
            PreparedStatement preparedStatement = connection.prepareStatement(sql);

            ResultSet resultSet = preparedStatement.executeQuery();

            while (resultSet.next()) {
                String username = resultSet.getString(2);
                if (username.equalsIgnoreCase(name)) {
                    int id = resultSet.getInt(1);
                    String password = resultSet.getString(3);
                    Date registrationDate = resultSet.getDate(4);
                    user = new User(id, username, password, registrationDate);
                    break;
                }
            }
            preparedStatement.close();
        } catch (SQLException e) {
            new ExceptionDialog("Database connection error", e).showAndWait();
        }
        return user;
    }

    public static List<User> findAllUsers() {
        return null;
    }

    public static int getIncrementId() {
        Connection connection = authSystem.getDatabase().getConnection();
        String sql = "SELECT * from users";
        Set<Integer> ids = new HashSet<>();
        try {
            PreparedStatement preparedStatement = connection.prepareStatement(sql);

            ResultSet resultSet = preparedStatement.executeQuery();
            while (resultSet.next()) {
                    int id = resultSet.getInt(1);
                    ids.add(id);
            }
            preparedStatement.close();
        } catch (SQLException e) {
            new ExceptionDialog("Database connection error", e).showAndWait();
        }
        return ids.size() > 0 ? Collections.max(ids) + 1 : 0;
    }

    public static void register(String username, String password) {
        if (findUser(username) != null) {
            return;
        }

        String hashedPassword = BCrypt.hashpw(password, BCrypt.gensalt(getIncrementId() + 10));
        User user = new User(username, hashedPassword);

        Connection connection = authSystem.getDatabase().getConnection();
        String sql = "INSERT INTO users (id, username, password, registration_date)" +
                     "VALUES (?, ?, ?, ?)";
        try {
            PreparedStatement preparedStatement = connection.prepareStatement(sql);
            preparedStatement.setInt(1, user.getId());
            preparedStatement.setString(2, user.getUsername());
            preparedStatement.setString(3, user.getHashedPassword());
            preparedStatement.setDate(4, new java.sql.Date(user.getRegistrationDate().getTime()));

            preparedStatement.execute();
            preparedStatement.close();
        } catch (SQLException e) {
            new ExceptionDialog("Database connection error", e).showAndWait();
        }
    }

    public static boolean matchPassword(String password, User user) {
        return user != null && BCrypt.checkpw(password, user.getHashedPassword());
    }
}