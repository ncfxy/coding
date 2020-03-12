import ListNode, { printLinkedList } from './ListNode';

debugger;

function mergeList(head1: ListNode | null, head2: ListNode | null): ListNode|null {
    if(head1 == null) {
        return head2;
    }
    if(head2 == null) {
        return head1;
    }
    let mergeListHead = null;
    if(head1.val < head2.val) {
        mergeListHead = head1;
        mergeListHead.next = mergeList(head1.next, head2);
    } else {
        mergeListHead = head2;
        mergeListHead.next = mergeList(head1, head2.next);
    }
    return mergeListHead;
}

let head1 = new ListNode(1);
head1.next = new ListNode(5);
head1.next.next = new ListNode(9);
let head2 = new ListNode(2);
head2.next = new ListNode(4);
head2.next.next = new ListNode(10);

printLinkedList(head1);
printLinkedList(head2);
let newHead = mergeList(head1, head2);
printLinkedList(newHead);
let newHead2 = mergeList(newHead, null);
printLinkedList(newHead2);
printLinkedList(head1);
printLinkedList(head2);
