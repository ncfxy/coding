class Solution {
    public ListNode deleteNode(ListNode head, int val) {
        ListNode preNode = null;
        ListNode node = head;
        while (node != null) {
            if (node.val == val) {
                if(preNode == null) {
                    return node.next;
                } else {
                    preNode.next = node.next;
                }
                node.next = null;
                break;
            }
            preNode = node;
            node = node.next;
        }
        return head;
    }

    public static void main(String[] args) {
        Solution so = new Solution();
        ListNode node1 = new ListNode(4);
        node1.next = new ListNode(5);
        node1.next.next = new ListNode(1);
        node1.next.next.next = new ListNode(9);
        ListNode head = so.deleteNode(node1, 5);
        ListNode.printList(head);
    }
}