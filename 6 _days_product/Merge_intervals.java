import java.util.*;


class Interval {
    int start;
    int end;


    Interval(int start, int end) {
        this.start = start;
        this.end = end;
    }
}


public class Merge_intervals {

    public static List<Interval> mergeIntervals(List<Interval> intervals) {
        List<Interval> result = new ArrayList<>();


        if (intervals.isEmpty()) {
            return result;
        }


        for (int i = 0; i < intervals.size() - 1; i++) {
            for (int j = i + 1; j < intervals.size(); j++) {
                if (intervals.get(i).start > intervals.get(j).start) {
                    Interval temp = intervals.get(i);
                    intervals.set(i, intervals.get(j));
                    intervals.set(j, temp);
                }
            }
        }


        Interval current = intervals.get(0); 
        for (int i = 1; i < intervals.size(); i++) {
            Interval next = intervals.get(i);

            if (current.end >= next.start) {
                current.end = Math.max(current.end, next.end);
            } else {
                result.add(current);
                current = next;
            }
        }


        result.add(current);


        return result;
    }


    public static void main(String[] args) {
        Scanner scanner = new Scanner(System.in);


        System.out.print("Enter the number of intervals: ");
        int n = scanner.nextInt();


        List<Interval> intervals = new ArrayList<>();
        System.out.println("Enter the intervals (start and end):");
        for (int i = 0; i < n; i++) {
            int start = scanner.nextInt();
            int end = scanner.nextInt();
            intervals.add(new Interval(start, end));
        }


        List<Interval> mergedIntervals = mergeIntervals(intervals);


        System.out.println("Merged intervals:");
        for (Interval interval : mergedIntervals) {
            System.out.println("[" + interval.start + ", " + interval.end + "]");
        }


        scanner.close();
    }
}
