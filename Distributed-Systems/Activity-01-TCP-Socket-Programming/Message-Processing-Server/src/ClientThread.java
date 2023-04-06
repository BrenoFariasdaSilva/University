import java.net.*;
import java.io.*;
import java.nio.file.Paths;
import java.util.*;

public class ClientThread implements Runnable {
    DataInputStream in;
    DataOutputStream out;
    Socket clientSocket;

    final static String[] preProcessedHashes = {
            "8871f959957ee6ebfd5d585aa03691e7affb6c5c4a2c31b648906ab235645358cd0efba62245f401aa38fddcf7db34169dcf655ae5631a79a5c4fcdf2f9f33df", // breno
            "7aa9c772629c40ccdd9061c0fcf46432c74b64c6ab6dcbda0959953a6f63c2c854b29df07ceaeb96c6034731b7a40db7a4645310c8814d7d8da8c1147e9f3691" // campiolo
    };

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

                // TODO: Finish logic of the authenticated users.
                if (!authenticated) {
                    System.out.println("ERROR 403 - FORBIDDEN! Please autenticate!");
                } else {
                    if (buffer.contains("CONNECT")) {
                        out.writeUTF(this.connect(buffer.substring(8), currentRelativePath));
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
                                if (i < files.size() - 1) {
                                    builder.append("\n");
                                }
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
                                if (i < folders.size() - 1) {
                                    builder.append("\n");
                                }
                            }
                            out.writeUTF(builder.toString());
                        }
                    } else {
                        out.writeUTF("Invalid input!");
                    }
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

    public boolean authenticate(final String password) {
        for (String preProcessedHash : preProcessedHashes) {
            if (preProcessedHash.equals(password)) { return true; }
        }
        return false;
    }

    public void createUserDirectory(final String user, StringBuilder currentRelativePath) {
        File userDirectory = new File("./" + user);
        if (!userDirectory.exists()){
            userDirectory.mkdirs();
        }
        currentRelativePath.delete(0, currentRelativePath.length());
        currentRelativePath.append("/");
        currentRelativePath.append(user);
    }

    public String getAbsolutePath () {
        return Paths.get("").toAbsolutePath().toString();
    }

    public String connect(final String buffer, StringBuilder currentRelativePath) {
        String[] loginCredentials = buffer.split(",");

        if (this.authenticate(loginCredentials[1])) {
            this.createUserDirectory(loginCredentials[0], currentRelativePath);
            return successMessage;
        }
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
