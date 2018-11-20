

import java.io.BufferedReader;
import java.io.IOException;
import java.io.InputStreamReader;
import java.io.PrintWriter;
import java.net.ServerSocket;
import java.net.Socket;
import java.util.HashSet;

public class Server extends Thread{


    /**
     * The port that the server listens on.
     */
    private static int PORT = 9001;

    /**
     * The set of all names of clients in the chat room.  Maintained
     * so that we can check that new clients are not registering name
     * already in use.
     */
    private static HashSet<String> names = new HashSet<String>();

    /**
     * The set of all the print writers for all the clients.  This
     * set is kept so we can easily broadcast messages.
     */
    private static HashSet<PrintWriter> writers = new HashSet<PrintWriter>();

    public Server(int p){
        PORT = p;
    }

    public void run(){
        try {
            StartServer(PORT);
        } catch (IOException e) {
            e.printStackTrace();
        }
    }

    /**
     * The appplication main method, which just listens on a port and
     * spawns handler threads.
     */
    private void StartServer(int port) throws IOException {
        PORT = port;
        System.out.println("Server starting on port "+port);
        ServerSocket listener =new ServerSocket(port);
        try {
            while (true) {
                new Server.Handler(listener.accept()).start();
            }
        } catch (IOException e) {
            e.printStackTrace();
        } finally {
            listener.close();
        }
    }

    /**
     * A handler thread class.  Handlers are spawned from the listening
     * loop and are responsible for a dealing with a single client
     * and broadcasting its messages.
     */
    private static class Handler extends Thread {
        private String name;
        private Socket socket;
        private BufferedReader in;
        private PrintWriter out;

        /**
         * Constructs a handler thread, squirreling away the socket.
         * All the interesting work is done in the run method.
         */
        public Handler(Socket socket) {
            this.socket = socket;
        }

        /**
         * Services this thread's client by repeatedly requesting a
         * screen name until a unique one has been submitted, then
         * acknowledges the name and registers the output stream for
         * the client in a global set, then repeatedly gets inputs and
         * broadcasts them.
         */
        public void run() {
            try {

                // Create character streams for the socket.
                in = new BufferedReader(new InputStreamReader(
                        socket.getInputStream()));
                out = new PrintWriter(socket.getOutputStream(), true);
                writers.add(out);
                int phoneState = 0; //0 toggle pause/play, 1 next, 2 previouse
                while (true) {
                    String input = in.readLine();
                    if (input == null) {
                        return;
                    }
                    for (PrintWriter writer : writers) {
                        //writer.println("MESSAGE " + name + ": " + input);
                        if(input.startsWith("PI")){
                            phoneState = Integer.parseInt(input.substring(3));
                            writer.println(phoneState);
                        }
                        if(input.startsWith("PHONE")){
                            writer.println("phone message. Why was this sent again?");
                        }
                    }
                }
            } catch (IOException e) {
                System.out.println(e);
            } finally {

                try {
                    socket.close();
                } catch (IOException e) {
                }
            }
        }
    }


}
