import java.io.IOException;
import java.io.ObjectInputStream;
import java.net.ServerSocket;
import java.net.Socket;
import java.rmi.NotBoundException;
import java.rmi.registry.LocateRegistry;
import java.rmi.registry.Registry;

public class P2 {

	public static void main(String[] args) {
		// TODO Auto-generated method stub
		
		ServerSocket SocketServer;
		try {
			
			InterfaceRMI rmiServer;
			Registry registry;
			String Address="127.0.0.1";
			String Port="1099";
			
			registry=LocateRegistry.getRegistry("127.0.0.1",1099);
			System.out.println("RMI registry found on Port"+ Port);
			
			rmiServer = (InterfaceRMI)(registry.lookup("rmiServer"));
			
			SocketServer = new ServerSocket(2005);
			System.out.println("Waiting for connection");
			
			Socket connection = SocketServer.accept();
			System.out.println("Connection received and accepted");
			
			ObjectInputStream in = new ObjectInputStream(connection.getInputStream());
			
			int n =(int)in.readObject();
			int res;
			
			switch(n) {
			case 1 :
				int mat =(int)in.readObject();
				String nom =(String)in.readObject();
				String pnom =(String)in.readObject();
				res = rmiServer.insererEtud(mat, nom, pnom);
				break;
			case 2 :
				int mats =(int)in.readObject();
				res = rmiServer.suppEtud(mats);
				break;
			case 3 :
				int mata =(int)in.readObject();
				res = rmiServer.afficherEtud(mata);
				break;
			default :
		}
			
			SocketServer.close();
			connection.close();
			
		} catch (IOException | ClassNotFoundException | NotBoundException e) {
			// TODO Auto-generated catch block
			e.printStackTrace();
		}
		
	
		


	}

}
