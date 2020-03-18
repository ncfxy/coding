class Solution {
    public int minArray(int[] numbers) {
        int left = 0, right = numbers.length - 1;
        if(numbers[left] < numbers[right]) {
            // not rotate
            return numbers[0];
        }
        while(numbers[left] > numbers[right]) {
            int mid = (left + right) >> 1;
            if(numbers[mid] > numbers[right]) {
                left = mid + 1;
            } else {
                right = mid;
            }
        }
        int min = numbers[left];
        for(int i = left;i <= right;i++) {
            min = Math.min(numbers[i], min);
        }
        return min;
    }

    public static void main(String[] args) {
        Solution so = new Solution();
        int[] array1 = {3,4,5,1,2};
        int[] array2 = {2,2,2,0,1};
        int[] array3 = {3,1,3};
        System.out.println(so.minArray(array3));
    }
}