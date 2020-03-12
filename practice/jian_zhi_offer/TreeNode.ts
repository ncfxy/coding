export class BinaryTreeNode {
    public val: any;
    public left: BinaryTreeNode| null;
    public right: BinaryTreeNode | null;
    constructor(val: any) {
        this.val = val;
        this.left = null;
        this.right = null;
    }
}

export function preTraverse(root: BinaryTreeNode| null) {
    if(root == null) {
        return;
    }
    console.log(root.val);
    preTraverse(root.left);
    preTraverse(root.right);
}

export function midTraverse(root: BinaryTreeNode | null) {
    if(root == null) {
        return;
    }
    midTraverse(root.left);
    console.log(root.val);
    midTraverse(root.right);
}

export function postTraverse(root: BinaryTreeNode | null) {
    if(root == null) {
        return;
    }
    postTraverse(root.left);
    postTraverse(root.right);
    console.log(root.val);
}
