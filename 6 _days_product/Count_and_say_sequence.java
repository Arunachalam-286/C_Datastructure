import java.util.Scanner;

public class Count_and_say_sequence {
    public static void main(String[] args) {
        Scanner scanner = new Scanner(System.in);
        System.out.print("Enter the value of n: ");
        int n = scanner.nextInt(); 

        if (n <= 0) {
            System.out.println("Please enter a positive integer greater than 0.");
        } else {
            String result = "1"; 

            for (int i = 1; i < n; i++) {
                StringBuilder nextResult = new StringBuilder();
                int count = 1;

                for (int j = 1; j < result.length(); j++) {
                    if (result.charAt(j) == result.charAt(j - 1)) {
                        count++; 
                    } else {
                        nextResult.append(count).append(result.charAt(j - 1)); 
                        count = 1; 
                    }
                }
                nextResult.append(count).append(result.charAt(result.length() - 1)); 
                result = nextResult.toString();
            }
            System.out.println("The " + n + "th term in the Count and Say sequence is: " + result);
        }
        scanner.close();
    }
}
