import java.util.Map;
import java.util.ArrayList;
import java.util.HashMap;
import java.util.List;

class Solution {

    public static class ListNode {
        int val;
        ListNode next;

        ListNode(int x) {
            val = x;
        }
    }

    public ListNode mergeTwoLists(ListNode l1, ListNode l2) {
        ListNode head = new ListNode(0);
        ListNode tmp = head;
        while(l1 != null && l2 != null){
            if(l1.val < l2.val){
                tmp.next = l1;
                l1 = l1.next;
            }else {
                tmp.next = l2;
                l2 = l2.next;
            }
            tmp = tmp.next;
        }
        if(l1 == null){
            tmp.next = l2;
        }
        if(l2 == null){
            tmp.next = l1;
        }
        return head.next;
    }

    public static void main(String[] args) {
        Solution so = new Solution();
        ListNode node1 = new ListNode(1);
        node1.next = new ListNode(2);
        node1.next.next = new ListNode(4);

        ListNode node2 = new ListNode(1);
        node2.next = new ListNode(3);
        node2.next.next = new ListNode(4);

        ListNode result = so.mergeTwoLists(node1, node2);
        while(result != null){
            System.out.println(result.val);
            result = result.next;
        }
    }
}
