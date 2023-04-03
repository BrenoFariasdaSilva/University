import java.net.*;
import java.io.*;
import java.nio.file.Path;
import java.nio.file.Paths;
import java.util.ArrayList;
import java.util.Arrays;
import java.util.Objects;

public class ClientThread implements Runnable {
    DataInputStream in;
    DataOutputStream out;
    Socket clientSocket;

    public ClientThread (Socket clientSocket) {
        try {
            this.clientSocket = clientSocket;
            in = new DataInputStream(clientSocket.getInputStream());
            out = new DataOutputStream(clientSocket.getOutputStream());
        } catch (IOException ioe) {
            System.out.println("Connection:" + ioe.getMessage());
        }
    }

    @Override
    public void run() {
        try {
            String buffer = "";
            String currentPath = "";

            while (true) {
                buffer = in.readUTF();   /* aguarda o envio de dados */

                System.out.println("Cliente disse: " + buffer);

                if (buffer.equals("EXIT")) { break; }
                else if (buffer.contains("CONNECT")) { out.writeUTF(connect(buffer)); }
                else if (buffer.equals("PWD")) { out.writeUTF(this.pwd()); }
                else if (buffer.contains("CHDIR")) { out.writeUTF(this.chdir()); }
                else if (buffer.contains("GETFILES")) { out.writeUTF(this.getFiles(currentPath).toString()); }
                else if (buffer.contains("GETDIRS")) { out.writeUTF(this.getDirs(currentPath).toString()); }
            }

        } catch (EOFException eofe) {
                System.out.println("EOF: " + eofe.getMessage());
        } catch (IOException ioe) {
            System.out.println("IOE: " + ioe.getMessage());
        } finally {
            try {
                in.close();
                out.close();
                clientSocket.close();
            } catch (IOException ioe) {
                System.err.println("IOE: " + ioe);
            }
        }
        System.out.println("Thread de comunicação cliente finalizada.");
    }

    public String connect(final String buffer) {
        String[] login = buffer.split(",");
        System.out.println("Login Credentials: " + Arrays.toString(login));
        if (this.authenticate(login[1], login[2])) { return "SUCCESS"; }
        return "ERROR";
    }

    public boolean authenticate(final String username, final String password) {
        System.out.println("ToDo");
        return true;
    }

    public String pwd() throws IOException {
        Path currentRelativePath = Paths.get("");
        String currentPath = currentRelativePath.toAbsolutePath().toString();
        this.out.writeUTF(currentPath);
        return currentPath;
    }

    public String chdir() {
        System.out.println("ToDo");
        return "ToDo";
    }

    public ArrayList<String> getFiles(String currentPath) throws IOException {
        File folder = new File(currentPath);
        ArrayList<String> fileList = new ArrayList<>();

        this.out.writeUTF(String.valueOf(Objects.requireNonNull(folder.listFiles()).length));
        if (folder.listFiles() == null) { return fileList; } // Trying to avoid null pointer exception

        for (File f : Objects.requireNonNull(folder.listFiles())) { fileList.add(f.getName()); }

        return fileList;
    }

    public ArrayList<String> getDirs(String currentPath) throws IOException {
        // public String[] list() and public boolean isDirectory()
        File folder = new File(currentPath);
        this.out.writeUTF(String.valueOf(Objects.requireNonNull(folder.listFiles()).length));

        ArrayList<String> fileList = new ArrayList<>();
        if (folder.listFiles() == null) { return fileList; } // Trying to avoid null pointer exception

        for (File f : Objects.requireNonNull(folder.listFiles())) { if (f.isDirectory()) { fileList.add(f.getName()); } }

        return fileList;
    }
}
