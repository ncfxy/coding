import java.util.List;
import java.util.ArrayList;

class Solution {

    public List<String> generateParenthesis(int n) {
        List<String> result = new ArrayList<>();
        dfs(result, "", 0, 0, n);
        return result;
    }

    private void dfs(List<String> result, String tmp, int left, int right, int n){
        if(left < n){
            dfs(result, tmp + "(", left + 1, right, n);
        }
        if(left > right){
            dfs(result, tmp + ")", left, right + 1, n);
        }
        if(left == n && right == n){
            result.add(tmp);
        }
        return;
    }


    public static void main(String[] args) {
        Solution so = new Solution();
        List<String> result = so.generateParenthesis(3);
        for(int i = 0;i < result.size();i++){
            System.out.println(result.get(i));
        }
    }
}
