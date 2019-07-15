import java.util.*;

/**
 * Definition for singly-linked list.
 * public class ListNode {
 *     int val;
 *     ListNode next;
 *     ListNode(int x) { val = x; }
 * }
 */
class Solution {
    public ListNode addTwoNumbers(ListNode l1, ListNode l2) {
        ListNode ans = l1, father1 = l1;
        int extra = 0;
        while(l1 != null && l2 != null){
            l1.val = l1.val + l2.val + extra;
            extra = l1.val / 10;
            l1.val = l1.val % 10;
            father1 = l1;
            l1 = l1.next;
            l2 = l2.next;
        }
        if(l1 == null){
            father1.next = l2;
            l1 = l2;
        }
        while(l1 != null){
            l1.val = l1.val + extra;
            extra = l1.val / 10;
            l1.val = l1.val % 10;
            father1 = l1;
            l1 = l1.next;
        }
        if(extra > 0){
            ListNode newNode = new ListNode(extra);
            father1.next = newNode;
        }
        return ans;
    }

    public void outputListNode(ListNode list) {
        String result = "";
        while(list != null){
            result = result + list.val;
            list = list.next;
        }
        System.out.println(result);
    }

    public static void main(String[] args){
        Solution s = new Solution();
        ListNode node1 = new ListNode(8);
        node1.next = new ListNode(3);
        ListNode node2 = new ListNode(2);
        node2.next = new ListNode(6);
        s.outputListNode(node1);
        s.outputListNode(node2);
        ListNode result = s.addTwoNumbers(node1, node2);
        s.outputListNode(result);
    }

    public static class ListNode {
        int val;
        ListNode next;
        ListNode(int x) {
            val = x;
        }
    }
}