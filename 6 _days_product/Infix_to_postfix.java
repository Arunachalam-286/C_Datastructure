import java.util.Stack;
import java.util.Scanner;


class InfixToPost {


    public String infixToPost(String infixExp) {
        String postfix = "";
        Stack<Character> stack = new Stack<>();


        stack.push('(');
        infixExp = infixExp.concat(String.valueOf(')'));


        for (int i = 0; i < infixExp.length(); i++) {
            char character = infixExp.charAt(i);


            if (Character.isAlphabetic(character) || Character.isDigit(character)) {
                postfix = postfix.concat(String.valueOf(character));
            }
            else if (character == '(') {
                stack.push(character);
            }
            else if (isOperator(character)) {
                while (!stack.empty()) {
                    if (precedence(stack.peek()) >= precedence(character)) {
                        postfix = postfix.concat(String.valueOf(stack.pop()));
                    } else {
                        stack.push(character);
                        break;
                    }
                }
            }
            else if (character == ')') {
                while (!stack.empty()) {
                    if (stack.peek() != '(') {
                        postfix = postfix.concat(String.valueOf(stack.pop()));
                    } else {
                        stack.pop();
                        break;
                    }
                }
            }
        }
        return postfix;
    }


    private boolean isOperator(char character) {
        return character == '^' || character == '/' || character == '*' || character == '+' || character == '-';
    }

    private int precedence(char operator) {
        switch (operator) {
            case '^': return 3;
            case '/':
            case '*': return 2;
            case '+':
            case '-': return 1;
            default: return 0;
        }
    }
}


public class Infix_to_postfix{


    public static void main(String args[]) {
        Scanner scanner = new Scanner(System.in);

        System.out.print("Enter the infix expression: ");
        String infix = scanner.nextLine();


        InfixToPost converter = new InfixToPost();
        String postfix = converter.infixToPost(infix);

        System.out.println("Equivalent Postfix expression is: " + postfix);


        scanner.close();
    }
}
