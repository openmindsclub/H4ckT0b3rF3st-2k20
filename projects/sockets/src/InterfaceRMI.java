import java.rmi.Remote;
import java.rmi.RemoteException;

public interface InterfaceRMI extends Remote {

	int insererEtud(int mat,String n,String p) throws RemoteException;
	int suppEtud(int mat) throws RemoteException;
	int afficherEtud(int mat) throws RemoteException;
}
