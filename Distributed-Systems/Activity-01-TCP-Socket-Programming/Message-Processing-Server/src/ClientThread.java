import java.math.BigInteger;
import java.net.*;
import java.io.*;
import java.nio.file.Paths;
import java.security.MessageDigest;
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
            StringBuilder currentRelativePath = new StringBuilder("/"); // Começa com / por ser um servidor linux
            boolean authenticated = false;

            while (!buffer.equals("EXIT")) {
                buffer = in.readUTF();   /* aguarda o envio de dados */

                System.out.printf("Cliente disse: '%s'\n", buffer);

                if (buffer.contains("CONNECT")) { // CONNECT user,password
                    //TODO: Enviar apenas o username e o password. Fix
                    String loginCredentials = buffer.replace("CONNECT ", "");
                    out.writeUTF(this.connect(buffer.toString()));
                } else if (buffer.equals("PWD")) {
                    out.writeUTF(this.pwd(currentRelativePath.toString()));
                } else if (buffer.contains("CHDIR")) {
                    String[] pathValue = buffer.split(" ", 2);
                    if (this.chdir(currentRelativePath, pathValue[1])) {
                        out.writeUTF(successMessage);
                    } else {
                        out.writeUTF(errorMessage);
                    }
                } else if (buffer.equals("GETFILES")) {
                    List<String> files = this.getFiles(currentRelativePath.toString());
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
                    List<String> folders = this.getDirs(currentRelativePath.toString());
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

    public boolean authenticate(final String username, final String password) {
        if (this.getSHA512(username).equals(password)) { return true; }
        return false;
    }

    public String getSHA512(String password) {
        String encryptedPassword = "";
        try {
            MessageDigest digest = MessageDigest.getInstance("SHA-512");
            digest.reset();
            digest.update(password.getBytes("utf8"));
            encryptedPassword = String.format("%0128x", new BigInteger(1, digest.digest()));
        } catch (Exception e) {
            e.printStackTrace();
        }
        return encryptedPassword;
    }

    public void createUserDirectory(final String user) {
        File userDirectory = new File("./users/" + user);
        if (!userDirectory.exists()){
            userDirectory.mkdirs();
        }
    }

    public String getAbsolutePath () {
        return Paths.get("").toAbsolutePath().toString();
    }

    public String connect(final String buffer) {
        String[] loginCredentials = buffer.split(",");
        System.out.println("USERNAME: " + loginCredentials[0]);
        System.out.println("PASSWORD: " + loginCredentials[1]);

        if (this.authenticate(loginCredentials[0], loginCredentials[1])) { return successMessage; }
        return errorMessage;
    }

    public String pwd(String currentRelativePath) throws IOException {
        return currentRelativePath;
    }

    public boolean chdir(StringBuilder currentRelativePath, String folder) {
        File cdFolder = new File(this.getAbsolutePath());

        if (cdFolder.isDirectory()) {
            currentRelativePath.append(folder);
            return true;
        }

        return false;
    }

    public List<String> getFiles(final String currentRelativePath) throws IOException {
        File[] folder = new File(this.getAbsolutePath()).listFiles();
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
        File[] folder = new File(this.getAbsolutePath()).listFiles();
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
