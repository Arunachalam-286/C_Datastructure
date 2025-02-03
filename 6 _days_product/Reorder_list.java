import java.util.LinkedList;
import java.util.Scanner;
import java.util.Stack;
class Node {
   int data;
   Node next;
   Node(int data) {
       this.data = data;
       this.next = null;
   }
}
public class Reorder_list{
   public static void reorderList(Node head) {
       if (head == null || head.next == null) {
           return;
       }
       Node slow = head, fast = head;
       while (fast != null && fast.next != null) {
           slow = slow.next;
           fast = fast.next.next;
       }
       Node prev = null, curr = slow, next;
       while (curr != null) {
           next = curr.next;
           curr.next = prev;
           prev = curr;
           curr = next;
       }
       Node secondHalf = prev; 
       Node firstHalf = head;
       while (secondHalf.next != null) {
           Node temp1 = firstHalf.next;
           Node temp2 = secondHalf.next;
           firstHalf.next = secondHalf;
           secondHalf.next = temp1;
           firstHalf = temp1;
           secondHalf = temp2;
       }
   }
   public static void displayList(Node head) {
       Node temp = head;
       while (temp != null) {
           System.out.print(temp.data + " -> ");
           temp = temp.next;
       }
       System.out.println("NULL");
   }
   public static void main(String[] args) {
       Scanner scanner = new Scanner(System.in);
       System.out.print("Enter the number of nodes in the linked list: ");
       int n = scanner.nextInt();
       Node head = null, tail = null;
           for (int i = 0; i < n; i++) {
       	System.out.print("Enter the element of "+(i+1)+" :");
           int value = scanner.nextInt();
           Node newNode = new Node(value);
           if (head == null) {
               head = newNode;
               tail = newNode;
           } else {
               tail.next = newNode;
               tail = newNode;
           }
       }
       System.out.println("Original List:");
       displayList(head);
       reorderList(head);
       System.out.println("Reordered List:");
       displayList(head);
       scanner.close();
   }
}
