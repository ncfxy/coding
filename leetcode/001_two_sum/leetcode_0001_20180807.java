import java.util.Map;
import java.util.ArrayList;
import java.util.HashMap;
import java.util.List;

class Solution {
    public int[] twoSum(int[] nums, int target) {
        int[] ans = new int[2];
        Map<Integer, List<Integer> > myMap = new HashMap<>();
        for(int i = 0;i < nums.length;i++){
            if(!myMap.containsKey(nums[i])){
                List<Integer> list = new ArrayList<Integer>();
                list.add(i);
                myMap.put(nums[i], list);
            }else{
                myMap.get(nums[i]).add(i);
            }
        }
        for(Map.Entry<Integer, List<Integer>> entry: myMap.entrySet()){
            int temp = target - entry.getKey();
            List<Integer> otherList = myMap.get(temp);
            if(otherList != null){
                ans[0] = entry.getValue().get(0);
                if(otherList == entry.getValue()){
                    ans[1] = entry.getValue().get(1);
                }else {
                    ans[1] = otherList.get(0);
                }
                break;
            }
        }
        if(ans[0] > ans[1]){
            int tmp = ans[0];
            ans[0] = ans[1];
            ans[1] = tmp;
        }
        return ans;
    }

    public static void main(String[] args){
        Solution so = new Solution();
        int nums[] = {3,2,4};
        int result[] = so.twoSum(nums, 6);
        System.out.println(result[0]);
        System.out.println(result[1]);
    }
}
