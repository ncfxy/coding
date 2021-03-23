class Solution extends Thread{
    public ListNode mergeTwoLists(ListNode l1, ListNode l2) {
        ListNode tmpHead = new ListNode(0);
        ListNode p = tmpHead;
        while(l1 != null && l2 != null) {
            if(l1.val < l2.val) {
                p.next = l1;
                l1 = l1.next;
            } else {
                p.next = l2;
                l2 = l2.next;
            }
            p = p.next;
        }
        if(l1 != null) {
            p.next = l1;
        }
        if(l2 != null) {
            p.next = l2;
        }
        ListNode result = tmpHead.next;
        tmpHead.next = null;
        return result;
    }

    public void run() {
        ListNode node  = new ListNode(1);
        node.next = new ListNode(2);
        node.next.next = new ListNode(3);

        ListNode node2 = new ListNode(2);
        node2.next = new ListNode(4);
        node2.next.next = new ListNode(6);
        ListNode result = mergeTwoLists(null, null);
        ListNode.printList(result);
        result = mergeTwoLists(node, null);
        ListNode.printList(result);
        result = mergeTwoLists(null, node2);
        ListNode.printList(result);
        result = mergeTwoLists(node, node2);
        ListNode.printList(result);
    }

    public static void main(String[] args) {
        new Solution().start();
    }
}