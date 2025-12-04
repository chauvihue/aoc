import java.io.BufferedReader;
import java.io.IOException;
import java.nio.charset.StandardCharsets;
import java.nio.file.FileSystems;
import java.nio.file.Files;
import java.nio.file.Path;

public class part1 {
    static int num = 50;
    static int res = 0;
    static void parseLine(String s) {
        int delta;
        if (s.charAt(0) == 'L') {
            delta = Integer.parseInt(s.substring(1))%100;
            num -= delta;
            num = (num+100)%100;
        } else if (s.charAt(0) == 'R') {
            delta = Integer.parseInt(s.substring(1))%100;
            num += delta;
            num = num%100;
        }
    }
    public static void main(String[] args) {
        // Scanner in = new Scanner(System.in);
        try {
            Path path = FileSystems.getDefault().getPath("input.txt");
            BufferedReader in = Files.newBufferedReader(path, StandardCharsets.UTF_8);
            String line;
            while ((line = in.readLine()) != null) {
                parseLine(line);
                if (num == 0) res++;
            }
            System.out.println("ANS:\t"+res);
            in.close();
        } catch (IOException e) {
            e.printStackTrace();
        }
    }
}