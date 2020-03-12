debugger;

class ComplexListNode {
    public val: any;
    public next: ComplexListNode| null;
    public sibling: ComplexListNode | null;
    constructor(val: any){
        this.val = val;
        this.next = null;
        this.sibling = null;
    }
}

function cloneNodes(head: ComplexListNode | null) {
    let node = head;
    while(node != null) {
        let cloneNode = new ComplexListNode(node.val);
        cloneNode.next = node.next;
        cloneNode.sibling = null;
        node.next = cloneNode;
        node = cloneNode.next;
    }
}

function connectSiblingNodes(head: ComplexListNode | null) {
    let node = head;
    while(node != null) {
        let cloneNode = node.next;
        if(node.sibling != null) {
            cloneNode && (cloneNode.sibling = node.sibling.next);
        }
        cloneNode && (node = cloneNode.next);
    }
}

function reconnectNodes(head: ComplexListNode| null) {
    let node: ComplexListNode| null = head;
    let cloneHead: ComplexListNode| null = null;
    let cloneNode: ComplexListNode| null = null;

    if(node != null) {
        cloneHead = node.next;
        cloneNode = node.next;
        cloneHead && (node.next = cloneHead.next);
    }
    while(node != null) {
        cloneNode && (cloneNode.next = node.next);
        cloneNode && (cloneNode = cloneNode.next);
        cloneNode && (node.next = cloneNode.next);
        node = node.next;
    }
    return cloneHead;
}

function clone(head: ComplexListNode | null) {
    cloneNodes(head);
    connectSiblingNodes(head);
    return reconnectNodes(head);
}

let head = new ComplexListNode(1);
head.next = new ComplexListNode(2);
head.next.next = new ComplexListNode(3);
head.sibling = head.next.next;

let newHead = clone(head);

print(head);
print(newHead);
console.log(head === newHead);
console.log(head.next === newHead?.next);
console.log(head.next.next === newHead?.next?.next);

function print(head: ComplexListNode | null) {
    if(head != null) {
        let node: ComplexListNode | null = head;
        while(node != null) {
            console.log(node);
            node = node.next;
        }
    }
}
