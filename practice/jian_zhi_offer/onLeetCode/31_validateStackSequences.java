class Solution extends Thread{

    public boolean validateStackSequences(int[] pushed, int[] popped) {
        if(pushed == null || popped == null || pushed.length != popped.length){
            return false;
        }
        if(pushed.length == 0) {
            return true;
        }
        Stack<Integer> stack = new Stack<>();
        int pushIndex = 0;
        int popIndex = 0;
        while(popIndex < popped.length) {
            if(stack.isEmpty() || stack.peek() != popped[popIndex]) {
                if(pushIndex >= pushed.length) {
                    break;
                }
                stack.push(pushed[pushIndex++]);
            }
            if(stack.peek() == popped[popIndex]) {
                stack.pop();
                popIndex++;
            }
        }
        return popIndex >= popped.length;
    }

    public void run() {
        int[] pushed = {1,2,3,4,5};
        int[] poped = {4,3,5,1,2};
        System.out.println(this.validateStackSequences(pushed, poped));
        System.out.println(this.validateStackSequences(null, null));
    }

    public static void main(String[] args) {
        new Solution().start();
    }
}