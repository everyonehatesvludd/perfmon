import java.io.DataInputStream;
import java.io.IOException;
import java.net.ServerSocket;
import java.net.Socket;

/**
 * @author vregi, 1/8/2025
 */
public class MetricsServer {

    public static void main(String[] args) {
        if (args.length < 1){
            System.err.println("Usage: java <Class> <port>");
            System.exit(1);
        }

        try (
                ServerSocket server = new ServerSocket(Integer.parseInt(args[0]));
                Socket socket = server.accept();
                // some shit with input stream, still need to fix
                DataInputStream in = new DataInputStream(socket.getInputStream())
        ){
            while (true) {
                try {
                    long clientInput = in.readLong();
                    System.out.println("Processes: " + clientInput);
                } catch (IOException e) {
                    System.err.println("Something went wrong");
                    break;
                }

            }
        } catch (IOException e) {
            throw new RuntimeException(e);
        }
    }


}
