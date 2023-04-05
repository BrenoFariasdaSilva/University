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
            String currentRelativePath = "/"; // Começa com / por ser um servidor linux

            while (!buffer.equals("EXIT")) {
                buffer = in.readUTF();   /* aguarda o envio de dados */

                System.out.printf("Cliente disse: '%s'\n", buffer);

                if (buffer.contains("CONNECT")) { // CONNECT user, password
                    System.out.println("Implement");
                    String[] login = buffer.split(" ", 3);
                    // String encryptedPassword = this.getSHA512(login[2]);
                    out.writeUTF(connect(login[2]));
                } else if (buffer.equals("PWD")) {
                    out.writeUTF(this.pwd(currentRelativePath));
                } else if (buffer.contains("CHDIR")) {
                    String[] pathValue = buffer.split(" ", 2);
                    out.writeUTF(this.chdir(pathValue[1]));
                } else if (buffer.equals("GETFILES")) {
                    List<String> files = this.getFiles(currentRelativePath);
                    out.writeUTF(String.valueOf(files.size()));
                    if (files.size() > 0) {
                        var builder = new StringBuilder();
                        for (int i = 0; i < files.size(); i++) {
                            builder.append(files.get(i));
                            if (i < files.size() - 1) { builder.append("\n"); }
                        }
                        out.writeUTF(builder.toString());
                    }

                } else if (buffer.equals("GETDIRS")) {
                    List<String> folders = this.getDirs(currentRelativePath);
                    out.writeUTF(String.valueOf(folders.size()));
                    if (folders.size() > 0) {
                        var builder = new StringBuilder();
                        for (int i = 0; i < folders.size(); i++) {
                            builder.append(folders.get(i));
                            if (i < folders.size() - 1) { builder.append("\n"); }
                        }
                        out.writeUTF(builder.toString());
                    }
                } else {
                    out.writeUTF("Invalid input!");
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

    public String pwd(String currentRelativePath) throws IOException {
        return currentRelativePath;
    }

    public String chdir(String newPath) {
        File folder = new File(newPath);

        if (folder.isDirectory()) { return successMessage; }

        return errorMessage;
    }

    public List<String> getFiles(final String currentRelativePath) throws IOException {
        String absolutePath = Paths.get("").toAbsolutePath().toString();
        absolutePath.concat(currentRelativePath);

        File[] folder = new File(absolutePath).listFiles();
        ArrayList<String> fileList = new ArrayList<>();

        if (folder == null) { return Collections.emptyList(); }

        for (File f : Objects.requireNonNull(folder)) {
            if (!f.isDirectory()) {
                fileList.add(f.getName());
            }
        }

        return fileList;
    }

    public List<String> getDirs(final String currentRelativePath) throws IOException {
        String absolutePath = Paths.get("").toAbsolutePath().toString();
        absolutePath.concat(currentRelativePath);

        File[] folder = new File(absolutePath).listFiles();
        ArrayList<String> fileList = new ArrayList<>();

        if (folder == null) { return Collections.emptyList(); }

        for (File f : Objects.requireNonNull(folder)) {
            if (f.isDirectory()) {
                fileList.add(f.getName());
            }
        }

        return fileList;
    }
}
