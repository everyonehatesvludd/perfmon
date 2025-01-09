import java.io.IOException;
import java.io.PrintWriter;
import java.net.Socket;
import java.util.Scanner;

/**
 * @author vregi, 1/8/2025
 */
public class TestClient {
    public static void main(String[] args) {
        if (args.length < 2) {
            System.err.println("Usage: java <Class> <host> <port>");
            System.exit(1);
        }

        String host = args[0];
        int port = Integer.parseInt(args[1]);

        try (
                Socket socket = new Socket(host, port);
                PrintWriter out = new PrintWriter(socket.getOutputStream());
                Scanner scanner = new Scanner(System.in)
                ){
            String input;
            while ((input = scanner.nextLine()) != null){
                out.println(input);
                out.flush();
            }
        } catch (IOException e) {
            System.err.println("Something went wrong");
        }
    }
}
