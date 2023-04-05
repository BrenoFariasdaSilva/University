import java.net.*;
import java.io.*;
import java.nio.file.Path;
import java.nio.file.Paths;
import java.util.*;

public class ClientThread implements Runnable {
    DataInputStream in;
    DataOutputStream out;
    Socket clientSocket;

    final static String successMessage = "SUCCESS";
    final static String errorMessage = "ERROR";

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
            String currentPath = "/"; // Começa com / por ser um servidor linux

            while (!buffer.equals("EXIT")) {
                buffer = in.readUTF();   /* aguarda o envio de dados */

                System.out.printf("Cliente disse: '%s'\n", buffer);

                if (buffer.contains("CONNECT")) { // CONNECT user, password
                    System.out.println("Implement");
                    String[] login = buffer.split(" ", 3);
                    // String encryptedPassword = this.getSHA512(login[2]);
                    out.writeUTF(connect(login[2]));
                } else if (buffer.equals("PWD")) {
                    currentPath = this.pwd();
                    out.writeUTF(currentPath);
                } else if (buffer.contains("CHDIR")) {
                    String[] pathValue = buffer.split(" ", 2);
                    out.writeUTF(this.chdir(pathValue[1]));
                } else if (buffer.equals("GETFILES")) {
                    List<String> files = this.getFiles(currentPath);
                    final int numberOfFiles = files.size();
                    System.out.println("Number of files " + numberOfFiles);
                    var builder = new StringBuilder();
                    for (int i = 0; i < numberOfFiles; i++) { builder.append(files.get(i)); }
                    out.writeUTF(builder.toString());
                } else if (buffer.equals("GETDIRS")) {
                    out.writeUTF(this.getDirs(currentPath).toString());
                } else {
                    System.out.println("Invalid input!");
                }
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
        if (this.authenticate(login[1], login[2])) { return successMessage; }
        return errorMessage;
    }

    public boolean authenticate(final String username, final String password) {
        System.out.println("ToDo");
        return true;
    }

    public String pwd() throws IOException {
        Path currentRelativePath = Paths.get("");
        String currentAbsolutePath = currentRelativePath.toAbsolutePath().toString();
        this.out.writeUTF(currentAbsolutePath);
        return currentAbsolutePath;
    }

    public String chdir(String newPath) {
        File folder = new File(newPath);

        if (folder.isDirectory()) { return successMessage; }

        return errorMessage;
    }

    public List<String> getFiles(String currentPath) throws IOException {
        File folder = new File(currentPath);
        ArrayList<String> fileList = new ArrayList<>();

        File[] files = folder.listFiles();
        if (files == null) { return Collections.emptyList(); }
        this.out.writeUTF(String.valueOf(files.length));

        for (File f : Objects.requireNonNull(files)) { fileList.add(f.getName()); }

        final int numberOfFiles = fileList.size();

        System.out.println("Number of files in GETFILES function: " + numberOfFiles);
        System.out.println(fileList.toString());

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
