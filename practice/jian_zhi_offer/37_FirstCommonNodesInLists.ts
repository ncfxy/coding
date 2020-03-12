import ListNode from "./ListNode";

function findFirstCommonNode(head1: ListNode | null, head2: ListNode | null) {
    let length1 = getListLength(head1);
    let length2 = getListLength(head2);
    if(length1 === 0 || length2 === 0) {
        return null;
    }
    let diffLength = length1 > length2 ? length1 - length2 : length2 - length1;
    let longNode: ListNode | null = length1 > length2 ? head1 : head2;
    let shortNode: ListNode | null = length1 > length2 ? head2: head1;
    for(let i = 0;i < diffLength;i++) {
        longNode && (longNode = longNode.next);
    }
    let commonNode: ListNode | null  = null;
    while(longNode != null && shortNode != null) {
        if(longNode === shortNode) {
            commonNode = longNode;
            break;
        }
        longNode = longNode.next;
        shortNode = shortNode.next;
    }
    return commonNode;
}

function getListLength(head: ListNode | null): number {
    if(head == null) {
        return 0;
    }
    let node: ListNode | null = head;
    let length = 0;
    while(node != null) {
        length++;
        node = node.next;
    }
    return length;
}

let head1 = new ListNode(1);
head1.next = new ListNode(2);
head1.next.next = new ListNode(3);
head1.next.next.next = new ListNode(4);
head1.next.next.next.next = new ListNode(5);
let head2 = new ListNode(2);

console.log(findFirstCommonNode(head1, head1));
console.log(findFirstCommonNode(head1, head1.next.next.next.next));
console.log(findFirstCommonNode(head1, head2));
head2.next = head1.next.next;
console.log(findFirstCommonNode(head1, head2));
console.log(findFirstCommonNode(null, null));