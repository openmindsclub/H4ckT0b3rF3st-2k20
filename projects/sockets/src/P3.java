
import java.io.IOException;
import java.net.ServerSocket;
import java.net.Socket;
import java.rmi.RemoteException;
import java.rmi.registry.LocateRegistry;
import java.rmi.registry.Registry;
import java.sql.Connection;
import java.sql.DriverManager;
import java.sql.ResultSet;
import java.sql.SQLException;
import java.sql.Statement;

public class P3 extends java.rmi.server.UnicastRemoteObject implements InterfaceRMI{

	String Address;
	static int Port=1099;
	
	static Connection conn = null;
	static String url = "jdbc:mysql://localhost:3306/";
	static String dbName = "master2";
	static String driver = "com.mysql.jdbc.Driver";
	static String userName = "root";
	static String password = "";
	
	
	protected P3() throws RemoteException {
		super();
		// TODO Auto-generated constructor stub
	}

	public static void main(String[] args) {
		// TODO Auto-generated method stub
		P3 s = null;
		try {
			/*s = new P3();
			System.out.println("Hello Server is ready");
			Registry registry = LocateRegistry.createRegistry(Port);
			System.out.println("Created RMI registry on port "+Port);
			registry.rebind("rmiServer", s);*/
			
			Class.forName(driver).newInstance();
			conn = DriverManager.getConnection(url+dbName,userName,password);
			System.out.println("Connected to the database");
			try {
				s.insererEtud(4444, "ghebache", "bouchra");
			} catch (RemoteException e) {
				// TODO Auto-generated catch block
				e.printStackTrace();
			}
			
			
		} catch (InstantiationException | IllegalAccessException | ClassNotFoundException | SQLException e) {
			// TODO Auto-generated catch block
			e.printStackTrace();
		}
		


	}

	@Override
	public int insererEtud(int mat, String n, String p) throws RemoteException {
		// TODO Auto-generated method stub
		String q = "insert into etudiant values ("+mat+","+n+","+p+");";
		
		try {
			
			Statement stmt = (Statement) conn.createStatement();
			ResultSet rs = stmt.executeQuery(q);
			System.out.println("etudiant insere");
			return 0;
			
		} catch (SQLException e) {
			// TODO Auto-generated catch block
			e.printStackTrace();
			return 1;
		}
		
	}

	@Override
	public int suppEtud(int mat) throws RemoteException {
		// TODO Auto-generated method stub
		String q = "delete from etudiant where mat ="+mat;
		try {
			
			Statement stmt = (Statement) conn.createStatement();
			ResultSet rs = stmt.executeQuery(q);
			System.out.println("etudiant supprime");
			return 0;
			
		} catch (SQLException e) {
			// TODO Auto-generated catch block
			e.printStackTrace();
			return 1;
		}
	}

	@Override
	public int afficherEtud(int mat) throws RemoteException {
		// TODO Auto-generated method stub
		String q = "select * from etudiant where mat ="+mat;
try {
			
			Statement stmt = (Statement) conn.createStatement();
			ResultSet rs = stmt.executeQuery(q);
			while(rs.next()) {
				System.out.println("Mat = "+rs.getString(1)+"Nom = "+rs.getString(2)+"Prenom = "+rs.getString(3));
			}
			return 0;
			
		} catch (SQLException e) {
			// TODO Auto-generated catch block
			e.printStackTrace();
			return 1;
		}
	}

}
