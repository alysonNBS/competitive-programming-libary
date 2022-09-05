// time-complexity: O(n log n)
// space-complexity: O(n)
int lengthOfLIS(vector<int>& nums) {
    const int INF = 0x3f3f3f3f;
    vector<int> dp(nums.size() + 1, INF);
    int length = 0;
    dp[0] = -INF;
    for (const auto& num : nums) {
        // change lower_bound to upper_bound if u want non-decreasing instead of it
        int i = lower_bound(dp.begin(), dp.end(), num) - dp.begin();
        dp[i] = min(dp[i], num);
        length = max(length, i);
    }
    return length;
}
