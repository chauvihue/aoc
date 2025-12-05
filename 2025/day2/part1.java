
import java.io.BufferedReader;
import java.io.IOException;
import java.nio.charset.StandardCharsets;
import java.nio.file.FileSystems;
import java.nio.file.Files;
import java.nio.file.Path;
import java.util.ArrayList;
import java.util.Arrays;
import java.util.Comparator;
import java.util.Scanner;

/*
    N = max R < 4*10^9 
    --> Loop through possible first halves (1 --> 10^4-1)
    --> binary search to see if it's in any range
    O(sqrt(N))
*/

public class part1 {
    // this store references to Long[] arrays
    static ArrayList<Long[]> ranges = new ArrayList<>(); 
    static long res = 0;
    static private void parse() {
        Path path = FileSystems.getDefault().getPath("input.txt");
        try {
            BufferedReader in = Files.newBufferedReader(path, StandardCharsets.UTF_8);
            Scanner in_scanner = new Scanner(in.readLine());
            in.close();
            in_scanner.useDelimiter("[,-]"); 
            // the string inside use Regex "[,-]" means either , or _
            Long[] new_range = new Long[2];
            // A Long variable stores a reference to a Long object,
            // which internally contains a primitive long value.
            while (in_scanner.hasNext()) {
                new_range[0] = in_scanner.nextLong(); 
                new_range[1] = in_scanner.nextLong(); 
                ranges.add(new_range.clone()); // this passes by references
                // without .clone(), every element in ranges will be referencing the same array
            }
            in_scanner.close();
        } catch (IOException e) {
            e.printStackTrace();
        }
    }
    static private long genID(int half) {
        String s = Integer.toString(half);
        return Long.parseLong(s+s);
    }
    static private boolean inARange(long num) { 
        int l = 0, r = ranges.size()-1;
        Long[] cur_range = new Long[2];
        while (l <= r) {
            int mid = (l+r)>>1;
            cur_range = ranges.get(mid);
            if (cur_range[0] <= num) {
                if (cur_range[1] >= num) return true;
                l = mid + 1;
            } else r = mid-1;
        }
        return false;
    }
    static private void getAnswer() {
        ranges.sort(new PairComp());
        for (int i =    0; i < ranges.size(); i++)
            System.out.println(Arrays.toString(ranges.get(i)));
        inARange(446446);
        long validid;
        for (int i = 1; i <= 99999; i++) {
            validid = genID(i);
            if (!inARange(validid)) continue;
            System.err.println(validid);
            res += validid;    
        }
    }
    public static void main(String[] args) {
        parse();
        getAnswer();
        System.out.println("ANS: "+res);
    }
    
}

class PairComp implements Comparator {
    @Override
    public int compare(Object p1, Object p2) {
        Long[] a = (Long[])p1;
        Long[] b = (Long[])p2;
        if (a[0] == b[0]) {
            if (a[1] > b[1]) return -1;
            else if (a[1] < b[1]) return 1;
            else return 0;
        } else {
            if (a[0] < b[0]) return -1;
            else return 1;
        }
    }
}