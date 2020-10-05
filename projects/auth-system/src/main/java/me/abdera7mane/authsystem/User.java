package me.abdera7mane.authsystem;

import me.abdera7mane.authsystem.util.UserUtils;

import java.util.Date;

public class User {
    private final int id;
    private final String username;
    private final String hashedPassword;
    private final Date registrationDate;

    public User(String username, String hashedPassword) {
        this(UserUtils.getIncrementId(), username, hashedPassword, new Date());
    }

    public User(int id, String username, String hashedPassword, Date registrationDate) {
        this.id = id;
        this.username = username;
        this.hashedPassword = hashedPassword;
        this.registrationDate = registrationDate;
    }

    public int getId() {
        return this.id;
    }

    public String getUsername() {
        return this.username;
    }

    public String getHashedPassword() {
        return this.hashedPassword;
    }

    public Date getRegistrationDate() {
        return registrationDate;
    }

    @Override
    public boolean equals(Object o) {
        if (this == o) return true;
        if (o == null || getClass() != o.getClass()) return false;

        User user = (User) o;

        if (id != user.id) return false;
        return username.equals(user.username);
    }

    @Override
    public int hashCode() {
        int result = id;
        result = 31 * result + username.hashCode();
        return result;
    }

    @SuppressWarnings("StringBufferReplaceableByString")
    @Override
    public String toString() {
        return  new StringBuilder("User{")
        .append("id=").append(id)
        .append(", username='").append(username).append('\'')
        .append(", registrationDate=").append(registrationDate)
        .append('}')
        .toString();
    }
}
