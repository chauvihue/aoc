import java.io.BufferedReader;
import java.io.IOException;
import java.nio.charset.StandardCharsets;
import java.nio.file.FileSystems;
import java.nio.file.Path;
import java.nio.file.Files;
import java.util.ArrayList;

public class part1 {
    static private ArrayList<String> lines = new ArrayList<>();
    static private int res = 0;
    private static void parse() {
        Path path = FileSystems.getDefault().getPath("input.txt");
        try {
            BufferedReader in = Files.newBufferedReader(path, StandardCharsets.UTF_8);
            while (in.ready()) lines.add(in.readLine());
        } catch (IOException e) {
            e.printStackTrace();
        }
    }
    private static int getMaxCharPos(String s) {
        int max_pos = 0;
        char max = s.charAt(0);
        for (int i = 1; i < s.length(); i++) if (max < s.charAt(i)) {
            max_pos = i;
            max = s.charAt(i);
        }
        return max_pos;
    }
    private static int getMaxJoltage(String s) {
        // find the max digit of the entire string s (let's say the index of it is i)
        // then find the max digit of the substring s[i+1...n] 
        // if i == n then find a max digit before it
        // piece them together and we have the max joltage
        // 
        int max1_pos = getMaxCharPos(s), max2_pos;
        if (max1_pos == s.length()-1) {// max char is at the end of string
            max2_pos = max1_pos;
            max1_pos = getMaxCharPos(s.substring(0, max2_pos));
        } else max2_pos = max1_pos+1+getMaxCharPos(s.substring(max1_pos+1));
        return (int)(s.charAt(max1_pos)-'0')*10+(s.charAt(max2_pos)-'0');
    }
    private static void process() {
        // safe to assume that each line has more than 2 digits
        for (int i = 0; i < lines.size(); i++) {
            System.out.println(getMaxJoltage(lines.get(i)));
            res += getMaxJoltage(lines.get(i));
        }
    }
    public static void main(String[] args) {
        parse();
        process();
        System.out.println("ANS: "+res);
    }
}