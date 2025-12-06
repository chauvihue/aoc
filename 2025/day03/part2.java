import java.io.BufferedReader;
import java.io.IOException;
import java.nio.charset.StandardCharsets;
import java.nio.file.FileSystems;
import java.nio.file.Path;
import java.nio.file.Files;
import java.util.ArrayList;
import java.util.Arrays;

public class part2 {
    static private ArrayList<String> lines = new ArrayList<>();
    static private long res = 0;
    static private String[][] dp;
    private static void parse(String filename) {
        Path path = FileSystems.getDefault().getPath(filename);
        try {
            BufferedReader in = Files.newBufferedReader(path, StandardCharsets.UTF_8);
            while (in.ready()) lines.add(in.readLine());
        } catch (IOException e) {
            e.printStackTrace();
        }
    }
    private static String maxString(String s1, String s2) {
        if (s1.length() < s2.length()) return s2;
        if (s1.length() > s2.length()) return s1;
        for (int i = 0; i < s1.length(); i++) // len(s1) == len(s2)
            if (s1.charAt(i) != s2.charAt(i)) { // s1 != s2
                if (s1.charAt(i) > s2.charAt(i)) return s1;
                else return s2;
            }
        return s1; // s1 == s2
    }
    private static long getMaxJoltage(String s) {
        /*
            dp[i][j]: max joltage with exactly j digits 
            considering range 1..i (string is 1-indexed)

            basecase: dp[i][0] = 0
            
            dp[i][j] = max(dp[i-1][j], dp[i-1][j-1]+s[i])
        */
        int n = s.length();
        s = ' '+s;
        dp = new String[n+3][20];
        for (int i = 0; i <= n; i++) 
            for (int j = 0; j <= 12; j++) dp[i][j] = "";
        for (int j = 1; j <= 12; j++) {
            for (int i = 1; i <= n; i++) {
                dp[i][j] = maxString(dp[i-1][j], dp[i-1][j-1]+s.charAt(i));
            }
        }
        return Long.parseLong(dp[n][12]);
    }
    private static void process() {
        // safe to assume that each line has more than 2 digits
        for (int i = 0; i < lines.size(); i++) {
            // System.out.println(getMaxJoltage(lines.get(i)));
            res += getMaxJoltage(lines.get(i));
        }
    }
    public static void main(String[] args) {
        parse("input.txt");
        process();
        System.out.println("ANS: "+res);
    }
}