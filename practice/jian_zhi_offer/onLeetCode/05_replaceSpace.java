class Solution {
    public String replaceSpace(String s) {
        StringBuffer buffer = new StringBuffer();
        for(int i = 0;i < s.length();i++) {
            if(s.charAt(i) == ' ') {
                buffer.append("%20");
            } else {
                buffer.append(s.charAt(i));
            }
        }
        return buffer.toString();
    }

    public String replaceSpace2(String s) {
        return s.replaceAll(" ", "%20");
    }

    public static void main(String[] args) {
        Solution so = new Solution();
        String s = so.replaceSpace2("We are happy.");
        System.out.println(s);
    }
}
