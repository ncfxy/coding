export default class ListNode {
    public val: any;
    public next: ListNode | null;
    constructor(val: any) {
        this.val = val;
        this.next = null;
    }
}

export function printLinkedList(pListHead: ListNode | null) {
    if(!pListHead) {
        return;
    }
    let pNode: ListNode | null = pListHead;
    let result = '';
    while(pNode != null) {
        result += pNode.val;
        pNode = pNode.next;
    }
    console.log(result);
}