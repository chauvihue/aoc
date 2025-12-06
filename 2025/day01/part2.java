import java.io.BufferedReader;
import java.io.IOException;
import java.nio.charset.StandardCharsets;
import java.nio.file.FileSystems;
import java.nio.file.Files;
import java.nio.file.Path;

public class part2 {
    static int num = 50;
    static int res = 0;
    static void parseLine(String s) {
        int delta;
        int lastnum = num;
        if (s.charAt(0) == 'L') {
            delta = Integer.parseInt(s.substring(1));
            res += delta/100;
            num -= delta%100;
            num = (num+100)%100;
            if (num > lastnum && lastnum != 0) // we only reduced the number --> we've croseed 0 once
                res++;
            else if (num == 0) res++;
        } else if (s.charAt(0) == 'R') {
            delta = Integer.parseInt(s.substring(1));
            res += delta/100;
            num += delta%100;
            num = num%100;
            if (num < lastnum && lastnum != 0) // we only increased the number --> we've croseed 0 once
                res++;
            else if (num == 0) res++;
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
            }
            System.out.println("ANS:\t"+res);
            in.close();
        } catch (IOException e) {
            e.printStackTrace();
        }
    }
}