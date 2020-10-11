import java.io.IOException;
import java.io.ObjectOutputStream;
import java.net.Socket;
import java.net.UnknownHostException;
import java.util.Scanner;

public class P1 {

	public static void main(String[] args) {
		// TODO Auto-generated method stub
		
		Socket SocketClient;
		try {
			
			
			SocketClient = new Socket("localhost",2005);
			ObjectOutputStream out = new ObjectOutputStream(SocketClient.getOutputStream());
			
			Scanner sc = new Scanner(System.in);
			System.out.println("Veuillez choisir une operation :");
			System.out.println("1 : Insertion d'un etudiant");
			System.out.println("2 : Suppression d'un etudiant");
			System.out.println("3 : Afficher les info d'un etudiant");
			
			int n = sc.nextInt();
			
			switch(n) {
				case 1 :
					System.out.println("Veuillez donner les info de l'etudiant :");
					System.out.println("Matricule :");
					int mat = sc.nextInt();
					System.out.println("Nom :");
					String nom = sc.nextLine();
					System.out.println("Prenom :");
					String pnom = sc.nextLine();
					out.writeObject(1);
					out.writeObject(mat);
					out.writeObject(nom);
					out.writeObject(pnom);
					break;
				case 2 :
					System.out.println("Veuillez donner le matricule de l'etudiant a supprimer");
					System.out.print("Matricule = ");
					int mats = sc.nextInt();
					out.writeObject(2);
					out.writeObject(mats);
					break;
				case 3 :
					System.out.println("Veuillez donner le matricule de l'etudiant");
					System.out.print("Matricule = ");
					int mata = sc.nextInt();
					out.writeObject(3);
					out.writeObject(mata);
					break;
				default :
			}
			sc.close();
			
		} catch (UnknownHostException e) {
			// TODO Auto-generated catch block
			e.printStackTrace();
		} catch (IOException e) {
			// TODO Auto-generated catch block
			e.printStackTrace();
		}
		
	

	}

}
