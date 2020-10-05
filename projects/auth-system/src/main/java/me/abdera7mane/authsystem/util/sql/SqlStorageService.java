package me.abdera7mane.authsystem.util.sql;

import java.sql.Connection;
import java.sql.DatabaseMetaData;
import java.sql.DriverManager;
import java.sql.ResultSet;
import java.sql.SQLException;
import java.sql.Statement;

@SuppressWarnings("SqlNoDataSourceInspection")
public class SqlStorageService {
    private static final String H2_DRIVER = "org.h2.Driver";
    private static final String URL = "jdbc:h2:file:./data";
    private static final String USER = "sa";
    private static final String PASSWORD = "";
    private Connection connection;

    public void setup() throws SQLException, ClassNotFoundException {
        if (this.getConnection() != null) {
            throw new IllegalStateException("the SqlStorageService is already setted up on this instance");
        }

        Class.forName(H2_DRIVER);
        this.connection = DriverManager.getConnection(URL, USER, PASSWORD);
        this.preConfigure();

    }

    public void stop() throws SQLException {
        this.getConnection().close();
        this.connection = null;
    }

    private void preConfigure() throws SQLException {
        DatabaseMetaData dbmeta = this.getConnection().getMetaData();

        String tableName = "users";

        ResultSet tables = dbmeta.getTables(null, null, tableName.toUpperCase(), null);
        while (tables.next()) {
            String name = tables.getString("TABLE_NAME");
            if (name != null && name.equalsIgnoreCase(tableName)) {
                return;
            }
        }

        Statement statement = this.getConnection().createStatement();
        String sql =  "CREATE TABLE " + tableName
                    + " (id INTEGER not NULL AUTO_INCREMENT,"
                    + " username VARCHAR(60),"
                    + " password VARCHAR(255),"
                    + " registration_date DATE,"
                    + " PRIMARY KEY ( id ))";
        statement.executeUpdate(sql);
        statement.close();
    }

    public Connection getConnection() {
        return this.connection;
    }
}